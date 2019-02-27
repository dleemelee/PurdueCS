#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 *  This function returns the next word in the string *cptr.
 *  When the *cptr reaches the NULL character '\0', 
 *  the function returns NULL.
 *
 *  The returned memory space is allocated (malloc) by this function.
 *  For example, if *cptr is "abc def", you should allocate a memory space,
 *  copy the string "abc" to it, and return it.
 *  It is the caller's responsibility to free the space.
 *
 *  In addition, you have to update *cptr to point to the space that
 *  have not been parsed. 
 *  For example, if *cptr is "abc def", you should update
 *  the *cptr to point to the space character between "abc" and "def".
 *
 */



char *nextword(char **cptr)
{
    char x = ' ';
    char* newWord = (char*)malloc(10);
    int i = 0;
    if(**cptr == ' ') {
	while(**cptr == ' '){
	    (*cptr)++;
	}
    }
    if(**cptr == '\0') {
	return NULL;
    }
    while( x != '\0' )
    {
        x = **cptr;
	if(x == ' '|| x== '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r'||x == '\0')
	{
	    if(**cptr == '\0'){
		return newWord;
	    }
   	    return newWord;
	}
	else{
	    *(newWord+i) = x;
	    i++;
	    (*cptr)++;
	}
    }
    return NULL;
}

/*
 *  Do NOT change any of the lines between here and the end of the file
 */ 

int main(int argc, char *argv[])
{
    char *word = NULL;
    unsigned int count = 0;
    char *usage = "Usage: nextword \"string\"\n";
    char *cptr = NULL;

    if (argc != 2) {
        printf("%s", usage);
        exit(1);
    }

    cptr = argv[1];
    while( (word =  nextword(&cptr)) != NULL) {
        printf("%d: \"%s\" | \"%s\"\n", count++, word, cptr);
        free(word);
    }
    
    return 0;
}

