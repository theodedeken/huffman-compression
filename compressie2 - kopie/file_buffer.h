#pragma once
#ifndef FILE_BUFFER
#define FILE_BUFFER

#include "datastructs.h"

unsigned char buffer_next_char(FileBuffer* fbuffer);

FileBuffer* buffer_alloc();

FileBuffer* buffer_alloc_size(int size);

void buffer_write_char(FileBuffer* fbuffer, unsigned char c);

void buffer_free(FileBuffer* fbuffer);

void buffer_write_bits(FileBuffer* fbuffer, unsigned long long bits, int length);

void buffer_write_bit(FileBuffer* fbuffer, unsigned int bit);

void buffer_write_string(FileBuffer* fbuffer, char* string, int length);

int buffer_next_bit(FileBuffer* fbuffer);

unsigned long long buffer_next_bits(FileBuffer* fbuffer, int amount);

void buffer_flip(FileBuffer* fbuffer);

void buffer_compact(FileBuffer* fbuffer);

void buffer_bit_flush(FileBuffer* fbuffer);

#endif