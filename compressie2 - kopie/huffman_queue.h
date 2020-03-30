#pragma once
#ifndef HUFFMAN_QUEUE
#define HUFFMAN_QUEUE

#include "datastructs.h"

typedef struct
{
	HuffmanNode** items;
	int item_count;
	int item_max_count;
} HuffmanQueue;

HuffmanQueue* pqueue_alloc();

void pqueue_free(HuffmanQueue* queue);

HuffmanNode* pqueue_remove_first(HuffmanQueue* q);

void pqueue_add(HuffmanQueue* q, HuffmanNode* node);

void pqueue_swap_items(HuffmanQueue* q, int index1, int index2);

void pqueue_fix_up(HuffmanQueue* q, int index);

void pqueue_fix_down(HuffmanQueue* q, int index);

#endif