all: test1 test2
test1: test_linkedlist.c linkedlist.c linkedlist.h
	gcc -g -Werror -Wall -o test1  test_linkedlist.c linkedlist.c 
test2: test_hashtable.c hashtable.c hash.o hashtable.h
	gcc -g -Werror -Wall -o test2 test_hashtable.c hashtable.c hash.o
