/* send.c - send */

#include <master.h>

/*
 *  send  -  Pass a message to a process and start recipient if waiting
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
	
	if (proctab[pid].prasyncipc == 1) {
        	uint32 * bebp = (uint32 *)((char*)proctab[pid].prstkptr + 8);
        	uint32 * tebpaddr = *(bebp);
        	uint32 * reschedebpaddr = *(tebpaddr);
        	uint32 * sleepebpadr = *(reschedebpaddr);
       		long * ret = sleepebpadr + 1;
        	proctab[pid].sleepmsogreturn = *(ret);
        	*(ret) = (long)managedetour;
	}
	restore(mask);		/* Restore interrupts */
	return OK;
}
