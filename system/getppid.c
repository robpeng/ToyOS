#include <master.h>
pid32 getppid(pid32 process) {
	if (process < 0 || process >= NPROC) {
		return SYSERR;
	}
	if (proctab[process].prstate == PR_FREE) {
		return SYSERR;
	}
	if (process == 0) {
		return 0;
	}
	return proctab[process].prparent;		
}
