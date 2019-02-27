#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_triangle(int side, int height);

void print_triangle(int side, int height) {
	int i, j, counter;
	counter = 0;
	printf("\n");
	if( side == 1) {
	for (i = 0; i < height; i++) {
		for (j = 0; j < height; j++) {
			char c = ((side = 1) ? (j > counter ? ' ' : '*') : (side = 2) ? (height - j > counter + 1 ? ' ' : '*') : '\0');
			printf("%c", c);
		}
		printf("\n");
		counter++;
	}
	}
	else if( side == 2) {
	counter = height-1;
	for (i = 0; i < height; i++) {
                for (j = 0 ; j < height; j++) {
                 if(j < counter ) {
			printf(" ");
		 }
		 else{
    	          printf("*");
		  }
               }
               printf("\n");
               counter--;
        }
																	
	}
}

int main(int argc, char** argv) {
	printf("Draw Right Angle Triangle\n");
	int side, height;
	char* response = (char*)malloc(16* sizeof(char));
	int firstrun = 1;

	while (1) {	
		if (! strcmp(response, "n") ) {	
			free(response);
			return 0;
		}
		*response = '\0';	
		printf("\nPlease enter your choice of right triangle\n");
		printf("1 for left aligned right angle triangle\n");
		printf("2 for right aligned right angle triangle\n");
		while ( 1  ) {
			printf("\nEnter your choice [1/2]: ");
			scanf("%s", response);
			if(! strcmp(response, "1"))  {
				break;
			}
			else if(!strcmp(response, "2")) {
				break;
			}
			
		}
		side = atoi(response);
		*response = '\0';
		height = -1;
		while (height < 0 || height > 100) {
			printf("\nEnter the height of the triangle [0-100]: ");
			scanf("%d", &height);
			fflush(stdin);
		
		}
		print_triangle(side, height);
		while ( 1 )
		{
                        if (firstrun) {
                                printf("\nDo you want to continue? [y/n]: ");
                                scanf("%s", response);
                        } else {
                                printf("Draw Right Angle Triangle\n");
                                strcpy(response, "y");
                                firstrun = 0;
                        }
		 	
			if(!strcmp(response, "y")) {
				break;
			}
			else  if(!strcmp(response, "n")) {
				break;	
			}
                }
		if(!strcmp(response, "n")) {
			break;
		}
	}
	return 0;
}


