#pragma once
#include "datastructs.h"
#include "long_buffer.h"
#include "prediff_window.h"

FileBuffer* prediff_encode(LongBuffer* lbuffer);

LongBuffer* prediff_decode(FileBuffer* fbuffer);

Match* read_match(FileBuffer* fbuffer);

void write_match(FileBuffer* fbuffer, Match* match);


