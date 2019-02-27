#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  FILE * db;
  FILE * log;
  FILE * newfile;
  db = fopen("./student.csv", "a+");
  log  = fopen("./log.txt", "a+");
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  while(1) {
		char* command = malloc(10);
		printf("Enter a command: \n");
		gets(command);
		char* str = malloc(50);
    printf("Enter row to %s:\n", command);
    gets(str);
	 
		if(strstr(command, "insert")) {
			fprintf(db , "%s\n", str);
		}
		else if(strstr(command, "delete")) {
      int find = 0;
      char choice = 'n';
      while((read = getline(&line, &len, db)) != -1 && choice != 'y') {
        printf("%c %s\n",choice,  line);
        if(strstr(line, str)){
          find = 1;
          printf("Is %s the line you wish to delete? Press 'y' to delete\n", line);
          choice = getchar();
        }
      }
      if(find) {
        fprintf(db, "DELETED" );
      }
		}
		else if(strstr(command, "update")) {

		}
		else if(strstr(command, "quit")) {
			printf("quit");
		  break;
    }
		else {
			printf("nothing\n");
		}
    fprintf(log, "command: %s line: %s\n", command, str);
	}

  fclose(db);
  fclose(log);
 /*
  FILE * db;
  db = fopen("./student.csv", "a+");
  
  fprintf(db , "Benjamin Bayer, 305-61-2435, 373-1616, 2918 Bluebonnet Lane, NULL, 19, 3.21\n");

  fclose(db);
*/
  return 0;

}
