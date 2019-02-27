
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
#include <assert.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  top = 0;
}

double stack_pop()
{
	assert(!stack_is_empty());
	top--;
	// Add implementation here`
	// Be sure to check if stack is empty, using assert or otherwise, "Stack Underflow" would be the error here
	return stack[top];
}

void stack_push(double val)
{
	assert(top <= MAXSTACK);
	stack[top] = val;
	top++;
	// Add implementation here
	// Be sure to check if stack is full, using assert or otherwise, "Stack Overflow" would be the error here
}

void stack_print()
{
	printf("Stack:\n");

	if( stack_is_empty()) {
		printf("Stack is empty\n");
		return;
	}
	int i;
	for( i = 0; i < top; i++) {
		printf("%d: %lf\n", i, stack[i]);
	}
	// Add implementation here
}

int stack_top()
{
  return top;
}

int stack_max()
{
  return MAXSTACK;
}

int stack_is_empty()
{
  return top == 0;
}


