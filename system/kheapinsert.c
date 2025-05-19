
#include <master.h>
extern uint16 kheapflag;
void kheapinsert(struct perprocmem *ptr, char *memptr, uint32 msz) {
	kheapflag = 1;
	struct perprocmem * newBlock = (struct perprocmem *)getmem(sizeof(struct perprocmem));
	newBlock->memsize = msz;
	newBlock->memptr = memptr;
	if (ptr == NULL) {
		newBlock->memnext = NULL;
		proctab[getpid()].prheapbeg = newBlock;
		return;
	}
	struct perprocmem * curr = ptr;
	struct perprocmem * prev = NULL;
	while (curr != NULL && newBlock->memptr > curr->memptr) {
		prev = curr;
		curr = curr->memnext;
	}	
	if (prev == NULL) {
		newBlock->memnext = ptr;
		proctab[getpid()].prheapbeg = newBlock;
		return;
	}
	if (curr == NULL) {
		prev->memnext = newBlock;
		newBlock->memnext = NULL;
		return;
	}
	newBlock->memnext = prev->memnext;
	prev->memnext = newBlock;
}
