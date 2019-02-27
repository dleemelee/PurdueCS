
all: toascii countlines towords test_stack rpncalc

toascii: toascii.c
	gcc -Wall -Werror -g -o toascii toascii.c
countlines: countlines.c
	gcc -Wall -Werror -g -o countlines countlines.c
towords: towords.c  nextword.c
	gcc -Wall -Werror -g -o towords towords.c nextword.c
test_stack: test_stack.c stack.c
	gcc -Wall -Werror -g -o test_stack test_stack.c stack.c
rpncalc: rpncalc.c rpn.c nextword.c stack.c
	gcc -Wall -Werror -g -o rpncalc rpncalc.c rpn.c nextword.c stack.c -lm


clean:
	rm -f countlines towords test_stack rpncalc *out
