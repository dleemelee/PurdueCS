#include <stdio.h>
//

int main(int argc, char **argv) {
	printf("Welcome to the High Low game...\n");
	int current_number = 50;
	int low = 1;
	int high = 100;
	while (1) {
		printf("Think of a number between 1 and 100 and press <enter>");
		low = 1;
		high = 100;
		current_number = 50;
		getchar();
		while (high >= low) {
			char ans;
			printf("Is it higher than %d? (y/n)\n",current_number);
			scanf("%c",&ans);	
			getchar();
			if( ans == 'y') {
				low = current_number+1;
				current_number = (low + high)/2; 
			}
			else if(ans == 'n'){
				high = current_number-1;
				current_number = (high + low)/2;
			}
		}
		printf("\n>>>>>> The number is %d\n\n",low);
		printf("Do you want to continue playing (y/n)?\n");
		char c;
		c = getchar();
		getchar();
		if( c == 'n') {
			break;
			}
		
 		}	
  	return 0;
}


