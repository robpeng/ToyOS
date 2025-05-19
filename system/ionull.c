/* ionull.c - ionull */

#include <master.h>

/*
 *  ionull  -  Do nothing (used for "don't care" entries in devtab)
 */
devcall	ionull(void)
{
	return OK;
}
