/* getpid.c - getpid */

#include <master.h>

/*
 *  getpid  -  Return the ID of the currently executing process
 */
pid32	getpid(void)
{
	return (currpid);
}
