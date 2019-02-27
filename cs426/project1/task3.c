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
  //buffer overflow. The character input can get overflowed. One way to exploit this is by trying to print a large enough string. Printing a string larger than size 4 will give a warning with stack smashing involved.
	char input[4];
	gets(input);
}

int main()
{
	vulnerable();
	print_bad_grade();
	return 0;
}
