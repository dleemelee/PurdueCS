#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char grade[5];
	char name[10];
  char password[10];
  String pw = "password";
	strcpy(grade, "nil");
  
	gets(name);


  gets(password);
  //makes sure that the user is authenticated with a password. Althoguth this would make another hardcoded password error, this is for the purpose of fixing just this vulnerability.
  if( strcmp(pw, password)) {
	  printf("Hi %s! Your grade is %s.\n", name, grade);
					
  }
	exit(0);	
}

