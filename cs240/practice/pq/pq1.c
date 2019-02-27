#include <stdlib.h>
#include <stdio.h>

typedef struct item{
	int value;
	int priority;
} item_t;

typedef struct priority_queue{
	item_t ** queue;
	int head;
	int count;
	int maxSize;
}priority_queue_t;

void setHead(priority_queue_t* q){
	int max = -1;
	int maxIndex = -1;
	int i;
	for(i = 0; i< q->count; i++){
		if(q->queue[i] != NULL){
			if(q->queue[i]->priority >= max){
				max = q->queue[i]->priority;
				maxIndex = i;
			}
		}
	}

	q->head = maxIndex;

}

priority_queue_t* newQ(int size){
	priority_queue_t *Q;
	Q = (priority_queue_t*) malloc(sizeof(priority_queue_t));
	if(Q == NULL){
		return NULL;
	}
	item_t** X = (item_t**)malloc(size * sizeof(item_t));
	if(X == NULL){
		return NULL;
	}
	Q->queue = X;


	Q->maxSize = size;
	Q->head = -1;
	Q->count = 0;

	return Q;
}

int enqueue(priority_queue_t* q, int value, int priority){

	item_t* x = (item_t*) malloc (sizeof(item_t));

	if(x == NULL){
		return -1;
	}

	q->queue[q->count] = x;
	q->queue[q->count]->value = value;
	q->queue[q->count]->priority = priority;

	q->count++;

	setHead(q);

	return 0;
}

int dequeue(priority_queue_t* q){

	// IF Queue is empty, so nothing to pop, return 0;
	if(q->head == -1){
		printf("EMPTY POP.\n");
		return 0;
	}
	setHead(q);
	int x = q->queue[q->head]->value;
	free(q->queue[q->head]);
	q->queue[q->head] = NULL;
	q->count--;


	setHead(q);

	printf("POP:%d\n",x);

	return x;
}


int main(){
	priority_queue_t* Q = newQ(2);


	enqueue(Q,1111,7);
	enqueue(Q,2222,9);
	enqueue(Q,3333,8);
	dequeue(Q);
	dequeue(Q);


	free(Q);
	return 0;
}
