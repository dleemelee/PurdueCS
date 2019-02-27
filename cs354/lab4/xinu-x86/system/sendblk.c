/* sendblk.c - sendblk */

#include <xinu.h>

/*-----------------------------------------------------------------------
 * sendblk  -  Pass a message to a process and start recipient if waiting
 *-----------------------------------------------------------------------
 */

syscall sendblk(
    pid32   pid,
    umsg32  msg
  ) 
{
  intmask mask;
  struct procent *prptr;
  mask = disable();

  if( isbadpid(pid)) {
    restore(mask);
    return SYSERR;
  }

  prptr = &proctab[pid];
  if(prptr->prstate == PR_FREE) {
    restore(mask);
    return SYSERR;
  }
  if(prptr->prhasmsg == TRUE) {
    //TODO LAB4
    enqueue(currpid, prptr->sendqueue);
    proctab[currpid].prstate = PR_SNDBLK;
    proctab[currpid].sendblkmsg = msg;
    proctab[currpid].sendblkrcp = pid;
    prptr->rcpblkflag++;
    
    resched(); //block and context switch until msg sent?
  }
  else {
    prptr->prhasmsg = TRUE;
    /*
    if(prptr->prhascb == TRUE) {
      kprintf("YELLO\n");
      kprintf("HAHA: %d, %d, %d", TRUE,FALSE, prptr->running);
      kprintf("DONE\n");
      if(prptr->running == FALSE) {
        prptr->running = TRUE;
        kprintf("a\n");
        enable();
        kprintf("b\n");
        prptr->fptr();
        kprintf("c\n");
        mask = disable();
        kprintf("d\n");
        prptr->running = FALSE;

      }
    }
    */ 
  } 
  prptr->prmsg = msg;

  if(prptr->prstate == PR_RECV) {
    ready(pid);
  }
  else if(prptr->prstate == PR_RECTIM) {
    unsleep(pid);
    ready(pid);
  }

  restore(mask);
  return OK;

}
