/* getmem.c - getmem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getmem  -  Allocate heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char  	*getmem_r(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*prev, *curr, *leftover;
  struct procent *prptr = &proctab[currpid];

	mask = disable();
	if (nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}
  uint32 truesize = nbytes;
	nbytes = (uint32) roundmb(nbytes) + ((uint32)roundmb(sizeof(struct memblk)));	/* Use memblk multiples	*/

	prev = &memlist;
	curr = memlist.mnext;
	while (curr != NULL) {			/* Search free list	*/

		if (curr->mlength == nbytes) {	/* Block is exact match	*/
			prev->mnext = curr->mnext;
			memlist.mlength -= nbytes;

      struct memblk *currblock = (struct memblk *)curr;
      currblock->mnext = prptr->prmem.mnext;
      prptr->prmem.mnext = curr;
      currblock->mlength = truesize;
      prptr->prmem.mlength = truesize;
			restore(mask);
			return (char *)((uint32)curr+((uint32)roundmb(sizeof(struct memblk))));

		} else if (curr->mlength > nbytes) { /* Split big block	*/
			leftover = (struct memblk *)((uint32) curr +
					nbytes);
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			memlist.mlength -= nbytes;

      struct memblk *currblock = (struct memblk *)curr;
      currblock->mnext = prptr->prmem.mnext;
      prptr->prmem.mnext = curr;
      currblock->mlength = truesize;
      prptr->prmem.mlength = truesize;

			restore(mask);
			return (char *)((uint32)curr+((uint32)roundmb(sizeof(struct memblk))));
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;
}

syscall r_mem_allocated(pid32 pid, uint32* buf) {

  struct procent *prptr = &proctab[pid];
  struct memblk *curr = prptr->prmem.mnext;
  uint32 count = 0;
  while(curr!=NULL) {
    count+=(curr->mlength);
    curr = curr->mnext;
  }
  
  *buf = count;
  return OK;

}
