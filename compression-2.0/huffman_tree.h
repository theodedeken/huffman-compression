#pragma once
#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include "datastructs.h"

HuffmanNode* tree_connect(HuffmanNode* left, HuffmanNode* right);

void tree_set_codes(HuffmanNode* root, int depth, int value);

void tree_write_buffer(HuffmanNode* root, FileBuffer* fbuffer);

HuffmanNode* tree_reconstruct(HuffmanNode* root, FileBuffer* fbuffer);

void tree_free(HuffmanNode* root);

void tree_print(HuffmanNode* root, int i);

#endif