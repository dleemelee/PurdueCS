/*	linit.c	- linit	initialize lock system */
#include <xinu.h>

/* Lab 3: Complete this function */

// declare any global variables here

struct lockent locktab[NLOCKS];

void linit(void) {
  
	// your implementation goes here
        // make sure to call this in initialize.c

  struct lockent* lptr;
  int i;

  for(i = 0; i < NLOCKS; i++) {
    lptr = &locktab[i];
    lptr->lstate = L_FREE;
    lptr->queuehead = newqueue();
    //lptr->queuetail = lptr->queuehead+1;
    lptr->rcount = 0;
    lptr->wcount = 0;
    lptr->ltype = -1;
  }
}
