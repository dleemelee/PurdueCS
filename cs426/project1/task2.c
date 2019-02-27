#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char grade[5];
	char name[10];
  //hardcoded credentials, the grade is a credential that should not be revealed unless the user does it themselves.
	strcpy(grade, "nil");
  
  //buffer overflow in both strcpy and gets. It is the buffers in gets can be overflowed which can lead to overwriting parts of the code unintended, or running a part of the code that was intended to be hidden.
	gets(name);
 
  //missing authentication before personal information is given, the user needs to be authenticated that the right user is given the right information.
	printf("Hi %s! Your grade is %s.\n", name, grade);
					
	exit(0);	
}

