/*  main.c  - main */
#include <master.h>

extern unsigned int clkcounterfine;
void sndB()
{
while( 1 )
kputc('B');
}
void sndA()
{
while( 1 )
kputc('A');
}

void sndC()
{
while( 1 )
kputc('C');
}

void sndD() {
	
}
process	main(void)
{
    
	//kprintf("%d", NPROC);
	//kprintf("%d", testaddfourC());
	/*
	int i = 0;
	for (; i < 10; i++) {
		kprintf("%d\n", create(sndD, 1024 , 20, "process 1", 0));
	}
	kprintf("%d\n", createminpid(sndD, 1024, 20, "process 2", 0));
	kprintf("%d\n", createminpid(sndD, 1024, 20, "process 3", 0));
	*/
	int i = 0;
	for (; i < 142000000; i++) {
		//kprintf("%d\n%d\n", clkcountefine, clktime);
	}
	kprintf("%d\n%d\n", clkcounterfine, clktime);

	return OK;
	
}
