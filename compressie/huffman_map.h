#pragma once
#ifndef HUFFMAN_MAP
#define HUFFMAN_MAP

#include "datastructs.h"
#include "huffman_queue.h"

/*
* Struct om een map van HuffmanNodes voor te stellen met als key unsigned char.
*/
typedef struct
{
	HuffmanNode** items;
} HuffmanMap;

/*
* Alloceer geheugen voor 2^8 items zodat ieder unsigned char wijst naar een unieke plaats.
*/
HuffmanMap* map_alloc();

/*
* Geef geheugen vrij gebruikt door de map.
*/
void map_free(HuffmanMap* map);

/*
* Voeg een HuffmanNode toe op de plaats aangegeven door de key.
*/
void map_insert(HuffmanMap* map, unsigned char key, HuffmanNode* item);

/*
* Geef de HuffmanNode terug die op plaats key is opgeslagen.
*/
HuffmanNode* map_find(HuffmanMap* map, unsigned char key);

/*
* Voeg alle items van deze map toe aan een priorityqueue.
*/
void map_fill_pqueue(HuffmanMap* map, HuffmanQueue* pqueue);

/*
* Geef terug of er al een HuffmanNode is opgeslagen op plaats key.
*/
int map_contains(HuffmanMap* map, unsigned char key);

#endif

