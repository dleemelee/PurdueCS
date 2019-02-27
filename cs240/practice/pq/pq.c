#include <stdlib.h>
#include <stdio.h>

typedef struct item{
    int value;
    int priority;
}item_t;

typedef struct priority_queue{
    item_t ** queue;
    int head;
    int num_elements;
    int max_size;
}priority_queue_t;

priority_queue_t * newQ(int max_size) {
    priority_queue_t * q = (priority_queue_t*)malloc(sizeof(priority_queue_t));
    q->queue = (item_t**)malloc(max_size*sizeof(item_t*));
    q->head = -1;
    q->num_elements = 0;
    q->max_size = max_size;
    return q;
}

int getHead(priority_queue_t * q) {
    int i, maxIndex, max = -1;
    for(i = 0; i < q->max_size-1; i++){
	if(q->queue[i] != NULL){
	    int temp = q->queue[i]->priority;
	    if(temp > max){
		max = temp;
		maxIndex = i;
	    }
	}
    }
    return maxIndex;
}

int enqueue(priority_queue_t * q, int value, int priority) {
    if(q->num_elements > q->max_size ){
	return -1;
    }
    int i = 0;
    for(i = 0; i < q->max_size; i++) {
	if(q->queue[i] == NULL) {
	    q->queue[i] = (item_t*)malloc(sizeof(item_t));
	    if(q->queue[i] == NULL) {
		return -1;
	    }
	    q->queue[i]->value = value;
	    q->queue[i]->priority = priority;
	    q->num_elements++;
	    q->head = getHead(q);
	    return 0;
	}
    }
    return 0;
}

int dequeue(priority_queue_t * q){
    if(q->num_elements == 0){
	return 0;
    }
    int highest = getHead(q);
    int val = q->queue[highest]->value;
    free(q->queue[highest]);
    q->num_elements--;
    q->head = getHead(q);
    return val;
}

int main(){
    priority_queue_t* q = newQ(10);
    enqueue(q, 1, 1);
    enqueue(q,20,5);
    enqueue(q,30 ,3);
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    printf("%d\n", dequeue(q));
    free(q);
    return 0;
}
