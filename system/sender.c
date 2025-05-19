/* for sending process, which simply sends a message */
#include <master.h>
extern  unsigned int clkcounterfine; 
void sender(pid32 pid, umsg32 message) {
	send(pid, message);
	kprintf("send %d %d %d\n", getpid(), clkcounterfine, message);
}
