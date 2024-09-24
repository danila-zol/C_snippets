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
	char *data;
	uint64_t neighbours_count;
	struct Neighbour {
		struct GraphNode *n;
		struct Neighbour *next;
	} *neighbours;
};


struct Graph {
	size_t size;
	struct GraphNode nodes[];
};

typedef struct LLNode LLNode;
typedef struct LLNode DQueue;
typedef struct GraphNode GraphNode;
typedef struct Graph Graph;

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

LLNode *stack(LLNode *q, LLNode *node)
{
	q->next = node;
	node->prev = q;
	return node;
}

LLNode *pop(LLNode *q) 
{
	LLNode *prev_node = q->prev;
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

int graph_add_node(struct Graph **g, struct GraphNode *gn)
{
	if (!(*g = realloc(*g, sizeof(*g) + ((*g)->size + 1) * sizeof(struct GraphNode)))) {
		return -1;
	}

	(*g)->size++;
	memcpy((*g)->nodes + ((*g)->size - 1), gn, sizeof(*gn));

	return 1;
}

int node_add_neighbour(struct GraphNode *g, struct GraphNode *neighbour)
{
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
	size_t len = 8;
	char *names[8] = {"You", "Alice", "Bob", "Claire", "Preggy", "Anuj", "Thom", "Jhonny"};
	struct Graph *graph = malloc(sizeof(struct Graph));
	graph->size = 0;

	struct GraphNode *gn = malloc(sizeof(*gn));
	for (int n = 0; n < len; n++) {
		gn->data = malloc(strlen(names[n]) + 1);
		strcpy(gn->data, names[n]);
		graph_add_node(&graph, gn);
	}
	free(gn);
	struct GraphNode *nodes = graph->nodes;

	for (int n = 0; n < len; n++) {
		printf("%lu: %s\n", (unsigned long) (graph->nodes + n), graph->nodes[n].data);
	}

	// for (int n = 0; n < len; n++) {
	// 	struct GraphNode gn = graph->nodes[n];
	// 	switch (n) {
	// 		case 0:
	// 			node_add_neighbour(&gn, &graph->nodes[2]);
	// 			node_add_neighbour(&gn, &graph->nodes[1]);
	// 			node_add_neighbour(&gn, &graph->nodes[3]);
	// 	}
	// }

	return 0;
}
