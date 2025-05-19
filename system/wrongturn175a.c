//found sleeps return address through the ebps, and modified that ret address

#include <master.h>

void wrongturn175a(pid32 traveler) {
	if (traveler < 0 || traveler >= NPROC) {
               return;
       }
       if (proctab[traveler].prstate == PR_FREE) {
               return;
       }
       uint32 * bebp = (uint32 *)((char*)proctab[traveler].prstkptr + 8);
       uint32 * tebpaddr = *(bebp);
       uint32 * reschedebpaddr = *(tebpaddr);
       uint32 * sleepebpadr = *(reschedebpaddr);
       long * ret = sleepebpadr + 1;
       *(ret) = (long)delphi;

}
