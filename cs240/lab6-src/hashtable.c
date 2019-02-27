#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

hashtable_t *create_hashtable(int max_size) {
    int i;
    if(max_size <= 0){
	return NULL;
    }
    hashtable_t *newhash = (hashtable_t*)malloc(sizeof(hashtable_t));
    newhash->table = (hashtable_ent_t**)malloc(sizeof(hashtable_ent_t*)*max_size);
    for(i = 0; i < max_size; i++){
	newhash->table[i] = NULL;
    }
    newhash->table_len = max_size;
    return newhash;
}

void free_hashtable(hashtable_t *table){
    int i;hashtable_ent_t* currHash;
    struct hashtable_ent* nextHash;
    for(i = 0; i < table->table_len; i++){
	if(table->table[i]!=NULL){
	    currHash = table->table[i];
	    while(currHash != NULL){
	        nextHash = currHash->next;
		free(currHash->key);
	        free(currHash);
		currHash = nextHash;
	    }
	}
    }
    free(table->table);
    free(table);
}

int get(hashtable_t *table, const char *key, double *value){
    if(table == NULL || key == NULL || value == NULL){
	return -1;
    }
    hashtable_ent_t* currPair; int hashVal = hash(key)%table->table_len;
    currPair = table->table[hashVal];
    while(currPair!=NULL){
	if(strcmp(currPair->key, key) == 0){
	    *value = currPair->value;
	    return 0;
	}
	currPair = currPair->next;
    }
    return -1;
}

int set(hashtable_t *table, const char *key, double value){
    int hashVal = hash(key)%table->table_len;
    hashtable_ent_t *currNode;
    if(key_exists(table, key) == 1) {
	currNode = table->table[hashVal];
	while(currNode != NULL){
	    if(strcmp(currNode->key, key) == 0){
		currNode->value = value;
		return 0;
	    }
	    currNode = currNode->next;
	}
    }
    else{
        currNode = table->table[hashVal];
	if(currNode == NULL){
	    table->table[hashVal] = (struct hashtable_ent*)malloc(sizeof(struct hashtable_ent));
	    table->table[hashVal]->next = NULL;
	    table->table[hashVal]->value = value;
	    table->table[hashVal]->key = (char*)malloc(sizeof(char)*20);
	    strcpy(table->table[hashVal]->key, key);
	}
	else{
	    while(currNode != NULL) {
	        if(currNode-> next == NULL) {
		    currNode->next = (struct hashtable_ent*)malloc(sizeof(struct hashtable_ent));
		    currNode->next->value = value;
		    currNode->next->key = (char*)malloc(sizeof(char)*20);
		    strcpy(currNode->next->key, key);
		    currNode->next->next = NULL;
		    return 0;
	        }
	        currNode = currNode->next;
	    }
	}
    }
    return -1;
}

int key_exists(hashtable_t *table, const char *key){
    if(table == NULL || key == NULL) {
	return -1;
    }
    int hashVal = hash(key)%table->table_len;
    hashtable_ent_t *currNode = table->table[hashVal];
    while(currNode != NULL){
	if(strcmp(currNode->key,key) == 0){
	    return 1;
	}
	currNode = currNode->next;
    }
    return 0;
}

int remove_key(hashtable_t *table, const char *key){
    if(key_exists(table, key) == 0){
	return -1;
    }
    if(table == NULL || key == NULL){
	return -1;
    }
    int hashVal = hash(key)%table->table_len;
    hashtable_ent_t *currNode = table->table[hashVal];
    if(strcmp(currNode->key, key) == 0){
	free(currNode->key);
	table->table[hashVal] = currNode->next;
	free(currNode);
	return 0;
    }
    while(currNode->next != NULL) {
        if(strcmp(currNode->next->key, key) == 0){
	    struct hashtable_ent *tempNode = currNode->next->next;
	    free(currNode->next->key);
	    free(currNode->next);
	    currNode->next = tempNode;
	    return 0;
	}
	currNode = currNode->next;
    }
    return -1;
}

void print_table(hashtable_t *table){
    hashtable_ent_t *currNode;
    int i;
    for(i = 0; i < table->table_len; i++){
        printf("HASH = %d ---", i);
        currNode = table->table[i];
	while(currNode!=NULL){
	    printf(" %lf ---", currNode->value);
	    currNode = currNode->next;
	}
	printf("\n");
    }
}
/*
int main(){
    hashtable_t* table = create_hashtable(5);
    set(table, "asdf", 1);
    set(table, "adsflkj", 2);
    set(table, "afdsa", 3);
    set(table, "afd", 4);
    set(table, "awrqr", 5);
    set(table, "aetwrqe", 6);
    print_list(table);
    free_hashtable(table);
    
    return 0;
}
*/
