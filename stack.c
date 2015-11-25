/***************************************************************
  Name: Paul Lewis
  File Name: stack.c

  Code for a stack
***************************************************************/

#include "stack.h"

/* 
 * A function to create a stack using dynamic memory allocation
 * returns a pointer to a stack
 */
struct stack *newStack() {
	struct stack *s;
	s = (struct stack *)malloc(sizeof(struct stack));
	if(s == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		exit(1);
	}
	s->items = (char *)malloc(DEFAULT_CAPACITY*sizeof(char));
	if(s->items == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		exit(1);
	}
	s->capacity = DEFAULT_CAPACITY;
	s->top = -1;
	return s;	
}

/*
 * A function to push an item on to the stack
 * Increases the size of the stack when needed
 */
void pushStack(struct stack *s, char c) {
	int i;
	s->top++;
	if(s->top == s->capacity) {
		char *temp;
		s->capacity = 2*s->capacity;
		temp = (char*)malloc(s->capacity*sizeof(char));
		if(temp == NULL) {
			fprintf(stderr, "Memory allocation failed!\n");
			exit(1);
		}
		for(i=0;i<s->capacity;i++) {
			temp[i] = s->items[i];
		}
		free(s->items);
		s->items = temp;
	}
	s->items[s->top] = c;
}

/*
 * A function to pop an item off the top of the stack
 * Returns item and decrements top, returns nothing if stack is empty
 */
char popStack(struct stack *s) {
	if(s->top == -1) {
		fprintf(stderr, "Error; stack is empty.\n");
		return 0;
	}
	else {
		s->top--;
		return s->items[s->top+1];
	}
}

/*
 * A function to show if stack is empty
 * returns Boolean, TRUE or FALSE
 */
int isEmptyStack(struct stack *s) {
	if(s->top == -1)
		return 1;
	else
		return 0;
}

/*
 * A function to free up memory used by stack
 * Returns a NULL pointer
 */
struct stack *freeStack(struct stack *s) {
	free(s->items);
	free(s);
	return s;
}
