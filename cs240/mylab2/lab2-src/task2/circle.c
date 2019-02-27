#include <stdio.h>
#include "circle.h"
//

int main(int argc, char **argv) {
	
	double r;
	double area, circumference;

        printf("Finding area and circumference of a circle given a radius\n");
        while (1) {
		printf("Enter the radius and <enter>: ");

		scanf("%lf",&r);
		getchar();
		
		if( r >= 0 ) {
			area = r*r * pi;
			circumference = 2 * r * pi;
			printf("Area is = %lf \nCircumference is = %lf \n",area, circumference);
		}
		else {
			printf("Radius cannot be negative\n");

		}	

		printf("Do you want to continue? Type y/n and <enter>");
		char c;
		c = getchar();
		if( c == 'n') {
			break;
		}
		
	}
	return 0;
}

