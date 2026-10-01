#include <types.h>
#include <kern/errno.h>
#include <kern/fcntl.h>
#include <limits.h>
#include <lib.h>
#include <copyinout.h>
#include <synch.h>
#include <current.h>
#include <proc.h>
#include <vfs.h>
#include <uio.h>
#include <vnode.h>
#include <kern/seek.h>
#include <kern/stat.h>
#include <openfile.h>
#include <syscall.h>

/*
 * Table of the open files currently present in the system.
 * A single openfile may be referenced by more than one descriptor.
 */
static struct openfile system_file_table[SYSTEM_OPEN_MAX];

/*
 * Protects allocation and reference count updates in the system table.
 */
static struct lock *system_file_table_lock;

/*
 * Initialize the global open file table.
 */
void openfile_bootstrap(void)
{
    system_file_table_lock =
        lock_create("system open file table");

    if (system_file_table_lock == NULL)
    {
        panic("openfile_bootstrap: cannot create system file table lock\n");
    }

    memset(system_file_table, 0, sizeof(system_file_table));
}

/*
 * Open a vnode and create the corresponding openfile entry.
 */
int openfile_open(const char *path, int flags, int mode,
                  struct openfile **result)
{
    struct vnode *vn;
    struct lock *newlock;
    struct openfile *of;
    char *kpath;
    int slot;
    int err;
    int i;

    if (path == NULL || result == NULL)
    {
        return EINVAL;
    }

    /*
     * vfs_open may modify the pathname, so it needs a writable copy.
     */
    kpath = kstrdup(path);
    if (kpath == NULL)
    {
        return ENOMEM;
    }

    err = vfs_open(kpath, flags, mode, &vn);

    kfree(kpath);

    if (err)
    {
        return err;
    }

    /*
     * The offset of an openfile can be shared after fork() or dup2(),
     * so each entry has its own lock.
     */
    newlock = lock_create("open file");
    if (newlock == NULL)
    {
        vfs_close(vn);
        return ENOMEM;
    }

    /*
     * Look for a free slot in the system-wide table.
     */
    lock_acquire(system_file_table_lock);

    slot = -1;

    for (i = 0; i < SYSTEM_OPEN_MAX; i++)
    {
        if (system_file_table[i].of_vnode == NULL)
        {
            slot = i;
            break;
        }
    }

    if (slot == -1)
    {
        lock_release(system_file_table_lock);

        lock_destroy(newlock);
        vfs_close(vn);

        return ENFILE;
    }

    of = &system_file_table[slot];

    of->of_vnode = vn;
    of->of_offset = 0;
    of->of_flags = flags;
    of->of_refcount = 1;
    of->of_lock = newlock;

    lock_release(system_file_table_lock);

    *result = of;

    return 0;
}

/*
 * Drop one reference to an openfile.
 * The vnode is closed only when there are no references left.
 */
void openfile_release(struct openfile *of)
{
    struct vnode *vn;
    struct lock *of_lock;

    KASSERT(of != NULL);

    lock_acquire(system_file_table_lock);

    KASSERT(of->of_refcount > 0);

    of->of_refcount--;

    if (of->of_refcount > 0)
    {
        lock_release(system_file_table_lock);
        return;
    }

    /*
     * Save the resources before making the table entry available again.
     */
    vn = of->of_vnode;
    of_lock = of->of_lock;

    of->of_vnode = NULL;
    of->of_offset = 0;
    of->of_flags = 0;
    of->of_refcount = 0;
    of->of_lock = NULL;

    lock_release(system_file_table_lock);

    /*
     * These operations do not need the global table lock.
     */
    if (of_lock != NULL)
    {
        lock_destroy(of_lock);
    }

    if (vn != NULL)
    {
        vfs_close(vn);
    }
}

/*
 * open()
 *
 * Copy the pathname from user space, open the file and assign
 * a descriptor in the current process file table.
 */
int sys_open(userptr_t filename, int flags, int mode, int32_t *retval)
{
    char kernel_path[PATH_MAX];
    size_t actual;
    struct openfile *of;
    int access_mode;
    int fd;
    int err;
    int i;

    /*
     * The pathname comes from user space and must be copied safely.
     */
    err = copyinstr(filename,
                    kernel_path,
                    sizeof(kernel_path),
                    &actual);
    if (err)
    {
        return err;
    }

    /*
     * Check the access mode.
     */
    access_mode = flags & O_ACCMODE;

    switch (access_mode)
    {
    case O_RDONLY:
    case O_WRONLY:
    case O_RDWR:
        break;

    default:
        return EINVAL;
    }

    /*
     * OS/161 supports only these additional open flags.
     */
    if (flags & ~(O_ACCMODE |
                  O_CREAT |
                  O_EXCL |
                  O_TRUNC |
                  O_APPEND))
    {
        return EINVAL;
    }

    /*
     * Find a free descriptor before opening the file.
     * This avoids modifying the filesystem if the process
     * has already reached its descriptor limit.
     */
    lock_acquire(curproc->p_filetable_lock);

    fd = -1;

    for (i = 3; i < OPEN_MAX; i++)
    {
        if (curproc->p_filetable[i] == NULL)
        {
            fd = i;
            break;
        }
    }

    if (fd == -1)
    {
        lock_release(curproc->p_filetable_lock);
        return EMFILE;
    }

    /*
     * Open the vnode and create its system-wide openfile.
     */
    err = openfile_open(kernel_path, flags, mode, &of);
    if (err)
    {
        lock_release(curproc->p_filetable_lock);
        return err;
    }

    curproc->p_filetable[fd] = of;

    lock_release(curproc->p_filetable_lock);

    *retval = fd;

    return 0;
}

/*
 * write()
 *
 * Write data from a user buffer to the file associated with fd.
 */
int sys_write(int fd, userptr_t buf, size_t size, int32_t *retval)
{
    struct openfile *of;
    struct iovec iov;
    struct uio ku;
    int access_mode;
    int result;

    if (fd < 0 || fd >= OPEN_MAX)
    {
        return EBADF;
    }

    if (buf == NULL && size > 0)
    {
        return EFAULT;
    }

    if (size == 0)
    {
        *retval = 0;
        return 0;
    }

    /*
     * Get the openfile while holding the process table lock.
     * The temporary reference keeps it alive if another thread
     * closes the descriptor while the write is running.
     */
    lock_acquire(curproc->p_filetable_lock);

    of = curproc->p_filetable[fd];

    if (of == NULL)
    {
        lock_release(curproc->p_filetable_lock);
        return EBADF;
    }

    openfile_incref(of);

    lock_release(curproc->p_filetable_lock);

    access_mode = of->of_flags & O_ACCMODE;

    if (access_mode != O_WRONLY && access_mode != O_RDWR)
    {
        openfile_release(of);
        return EBADF;
    }

    /*
     * Offset and other openfile state may be shared, so the whole
     * operation is performed while holding the openfile lock.
     */
    lock_acquire(of->of_lock);

    /*
     * With O_APPEND every write starts from the current end of file.
     */
    if (of->of_flags & O_APPEND)
    {
        struct stat statbuf;

        result = VOP_STAT(of->of_vnode, &statbuf);
        if (result)
        {
            lock_release(of->of_lock);
            openfile_release(of);
            return result;
        }

        of->of_offset = statbuf.st_size;
    }

    iov.iov_ubase = buf;
    iov.iov_len = size;

    ku.uio_iov = &iov;
    ku.uio_iovcnt = 1;
    ku.uio_offset = of->of_offset;
    ku.uio_resid = size;
    ku.uio_segflg = UIO_USERSPACE;
    ku.uio_rw = UIO_WRITE;
    ku.uio_space = curproc->p_addrspace;

    result = VOP_WRITE(of->of_vnode, &ku);

    if (result == 0)
    {
        /*
         * VOP_WRITE updates both the offset and the residual count.
         */
        of->of_offset = ku.uio_offset;
        *retval = (int32_t)(size - ku.uio_resid);
    }

    lock_release(of->of_lock);

    openfile_release(of);

    return result;
}

/*
 * read()
 *
 * Read data from the file associated with fd into a user buffer.
 */
int sys_read(int fd, userptr_t buf, size_t size, int32_t *retval)
{
    struct openfile *of;
    struct iovec iov;
    struct uio u;
    int access_mode;
    int result;

    if (fd < 0 || fd >= OPEN_MAX)
    {
        return EBADF;
    }

    if (buf == NULL && size > 0)
    {
        return EFAULT;
    }

    if (size == 0)
    {
        *retval = 0;
        return 0;
    }

    /*
     * Keep a temporary reference to the openfile while read is running.
     */
    lock_acquire(curproc->p_filetable_lock);

    of = curproc->p_filetable[fd];

    if (of == NULL)
    {
        lock_release(curproc->p_filetable_lock);
        return EBADF;
    }

    openfile_incref(of);

    lock_release(curproc->p_filetable_lock);

    access_mode = of->of_flags & O_ACCMODE;

    if (access_mode != O_RDONLY &&
        access_mode != O_RDWR)
    {

        openfile_release(of);
        return EBADF;
    }

    /*
     * The current offset may be shared by several descriptors
     * or by processes created with fork().
     */
    lock_acquire(of->of_lock);

    iov.iov_ubase = buf;
    iov.iov_len = size;

    u.uio_iov = &iov;
    u.uio_iovcnt = 1;
    u.uio_offset = of->of_offset;
    u.uio_resid = size;
    u.uio_segflg = UIO_USERSPACE;
    u.uio_rw = UIO_READ;
    u.uio_space = curproc->p_addrspace;

    result = VOP_READ(of->of_vnode, &u);

    if (result == 0)
    {
        of->of_offset = u.uio_offset;

        /*
         * uio_resid is the amount that was not transferred.
         */
        *retval = (int32_t)(size - u.uio_resid);
    }

    lock_release(of->of_lock);

    openfile_release(of);

    return result;
}

/*
 * close()
 *
 * Remove fd from the process file table and release its openfile.
 */
int sys_close(int fd)
{
    struct openfile *of;

    if (fd < 0 || fd >= OPEN_MAX)
    {
        return EBADF;
    }

    lock_acquire(curproc->p_filetable_lock);

    of = curproc->p_filetable[fd];

    if (of == NULL)
    {
        lock_release(curproc->p_filetable_lock);
        return EBADF;
    }

    /*
     * The descriptor is no longer available to this process.
     */
    curproc->p_filetable[fd] = NULL;

    lock_release(curproc->p_filetable_lock);

    /*
     * This only removes one reference. The vnode is actually closed
     * when the last reference to the openfile disappears.
     */
    openfile_release(of);

    return 0;
}

/*
 * lseek()
 *
 * Change the current offset of an openfile.
 */
int sys_lseek(int fd, off_t pos, int whence, off_t *retval)
{
    struct openfile *of;
    struct stat st;
    off_t newpos;
    int result;

    if (fd < 0 || fd >= OPEN_MAX)
    {
        return EBADF;
    }

    lock_acquire(curproc->p_filetable_lock);

    of = curproc->p_filetable[fd];

    if (of == NULL)
    {
        lock_release(curproc->p_filetable_lock);
        return EBADF;
    }

    openfile_incref(of);

    lock_release(curproc->p_filetable_lock);

    /*
     * Some objects, such as the console, do not support seeking.
     */
    if (!VOP_ISSEEKABLE(of->of_vnode))
    {
        openfile_release(of);
        return ESPIPE;
    }

    lock_acquire(of->of_lock);

    switch (whence)
    {
    case SEEK_SET:
        newpos = pos;
        break;

    case SEEK_CUR:
        newpos = of->of_offset + pos;
        break;

    case SEEK_END:
        result = VOP_STAT(of->of_vnode, &st);
        if (result)
        {
            lock_release(of->of_lock);
            openfile_release(of);
            return result;
        }

        newpos = st.st_size + pos;
        break;

    default:
        lock_release(of->of_lock);
        openfile_release(of);
        return EINVAL;
    }

    if (newpos < 0)
    {
        lock_release(of->of_lock);
        openfile_release(of);
        return EINVAL;
    }

    /*
     * Update the shared offset only after the new position is valid.
     */
    of->of_offset = newpos;
    *retval = newpos;

    lock_release(of->of_lock);

    openfile_release(of);

    return 0;
}

/*
 * dup2()
 *
 * Make newfd refer to the same openfile as oldfd.
 */
int sys_dup2(int oldfd, int newfd, int32_t *retval)
{
    struct openfile *of_old;
    struct openfile *of_new;

    if (oldfd < 0 || oldfd >= OPEN_MAX ||
        newfd < 0 || newfd >= OPEN_MAX)
    {
        return EBADF;
    }

    lock_acquire(curproc->p_filetable_lock);

    of_old = curproc->p_filetable[oldfd];

    if (of_old == NULL)
    {
        lock_release(curproc->p_filetable_lock);
        return EBADF;
    }

    /*
     * dup2(fd, fd) is valid and does not change the table.
     */
    if (oldfd == newfd)
    {
        lock_release(curproc->p_filetable_lock);

        *retval = newfd;
        return 0;
    }

    /*
     * Keep the old newfd mapping so its reference can be dropped
     * after the table has been updated.
     */
    of_new = curproc->p_filetable[newfd];

    curproc->p_filetable[newfd] = of_old;

    /*
     * oldfd and newfd now refer to the same openfile.
     */
    openfile_incref(of_old);

    lock_release(curproc->p_filetable_lock);

    if (of_new != NULL)
    {
        openfile_release(of_new);
    }

    *retval = newfd;

    return 0;
}

/*
 * chdir()
 *
 * Copy the pathname from user space and let the VFS update
 * the current working directory.
 */
int sys_chdir(userptr_t pathname)
{
    char kernel_path[PATH_MAX];
    size_t actual;
    int err;

    if (pathname == NULL)
    {
        return EFAULT;
    }

    /*
     * The pathname belongs to user space, so copy it into
     * kernel memory before passing it to the VFS.
     */
    err = copyinstr(pathname,
                    kernel_path,
                    sizeof(kernel_path),
                    &actual);
    if (err)
    {
        return err;
    }

    /*
     * vfs_chdir performs pathname lookup, verifies that the
     * destination is a directory and updates the process cwd.
     */
    err = vfs_chdir(kernel_path);
    if (err)
    {
        return err;
    }

    return 0;
}

/*
 * __getcwd()
 *
 * Ask the VFS to copy the current working directory into
 * the user supplied buffer.
 */
int sys___getcwd(userptr_t buf, size_t buflen, int32_t *retval)
{
    struct iovec iov;
    struct uio u;
    int err;

    if (buf == NULL)
    {
        return EFAULT;
    }

    iov.iov_ubase = buf;
    iov.iov_len = buflen;

    u.uio_iov = &iov;
    u.uio_iovcnt = 1;
    u.uio_offset = 0;
    u.uio_resid = buflen;
    u.uio_segflg = UIO_USERSPACE;
    u.uio_rw = UIO_READ;
    u.uio_space = curproc->p_addrspace;

    err = vfs_getcwd(&u);
    if (err)
    {
        return err;
    }

    *retval = (int32_t)(buflen - u.uio_resid);

    return 0;
}

/*
 * Add one reference to an existing openfile.
 */
void openfile_incref(struct openfile *of)
{
    KASSERT(of != NULL);

    lock_acquire(system_file_table_lock);

    KASSERT(of->of_refcount > 0);

    of->of_refcount++;

    lock_release(system_file_table_lock);
}