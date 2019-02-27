/*	ldelete.c - ldelete 	*/
#include <xinu.h>

/* Lab 3: Complete this function */

syscall ldelete( 
		int32 ldes	/* lock descriptor */
	)
{
	// your implementation
  intmask mask;
  struct lockent *lptr;
  
  mask = disable();

  if(ldes < 0 || ldes > NLOCKS) {
    restore(mask);
    return SYSERR;
  }
  
  lptr = &locktab[ldes];
  lptr->lstate = L_FREE;

  if(nonempty(lptr->queuehead)) {
    while( nonempty(lptr->queuehead) ) {
      pid32 pid = getfirst(lptr->queuehead);
      proctab[pid].lockdel = 1;
      ready(pid);
    }
    resched();
  }

  restore(mask);
	return OK;
}
