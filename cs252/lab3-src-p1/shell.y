
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
    Command::_currentSimpleCommand->insertArgument( $1 );\
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

#if 0
main()
{
  yyparse();
}
#endif
