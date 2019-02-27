/* cbreg.c - cbreg */

#include <xinu.h>

syscall cbreg(
    int ( * fnp) (void)
  )
{
  int mask = disable();
  if(proctab[currpid].prhascb == TRUE) {
    restore(mask);
    return SYSERR;
  }
  proctab[currpid].fptr = fnp;
  proctab[currpid].prhascb = TRUE; 
  restore(mask);
  return OK;
}
