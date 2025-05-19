// here is where I can register a callback function in the currently running process

#include <master.h>

int32 registercbk(void(*fcbk)(void)) {
	if (fcbk == NULL) {
		return SYSERR;
	}
	pid32 pid = getpid();
	if (proctab[pid].prasyncipc == 1) {
		return SYSERR;
	}
	proctab[pid].prasyncipc = 1;
	proctab[pid].prrecvcbk = fcbk;
	return OK;
}
