#include <stdio.h>
//

int main(int argc, char **argv) {
        printf("Finding maximum among three numbers a,b and c\n");
        int a, b, c;
	int max, min;

	while (1) {

		printf("Type a and <enter>: ");
		scanf("%d", &a);
		getchar();

		printf("Type b and <enter>: ");
		scanf("%d", &b);
		getchar();


		printf("Type c and <enter>: ");
		scanf("%d", &c);
		getchar();
		
		if( a > b && a > c) {
			max = a;
		}
		else if( a < b && a < c) {
			min  = a;
		}
		if( b > a && b > c) {
			max = b;
		}
		else if( b < a && b< c) {
			min  = b;
		}
		if( c > a && c > b) {
			max = c;
		}
		else if( c < a && c < b ) {
			min = c;
		}
		if( a > 100 || a < 0 || b > 100 || b < 0 || c > 100 || c < 0) {
			printf("Numbers are not in the correct range [0-100]\n");
		}
		else if(a==b&&b==c) {
			printf("All three values are equal\n");
		}
		else{
			printf("maximum = %d\nminimum = %d\n", max, min);
		}
		printf("Do you want to continue? Type y/n and <enter>");
		char answer;
		answer = getchar();
		if(answer == 'n') {
		printf("Bye\n");
		break;
		}
	}
 
	return 0;
}

