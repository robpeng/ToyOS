/* getticks.c - getticks */

#include <master.h>

/*
 *  getticks  -  Retrieve the number of clock ticks since CPU reset
 */
uint64  	getticks()
{
	uint64 ret;
	asm volatile ( "rdtsc" : "=A"(ret) );
	return ret;
}
