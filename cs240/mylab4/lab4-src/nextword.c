
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int lastword = 0;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c, pastword,j;
	while(1) {
		for(j = 0; j < wordLength; j++) {
			word[j] = '\0';
		}

		wordLength = 0;
		while((c=fgetc(fd))!=EOF)
		{
			assert(wordLength < MAXWORD);
			if( !isspace(c) ) {
				word[wordLength] = c;
				wordLength++;
				pastword = 0;
			}
			else if( !pastword ) 
			{
				pastword = 1;
				return word;
			}
		}
			return NULL;
		

		
	}
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// Include an assert statement that the current word is not MAXWORD characters long or longer
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
	return NULL;

}

