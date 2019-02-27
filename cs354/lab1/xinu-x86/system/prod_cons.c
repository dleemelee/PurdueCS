/*------------------------------------------------------------------------
 *  prod_cons.c  - implementation of the producer/consumer simulation
 *------------------------------------------------------------------------
 */

#include <xinu.h>
#include "prod_cons.h"

/* the global shared buffer that contains the data */
uint8 buffer[BUFFERSIZE];	

/* array to keep track of number of items produced by each producer */
int32 prod_item_count[NPRODUCERS]={0};	

/* 2D array to keep track of number of items consumed for each producer-consumer pair */
int32 cons_item_count[NCONSUMERS][NPRODUCERS]={{0}};  


/* insert other global variables here */

//semaphores
sid32 prod_sem;
sid32 cons_sem;
sid32 mutex; 

pid32 prod_pid[NPRODUCERS];
pid32 cons_pid[NCONSUMERS];

//buffer count
int buff_count_prod = 0;
int buff_count_cons = 0;

/*------------------------------------------------------------------------
 * Function used by producer to insert item into buffer
 *------------------------------------------------------------------------
 */
void insert_buffer(uint8 item)
{
  //kprintf("C");
  wait(mutex);
  buffer[buff_count_prod++] = item;
  if(buff_count_prod >= BUFFERSIZE) {
    buff_count_prod = 0;
  }
  signal(mutex);
} /* insert_buffer */

/*------------------------------------------------------------------------
 * Function used by consumer to remove an item from buffer
 *------------------------------------------------------------------------
 */
uint8 remove_buffer()
{
  //kprintf("D");
  wait(mutex);
  uint8 ret = buffer[buff_count_cons++];
  if(buff_count_cons >= BUFFERSIZE) {
    buff_count_cons = 0;
  }
  signal(mutex);
  return ret;
} /* remove_buffer */

/*------------------------------------------------------------------------
 * Function to implement producer process. It has the following parameters:
 * producer_tag: a label that consists of a single character used to 
 * label items produced and in the output is used to identify the producer.
 * prod_count: An integer that specifies the number of items to 
 * insert during each time interval.
 * prod_sleep_time: An integer that specifies the number of milliseconds 
 * to delay between each interval.
 *------------------------------------------------------------------------
 */
void producer(uint8 producer_tag, int32 prod_count, int32 prod_sleep_time)
{
  int k = 0;
  //kprintf("A\n");
  for(k = 0; k < NPRODUCERS; k++) {
    //kprintf("%c, %c\n", producer_tag, producer_tags[k]);
    if(producer_tag == producer_tags[k]) {
      break;
    }
  }
  //kprintf("%d",k);
  int i = 0;
  while(1) {
    wait(prod_sem);
    //signal(cons_sem);
    insert_buffer(k);
    i++;
    prod_item_count[k]++;
  signal(cons_sem);
    if(i == prod_count) {
      i = 0;
      sleepms(prod_sleep_time);
    }
  }
} /* producer */

/*------------------------------------------------------------------------
 * Function to implement consumer process. It has the following parameters:
 * consumer_tag: a label that consists of a single character and is used in 
 * the output to identify the consumer.
 * cons_count: An integer that specifies the number of items to extract 
 * during each time interval.
 * cons_sleep_time: An integer that specifies the number of milliseconds 
 * to delay between each interval.
 *------------------------------------------------------------------------
 */
void consumer(uint8 consumer_tag, int32 cons_count, int32 cons_sleep_time)
{
  //kprintf("B\n");
  int i;
  int j = 0;
  for(j = 0; j < NCONSUMERS; j++) {
    if(consumer_tag == consumer_tags[j]) {
      break;
    }
  }
  i=0;
  //kprintf("%d",j);
  while(1){
    //kprintf("A");
    wait(cons_sem);
    //kprintf("B");
    cons_item_count[j][remove_buffer()]++;
    i++;
    signal(prod_sem);
    if(i == cons_count) {
      i = 0;
      sleepms(cons_sleep_time);
    }
  }
} /* consumer */


/*------------------------------------------------------------------------
 *  start_prod_con  -  Initializes and starts the producer/consumer
 *                           simulation
 *------------------------------------------------------------------------
 */
void start_prod_con(void)
{
  prod_sem = semcreate(BUFFERSIZE);
  cons_sem = semcreate(0);
  mutex  = semcreate(1);
  int i;
  for(i = 0; i < NPRODUCERS; i++) {
    prod_pid[i] = create(producer,1024,20,"producer",3,producer_tags[i], producer_counts[i],producer_sleep_times[i] );
    resume(prod_pid[i]);
  }
  
  for(i = 0; i < NCONSUMERS; i++) {
    cons_pid[i] = create(consumer,1024,20,"consumer",3, consumer_tags[i],consumer_counts[i], 100);
    resume(cons_pid[i]);
  }
} /* start_prod_con */

/*------------------------------------------------------------------------
 *  stop_prod_con  -  Stops the currently executing producer/consumer
 *                           simulation
 *------------------------------------------------------------------------
 */
void stop_prod_con(void)
{
  int i = 0;
  for(i = 0; i < NPRODUCERS; i++) {
    kill(prod_pid[i]);
  }
  
  for(i = 0; i < NCONSUMERS; i++) {
    kill(cons_pid[i]);
  }
  semdelete(prod_sem);
  semdelete(cons_sem);
  semdelete(mutex);
} /* stop_prod_con */

/*------------------------------------------------------------------------
 *  print_report  -  Prints the final report for the producer/consumer
 *                           simulation
 *------------------------------------------------------------------------
 */
void print_report(void)
{
  kprintf("\n");
  int i;
  int j;
  for(i = 0; i < NPRODUCERS; i++) {
    kprintf("Producer %c: Created %d items\n", producer_tags[i], prod_item_count[i]); 
  }
  for(i = 0; i < NCONSUMERS; i++) {
    kprintf("Consumer %c:", consumer_tags[i]);
    for(j = 0; j < NPRODUCERS; j++) {
      kprintf(" deleted %d items from producer %c,", cons_item_count[i][j], producer_tags[j]);
    }
    kprintf("\n");
  }
} /* print_report */

