/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

prch(c)
char c;
{
  int i;
  
  while(1) {
    for (i=0; i < 1; i++);
      kprintf("%c",c);
    } /*while*/
} /* prch */

main()
{
  kprintf("\n\nHello world, Xinu lives!\n\n");
  resume(create(prch,2000,20,"proc A",1,'A'));
  resume(create(prch,2000,20,"proc B",1,'B'));
  resume(create(prch,2000,20,"proc C",1,'C'));
} /* main */

/*
process	main(void)
{

	kprintf("\nWhy is it always Hello World?\n");
	kprintf("\nI'm the first XINU app and running function main() in system/main.c.\n");
	kprintf("\nI was created by nulluser() in system/initialize.c using create().\n");
	kprintf("\nMy creator will turn itself into the do-nothing null process.\n");
	kprintf("\nI will create a second XINU app that runs shell() in shell/shell.c as an example.\n");
	kprintf("\nYou can do something else, or do nothing; it's completely up to you.\n");
	kprintf("\n...creating a shell\n");
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
*/
	/* Wait for shell to exit and recreate it */
/*
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
*/
