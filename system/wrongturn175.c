// change the return address to delphi

#include <master.h>

void wrongturn175(pid32 traveler) {
	if (traveler < 0 || traveler >= NPROC) {
		return;
	}
	if (proctab[traveler].prstate == PR_FREE) {
		return;
	}
	uint32 * bebp = (uint32 *)((char*)proctab[traveler].prstkptr + 8);
	uint32 * tebpaddr = *(bebp);
	long * ret = tebpaddr + 1;
	*(ret) = (long)delphi;
} 
