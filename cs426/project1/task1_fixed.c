#include <stdio.h>
#include <stdlib.h>
void readSecretFile();

int main() {
	unsigned int x = 100;
  //changed y to an int so that it can hold negative integers.
	int y;

	unsigned int number = 42;

	printf("Input a number: ");
	scanf("%d", &y);
	
	x = x + y;
  
  printf("CURRENT x: %d, y:%d\n", x, y);

	if (x == 42) {
		readSecretFile();
	}
}

void readSecretFile() {

	/** Helper function, not needed for the solution */
	FILE *fptr = fopen("secretfile.txt", "r");
	if (fptr == NULL) {
		printf("cannot open, but you triggered the exploit!\n");
		exit(0);
	}
	char ch = fgetc(fptr);
	while (ch != EOF) {
		printf("%c", ch);
		ch = fgetc(fptr);
	}
	fclose(fptr);
}
