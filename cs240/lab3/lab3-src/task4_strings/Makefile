all: test_mystring

test_mystring: test_mystring.c mystring.c
	gcc -g -Wall -Werror -o test_mystring test_mystring.c mystring.c

clean:
	rm -f *.o *.out total.txt grades1.rt test_mystring

