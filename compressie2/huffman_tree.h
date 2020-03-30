#pragma once
#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include "datastructs.h"

/*
* Verbind twee nodes in de boom door een nieuwe node aan te maken als ouder van de twee.
*/
HuffmanNode* tree_connect(HuffmanNode* left, HuffmanNode* right);

/*
* Overloop de boom en vul de bitcodes in van ieder blad
*/
void tree_set_codes(HuffmanNode* root, int depth, int value);

/*
* Schrijf de boom in de buffer.
*/
void tree_write_buffer(HuffmanNode* root, FileBuffer* fbuffer);

/*
* Lees de boom uit de buffer en reconstrueer.
*/
HuffmanNode* tree_reconstruct(HuffmanNode* root, FileBuffer* fbuffer);

/*
* Geef het geheugen vrij van de boom.
*/
void tree_free(HuffmanNode* root);

/*
* Debugmethode om de boom uit te printen.
*/
void tree_print(HuffmanNode* root, int i);

#endif