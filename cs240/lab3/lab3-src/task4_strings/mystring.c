
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

char * mystrcpy(char * dest, char * src) {
	int len = mystrlen(src);
	int i;
	for( i = 0; i <= len; i++){
		dest[i] = src[i];
	}
	
	return dest;
}

char * mystrcat(char * dest, char * src) {
	int srclen = mystrlen(src);
	int destlen = mystrlen(dest);
	int i = 0;
	for (i = 0 ; i < srclen+destlen ; i++) {
		dest[i] = src[i];
	}
	return dest;
}

int mystrcmp(char * s1, char * s2) {
	int i;
	int s1len = mystrlen(s1);
	int s2len = mystrlen(s2);

	if( s1len > s2len) return 1;
	if(s1len < s2len) return -1;
	return 0;
}

char * mystrstr(char * hay, char * needle) {
	int i;
	int j;
	int haylen = mystrlen(hay);
	int needlelen = mystrlen(needle);
	for (i = 0; i < haylen; i++) {
		if (hay[i] == needle[0]) {
			for (j = 1; hay[j] == needle[j]; j++) {}
			if (j == needlelen) {
				return (hay + i);
			}
		}
	}
	return NULL;
}

char * mystrdup(char * s) {
	int len = mystrlen(s);
	char* dup = (char*)malloc((len) * sizeof(char));
	int i;
	for (i = 0; i < len; i++) {
		dup[i] = s[i];
	}
	return dup;
}

char * mymemcpy(char * dest, char * src, int n)
{
	int len = mystrlen(src) +1;
	int i;
	for (i = 0; i < len; i++) {
		dest[i] = src[i];
	}
	return dest;
}

