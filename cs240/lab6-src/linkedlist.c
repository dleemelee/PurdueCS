#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedlist.h"

/*
 * just in case i need to implement this
typedef struct node {
    struct node *next;
    struct node *prev;

    long int timestamp;
    short transaction_type;
    char *company1;
    char *company2;
    double value;
} node_t;
*/

linkedlist_t *create_linkedlist(){
    linkedlist_t *list = malloc(sizeof(linkedlist_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void free_linkedlist(linkedlist_t* list){
    node_t* node  = list->head;
    while(node != NULL){
    	node_t* nextNode = node->next;
	delete_node(node);
	node = nextNode;
    }
    free(list);
}

int add_node(linkedlist_t *list, node_t *node){
    if(list == NULL || node == NULL) {
	return -1;
    }
    if(list->head == NULL) {
	list->head = node;
	if(list->tail == NULL) {
	    list->tail = node;
	    return 0;
	}
    }
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
    return 0;
}

int remove_node(linkedlist_t *list, node_t *node){
   if(list == NULL || node == NULL) {
	return -1;
   }
   if(list->head == list->tail){
   	list->tail = NULL;
	list->head = NULL;
	return 0;
   }
   if(list->head == node){
	list->head->next->prev = NULL;
	list->head = list->head->next;
	return 0;
   }
   if(list->tail == node){
	list->tail->prev->next = NULL;
	list->tail = list->tail->prev;
	return 0;
   }
   node_t *currNode = list->head;
   while(currNode != NULL) {
	if(node == currNode){
	    node_t *prevNode = currNode->prev;
	    node_t *nextNode = currNode->next;
	    prevNode->next = nextNode;
	    nextNode->prev = prevNode;
	    return 0;
	}
	currNode = currNode->next;
    }
    return -1;
}

node_t * create_node(long int timestamp, short transaction_type, const char *company1, const char *company2, double value) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node->prev = NULL;
    node->next = NULL;
    node->timestamp = timestamp;
    node->transaction_type = transaction_type;
    if(company1 == NULL) {
	node->company1 = NULL;
    }
    else{
	node->company1 = (char*)malloc(10*sizeof(char));
	strcpy(node->company1, company1);
    }
    if(company2 == NULL) {
	node->company2 = NULL;
    }
    else{
	node->company2 = (char*)malloc(10*sizeof(char));
	strcpy(node->company2, company2);
    }
    node->value = value;
    return node;
}

void delete_node(node_t *node){
    free(node->company1);
    free(node->company2);
    free(node);
}

node_t* find_node(linkedlist_t *list, long int timestamp) {
    if(list == NULL){
	return NULL;
    }
    node_t* node = list->head;
    while(node != NULL){
	if(node->timestamp == timestamp){
	    return node;
	}
	node = node->next;
    }
    return NULL;
}

void print_list(linkedlist_t *list) {
    node_t *node = list->head;
    while(node != NULL) {
	printf("%lf\n",node->value);
	node = node->next;
    }
}
/*
int main(){
    linkedlist_t *list = create_linkedlist();
    node_t* node1 = create_node(0,0,NULL,NULL,0);
    node_t* node2 = create_node(1,1,NULL,NULL,1);
    node_t* node3 = create_node(2,2,NULL,NULL,2);
    add_node(list, node1);
    add_node(list, node2);
    add_node(list, node3);
    print_list(list);
    printf("----------------------------------------------------1-------------------------------------------------\n");
    remove_node(list, node1);
    delete_node(node1);
    print_list(list);
    printf("-----------------------------------------------------2-----------------------------------------------\n");
    remove_node(list, node2);
    delete_node(node2);
    print_list(list);
    printf("---------------------------------------------------3------------------------------------------------\n");
    remove_node(list, node3);
    delete_node(node3);
    print_list(list);
    free_linkedlist(list);
    return 0;
}*/
