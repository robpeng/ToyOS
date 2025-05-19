/* ready.c - ready */

#include <master.h>

qid16	readylist;			/* Index of ready list		*/
extern unsigned int clkcounterfine;

/*ready  -  Make a process eligible for CPU service
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	prptr->prreadystart = clkcounterfine;
	prptr->prnumready++;
	insert(pid, readylist, prptr->prprio);
	resched();

	return OK;
}
