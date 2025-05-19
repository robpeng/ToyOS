/* yield.c - yield */

#include <master.h>

/*
 *  yield  -  Voluntarily relinquish the CPU (end a timeslice)
 */
syscall	yield(void)
{
	intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	resched();
	restore(mask);
	return OK;
}
