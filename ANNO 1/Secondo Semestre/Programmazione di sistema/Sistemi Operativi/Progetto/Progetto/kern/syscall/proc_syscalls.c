#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <thread.h>
#include <current.h>
#include <proc.h>
#include <addrspace.h>
#include <syscall.h>
#include <synch.h>
#include <mips/trapframe.h>
#include <kern/fcntl.h>
#include <copyinout.h>
#include <vfs.h>
#include <vnode.h>
#include <limits.h>
#include <kern/wait.h>

/*
 * Terminate the current process.
 */
void
sys__exit(int status)
{
#if OPT_WAITPID
	struct proc *p;
	struct addrspace *as;

	p = curproc;

	KASSERT(p != NULL);

	/*
	 * Save the exit status for waitpid().
	 */
	p->p_status = _MKWAIT_EXIT(status);

	/*
	 * The user address space is no longer needed.
	 */
	as = proc_setas(NULL);
	as_deactivate();

	if (as != NULL) {
		as_destroy(as);
	}

#if OPT_PDSC2
	/*
	 * Detach before making the process collectable.
	 *
	 * This guarantees that proc_destroy() will always see
	 * p_numthreads == 0.
	 */
	proc_remthread(curthread);

	/*
	 * Mark the process as exited, handle its children and
	 * either wake the parent or automatically reap an orphan.
	 *
	 * proc_finish_exit() may destroy p, so do not use p after
	 * this call.
	 */
	proc_finish_exit(p);

#else
	V(p->p_sem);
#endif

#else
	struct addrspace *as;

	as = proc_setas(NULL);
	as_deactivate();

	if (as != NULL) {
		as_destroy(as);
	}
#endif

	thread_exit();

	panic("thread_exit returned\n");
}

/*
 * Return the PID of the current process.
 */
pid_t sys_getpid(void)
{
#if OPT_WAITPID

	KASSERT(curproc != NULL);

	return curproc->p_pid;

#else

	return -1;

#endif
}

/*
 * Wait for one of the current process's children.
 */
int
sys_waitpid(pid_t pid,
            userptr_t statusp,
            int options,
            pid_t *retval)
{
#if OPT_WAITPID
	struct proc *child;
	int status;
	int result;

	KASSERT(curproc != NULL);
	KASSERT(retval != NULL);

	/*
	 * Support only the standard blocking behaviour and WNOHANG.
	 */
	if (options != 0 && options != WNOHANG) {
		return EINVAL;
	}

	/*
	 * Find the requested process.
	 */
	child = proc_search_pid(pid);

	if (child == NULL) {
		return ESRCH;
	}

#if OPT_PDSC2
	/*
	 * A process may wait only for one of its own children.
	 */
	if (child->p_parent_pid != curproc->p_pid) {
		return ECHILD;
	}

	/*
	 * WNOHANG:
	 *
	 * If the child is still running, return immediately with 0.
	 */
	if (options == WNOHANG &&
	    !proc_has_exited(child)) {

		*retval = 0;

		return 0;
	}
#endif

	/*
	 * If the child has already exited this P() returns immediately.
	 * Otherwise, with options == 0, wait for it.
	 */
	status = proc_wait(child);

	if (statusp != NULL) {

		result = copyout(&status,
		                 statusp,
		                 sizeof(status));

		/*
		 * Do not destroy the child if copyout fails.
		 *
		 * The parent must be able to retry waitpid().
		 */
		if (result) {
			return result;
		}
	}

	/*
	 * The exit status has been collected successfully.
	 */
	proc_destroy(child);

	*retval = pid;

	return 0;

#else
	(void)pid;
	(void)statusp;
	(void)options;
	(void)retval;

	return ENOSYS;
#endif
}

/*
 * Entry point of the child thread created by fork().
 */
static void
call_enter_forked_process(void *tf_ptr,
						  unsigned long unused)
{
	struct trapframe *tf;

	(void)unused;

	tf = (struct trapframe *)tf_ptr;

	enter_forked_process(tf);

	panic("enter_forked_process returned\n");
}

/*
 * Create a child process.
 */
int sys_fork(struct trapframe *ctf,
			 pid_t *retval)
{
	struct proc *child;
	struct addrspace *child_as;
	struct trapframe *child_tf;
	int result;
	int create_err;

	KASSERT(ctf != NULL);
	KASSERT(retval != NULL);
	KASSERT(curproc != NULL);

	/*
	 * Create the process structure.
	 */
	create_err = 0;
	child = proc_create_fork(curproc->p_name, &create_err);

	if (child == NULL)
	{
		return create_err != 0 ? create_err : ENOMEM;
	}

	/*
	 * Copy the parent's address space.
	 */
	result = as_copy(curproc->p_addrspace,
					 &child_as);

	if (result)
	{
		proc_destroy(child);
		return result;
	}

	child->p_addrspace = child_as;

#if OPT_PDSC2

	/*
	 * Copy the file descriptor table.
	 *
	 * Descriptors remain separate, while openfile structures
	 * are shared.
	 */
	proc_filetable_copy(curproc, child);

#endif

	/*
	 * Copy the trapframe.
	 */
	child_tf = kmalloc(sizeof(struct trapframe));

	if (child_tf == NULL)
	{
		proc_destroy(child);
		return ENOMEM;
	}

	memcpy(child_tf,
		   ctf,
		   sizeof(struct trapframe));

	/*
	 * Create the child thread.
	 */
	result = thread_fork(curproc->p_name,
						 child,
						 call_enter_forked_process,
						 child_tf,
						 0);

	if (result)
	{

		kfree(child_tf);

		proc_destroy(child);

		return result;
	}

	/*
	 * Parent receives the child PID.
	 */
	*retval = child->p_pid;

	return 0;
}

/*
 * Replace the current program image with a new executable.
 */
int sys_execv(userptr_t progname,
			  userptr_t argv)
{
	struct addrspace *newas;
	struct addrspace *oldas;
	struct vnode *v;

	vaddr_t entrypoint;
	vaddr_t stackptr;
	vaddr_t argv_user;
	vaddr_t *uargv;

	char kernel_prog[PATH_MAX];
	char **kargv;
	char *arg_buffer;
	userptr_t user_arg;

	size_t actual;
	size_t len;
	size_t argbytes;

	int argc;
	int i;
	int result;

	/*
	 * progname and argv are user-space pointers.
	 */
	if (progname == NULL || argv == NULL)
	{
		return EFAULT;
	}

	/*
	 * Copy the executable pathname into kernel space.
	 */
	result = copyinstr(progname,
					   kernel_prog,
					   sizeof(kernel_prog),
					   &actual);

	if (result)
	{
		return result;
	}

	/*
	 * Empty pathname is invalid.
	 */
	if (kernel_prog[0] == '\0')
	{
		return EINVAL;
	}

	/*
	 * Count argv entries.
	 */
	argc = 0;

	while (1)
	{

		result = copyin(
			(const_userptr_t)((vaddr_t)argv +
							  argc * sizeof(userptr_t)),
			&user_arg,
			sizeof(user_arg));

		if (result)
		{
			return result;
		}

		if (user_arg == NULL)
		{
			break;
		}

		argc++;

		/*
		 * Prevent an invalid argv from growing indefinitely.
		 */
		if ((size_t)argc *
				sizeof(userptr_t) >=
			ARG_MAX)
		{

			return E2BIG;
		}
	}

	/*
	 * Allocate the kernel argv array.
	 */
	kargv = kmalloc(
		(argc + 1) * sizeof(char *));

	if (kargv == NULL)
	{
		return ENOMEM;
	}

	for (i = 0; i <= argc; i++)
	{
		kargv[i] = NULL;
	}

	/*
	 * Temporary argument buffer.
	 */
	arg_buffer = kmalloc(ARG_MAX);

	if (arg_buffer == NULL)
	{
		kfree(kargv);
		return ENOMEM;
	}

	argbytes = 0;

	/*
	 * Copy all argument strings from user space.
	 */
	for (i = 0; i < argc; i++)
	{

		result = copyin(
			(const_userptr_t)((vaddr_t)argv +
							  i * sizeof(userptr_t)),
			&user_arg,
			sizeof(user_arg));

		if (result)
		{
			goto fail_args;
		}

		result = copyinstr(user_arg,
						   arg_buffer,
						   ARG_MAX,
						   &actual);

		if (result)
		{
			goto fail_args;
		}

		if (argbytes + actual > ARG_MAX)
		{

			result = E2BIG;

			goto fail_args;
		}

		argbytes += actual;

		kargv[i] = kstrdup(arg_buffer);

		if (kargv[i] == NULL)
		{

			result = ENOMEM;

			goto fail_args;
		}
	}

	kargv[argc] = NULL;

	/*
	 * The argv pointer array also occupies argument space.
	 */
	if (argbytes +
			(argc + 1) * sizeof(vaddr_t) >
		ARG_MAX)
	{

		result = E2BIG;

		goto fail_args;
	}

	kfree(arg_buffer);

	arg_buffer = NULL;

	/*
	 * Open the executable.
	 */
	result = vfs_open(kernel_prog,
					  O_RDONLY,
					  0,
					  &v);

	if (result)
	{
		goto fail_kargv;
	}

	/*
	 * Create a new address space.
	 */
	newas = as_create();

	if (newas == NULL)
	{

		vfs_close(v);

		result = ENOMEM;

		goto fail_kargv;
	}

	/*
	 * Temporarily install the new address space.
	 */
	oldas = proc_setas(newas);

	as_activate();

	/*
	 * Load the executable.
	 */
	result = load_elf(v,
					  &entrypoint);

	vfs_close(v);

	if (result)
	{

		proc_setas(oldas);

		as_activate();

		as_destroy(newas);

		goto fail_kargv;
	}

	/*
	 * Create the new stack.
	 */
	result = as_define_stack(newas,
							 &stackptr);

	if (result)
	{

		proc_setas(oldas);

		as_activate();

		as_destroy(newas);

		goto fail_kargv;
	}

	/*
	 * Kernel array containing the final user-space addresses
	 * of the strings.
	 */
	uargv = kmalloc(
		(argc + 1) * sizeof(vaddr_t));

	if (uargv == NULL)
	{

		proc_setas(oldas);

		as_activate();

		as_destroy(newas);

		result = ENOMEM;

		goto fail_kargv;
	}

	/*
	 * Copy strings onto the user stack.
	 */
	for (i = argc - 1; i >= 0; i--)
	{

		len = strlen(kargv[i]) + 1;

		/*
		 * Keep strings aligned to 8 bytes.
		 */
		stackptr -= ROUNDUP(len, 8);

		result = copyoutstr(
			kargv[i],
			(userptr_t)stackptr,
			len,
			NULL);

		if (result)
		{

			kfree(uargv);

			proc_setas(oldas);

			as_activate();

			as_destroy(newas);

			goto fail_kargv;
		}

		uargv[i] = stackptr;
	}

	uargv[argc] = 0;

	/*
	 * Reserve space for argv itself.
	 */
	stackptr -=
		(argc + 1) * sizeof(vaddr_t);

	/*
	 * Align argv.
	 */
	stackptr &= ~(vaddr_t)7;

	argv_user = stackptr;

	/*
	 * Copy argv[] onto the new user stack.
	 */
	result = copyout(
		uargv,
		(userptr_t)argv_user,
		(argc + 1) * sizeof(vaddr_t));

	kfree(uargv);

	if (result)
	{

		proc_setas(oldas);

		as_activate();

		as_destroy(newas);

		goto fail_kargv;
	}

	/*
	 * The new program image is complete.
	 */
	if (oldas != NULL)
	{
		as_destroy(oldas);
	}

	/*
	 * Release kernel argv copies.
	 */
	for (i = 0; i < argc; i++)
	{
		kfree(kargv[i]);
	}

	kfree(kargv);

	/*
	 * Enter user mode.
	 *
	 * A successful execv() never returns.
	 */
	enter_new_process(
		argc,
		(userptr_t)argv_user,
		NULL,
		stackptr,
		entrypoint);

	panic("enter_new_process returned\n");

	return EINVAL;

/*
 * Error while copying arguments.
 */
fail_args:

	if (arg_buffer != NULL)
	{
		kfree(arg_buffer);
	}

/*
 * Release all argv allocations.
 */
fail_kargv:

	for (i = 0; i < argc; i++)
	{

		if (kargv[i] != NULL)
		{
			kfree(kargv[i]);
		}
	}

	kfree(kargv);

	return result;
}