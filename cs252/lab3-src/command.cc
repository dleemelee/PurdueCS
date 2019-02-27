/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include "command.hh"


Command::Command()
{
	// Create available space for one simple command
	_numOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
  _appendErr = 0;
  _appendOut = 0;

  _errCount = 0;
  _inCount = 0;
  _outCount = 0;
}

void Command::insertSimpleCommand( SimpleCommand * simpleCommand ) {
	if ( _numOfAvailableSimpleCommands == _numOfSimpleCommands ) {
		_numOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numOfSimpleCommands ] = simpleCommand;
	_numOfSimpleCommands++;
}

void Command:: clear() {
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile && !_errFile ) {
		free( _outFile );
	}

	if ( _inFile ) {
		free( _inFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
  _appendErr = 0;
  _appendOut = 0;

  _errCount = 0;
  _inCount = 0;
  _outCount = 0;

}

void Command::print() {
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inFile?_inFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void Command::execute() {
	// Don't do anything if there are no simple commands
	if ( _numOfSimpleCommands == 0 ) {
    prompt();
		return;
	}
  if( !strcmp(_simpleCommands[0]->_arguments[0], "exit") ) {
    exit(0);
  }
  	// Print contents of Command data structure
	if(isatty(0)){
    print();
  }
	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec
  if(_inCount > 1) {
    printf("Ambiguous input redirecti\n");
  }
  else if(_outCount > 1) {
    printf("Ambiguous output redirect\n");
  }
  else if(_errCount > 1) {
    printf("Ambiguous error redirect\n");
  }
  else {

  int tmpin = dup(0);
  int tmpout = dup(1);
  int tmperr = dup(2);

  int fdin;
  int fderr;
  if (_inFile) {
    //TODO
    fdin = open(_inFile, O_RDONLY);
  }
  else {
    fdin = dup(tmpin);
  }
  if(_errFile) {
    //TODO
    //printf("ERRFILE\n");
    if(!_appendErr){
      fderr = creat(_errFile, 0666);
    }
    else{
      fderr = open(_errFile, O_RDWR | O_APPEND | O_CREAT);
    }  
  }
  else {
    fderr = dup(tmperr);
  }
  dup2(fderr, 2);
  int ret;
  int fdout;
  for(int i = 0; i < _numOfSimpleCommands; i++) {
   dup2(fdin, 0);
    close(fdin);
    if(i == _numOfSimpleCommands-1) {
      if(_outFile){
        //TODO
        if(_errFile){
          fdout = fderr;
        }
        else if(!_appendOut) {
          fdout = creat(_outFile, 0666);
        }
        else{
          fdout = open(_outFile, O_RDWR | O_APPEND | O_CREAT);
        }
      }
      else {
        fdout = dup(tmpout);
      }
    }
    else {
      int fdpipe[2];
      pipe(fdpipe);
      fdout = fdpipe[1];
      fdin = fdpipe[0];
    }
    dup2(fdout,1);
    close(fdout);
    
    /*
    if( !strcmp(_simpleCommands[i]->_arguments[0], "source")) {
      FILE * f = fopen(_simpleCommands[i]->_arguments[1],"r");
      while(
      for(env = environ; *env != 0; env++)
      {
        char* thisEnv = *env;
        fprintf(stdout,"%s\n", thisEnv);
      }
    }*/
    if( !strcmp(_simpleCommands[i]->_arguments[0], "setenv")) {
      if(_simpleCommands[i]->_numOfArguments!=3)
        setenv(NULL,NULL,0);
      else
        setenv(_simpleCommands[i]->_arguments[1],_simpleCommands[i]->_arguments[2],1);
    }
    else if( !strcmp(_simpleCommands[i]->_arguments[0], "unsetenv")) {
      if(_simpleCommands[0]->_numOfArguments!=2)
        unsetenv(NULL);
      else
        unsetenv(_simpleCommands[i]->_arguments[1]);
    }
    else if( !strcmp(_simpleCommands[i]->_arguments[0], "cd")) {
      if(_simpleCommands[i]->_numOfArguments!=2)
        ret = chdir(getenv("HOME"));
      else
        ret = chdir(_simpleCommands[i]->_arguments[1]);
      if(ret == -1) {
        fprintf(stderr, "No such file or directory");
      }
    }
    else{
      ret = fork();
      if(ret == 0) {
        execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
        perror("execvp");
        _exit(1);
      }
    }

  /*
  if( !strcmp(_simpleCommands[0]->_arguments[0], "jobs")) {
    if(!strcmp(_simpleCommands[0]->numOfArguments == 1)){
       
    }
    else if(!strcmp(_simpleCommands[0]->numOfArguments == 2)) {

    }
    else if(!strcmp(_simpleCommands[0]->numOfArguments == 3)) {
      
    }
  }
  
  if( !strcmp(_simpleCommands[0]->_arguments[0], "source")) {
    if(_simpleCommands[0]->_numOfArguments!=2)
      source(NULL);
    else
      source(_simpleCommands[0]->_arguments[1]);
     builtin=1;
  }*/

  }//endFOR
  dup2(tmpin, 0);
  dup2(tmpout, 1);
  dup2(tmperr, 2);
  close(tmpin);
  close(tmpout);
  close(tmperr);

  if(!_background) {
    waitpid(ret, NULL, 0);
  }
  }
	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	prompt();
}

// Shell implementation

void Command::prompt() {
  if(isatty(0)){
	  printf("myshell>");
	  fflush(stdout);
  }
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;
