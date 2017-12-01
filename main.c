#include <stdio.h>
#include <stdbool.h>
#include "stack.c"

// So this is a really arbitrary decision to make, but do I want to parse as
// the user writes or after everything
//
// I'll probably go as the user writes to see if I have to backtrack at all


enum Operator_Weight {
	FIRST = 1,
	SECOND = 2,
	PAREN = 3,
};

enum Operator_Weight op_weight(char op) {
	switch(op) {
		case '+':
		case '-':
			return FIRST;
		case '*':
		case '/':
			return SECOND;
		case '(':
		case ')':
			return PAREN;
		default:
			printf("ERR");
			return 0;
	}
}


/*
void infix2postfix_logic(char c, struct Parse_Group *pg) {
	switch (c) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			push(&pg->parsed, c);
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			if (LList_len(&pg->ops.top) == 0) {
				push(&pg->ops, c);
			} else if (op_weight(top(&pg->ops)) >= op_weight(c)) {
				push(&pg->parsed, popoff(&pg->ops));
				push(&pg->ops, c);
			} else {
				push(&pg->ops, c);
			}
			break;
		case '\n':
			while (LList_len(&pg->ops.top) != 0) {
				push(&pg->parsed, popoff(&pg->ops));
			}
		default:
			push(&pg->parsed, c);
			break;
	}
	printf("stack: \n");
	LList_print(&pg->ops.top);
	printf("\n");

}
*/

// Improved function from http://csis.pace.edu/~wolf/CS122/infix-postfix.htm
// Turns out the algorithm is very simple
// I'm dumb :P
void parse(char *expr) {
	struct Stack op_stack = new();
	bool empty = true;
	for (char c; (c = *expr); expr++) {
		switch (c) {
			case ' ':
				break;
			case '(':
			case '+':
			case '-':
			case '*':
			case '/':
				if (c == '(') {
					empty = true;
				} else if (empty) {
					empty = false;
				} else if (op_weight(top(&op_stack)) >= op_weight(c)) {
					printf("%c", popoff(&op_stack));
					printf(" ");
				}

				push(&op_stack, c);
				break;

			case ')':
				; char z;// < why
				while ((z = popoff(&op_stack)) != '(') {
					printf("%c", z);
					printf(" ");
				}
				break;

			default:
				for (c = *expr++; c != '\0' && c != ' ' && c != '+' && c != '-' && c != '*' ; c = *expr++) {
					printf("%c", c);
				}
				printf(" ");
				expr--;
				break;
		}
	}

	while (LList_len(&op_stack.top) != 0) {
		printf("%c", popoff(&op_stack));
		printf(" ");
	}

}

// Test cases:
// 	4 + 5
// 		4 5 +
//
// 	3 - 2 * 6
// 		2 6 * 3 -
//
// 	(3 - 2) * 6
// 		3 2 - 6 *


#include <string.h>
int main(int argc, char *argv[]) {

	if (argc != 2) {
		printf("wrong\n");
		return 2;
	}

	char z[strlen(argv[1])];
	strcpy(z, argv[1]);
	parse(z);
	printf("\n");

	return 0;
}
