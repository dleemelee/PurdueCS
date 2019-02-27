#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

pid_t ppid = getppid();

unsigned int a = (unsigned int) ppid;



printf("%d\n",  a);

return 0;

}
