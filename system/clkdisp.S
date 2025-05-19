/* clkdisp.s - clkdisp (x86) */

/*
 * clkdisp  -  Interrupt dispatcher for clock interrupts (x86 version)
 */
#include <icu.s>
		.text
		.globl	clkdisp		# Clock interrupt dispatcher
clkdisp:
		pushal			# Save registers
		cli			# Disable further interrupts
		movb	$EOI,%al	# Reset interrupt
		outb	%al,$OCW1_2

		call	clkhandler	# Call high level handler
		mov clkcounterfine, %eax
		add $1, %eax
		mov %eax, clkcounterfine 		 		
		movl makedetouralrm, %eax
       		cmpl $0, %eax
       		je endops
      		movl $0, %eax
       		movl %eax, makedetouralrm
       		movl 36(%esp), %eax
       		movl %eax, -8(%esp)
       		movl 40(%esp), %eax
      		movl %eax, 36(%esp)
       		movl 32(%esp), %eax
       		movl %eax, 40(%esp)
       		movl 28(%esp), %eax
       		movl %eax, 32(%esp)
       		movl 24(%esp), %eax
       		movl %eax, 28(%esp)
       		movl 20(%esp),%eax
       		movl %eax,  24(%esp)
       		movl 16(%esp), %eax
       		movl %eax, 20(%esp)
       		movl 12(%esp),%eax
       		movl %eax,  16(%esp)
       		movl 8(%esp), %eax
      		movl %eax, 12(%esp)
       		movl 4(%esp),%eax
       		movl %eax,  8(%esp);
       		movl (%esp), %eax
       		movl %eax, 4(%esp)
       		lea restoreandret, %eax
		movl %eax, (%esp)
                pushl $512;
                subl $8, %esp
                lea proctab, %ecx;
                movl currpid , %eax
                movl $108, %edx
                imul %edx, %eax
                addl %eax, %ecx;
                movl (%ecx), %eax;
                movl %eax, (%esp)
                iret;


       endops: 
               sti                     # Restore interrupt status
               popal                   # Restore registers
               iret                    # Return from interrupt


       restoreandret:
               //sti; 
               popal;
               popfl;
               ret;
                                                                                      

