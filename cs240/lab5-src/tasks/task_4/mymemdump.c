
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
   
    // ToDo: remove hints below 
   /* int i;
    int j;
    for (i=0; i < len; i+=16) {
        int c = p[i]&0xFF; // Get value at [p]. The &0xFF is to make sure you truncate to 8bits or one byte.
	fprintf(fd, "0x%016lX: ", (unsigned long) p); 
    	for(j = 0; j < 16; j++) {
		c = p[i+j]&0xFF;
		fprintf(fd, "%02X ", c);
	}
	for(j = 0; i < 16; j++) {
		c = p[i+j]&0xFF;
		fprintf(fd, "%c",(char)(c>=32)?c:'.');
	}
        fprintf(fd,"\n");
    }
    */
    
    int counter,c;
    for(counter = 0;counter < len; counter+=16) {
	fprintf(fd, "0x%016lX: ",(unsigned long)p+counter);
	int i;
	for( i = counter; (i < len) && (i < counter+16); i++){
	    c = p[i]&0xFF;
	    fprintf(fd, "%02X ", c);
	}
	int j = len;
	while (j < counter+16){
	    j++;
	    fprintf(fd, "%s ", "  ");
	}
	fprintf(fd, "%s", " ");
	for(i = counter; (i < len)&&(i < counter+16); i++){
	    c = p[i]&0xFF;
	    fprintf(fd, "%c", (c>=32 && c <= 127)?c:'.');
	}
	fprintf(fd,"\n");
    }

}

