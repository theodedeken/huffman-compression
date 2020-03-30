#pragma once
#ifndef DATASTRUCT
#define DATASTRUCT

/*
* Struct dat een node voorstelt die kan gebruikt worden in de map, priorityqueue en boom 
* die nodig is om huffmancodering uit te voeren.
*/
typedef struct HuffmanNode HuffmanNode;

struct HuffmanNode
{
	unsigned char c;
	int leaf;
	unsigned int count;
	HuffmanNode* leftchild;
	HuffmanNode* rightchild;
	unsigned int bit_value;
	unsigned int bit_length;
};

/*
* Struct die een buffer van bytes voorstelt.
*/
typedef struct
{
	unsigned char* buffer;
	unsigned int max_size;
	unsigned int size;
	unsigned int pointer;
	unsigned int char_buffer;
	unsigned int bitcount;
}FileBuffer;

#endif