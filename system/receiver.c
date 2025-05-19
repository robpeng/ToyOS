
#include <master.h>
extern unsigned int clkcounterfine;
void msghandler() {
	kprintf("received %d %d %d\n\n", getpid(), clkcounterfine, proctab[getpid()].prmsg);
}

void receiver() {
	if (registercbk(&msghandler) != OK) {
		kprintf("register didn't work");
		exit();
	}
	kprintf("before sleep\n");
	sleepms(1000);
	while(1) {
		kprintf("correctly in receiver after sleep\n");
	}
}
