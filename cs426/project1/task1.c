#include <stdio.h>
#include <stdlib.h>
void readSecretFile();

int main() {

  //Integer Overflow, the y has to becfome a negative number for us to have 42 as y. This is because y has to subtract 58 from x to become 42. Unsigned int is not designed to hold negative integers.
	unsigned int x = 100;
	unsigned int y;

	unsigned int number = 42;

	printf("Input a number: ");
	scanf("%d", &y);
	
	x = x + y;

  //hardcoded credentials, the number x has to become is hardcoded which is the only trigger for the readSecretFile() function.
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
