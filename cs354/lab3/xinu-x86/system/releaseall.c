/*	releaseall.c - releaseall	*/
#include <xinu.h>
#include <stdarg.h>
/* Lab 3: Complete this function */

syscall releaseall (int32 numlocks, ...) {

	//your implementation goes here
  intmask mask;
  va_list ap;
  va_start(ap, numlocks);
  int ldes = va_arg(ap, int);
  mask = disable();
  for(int i = 1; i < numlocks; i++) {
    struct lockent *lptr = &locktab[ldes];

    int lock = queuetab[lptr->queuehead].qnext;
    if(queuetab[lock].qtype == READER) {
      lptr->rcount++;
    }
    else if(queuetab[lock].qtype == WRITER) {
      lptr->wcount++;
    }
    dequeue(lock);
    ready(lock);

    ldes = va_arg(ap, int);
  }

  restore(mask);
	return OK;
}
