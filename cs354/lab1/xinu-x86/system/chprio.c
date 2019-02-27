/* chprio.c - chprio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  chprio  -  Change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
pri16	chprio(
	  pid32		pid,		/* ID of process to change	*/
	  pri16		newprio		/* New priority			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	pri16	oldprio;		/* Priority to return		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return (pri16) SYSERR;
	}
  if(newprio > 20) {
    newprio = 20;
  }
  else if(newprio < -20) {
    newprio = -20;
  }
	prptr = &proctab[pid];
	oldprio = prptr->prextprio;
	prptr->prextprio = newprio;
  prptr->prprio = prptr->prprio - oldprio + newprio;
  resched();
	restore(mask);
	return oldprio;
}
