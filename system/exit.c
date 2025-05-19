/* exit.c - exit */

#include <master.h>

/*
 *  exit  -  Cause the calling process to exit
 */
void	exit(void)
{
	kill(getpid());		/* Kill the current process */
}
