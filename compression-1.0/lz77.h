#pragma once
#ifndef LZ77
#define LZ77

#include "datastructs.h"
#include "window.h"

FileBuffer* lz77_encode(FileBuffer* fbuffer);

void write_match(FileBuffer* fbuffer, Match match);

Match read_match(FileBuffer* fbuffer);

FileBuffer* lz77_decode(FileBuffer* fbuffer);

#endif
