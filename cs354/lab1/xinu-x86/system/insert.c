/* insert.c - insert */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insert  -  Insert a process into a queue in descending key order
 *------------------------------------------------------------------------
 */
status	insert(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Key for the inserted process	*/
	)
{
	int16	curr;			/* Runs through items in a queue*/
	int16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}
  kprintf("%s\n", proctab[pid].prname); 
  kprintf("%d, %d, %d\n", pid, q, key);
  /*qid16 it = firstid(q);
  while(queuetab[it].qkey >=key ) {
    kprintf("hello%d\n", queuetab[it].qkey);
    it = queuetab[it].qnext;
  }
  kprintf("%d, %d\n", queuetab[it].qkey, key);*/
	curr = firstid(q);
	while (queuetab[curr].qkey < key) {
		curr = queuetab[curr].qnext;
	}
	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}
