

#include <master.h>

extern unsigned int clkcounterfine;

syscall alarm(uint32 alarmmsec, void (* cbf) (void)) {
	if (alarmmsec == 0) {
		return SYSERR;
	}		
	if (alarmmsec > 15000) {
		return SYSERR;
	}
	if (cbf == NULL) {
		return SYSERR;
	}
	if (!(((uint32)&text <=  (uint32)cbf) && ((uint32)cbf <= (uint32)&etext))) {
		return SYSERR;
	}
	if (proctab[getpid()].pralrmcounter != 0) {
		return SYSERR;
	}
	proctab[getpid()].prcbf = cbf;
	proctab[getpid()].pralrmcounter = clkcounterfine + alarmmsec;
	return OK;
}
