/*	lcreate.c - lcreate	*/
#include <xinu.h>

/* Lab 3: Complete this function */



local int32 newlock(void);

int32 lcreate() {
  intmask  mask;
  int32 ldes;

  mask = disable();

  if(((ldes=newlock())==SYSERR)) {
    restore(mask);
    return SYSERR;
  }

  restore(mask);
  return ldes;
}

local int32 newlock() {
  static int32 nextlock = 0;
  int32 ldes = 0;
  int i;

  for(i = 0; i < NLOCKS; i++) {
    ldes = nextlock++;
    if(nextlock >= NLOCKS) {
      nextlock = 0;
    }
    if(locktab[ldes].lstate == L_FREE) {
      locktab[ldes].lstate = L_LOCK;
      return ldes;
    }

  }
  return SYSERR;
}
