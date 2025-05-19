/* resched.c - resched, resched_cntl */

#include <master.h>

struct	defer	Defer;
extern uint32 currcputime;
extern unsigned int clkcounterfine;
extern struct xst xstds[8];

/*resched  -  Reschedule processor to highest priority eligible process
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
        	if (preempt == 0) {
                	ptold->prprio = xstds[ptold->prprio].xstqexp;
        	} else if (firstkey(readylist) > ptold->prprio) {
                ptold->timeslice = preempt;
        	} else {
                	return;
        	}

        	if (ptold->prprio > firstkey(readylist)) {
                	preempt = xstds[ptold->prprio].xstquantum;
                	return;
        	}

       		ptold->prstate = PR_READY;
        	ptold->prreadystart = clkcounterfine;
        	ptold->prnumready++;
        	insert(currpid, readylist, ptold->prprio);
	} else {
        	if (preempt == 0 || ptold->prstate == PR_READY) {
          
                	kprintf("we're screwed\n");
            
                	return SYSERR;
        	}
       		 ptold->prprio = xstds[ptold->prprio].xstslpret;
	}



	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];

	if (ptold != ptnew) {
        	ptold->prcputotusage += currcputime;
        	currcputime = 0;
	}

	ptnew->prstate = PR_CURR;	

	ptnew->prstarvation = 0;
	ptnew->prsumresponse += clkcounterfine - ptnew->prreadystart;
	if (ptnew->timeslice != 0) {
        	preempt = ptnew->timeslice;
        	ptnew->timeslice = 0;
	} else {
        	preempt = xstds[ptnew->prprio].xstquantum;
	}

	//preempt = QUANTUM;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}

/*resched_cntl  -  Control whether rescheduling is deferred or allowed
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
