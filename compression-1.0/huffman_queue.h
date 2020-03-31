#pragma once
#ifndef HUFFMAN_QUEUE
#define HUFFMAN_QUEUE

#include "datastructs.h"

/*
* Struct om priorityqueue van HuffmanNodes voor te stellen. Als datastructuur wordt een binaire boom gebruikt.
* items: de hoop als een array voorgestelt
* item_count: hoeveelheid items
* item_max_count: maximale hoeveelheid items waarvoor er geheugen is gealloceerd
*/
typedef struct
{
	HuffmanNode** items;
	int item_count;
	int item_max_count;
} HuffmanQueue;

/*
* Alloceer geheugen voor een priorityqueue.
*/
HuffmanQueue* pqueue_alloc();

/*
* Geef het geheugen vrij van de priorityqueue.
*/
void pqueue_free(HuffmanQueue* queue);

/*
* Geef het bovenste item terug van de priorityqueue en herbalanceer.
*/
HuffmanNode* pqueue_remove_first(HuffmanQueue* q);

/*
* Voeg een item toe aan de priorityqueue.
*/
void pqueue_add(HuffmanQueue* q, HuffmanNode* node);

/*
* Wissel twee items van plaats.
*/
void pqueue_swap_items(HuffmanQueue* q, int index1, int index2);

/*
* Herbalanceer hoop naar omhoog.
*/
void pqueue_fix_up(HuffmanQueue* q, int index);

/*
* Herbalanceer hoop naar omlaag.
*/
void pqueue_fix_down(HuffmanQueue* q, int index);

#endif