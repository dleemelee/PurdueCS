#include <cstdio>
#include <cstdlib>

#include "command.hh"
#include <signal.h>
#include <sys/wait.h>
int yyparse();

extern "C" void disp(int sig) {
  printf("\n");
  Command::_currentCommand.prompt();

}

void zombie(int sig) {
  int status;
  while(waitpid(-1, NULL, WNOHANG)>0);
  //wait3(&status, WNOHANG, (struct rusage *)NULL);
  return;
}

int main() {
  struct sigaction sa;
  sa.sa_handler = disp;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  struct sigaction sa2;
  sa2.sa_handler = zombie;
  sigemptyset (&sa2.sa_mask);
  sa2.sa_flags = SA_RESTART; 

  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGCHLD, &sa2, NULL);
  Command::_currentCommand.prompt();
	yyparse();
}
