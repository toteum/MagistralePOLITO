/*
 * Copyright (c) 2013
 *	The President and Fellows of Harvard College.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <types.h>
#include <spl.h>
#include <proc.h>
#include <current.h>
#include <addrspace.h>
#include <vnode.h>
#include <kern/fcntl.h>
#include <openfile.h>
#include <limits.h>
#include <synch.h>
#include <kern/errno.h>


#if OPT_WAITPID

#define MAX_PROC 100

/*
 * Global process table.
 *
 * It maps each PID to its process structure.
 */
static struct _processTable {
	int active;
	struct proc *proc[MAX_PROC + 1];
	int last_i;
	struct spinlock lk;
} processTable;

#endif


/*
 * Kernel process.
 *
 * Kernel-only threads belong to this process.
 */
struct proc *kproc;


/*
 * Search a process using its PID.
 */
struct proc *
proc_search_pid(pid_t pid)
{
#if OPT_WAITPID
	struct proc *p;

	if (pid <= 0 || pid > MAX_PROC) {
		return NULL;
	}

	spinlock_acquire(&processTable.lk);

	p = processTable.proc[pid];

	spinlock_release(&processTable.lk);

	return p;

#else
	(void)pid;

	return NULL;
#endif
}


/*
 * Initialize the fields required by waitpid and assign
 * a PID to a new process.
 */
static int
proc_init_waitpid(struct proc *proc, const char *name)
{
#if OPT_WAITPID
	int i;
	int pid_found;

	pid_found = 0;

	spinlock_acquire(&processTable.lk);

	for (i = 1; i <= MAX_PROC; i++) {

		if (processTable.proc[i] == NULL) {

			processTable.proc[i] = proc;
			processTable.last_i = i;

			proc->p_pid = i;

			pid_found = 1;

			break;
		}
	}

	spinlock_release(&processTable.lk);

	/*
	 * No free PID is available.
	 */
	if (!pid_found) {
		proc->p_pid = 0;
		return ENPROC;
	}

	proc->p_status = 0;

	/*
	 * Semaphore used by waitpid().
	 *
	 * The parent sleeps on this semaphore until the child exits.
	 */
	proc->p_sem = sem_create(name, 0);

	if (proc->p_sem == NULL) {

		spinlock_acquire(&processTable.lk);

		if (processTable.proc[proc->p_pid] == proc) {
			processTable.proc[proc->p_pid] = NULL;
		}

		spinlock_release(&processTable.lk);

		proc->p_pid = 0;

		return ENOMEM;
	}

	return 0;

#else
	(void)proc;
	(void)name;

	return 0;
#endif
}


/*
 * Remove a process from the global process table and
 * destroy the semaphore used by waitpid().
 */
static void
proc_end_waitpid(struct proc *proc)
{
#if OPT_WAITPID
	pid_t pid;

	pid = proc->p_pid;

	spinlock_acquire(&processTable.lk);

	if (pid > 0 &&
	    pid <= MAX_PROC &&
	    processTable.proc[pid] == proc) {

		processTable.proc[pid] = NULL;
	}

	spinlock_release(&processTable.lk);

	if (proc->p_sem != NULL) {
		sem_destroy(proc->p_sem);
		proc->p_sem = NULL;
	}

#else
	(void)proc;
#endif
}


/*
 * Create the basic process structure.
 */
static struct proc *
proc_create(const char *name, int *errp)
{
	struct proc *proc;

	if (errp != NULL) {
		*errp = 0;
	}

	proc = kmalloc(sizeof(*proc));

	if (proc == NULL) {
		if(errp != NULL) {
			*errp = ENOMEM;
		}
		return NULL;
	}

#if OPT_PDSC2
	proc->p_filetable_lock = NULL;
#endif

	proc->p_name = kstrdup(name);

	if (proc->p_name == NULL) {
		if(errp != NULL) {
			*errp = ENOMEM;
		}
		kfree(proc);
		return NULL;
	}

	/*
	 * Thread state.
	 */
	proc->p_numthreads = 0;
	spinlock_init(&proc->p_lock);

	/*
	 * Virtual memory state.
	 */
	proc->p_addrspace = NULL;

	/*
	 * Virtual file-system state.
	 */
	proc->p_cwd = NULL;


#if OPT_WAITPID
	proc->p_sem = NULL;
#endif


	/*
	 * Allocate the PID and initialize waitpid support.
	 */
	{
		int result;

		result = proc_init_waitpid(proc, name);

		if (result) {
			if(errp != NULL) {
				*errp = result;
			}

			kfree(proc->p_name);

			spinlock_cleanup(&proc->p_lock);

			kfree(proc);

			return NULL;
		}
	}


#if OPT_PDSC2
	{
		int fd;

		/*
		 * A generic process initially has no parent.
		 *
		 * proc_create_fork() assigns the real parent PID.
		 */
		proc->p_parent_pid = 0;
		proc->p_exited = false;
		proc->p_orphan = false;

		/*
		 * Start with an empty file descriptor table.
		 */
		for (fd = 0; fd < OPEN_MAX; fd++) {
			proc->p_filetable[fd] = NULL;
		}

		/*
		 * Protect the per-process file descriptor table.
		 */
		proc->p_filetable_lock =
		    lock_create("p_filetable");

		if (proc->p_filetable_lock == NULL) {
			if(errp != NULL) {
				*errp = ENOMEM;
			}

			proc_end_waitpid(proc);

			kfree(proc->p_name);

			spinlock_cleanup(&proc->p_lock);

			kfree(proc);

			return NULL;
		}
	}
#endif

	return proc;
}


/*
 * Create a process for fork().
 */
struct proc *
proc_create_fork(const char *name, int *errp)
{
	struct proc *newproc;

	newproc = proc_create(name, errp);

	if (newproc == NULL) {
		return NULL;
	}

	/*
	 * The address space is copied later by sys_fork().
	 */
	newproc->p_addrspace = NULL;

	/*
	 * fork() inherits the current working directory.
	 */
	spinlock_acquire(&curproc->p_lock);

	if (curproc->p_cwd != NULL) {

		VOP_INCREF(curproc->p_cwd);

		newproc->p_cwd = curproc->p_cwd;
	}

	spinlock_release(&curproc->p_lock);


#if OPT_PDSC2 && OPT_WAITPID

	/*
	 * Save the PID of the parent.
	 *
	 * waitpid() uses this field to check that a process can
	 * wait only for one of its own children.
	 */
	newproc->p_parent_pid = curproc->p_pid;

#endif

	return newproc;
}


#if OPT_PDSC2

/*
 * Copy a process file descriptor table.
 *
 * Parent and child have distinct fd tables, but inherited
 * descriptors point to the same openfile structures.
 */
void
proc_filetable_copy(struct proc *src,
                    struct proc *dst)
{
	int fd;

	KASSERT(src != NULL);
	KASSERT(dst != NULL);

	lock_acquire(src->p_filetable_lock);

	for (fd = 0; fd < OPEN_MAX; fd++) {

		if (src->p_filetable[fd] != NULL) {

			dst->p_filetable[fd] =
			    src->p_filetable[fd];

			/*
			 * The child owns another reference to
			 * the same open file.
			 */
			openfile_incref(
			    dst->p_filetable[fd]);
		}
	}

	lock_release(src->p_filetable_lock);
}

#endif

#if OPT_PDSC2 && OPT_WAITPID

/*
 * Return true if the process has completely exited.
 *
 * p_exited is protected by the process-table lock because exit
 * and orphan handling must be coordinated atomically.
 */
bool
proc_has_exited(struct proc *proc)
{
	bool exited;

	KASSERT(proc != NULL);

	spinlock_acquire(&processTable.lk);

	exited = proc->p_exited;

	spinlock_release(&processTable.lk);

	return exited;
}


/*
 * Complete process termination after its last thread has already
 * been detached.
 *
 * A normal process remains available until its parent collects it
 * with waitpid().
 *
 * An orphan has no parent that can collect it and is therefore
 * destroyed automatically.
 */
void
proc_finish_exit(struct proc *proc)
{
	struct proc *to_destroy[MAX_PROC];
	int destroy_count;
	int i;
	bool destroy_self;

	KASSERT(proc != NULL);
	KASSERT(proc != kproc);
	KASSERT(proc->p_numthreads == 0);

	destroy_count = 0;
	destroy_self = false;

	spinlock_acquire(&processTable.lk);

	/*
	 * The process has completely terminated.
	 */
	proc->p_exited = true;

	/*
	 * This process can no longer collect its children.
	 * Mark all of them as orphans.
	 */
	for (i = 1; i <= MAX_PROC; i++) {
		struct proc *child;

		child = processTable.proc[i];

		if (child == NULL) {
			continue;
		}

		if (child == proc) {
			continue;
		}

		if (child->p_parent_pid != proc->p_pid) {
			continue;
		}

		child->p_parent_pid = 0;
		child->p_orphan = true;

		/*
		 * If the child had already exited, nobody will ever
		 * call waitpid() for it, so reclaim it now.
		 */
		if (child->p_exited) {
			processTable.proc[i] = NULL;

			to_destroy[destroy_count] = child;
			destroy_count++;
		}
	}

	/*
	 * If this process itself had already become an orphan,
	 * no parent will ever collect it.
	 */
	if (proc->p_orphan) {
		if (proc->p_pid > 0 &&
		    proc->p_pid <= MAX_PROC &&
		    processTable.proc[proc->p_pid] == proc) {

			processTable.proc[proc->p_pid] = NULL;
		}

		destroy_self = true;
	}

	spinlock_release(&processTable.lk);


	/*
	 * proc_destroy() must not run while processTable.lk is held.
	 */
	for (i = 0; i < destroy_count; i++) {
		proc_destroy(to_destroy[i]);
	}


	if (destroy_self) {
		/*
		 * No parent exists, therefore there is nobody to wake.
		 */
		proc_destroy(proc);
	}
	else {
		/*
		 * Normal child: its parent may now collect the status.
		 *
		 * This V happens only after p_numthreads became zero.
		 */
		V(proc->p_sem);
	}
}

#endif

/*
 * Destroy a process and all resources still owned by it.
 */
void
proc_destroy(struct proc *proc)
{
	KASSERT(proc != NULL);
	KASSERT(proc != kproc);

	/*
	 * Release the current working directory.
	 */
	if (proc->p_cwd != NULL) {

		VOP_DECREF(proc->p_cwd);

		proc->p_cwd = NULL;
	}

	/*
	 * Destroy an address space that is still associated
	 * with the process.
	 */
	if (proc->p_addrspace != NULL) {

		struct addrspace *as;

		as = proc->p_addrspace;

		proc->p_addrspace = NULL;

		as_destroy(as);
	}


#if OPT_PDSC2

	/*
	 * Release all file descriptors.
	 */
	if (proc->p_filetable_lock != NULL) {

		int fd;

		lock_acquire(proc->p_filetable_lock);

		for (fd = 0; fd < OPEN_MAX; fd++) {

			struct openfile *of;

			of = proc->p_filetable[fd];

			if (of == NULL) {
				continue;
			}

			/*
			 * Remove the descriptor from the table first.
			 */
			proc->p_filetable[fd] = NULL;

			/*
			 * openfile_release() may acquire other locks,
			 * so do not keep the process file-table lock.
			 */
			lock_release(
			    proc->p_filetable_lock);

			openfile_release(of);

			lock_acquire(
			    proc->p_filetable_lock);
		}

		lock_release(proc->p_filetable_lock);

		lock_destroy(proc->p_filetable_lock);

		proc->p_filetable_lock = NULL;
	}

#endif


	/*
	 * Remove the PID and destroy the wait semaphore.
	 */
	proc_end_waitpid(proc);


	/*
	 * A process must not contain any thread when it is destroyed.
	 */
	KASSERT(proc->p_numthreads == 0);

	spinlock_cleanup(&proc->p_lock);

	kfree(proc->p_name);

	kfree(proc);
}


/*
 * Initialize process support.
 */
void
proc_bootstrap(void)
{
#if OPT_WAITPID
	int i;

	spinlock_init(&processTable.lk);

	processTable.active = 1;
	processTable.last_i = 0;

	for (i = 0; i <= MAX_PROC; i++) {
		processTable.proc[i] = NULL;
	}
#endif

	kproc = proc_create("[kernel]", NULL);

	if (kproc == NULL) {
		panic("proc_create for kproc failed\n");
	}
}


/*
 * Create a process for a program started directly by the kernel.
 */
struct proc *
proc_create_runprogram(const char *name)
{
	struct proc *newproc;

	newproc = proc_create(name, NULL);

	if (newproc == NULL) {
		return NULL;
	}

	/*
	 * runprogram() creates the address space later.
	 */
	newproc->p_addrspace = NULL;

	/*
	 * Inherit the current working directory.
	 */
	spinlock_acquire(&curproc->p_lock);

	if (curproc->p_cwd != NULL) {

		VOP_INCREF(curproc->p_cwd);

		newproc->p_cwd = curproc->p_cwd;
	}

	spinlock_release(&curproc->p_lock);


#if OPT_PDSC2
	{
		int err;

		/*
		 * stdin
		 */
		err = openfile_open(
		    "con:",
		    O_RDONLY,
		    0,
		    &newproc->p_filetable[0]);

		if (err) {

			proc_destroy(newproc);

			return NULL;
		}


		/*
		 * stdout
		 */
		err = openfile_open(
		    "con:",
		    O_WRONLY,
		    0,
		    &newproc->p_filetable[1]);

		if (err) {

			openfile_release(
			    newproc->p_filetable[0]);

			newproc->p_filetable[0] = NULL;

			proc_destroy(newproc);

			return NULL;
		}


		/*
		 * stderr
		 */
		err = openfile_open(
		    "con:",
		    O_WRONLY,
		    0,
		    &newproc->p_filetable[2]);

		if (err) {

			openfile_release(
			    newproc->p_filetable[1]);

			newproc->p_filetable[1] = NULL;

			openfile_release(
			    newproc->p_filetable[0]);

			newproc->p_filetable[0] = NULL;

			proc_destroy(newproc);

			return NULL;
		}
	}
#endif

	return newproc;
}


/*
 * Attach a thread to a process.
 */
int
proc_addthread(struct proc *proc,
               struct thread *t)
{
	int spl;

	KASSERT(proc != NULL);
	KASSERT(t->t_proc == NULL);

	spinlock_acquire(&proc->p_lock);

	proc->p_numthreads++;

	spinlock_release(&proc->p_lock);

	spl = splhigh();

	t->t_proc = proc;

	splx(spl);

	return 0;
}


/*
 * Detach a thread from its process.
 */
void
proc_remthread(struct thread *t)
{
	struct proc *proc;
	int spl;

	proc = t->t_proc;

	KASSERT(proc != NULL);

	spinlock_acquire(&proc->p_lock);

	KASSERT(proc->p_numthreads > 0);

	proc->p_numthreads--;

	spinlock_release(&proc->p_lock);

	spl = splhigh();

	t->t_proc = NULL;

	splx(spl);
}


/*
 * Return the address space associated with the current process.
 */
struct addrspace *
proc_getas(void)
{
	struct addrspace *as;
	struct proc *proc;

	proc = curproc;

	if (proc == NULL) {
		return NULL;
	}

	spinlock_acquire(&proc->p_lock);

	as = proc->p_addrspace;

	spinlock_release(&proc->p_lock);

	return as;
}


/*
 * Replace the current process address space and return the old one.
 */
struct addrspace *
proc_setas(struct addrspace *newas)
{
	struct addrspace *oldas;
	struct proc *proc;

	proc = curproc;

	KASSERT(proc != NULL);

	spinlock_acquire(&proc->p_lock);

	oldas = proc->p_addrspace;

	proc->p_addrspace = newas;

	spinlock_release(&proc->p_lock);

	return oldas;
}


/*
 * Wait until the process exits and return its status.
 *
 * IMPORTANT:
 * proc_wait() does not destroy the process.
 *
 * sys_waitpid() destroys the child only after copyout()
 * has completed successfully.
 */
int
proc_wait(struct proc *proc)
{
#if OPT_WAITPID
	int return_status;

	KASSERT(proc != NULL);

	/*
	 * Sleep until the process signals its termination.
	 */
	P(proc->p_sem);

	return_status = proc->p_status;

	/*
	 * Restore the semaphore notification.
	 *
	 * If copyout() later fails, waitpid() can be called again.
	 */
	V(proc->p_sem);

	return return_status;

#else
	(void)proc;

	return 0;
#endif
}