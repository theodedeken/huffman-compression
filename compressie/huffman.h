#pragma once
#ifndef HUFFMAN
#define HUFFMAN

#include "datastructs.h"

/*
* Pas huffmancodering toe op een buffer.
*/
FileBuffer* huffman_encode(FileBuffer* fbuffer);

/*
* Reconstrueer de originele buffer.
*/
FileBuffer* huffman_decode(FileBuffer* fbuffer);

#endif
