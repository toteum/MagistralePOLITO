#ifndef _OPENFILE_H_
#define _OPENFILE_H_

#include <types.h>
#include <limits.h>

#define SYSTEM_OPEN_MAX (10 * OPEN_MAX)

struct vnode;
struct lock;

/*
 * System-wide open file description.
 * Multiple file descriptors may refer to the same openfile.
 */
struct openfile {
    struct vnode *of_vnode;        /* Open VFS object */
    off_t of_offset;               /* Current shared file offset */
    int of_flags;                  /* Opening flags */
    unsigned int of_refcount;      /* Number of active references */
    struct lock *of_lock;          /* Protects open-file state */
};

void openfile_bootstrap(void);

int openfile_open(const char *path,
                  int flags,
                  int mode,
                  struct openfile **result);

void openfile_incref(struct openfile *of);
void openfile_release(struct openfile *of);

#endif /* _OPENFILE_H_ */