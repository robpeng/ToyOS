#include <master.h>
/* ppid wrapper using trap */

getppidtrap(pid32 pid) {
	int res = -1;
	asm volatile ("movl $21, %%edx\n\t" 
		//"movl %1, %%ecx\n\t" 
		//"pushl %%ecx\n\t"
		"pushl %1\n\t"
		 "int $35\n\t"
		"addl $4, %%esp\n\t" 
		"movl %%eax, %0"
		: "=r"(res)
		: "r"(pid)
		:"edx", "ecx");
	return res;
}
