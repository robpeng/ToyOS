
#include<kernel.h>

struct perprocmem {
	uint32 memsize;
	char * memptr;
	struct perprocmem * memnext;
};
