// implemented the needarest function, which is used for testing

#include <master.h>

void needarest() {
	kprintf("Need a rest");
	sleepms(500);
	while(1) {
	kprintf("Rested and ready");
	}
}
