/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receive(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
    //kprintf("Scheduling\n");
		resched();		/* Block until message arrives	*/
	}
  prptr->prhasmsg = FALSE;
  if(!isempty(prptr->sendqueue) && prptr->sendblkflag==TRUE) {
    pid32 sendpid = dequeue(prptr->sendqueue);
    prptr->rcpblkflag--;
    prptr->prhasmsg = TRUE;
    //kprintf("LOL: %d\n", prptr->rcpblkflag);
    if(!prptr->rcpblkflag) {
      prptr->prhasmsg = FALSE;
      resched();
    }
    ready(sendpid);
  }
  else if(!isempty(prptr->sendqueue) && prptr->sendblkflag == FALSE) {
    prptr->sendblkflag = TRUE;
    prptr->prhasmsg = TRUE;
    //prptr->rcpblkflag--;
  }

  msg = prptr->prmsg;
	restore(mask);
  //kprintf("RETURN\n");
	return msg;
}
