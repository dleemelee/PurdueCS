#include <stdio.h>
#include "hashtable.h"
#include "linkedlist.h"
#include <ctype.h>

int countCharacters(FILE *fd){
    char c;int count = 0;
    while((c = fgetc(fd))!= EOF){
	count++;
    }
    return count;
}

hashtable_t *read_accounts(FILE *fd){
    if(fd == NULL){
	return NULL;
    }
    hashtable_t *table = create_hashtable(5);
    char* temp1, temp2;
    char *line = (char*)malloc(sizeof(char)*100);
    while(fgets(line,countCharacters(fd) ,fd)){
	temp1 = strtok(line, " ");
	temp2 = strtok()
    }

}

