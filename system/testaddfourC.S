#include <icu.s>
	.text
	.globl testaddfourC
	
testaddfourC:
	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	pushl %edi
	pushl %esi
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl $2
	pushl $2
	pushl $3
	pushl $2
	call addfourC
	addl $16, %esp
	popl %edx
	popl %ecx
	addl $4, %esp
	popl %esi
	popl %edi
	popl %ebx
	popl %ebp
	ret


