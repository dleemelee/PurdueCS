#include <stdlib.h>
#include <stdio.h>

typedef struct item{
    int value;
}item_t;

typedef struct fifo_queue{
    item_t** queue;
    int head;
    int tail;
    int max_size;
}fifo_queue_t;

fifo_queue_t* createQueue(int size) {
    fifo_queue_t *Q;
    Q = (fifo_queue_t *)malloc(sizeof(fifo_queue_t));
    if(Q == NULL){
	return NULL;
    }
    item_t** x = (item_t**)malloc(size * sizeof(item_t*));
    Q->queue = x;
    Q->max_size = size;
    Q->head = 0;
    Q->tail = 0;
    return Q;
}


int enqueue(fifo_queue_t * q, int value){
    q->queue[q->tail] = (item_t*)malloc(sizeof(item_t));
    q->queue[q->tail]->value = value;
    q->tail++;
    return 0;
}

int dequeue(fifo_queue_t *q){
    int value = q->queue[q->head]->value;
    free(q->queue[q->head]);
    q->head++;
    return value;
}


int main() {
    fifo_queue_t* Q = createQueue(5);
    enqueue(Q, 6);
    enqueue(Q, 5);
    printf("%d\n", dequeue(Q));
    printf("%d\n", dequeue(Q));
    free(Q);
    return 0;
}
