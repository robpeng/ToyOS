#include <master.h>
/* wrapper function for chprio using trap */
chpriotrap(pid32 pid, pri16 pri) {
	int res = -1;
	  asm volatile ("movl $22, %%edx\n\t"
          "pushw %2\n\t"
	  "pushl %1\n\t"
           "int $35\n\t"
          "addl $6, %%esp\n\t"
          "movl %%eax, %0"
          : "=r"(res)
          : "r"(pid), "r"(pri)
          :"edx");
	  return res;	
}
