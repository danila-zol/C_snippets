#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>

struct LLNode {
	char *str;
	struct LLNode *next;
	struct LLNode *prev;
};

struct GraphNode {
	struct LLNode *data;
	uint64_t neighbours_count;
	struct LLNode **neighbours; // Array of pointers to neighbours
};

typedef struct LLNode LLNode;
typedef struct LLNode DQueue;

struct LLNode *search_list(const struct LLNode *ll, const char *str)
{
	const struct LLNode *current_node = ll;
	while (current_node->next != NULL) {
		if (strcmp(current_node->str, str) == 0) {
			return (struct LLNode *) current_node; // Cast away const
		}
	}

	return NULL;
}

DQueue *enqueue(DQueue *q, LLNode *node)
{
	q->next = node;
	node->prev = q;
	return node;
}

DQueue *dequeue(DQueue *q) 
{
	DQueue *prev_node = q->prev;
	prev_node->next = NULL;
	free(q->str);
	free(q);
	return prev_node;
}

void print_list(LLNode *ll)
{

	const struct LLNode *current_node = ll;
	while (current_node != NULL) {
		printf(current_node->prev != NULL ? "\"%s\" -> " : "\"%s\"", current_node->str);
		current_node = current_node->prev;
	}
	putchar('\n');
}

LLNode *arr2list(char **arr, size_t len)
{
	// Init the first node
	LLNode *ll = malloc(sizeof(LLNode));
	ll->str = malloc(strlen(arr[0]) + 1);
	strcpy(ll->str, arr[0]);
	ll->next = NULL;

	// Populate the rest of the list
	LLNode *next_node = ll;
	LLNode *curr_node;
	size_t str_len;
	for (int n = 1; n < len; n++) {
		curr_node = malloc(sizeof(LLNode));
		curr_node->next = next_node;
		curr_node->prev = NULL;
		next_node->prev = curr_node;
		curr_node->str = malloc(strlen(arr[n]) + 1);
		strcpy(curr_node->str, arr[n]);
		next_node = curr_node;
	}

	return ll;
}

char *make_up_word()
{
	srand(time(NULL));
	int len = rand() % 1024;
	char *word = malloc(len + 1);
	for (int n = 0; n < len; n++) {
		word[n] = 65 + (rand() % (122 - 65));
	}
	word[len] = '\0';

	return word;
}

int test_step()
{
	srand(time(NULL));
	const size_t len = rand() % 1024;
	char **arr = malloc(len * sizeof(char **));
	for (int n = 0; n < len; n++) {
		arr[n] = make_up_word();
	}
	LLNode *ll = arr2list(arr, len);

	for (int n = 0; n < len; n++) {
		if (strcmp(arr[n], ll->str) != 0) {
			printf("Words %s and %s at index %d don't match between array and list\n",
					arr[n], ll->str, n);
			return -1;
		}
	}
	
	return 1;
}

int test()
{
	srand(42);
	for (int n = 0; n < 10; n++) {
		if (!test_step()) {
			printf("Test %d failed \n", n);
			return -1;
		}

		printf("Test %d passed\n", n);
	}
	puts("All tests passed!");

	return 1;
}

int main()
{
	test();

	return 0;
}
