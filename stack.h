/***************************************************************
  Name: Paul Lewis
  File Name: stack.h
  
  Contains #includes, #defines, struct definitions and function prototypes for stack.c
***************************************************************/

#ifndef _STACK_H
#define _STACK_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Definitions
 */
#define DEFAULT_CAPACITY 100

/*
 * a dynamic stack data structure
 */
struct stack 
{
	int top;
	int capacity;
	char *items;
};

/*
 * Allocate memory for a new stack
 * Initialize the stack
 * Return a pointer to the new stack
 */
struct stack *newStack();

/*
 * Push the new item onto the top of the stack
 */
void pushStack(struct stack *s, char c);

/*
 * Remove one item from the top of the stack and return it
 * If the stack is empty, print an error message and return NOTHING
 */
char popStack(struct stack *s);

/*
 * Return TRUE if the stack is empty, otherwise FALSE
 * Stack is unchanged
 */
int isEmptyStack(struct stack *s);

/*
 * Free all memory allocated for the array of items
 * Free all memory allocated for the stack
 * Return a NULL pointer after memory is freed
 */
struct stack *freeStack(struct stack *s);

#endif
