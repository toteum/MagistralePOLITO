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

#ifndef _PROC_H_
#define _PROC_H_

#include <spinlock.h>
#include "opt-waitpid.h"
#include "opt-pdsc2.h"

#if OPT_PDSC2
#include <limits.h>
#endif

struct addrspace;
struct thread;
struct vnode;

#if OPT_PDSC2
struct openfile;
struct lock;
#endif

struct proc
{
	char *p_name;			/* Name of this process */
	struct spinlock p_lock; /* Lock for this structure */
	unsigned p_numthreads;	/* Number of threads in this process */

	/* VM */
	struct addrspace *p_addrspace; /* virtual address space */

	/* VFS */
	struct vnode *p_cwd; /* current working directory */

#if OPT_WAITPID
	int p_status;			 /* Exit status */
	pid_t p_pid;			 /* Process ID*/
	struct semaphore *p_sem; /* Synchronizes waitpid with process exit */
#endif

#if OPT_PDSC2
	pid_t p_parent_pid;

	bool p_exited;
	bool p_orphan;

	struct openfile *p_filetable[OPEN_MAX];
	struct lock *p_filetable_lock;
#endif
};

/* Kernel process */
extern struct proc *kproc;

/* Process lifecycle. */
void proc_bootstrap(void);
struct proc *proc_create_runprogram(const char *name);
struct proc *proc_create_fork(const char *name, int *errp);
void proc_destroy(struct proc *proc);

/* Thread/process association. */
int proc_addthread(struct proc *proc, struct thread *t);
void proc_remthread(struct thread *t);

/* Address-space management. */
struct addrspace *proc_getas(void);
struct addrspace *proc_setas(struct addrspace *);

/* PID and wait support. */
struct proc *proc_search_pid(pid_t pid);
int proc_wait(struct proc *proc);

#if OPT_PDSC2
/* Copy the file descriptor table during fork(). */
void proc_filetable_copy(struct proc *src, struct proc *dst);
#endif

#if OPT_PDSC2 && OPT_WAITPID
	bool proc_has_exited(struct proc *proc);
	void proc_finish_exit(struct proc *proc);
#endif

#endif /* _PROC_H_ */