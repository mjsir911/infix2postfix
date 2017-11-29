#include <stdio.h>
#include "llist.c"

struct Stack {
	struct LList top;
	size_t len;
};

struct Stack new(void) {
	struct Stack stack = {.len=0, .top={.val=0, .next=NULL}};
	return stack;
}

T popoff(struct Stack *stack) {
	size_t last = LList_len(&stack->top);
	if (last == 0) {
		printf("\npopping from empty stack\n");
		exit(2);
	}
	// TODO: use s.len
	struct LList *last_val = LList_index(&stack->top, last); // Get pointer as to not leak
	LList_index(&stack->top, last - 1)->next = NULL; // Remove from stack
	return last_val->val;
	//printf("%d", LList_index(&stack->top, last - 1)->next == NULL);
}

void push(struct Stack *stack, char val) {
	LList_append(&stack->top, val);
}

T top(struct Stack *stack) {
	return LList_get_last(&stack->top)->val;
}
