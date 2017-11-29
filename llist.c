#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

struct LList LList_init(char *startv) {
	struct LList list = {.val = *startv++, .next=NULL};
	struct LList *next = &list;

	list.next = next;
	for (char *val = startv; *val; val++) {
		next = LList_append(next, *val);
	}
	return list;
}

size_t LList_len(struct LList *llist) {
	size_t i = 0;
	for (struct LList *next = llist; next != NULL; next = next->next) {
		i++;
		//if (next == next->next) break;
	};
	return i - 1; // Off by one error
}

struct LList *LList_append(struct LList *llist, char val) {
	struct LList *child = LList_get_last(llist)->next = calloc(sizeof(struct LList), 1);
	child->val = val;
	return child;
}

void LList_print(struct LList *llist) {
	for (struct LList *next = llist; next != NULL; next = next->next) {
		printf(" %c ", next->val);
	}
}

struct LList *LList_index(struct LList *list, size_t index) {
	for (size_t i = 0; i < index; i++) {
		list = list->next;
	}
	return list;
}
