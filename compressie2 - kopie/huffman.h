#pragma once
#ifndef HUFFMAN
#define HUFFMAN

#include "datastructs.h"

FileBuffer* huffman_encode(FileBuffer* fbuffer);

FileBuffer* huffman_decode(FileBuffer* fbuffer);

#endif
