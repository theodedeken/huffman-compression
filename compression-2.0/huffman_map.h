#pragma once
#ifndef HUFFMAN_MAP
#define HUFFMAN_MAP

#include "datastructs.h"
#include "huffman_queue.h"

typedef struct
{
	HuffmanNode** items;
} HuffmanMap;

HuffmanMap* map_alloc();

void map_free(HuffmanMap* map);

void map_insert(HuffmanMap* map, unsigned char key, HuffmanNode* item);

HuffmanNode* map_find(HuffmanMap* map, unsigned char key);

void map_fill_pqueue(HuffmanMap* map, HuffmanQueue* pqueue);

int map_contains(HuffmanMap* map, unsigned char key);

#endif

