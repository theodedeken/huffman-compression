#include "huffman_map.h"
#include "huffman_queue.h"
#include <math.h>
#include <stdlib.h>

HuffmanMap* map_alloc() {
	HuffmanMap* map = (HuffmanMap*)calloc(1, sizeof(HuffmanMap));
	//allocate an array with size 2^8 so that every char has an unique location 
	map->items = (HuffmanNode**)calloc((int)pow(2,8), sizeof(HuffmanNode*));
	return map;
}

void map_free(HuffmanMap* map) {
	free(map->items);
	free(map);
}

void map_insert(HuffmanMap* map, unsigned char key, HuffmanNode* item) {
	map->items[key] = item;
}

HuffmanNode* map_find(HuffmanMap* map, unsigned char key) {
	return map->items[key];
}

void map_fill_pqueue(HuffmanMap* map, HuffmanQueue* pqueue) {
	int i;
	int limit = (int)pow(2, 8);
	for (i = 0; i < limit; i++) {
		if (map_contains(map, i)) {
			pqueue_add(pqueue, map->items[i]);
		}
	}
}

int map_contains(HuffmanMap* map, unsigned char key) {	
	return map->items[key] != NULL;
}