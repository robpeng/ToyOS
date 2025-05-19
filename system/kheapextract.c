
#include<master.h>
extern uint16 kheapflag;
void kheapextract(struct perprocmem * ptr, char * memptr) {
	if (ptr  == NULL) {
		return;
	}
	
	struct perprocmem * curr = ptr;
	struct perprocmem * prev = NULL;
	while (curr != NULL && curr->memptr != memptr) {
		prev = curr;
		curr = curr->memnext;
	}	
	if (curr == NULL) {
		return;
	}
	if (prev == NULL) {
		proctab[getpid()].prheapbeg = curr->memnext;
		kheapflag = 1;
		freemem((char*)curr, sizeof(struct perprocmem));
		return;
	}	
	prev->memnext = curr->memnext;
	kheapflag = 1;
	freemem((char*)curr, sizeof(struct perprocmem));
	return;
}
