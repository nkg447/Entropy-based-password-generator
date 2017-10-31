/*
* A Simple implementation of a stack data structure in C Language
  using a top variable to keep track of the peek element of the stack
*/
#include <stdio.h>

typedef struct Stack Stack;

/*
* A Structure named "Stack" having an index top and an array
*/
struct Stack
{
	int top;
	char arr[100];
};

/*
* A function to initialize the stack by setting top value to -1
* Requires Parameter - Stack pointer
*/
void init(Stack *stack){
	stack->top=-1;
}

/*
* A function to push values to the stack
* Requires Parameter - Stack Pointer, character to push
*/
void push(Stack *stack,char value){
	if(stack->top==99){
		printf("StackOverflow\n");	
		return;
	}
	stack->top++;
	stack->arr[stack->top]=value;
}

/*
* A function to pop out the last/peek element of the stack
* Requires Parameter - Stack Pointer
* Returns the top value of the stack
*/
char pop(Stack *stack){
	
	if(stack->top==-1){
		printf("StackUnderflow\n");
		return ' ';
	}
	char value = stack->arr[stack->top];
	stack->top--;
	return value;
}

/*
* A function to get the last/peek element of the stack
* Requires Parameter - Stack Pointer
* Returns the top value of the stack
*/
int peek(Stack *stack){
	if(stack->top==-1){
		printf("StackUnderflow\n");
		return ' ';
	}
	char value = stack->arr[stack->top];
	return value;
}

/*
* A function to check if the stack is empty
* Requires Parameter - Stack Pointer
* Returns -1 - is not Empty
		   1 - is Empty
*/
int isEmpty(Stack *stack){
	if(stack->top==-1)
		return 1;
	return -1;
}

