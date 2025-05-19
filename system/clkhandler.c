/* clkhandler.c - clkhandler */

#include <master.h>

/*
 * clkhandler - high level clock interrupt handler
 */

extern uint16 makedetouralrm;
extern unsigned int clkcounterfine;



void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/
	
	currcputime++;
	clkcounterfine++;


	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}
	

	int scheduleflag = 0; // checks if priorities changed
	if (clkcounterfine % (RECENTWIN*1000) == 0) {
        	uint16 curr = firstid(readylist);
        	uint16 start = curr;
        	while (curr != queuetail(readylist)) {
                	if (clkcounterfine - proctab[curr].prreadystart >= RECENTWIN * 1000) {
                        	//handles starving processes. if starvationprev on, handles those actions as well
                        	if (proctab[curr].prstarvation == 0) {
                                	proctab[curr].prstarvation = 1;
                                	proctab[curr].prstarvecount++;
                                	if (STARVATIONPREV == 1) {
                                        	scheduleflag = 1;
                                        	modprioready(curr, readylist, 7);
                                	}
                        	}
                	}
                	curr = queuetab[curr].qnext;
        	}
	}



	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}
	if (scheduleflag && preempt > 1) {
        	resched();
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = 0;
		resched();
		if (proctab[getpid()].pralrmcounter != 0 && proctab[getpid()].pralrmcounter <=
			clkcounterfine) {
        		proctab[getpid()].pralrmcounter = 0;
        		makedetouralrm = 1;
		}	
	}  else {
       		if (proctab[getpid()].pralrmcounter != 0  &&
               		proctab[getpid()].pralrmcounter <= clkcounterfine) {
              		proctab[getpid()].pralrmcounter = 0;
               		makedetouralrm = 1;
       		}
	}
}
