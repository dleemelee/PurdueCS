
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

%token	<string_val> WORD

%token 	NOTOKEN GREAT NEWLINE LESS GREATGREAT GREATAMPERSAND GREATGREATAMPERSAND PIPE AMPERSAND

%union	{
		char   *string_val;
	}

%{
//#define yylex yylex
#include <stdio.h>
#include "command.h"
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
	pipe_list iomodifier_opt background  NEWLINE {
		//printf("   Yacc: Execute command\n");
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
               //printf("   Yacc: insert argument \"%s\"\n", $1);

	       Command::_currentSimpleCommand->insertArgument( $1 );\
	}
	;

command_word:
	WORD {
               //printf("   Yacc: insert command \"%s\"\n", $1);
	       
	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

iomodifier_opt:
	iomodifier_opt GREAT WORD {
		//printf("   Yacc: insert output \"%s\"\n", $3);
		if(Command::_currentCommand._outFile) {
			printf("Ambiguous output redirect.\n");
		}
		Command::_currentCommand._outFile = $3;
	}
	|
	iomodifier_opt GREATGREAT WORD {
		//printf("   Yacc: insert output \"%s\"\n", $3);
		if(Command::_currentCommand._outFile) {
			printf("Ambiguous output redirect.\n");
		}
		Command::_currentCommand._outFile = $3;
		Command::_currentCommand._append = 1;
	}
	|
	iomodifier_opt LESS WORD {
		//printf("   Yacc: insert input \"%s\"\n", $3);
		Command::_currentCommand._inFile = $3;

	}
	|
	iomodifier_opt GREATAMPERSAND WORD {
		//printf("   Yacc: insert error \"%s\"\n", $3);
		if(Command::_currentCommand._errFile) {
			printf("Ambiguous error redirect.\n");
		}
		Command::_currentCommand._errFile = $3;

	}
	|
	iomodifier_opt GREATGREATAMPERSAND WORD {
		//printf("   Yacc: insert error \"%s\"\n", $3);
		if(Command::_currentCommand._errFile) {
			printf("Ambiguous error redirect.\n");
		}
		Command::_currentCommand._errFile = $3;
		Command::_currentCommand._append = 1;
	}
	| /* can be empty */ 
	;

background:
	AMPERSAND {
		Command::_currentCommand._background = 1;
	}
	|
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
