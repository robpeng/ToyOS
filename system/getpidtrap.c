#include <master.h>
/* wrapper for getpid using trap*/
getpidtrap() {
	int res = -1;
	asm volatile ("movl $20, %%edx\n\t"
         "int $35\n\t"
        "movl %%eax, %0"
        : "=r"(res));
	return res;
		
}
