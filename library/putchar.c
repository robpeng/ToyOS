/* putchar.c - putchar */

#include <master.h>
#include <stdio.h>

/*
 *  putchar  -  C putchar function
 */
int	putchar(
	  int		c
	)
{
    return fputc(c, stdout);
}
