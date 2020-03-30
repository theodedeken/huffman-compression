#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "datastructs.h"
typedef struct
{
	unsigned long long* buffer;
	unsigned int max_size;
	unsigned int size;
	unsigned int pointer;
}LongBuffer;

LongBuffer* convert_to_lbuffer(FileBuffer* fbuffer);

LongBuffer* longbuffer_alloc();

FileBuffer* convert_to_fbuffer(LongBuffer* lbuffer);

unsigned long long buffer_next_long(LongBuffer* lbuffer);

void buffer_write_long(LongBuffer* lbuffer, unsigned long long l);

lbuffer_free(LongBuffer* lbuffer);

int buffer_has_next(LongBuffer* lbuffer);
