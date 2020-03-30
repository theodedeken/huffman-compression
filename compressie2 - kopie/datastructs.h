#pragma once
#ifndef DATASTRUCT
#define DATASTRUCT

/*
* This struct represents a node which holds all the information to make the huffman tree
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
* Struct for reading and writing text or binary data
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