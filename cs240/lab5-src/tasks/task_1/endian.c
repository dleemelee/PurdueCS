#include <stdio.h>

int isBigEndian() {
    int i = 1;
    char *c =(char*) &i;
    if(*c){
	return 0;
    }
    return 1;
}

int main()
{
	if (isBigEndian()) {
		printf("Machine is Big Endian\n");
	}
    else {
		printf("Machine is Little Endian\n");
	}
    return 0;
}
