/*  lock.h	*/


// declare variables, #defines, 
#define L_FREE  0
#define L_LOCK  1
#define READER  0
#define WRITER  1


struct	lockent {
  
	//struct members
  int lstate; //state of lock
  int queuehead; //queue of lock
  int queuetail;
  int rcount; //number of readers
  int wcount; //number of writers
  int ltype; //type of lock READER/WRITER
  //pid32 plocked[NPROC];
  
};

/* Lab 3 lock table */

extern struct lockent locktab[];

