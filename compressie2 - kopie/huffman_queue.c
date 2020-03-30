#include "huffman_queue.h"

#include <stdlib.h>
#include <stdio.h> 

HuffmanQueue* pqueue_alloc() {
	int initial_max_items = 8;
	HuffmanQueue* res = (HuffmanQueue*)calloc(1, sizeof(HuffmanQueue));
	if (res == NULL) {
		printf("ERROR: pointer equals NULL\n");
		exit(1);
	}
	res->item_max_count = initial_max_items;

	res->item_count = 0;
	// binairy heap implementation leaves index 0 empty
	res->items = (HuffmanNode**)calloc(initial_max_items + 1, sizeof(HuffmanNode*));
	if (res->items == NULL) {
		free(res);
		printf("ERROR: pointer equals NULL\n");
		exit(1);
	}
	return res;
}

void pqueue_free(HuffmanQueue* queue) {
	queue->item_max_count = 0;
	queue->item_count = 0;
	free(queue->items);
	free(queue);
}

void pqueue_add(HuffmanQueue* q, HuffmanNode* node) {

	if (q->item_count == q->item_max_count) {
		int new_size = q->item_max_count * 2;
		q->items = realloc(q->items, (new_size + 1) * sizeof(HuffmanNode*));
		q->item_max_count = new_size;
	}
	q->item_count++;
	q->items[q->item_count] = node;
	pqueue_fix_up(q, q->item_count);

}

void pqueue_fix_up(HuffmanQueue* q, int index) {
	int child = index;
	int parent = index / 2;

	while (parent != 0 && q->items[parent]->count > q->items[child]->count) {
		pqueue_swap_items(q, parent, child);
		child = parent;
		parent /= 2;
	}
}

void pqueue_fix_down(HuffmanQueue* q, int index) {
	int parent = index;
	int child1 = parent * 2;
	int child2 = parent * 2 + 1;
	int balanced = 0;

	while (!balanced) {
		if (child1 > q->item_count) {
			balanced = 1;
		}
		else if (child1 == q->item_count) {
			if (q->items[parent]->count > q->items[child1]->count) {
				pqueue_swap_items(q, parent, child1);
			}
			balanced = 1;
		}
		else {
			if (q->items[parent]->count <= q->items[child1]->count && q->items[parent]->count <= q->items[child2]->count) {
				balanced = 1;
			}
			else if (q->items[child1]->count <= q->items[child2]->count) {
				pqueue_swap_items(q, parent, child1);
				parent = child1;
				child1 = parent * 2;
				child2 = parent * 2 + 1;
			}
			else {
				pqueue_swap_items(q, parent, child2);
				parent = child2;
				child1 = parent * 2;
				child2 = parent * 2 + 1;
			}
		}
	}
}

void pqueue_swap_items(HuffmanQueue* q, int index1, int index2) {
	HuffmanNode* temp = q->items[index1];
	q->items[index1] = q->items[index2];
	q->items[index2] = temp;
}

HuffmanNode* pqueue_remove_first(HuffmanQueue* q) {
	if (q->item_count == 0) {
		return NULL;
	}

	HuffmanNode* first = q->items[1];

	HuffmanNode* last = q->items[q->item_count];
	q->items[1] = last;
	q->items[q->item_count] = NULL;
	q->item_count--;

	pqueue_fix_down(q, 1);
	return first;
}