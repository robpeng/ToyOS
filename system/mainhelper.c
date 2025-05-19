/* used for testing */

#include <master.h>
void mainhelper() {
	pid32 x = create((void *)needarest, INITSTK, 2, "process 1", 0, NULL);
	resume(x);
	resume(create((void *)wrongturn175, INITSTK, 2, "process 1", 1, x));
	
	
}
