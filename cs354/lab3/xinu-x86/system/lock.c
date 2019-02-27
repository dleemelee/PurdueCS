/*	lock.c - lock */
#include <xinu.h>

/* Lab 3: Complete this function */

syscall lock(int32 ldes, int32 type, int32 lpriority) {

        //your implementation goes here
	//most of the logic can be implemented here
	//consider different cases as mentioned in the handout
  intmask mask;
  mask = disable();
  struct lockent *lptr;
  struct procent *prptr;
  int wait = 0;
  lptr = &locktab[ldes];
  if( ldes < 0 || ldes > NLOCKS || lptr->lstate == L_FREE ) {
    restore(mask);
    return SYSERR;
  }

  if(lptr->rcount == 0 && lptr->wcount == 0) {
    wait = 0;
  }
  else if( ( lptr->rcount == 0 && lptr->wcount != 0) ||
              (lptr->rcount != 0 && lptr->wcount == 0 && lptr->ltype == WRITER) ) {
    wait = 1;
  }
  else if(lptr->rcount != 0 && lptr->wcount == 0 && lptr->ltype == READER) {
    int curr = queuetab[lptr->queuehead].qnext;
    while(lpriority < queuetab[curr].qkey) {
      if(queuetab[curr].qtype == WRITER) {
        wait = 1;
      }
      curr = queuetab[curr].qnext;
    }
  }
  
  if(wait) {
    prptr = &proctab[currpid];
    prptr->prstate = PR_LWAIT;
    
    insert(currpid, lptr->queuehead, lpriority);
    
    queuetab[currpid].qtype = type;
    
    resched();
    restore(mask);
    if(prptr->lockdel = 0) {
      return OK;
    }
    else{
      return DELETED;
    }
  }

  if(type == READER) {
    lptr->rcount++;
  }
  else {
    lptr->wcount++;
  }
	return OK;
}
