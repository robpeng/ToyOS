/* used for detour */
	.text
	.globl managedetour

managedetour:
	 lea proctab, %ecx;
	 movl currpid , %eax
	 movl $68, %edx
	 imul %edx, %eax
	 addl %eax, %ecx;
	 movl (%ecx), %eax;
	 pushl %eax;
	 pushl %ebp
	 movl %esp, %ebp
	 addl $4, %ecx;
	 call (%ecx)
	 popl %ebp;
	 ret;
	 
	
		
	
