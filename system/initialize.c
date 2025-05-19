/* initialize.c - nulluser, sysinit */

/* Handle system initialization and become the null process */

#include <master.h>
#include <string.h>

int invalopcode = 0;
uint32 currcputime = 0;
uint16 quantumts = QUANTUM;
struct xst xstds[8];
uint16 kheapflag = 0;

extern	void	start(void);	/* Start of code			*/
extern	void	*_end;		/* End of code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
local	process startup(void);	/* Process to finish startup tasks	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

/* Control sequence to reset the console colors and cusor positiion	*/

#define	CONSOLE_RESET	" \033[0m\033[2J\033[;H"

/*
 * nulluser - initialize the system and become the null process
 */
void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */

	sysinit();

	/* Output memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */

	enable();

        
	///* Initialize the network stack and start processes */

	//net_init();

	/* Create a process to finish startup and start main */

	resume(creates((void *)startup, INITSTK, INITPRIO,
					"Startup process", 0, NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
		;		/* Do nothing */
	}

}


/*
 * startup  -  Finish startup takss that cannot be run from the Null
 *		  process and then create and resumethe main process
 */
local process	startup(void)
{

	/* Create a process to execute function main() */
	kprintf("Peng,Robert\n");
	resume(creates((void *)main, INITSTK, 25,
					"Main process", 0, NULL));

	/* Startup process exits at this point */

	return OK;
}


/*sysinit  -  Initialize all data structures and devices
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Reset the console */

	kprintf(CONSOLE_RESET);
	kprintf("\n%s\n\n", VERSION);

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;
	
	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}
	xstds[0].xstslpret = 0;
	xstds[0].xstqexp = 0;
    	xstds[0].xstquantum = QUANTUM;
    	xstds[1].xstslpret = 2;
    	xstds[1].xstqexp = 1;
    	xstds[1].xstquantum = 70;
    	xstds[2].xstslpret = 3;
    	xstds[2].xstqexp = 1;
    	xstds[2].xstquantum = 60;
    	xstds[3].xstslpret = 4;
    	xstds[3].xstqexp = 2;
    	xstds[3].xstquantum = 50;
    	xstds[4].xstslpret = 5;
    	xstds[4].xstqexp = 3;
    	xstds[4].xstquantum = 40;
    	xstds[5].xstslpret = 6;
    	xstds[5].xstqexp = 4;
    	xstds[5].xstquantum = 30;
    	xstds[6].xstslpret = 7;
    	xstds[6].xstqexp = 5;
    	xstds[6].xstquantum = 20;
    	xstds[7].xstslpret = 7;
    	xstds[7].xstqexp = 6;
    	xstds[7].xstquantum = 10;

	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
