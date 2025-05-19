#include <master.h>

suspendtrap(pid32 pid) {
	int res = -1;
	asm volatile ("movl $23, %%edx\n\t"
        "pushl %1\n\t"
         "int $35\n\t"
        "addl $4, %%esp\n\t"
        "movl %%eax, %0"
        : "=r"(res)
        : "r"(pid)
        :"edx", "ecx");
	return res;		
}
