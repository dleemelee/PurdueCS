
/*
 * CS-252
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%code requires 
{
#include <string>
#include <string.h>
#include <regex.h>
#include <dirent.h>

#if __cplusplus > 199711L
#define register      // Deprecated in C++11 so remove the keyword
#endif
}

%union
{
  char        *string_val;
  // Example of using a c++ type in yacc
  std::string *cpp_string;
}

%token <string_val> WORD
%token NOTOKEN GREAT LESS GREATGREAT GREATAMPERSAND GREATGREATAMPERSAND AMPERSAND PIPE ERR2 NEWLINE

%{
//#define yylex yylex
#include <cstdio>
#include "command.hh"

void yyerror(const char * s);
void expandWildcardsIfNecessary(char * arg);
int yylex();

%}

%%

goal:
  commands
  ;

commands:
  command
  | commands command
  ;

command: simple_command
       ;

simple_command:	
  pipe_list iomodifier_list background_opt NEWLINE {
    /*printf("   Yacc: Execute command\n");*/
    Command::_currentCommand.execute();
  }
  | NEWLINE 
  | error NEWLINE { yyerrok; }
  ;

pipe_list:
  command_and_args
  |
  pipe_list PIPE command_and_args
  ;

command_and_args:
  command_word argument_list {
    Command::_currentCommand.
    insertSimpleCommand( Command::_currentSimpleCommand );
  }
  ;

argument_list:
  argument_list argument
  | /* can be empty */
  ;

argument:
  WORD {
    /*printf("   Yacc: insert argument \"%s\"\n", $1);*/
    /*Command::_currentSimpleCommand->insertArgument( $1 );\*/
    expandWildcardsIfNecessary($1);
  }
  ;

command_word:
  WORD {
    /*printf("   Yacc: insert command \"%s\"\n", $1);*/
    Command::_currentSimpleCommand = new SimpleCommand();
    Command::_currentSimpleCommand->insertArgument( $1 );
  }
  ;

iomodifier_list:
  iomodifier_list iomodifier_opt
  |
  ;

iomodifier_opt:
  GREAT WORD {
    /*printf("   Yacc: insert output \"%s\"\n", $2);*/
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._outCount++;
 
  }
  |
  LESS WORD {
	  /*printf("   Yacc: insert output \"%s\"\n", $2);*/
    Command::_currentCommand._inFile = $2;
    Command::_currentCommand._inCount++;
  }
  |
  GREATGREAT WORD {
    /*printf("   Yacc: insert output \"%s\"\n", $2);*/
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._appendOut = 1;
    Command::_currentCommand._outCount++;

  }
  |
  GREATAMPERSAND WORD{
    /*printf("   Yacc: insert err \"%s\"\n", $2);*/
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._outFile = $2;    
    Command::_currentCommand._errCount++;
    Command::_currentCommand._outCount++;

  }
  |
  GREATGREATAMPERSAND WORD{
    /*printf("   Yacc: insert err \"%s\"\n", $2);*/
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._appendErr = 1;
    Command::_currentCommand._appendOut = 1;
    Command::_currentCommand._errCount++;
    Command::_currentCommand._outCount++;

  }
  |
  ERR2 WORD{
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._errCount++;
  }
  ;

background_opt:
  AMPERSAND {
    Command::_currentCommand._background = 1;
  }
  |/* Can be empty */
  ;

%%

void
yyerror(const char * s)
{
  fprintf(stderr,"%s", s);
}

void
quotes(char * s)
{
  int i = 0;
  if( s[0] == '"' ) {
    
  }
}

int cmpfunc (const void * a, const void * b) {
  char *c1 = *(char**)a;
  char *c2 = *(char**)b;
  return strcmp(c1,c2);
}

void expandWildcardsIfNecessary(char * arg) {
  char * startarg = arg;
  char * path = ".";
    /*memmove(&arg[0], &arg[1], strlen(arg));*/
  /*
  while(strchr(startarg, '\') != NULL) {
    endarg = strchr(++startarg,'\');
    if(endarg == NULL) {
      endarg = startarg[strlen(startarg)-1];
      
    }
    startarg = endarg;
  }
  */

  if(strchr(arg, '*') == NULL && strchr(arg, '?') == NULL){
    Command::_currentSimpleCommand->insertArgument(arg);
    return;
  }

  if(strchr(arg, '/') != NULL && arg[0] == '/') {
    while(strchr(startarg, '/')!=NULL) {
      startarg++;
    }
    int len = strlen(arg) - strlen(startarg);
    strncpy(path, arg, len);
    printf("%s\n", path);
  }

  char * reg = (char*)malloc(2*strlen(arg)+10);
  char * a = arg;
  char *r = reg;

  *r = '^'; r++;
  while(*a) {
    if(*a == '*') {
      *r = '.';
      r++;
      *r = '*';
      r++;
    }
    else if(*a == '?') {
      *r = '.';
      r++;
    }
    else if(*a == '.'){
      *r = '\\';
      r++;
      *r = '.';
      r++;
      
    }
    else {
      *r = *a;
      r++;
    }
    a++;
  }
  *r = '$';
  r++;
  *r = 0;
  
  regex_t regt; 
  int expbuf = regcomp(&regt ,reg, REG_EXTENDED | REG_NOSUB );
  if( expbuf != 0) {
    perror("regcomp");
    return;
  }

  DIR * dir = opendir(path);
  if(dir == NULL) {
    perror("oopenedir");
    return;
  }

  struct dirent * ent;
  regmatch_t regmatch;
  
  char ** entries = (char**)malloc(sizeof(char*));
  int size = 1;
  int n = 0;
  while( (ent = readdir(dir)) != NULL) {
    if(size == n) {
      size = size*2;
      entries = (char**) realloc(entries, size*sizeof(char*));
    }
    if(regexec(&regt, ent->d_name, 1, &regmatch, 0) == 0 ) {
      //Command::_currentSimpleCommand->insertArgument(strdup(ent->d_name));
      if(ent->d_name[0] != '.') {
        entries[n] = strdup(ent->d_name);
        n++;
      }
    }
  }
  qsort(entries, n, sizeof(char*), cmpfunc);
  closedir(dir);
  int i;
  for( i = 0; i < n; i++ ){ 
    Command::_currentSimpleCommand->insertArgument(strdup(entries[i]));
  }
  return;
}



#if 0
main()
{
  yyparse();
}
#endif
