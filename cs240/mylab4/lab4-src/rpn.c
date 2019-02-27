
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
  char *  c;
  char * pastc;
  double num2;
  double num1;
  double ans;
  FILE * fd = fopen(fileName, "r");
  while((c = nextword(fd)) != NULL) {
	if ( !strcmp(c, "+") || !strcmp(c, "-") || !strcmp(c, "*") || !strcmp(c, "/" ) || !strcmp(c, "pow"))  {
	if(stack_top() < 2) {
		printf("Stack underflow\n");
		exit(0);
	}
	num2 = stack_pop();
	num1 = stack_pop();
		if( !strcmp(c, "+")){
			ans = num1 + num2;
		}
		else if( !strcmp(c, "-")){
			ans = num1 - num2;
		}
		else if( !strcmp(c, "*")) {
			ans = num1 * num2;
		}
		else if( !strcmp(c, "pow")) {
			ans = pow(num1, num2);
		}
		else {
			ans = num1 / num2;
		}
		stack_push(ans);
	}
	else if(!strcmp(c, "")) {

	}
	else if(!strcmp(c, "x")) {
		stack_push(x);
	}
 	else if(!strcmp(c, "sin") || !strcmp(c, "cos") ||!strcmp(c, "log") || !strcmp(c, "exp") ) {
		double num = stack_pop();
		if(!strcmp(c, "sin")) {
			ans = sin(num);
		}
		else if( !strcmp(c, "cos")) {
			ans = cos(num);
		}
		else if(!strcmp(c, "log")) {
			ans = log(num);
		}
		else {
			ans = exp(num);
		}
		stack_push(ans);
	}
	else {
	stack_push(atof(c));
	pastc = c;
	}
}
  
if(stack_top() >= 2)
{
num2 = stack_pop();
num1 = stack_pop();
 
if( !strcmp(pastc, "+")){
ans = num1 + num2;
}
else if( !strcmp(pastc, "-")){
ans = num1 - num2;
}
else if( !strcmp(pastc, "*")) {
ans = num1 * num2;
}
else if( !strcmp(pastc, "/")) {
ans = num1 / num2;
}
else {
return HUGE_VAL;
}
}
stack_push(ans);
     
  return ans;
}

