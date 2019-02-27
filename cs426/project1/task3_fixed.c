#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void print_bad_grade(void)
{
	puts("Your grade is nil.");
	exit(0);
}

void print_good_grade(void)
{
	puts("Your grade is perfect.");
	exit(1);
}

void vulnerable()
{
  //fixed buffer overflow by figuring how many characters from stdin to read into input
	char input[4];
  fgets(input, 5, stdin);
}

int main()
{
	vulnerable();
	print_bad_grade();
	return 0;
}
