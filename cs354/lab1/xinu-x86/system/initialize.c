/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
extern	void xdone(void);	/* System "shutdown" procedure		*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
process scheduler_daemon();
int count_queue(qid16 q);
syscall system(pid32 p);

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */
		
	sysinit();

	kprintf("\n\r%s\n\n\r", VERSION);
	
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\r\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */

	enable();
  kprintf("HELLO");
  /* Create Scheduling Daemon Process */
  resume (
    system(create(scheduler_daemon, INITSTK, 0, "SDaemon", 0 
      ))
           );

	/* Create a process to execute function main() */

	resume (
	   create((void *)main, INITSTK, 0, "Main process", 0,
           NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
		;		/* Do nothing */
	}

}

process scheduler_daemon() {
  struct procent *prptr;
  int i;
  //kprintf("RUNNING\n");
  //calculate aveload
  int time = 0;
  int inst_loads[60];
  for(time = 0; time < 60; time++) {
    inst_loads[time] = 0;
  }
  time = 0;
  int sumload = 0;
  int aveload;
  while(1) {
    int mask = disable(); 
    if(time >= 60 ) {
      sumload-=inst_loads[(time)%60];
    }
    inst_loads[time%60] = count_queue(readylist);
    sumload+=inst_loads[time%60];
    if(time < 60)
      aveload = sumload/(time+1);
    else {
      aveload = sumload/60;
    }
    //iterate through processes
    for(i = 0; i < NPROC; i++) {
      prptr = &proctab[i];
      prptr->prrecent = (aveload * prptr->prrecent)/((2*aveload) + 1) + prptr->prextprio;
      prptr->prprio = prptr->prbaseprio + (2*prptr->prextprio) + prptr->prrecent;
      prptr->prquantum = QUANTUM + prptr->prrecent;
    }
    time++; //increment time for aveload
    restore(mask);
    sleep(1); 
  }
}

int count_queue(qid16 q) {
  int count = 0;
  int16 curr = q;
  while(queuetab[curr].qnext != queuehead(q)) {
    curr = queuetab[curr].qnext;
    count++;
  }
  return count;
}

syscall system(pid32 p) {
  if(proctab[p].prbaseprio == 50) {
    proctab[p].prbaseprio = 0;
    proctab[p].prprio-=50;
    if(proctab[p].prprio < 0) {
      proctab[p].prprio = 0;
    }
    //resched();
  }
}

/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
    //Lab 2 Variables initialize
    prptr->prbaseprio = 0;
    prptr->prextprio = 0;
    prptr->prrecent = 0;
    prptr->prquantum = 0;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;
  //Lab2 nullprocess niitialize
  prptr->prrecent = 0;
  prptr->prbaseprio = 0;
  prptr->prquantum = 2;
  prptr->prprio = 128;
  
	
	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}
	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
