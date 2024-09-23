#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct LLNode {
	int val;
	struct LLNode *next;
	struct LLNode *prev;
};

int count_list_length_step(struct LLNode *l, int acc)
{
	if (l->prev == NULL) {
		return acc;
	}

	return count_list_length_step(l->prev, ++acc);
}

int count_list_length(struct LLNode *l)
{
	int acc = 0;
	return count_list_length_step(l, acc);
}

int main()
{
	struct LLNode *l = malloc(sizeof(struct LLNode));
	l->prev = NULL;

	struct LLNode *new_lln;
	for (int n = 0; n < 11; n++) {
		new_lln = malloc(sizeof(struct LLNode));
		new_lln->val = n;
		new_lln->next = NULL;
		new_lln->prev = l;
		l->next = new_lln;
		l = new_lln;
	}

	int i = count_list_length(l);
	printf("%d\n", i);

	return 0;
}
