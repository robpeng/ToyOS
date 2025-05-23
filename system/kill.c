/* kill.c - kill */

#include <master.h>
extern uint16 kheapflag;

/*
 *  kill  -  Kill a process and remove it from the system
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/
	int32	i;			/* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	freestk(prptr->prstkbase, prptr->prstklen);
	
	struct perprocmem * curr = proctab[pid].prheapbeg;
 	if (curr == NULL) {

 	} else {
        	 while (curr != NULL) {
                         kprintf("kill() freed memory at address %d\n", curr->memptr);
                 	freemem(curr->memptr, curr->memsize);
                 	curr = curr->memnext;
         	}
         	curr = proctab[pid].prheapbeg;
         	struct perprocmem * pholder = NULL;
         	while (curr != NULL) {
                	 kheapflag = 1;
                	 pholder = curr->memnext;
                 	freemem((char*)curr, sizeof(struct perprocmem));
                 	curr = pholder;
         	}
 	}

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
