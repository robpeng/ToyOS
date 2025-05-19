/* getchar.c - getchar */

#include <master.h>
#include <stdio.h>

/*
 *  getchar  -  DOCUMENT
 */
int	getchar(
	  void
	)
{
    return fgetc(stdin);
}
