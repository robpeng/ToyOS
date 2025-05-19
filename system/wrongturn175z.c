//put the stack for delphi right above sleep's in the stack

#include <master.h>

void wrongturn175z(pid32 traveler) {
	if (traveler < 0 || traveler >= NPROC) {
        return;
	}
	if (proctab[traveler].prstate == PR_FREE) {
        	return;
	}
	char * stkptr = (char*)proctab[traveler].prstkptr;
	uint32 * ctxswebp = (uint32 *)(stkptr + 8);
	uint32 * reschedebp = (uint32 *)*(ctxswebp);
	uint32 * sleepebp = (uint32 *)*(reschedebp);
	uint32 * sleepret = (uint32 *)(sleepebp + 1);
	*(ctxswebp) -= 4;
	*(reschedebp) -= 4;
	*(ctxswebp + 1) -= 4;
	uint32 * curraddr = (uint32*)stkptr;
	for (; curraddr <= sleepebp - 1; curraddr = curraddr + 1) {
		*(curraddr - 1) = *(curraddr);
	}
	proctab[traveler].prstkptr  = stkptr - 4;
	*(sleepebp - 1) = *(sleepebp);
	*(sleepebp) = (long)delphiz;
	
			
}
