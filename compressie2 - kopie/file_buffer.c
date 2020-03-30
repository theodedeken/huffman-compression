#include "file_buffer.h"
#include <stdlib.h>

unsigned char buffer_next_char(FileBuffer* fbuffer) {
	if (fbuffer->pointer < fbuffer->size) {
		unsigned char ret = fbuffer->buffer[fbuffer->pointer];
		fbuffer->pointer++;
		return ret;
	}
	else {
		return NULL;
	}
}

FileBuffer* buffer_alloc() {
	FileBuffer* res = (FileBuffer*)calloc(1, sizeof(FileBuffer));
	if (res == NULL) {
		printf("ERROR: could not allocate buffer \n");
		exit(1);
	}
	res->buffer = calloc(8, sizeof(char));
	if (res->buffer == NULL) {
		printf("ERROR: could not allocate buffer \n");
		exit(1);
	}
	res->max_size = 8;
	return res;
}

FileBuffer* buffer_alloc_size(int size) {
	FileBuffer* res = (FileBuffer*)calloc(1, sizeof(FileBuffer));
	if (res == NULL) {
		printf("ERROR: could not allocate buffer \n");
		exit(1);
	}
	res->buffer = calloc(size, sizeof(char));
	if (res->buffer == NULL) {
		printf("ERROR: could not allocate buffer \n");
		exit(1);
	}
	res->max_size = size;
	res->size = size;
	return res;
}

void buffer_write_char(FileBuffer* fbuffer, unsigned char c) {
	if (fbuffer->size < fbuffer->max_size) {
		fbuffer->buffer[fbuffer->size] = c;
		fbuffer->size++;
	}
	else {
		fbuffer->buffer = realloc(fbuffer->buffer, fbuffer->max_size * 2 * sizeof(char));
		if (fbuffer->buffer == NULL) {
			printf("ERROR: could not reallocate buffer \n");
			exit(1);
		}
		fbuffer->max_size = fbuffer->max_size * 2;
		buffer_write_char(fbuffer, c);
	}
}

void buffer_free(FileBuffer* fbuffer) {
	fbuffer->bitcount = 0;
	fbuffer->char_buffer = NULL;
	fbuffer->max_size = 0;
	fbuffer->pointer = 0;
	fbuffer->size = 0;
	free(fbuffer->buffer);
	free(fbuffer);
}

void buffer_write_bits(FileBuffer* fbuffer, unsigned long long bits, int length) {
	int i;
	unsigned long long one = 1;
	for (i = 0; i < length; i++) {
		unsigned long long bit = (bits & (one << (length - 1 - i))) >> (length - 1 - i);
		buffer_write_bit(fbuffer, bit);
	}
}

void buffer_write_bit(FileBuffer* fbuffer, unsigned int bit) {
	fbuffer->char_buffer = fbuffer->char_buffer << 1 | bit;
	fbuffer->bitcount++;
	if (fbuffer->bitcount == 8){
		buffer_write_char(fbuffer, fbuffer->char_buffer);
		fbuffer->char_buffer = 0;
		fbuffer->bitcount = 0;
	}
}

void buffer_bit_flush(FileBuffer* fbuffer) {
	while (fbuffer->bitcount != 0) {
		buffer_write_bit(fbuffer, 0);
	}
}

int buffer_next_bit(FileBuffer* fbuffer) {
	if (fbuffer->bitcount == 0) {
		if (fbuffer->pointer < fbuffer->size) {
			fbuffer->char_buffer = buffer_next_char(fbuffer);
			fbuffer->bitcount = 8;
		}
		else {
			return -1;
		}
		
	}
	int bit = (fbuffer->char_buffer & (1 << (fbuffer->bitcount - 1))) >> (fbuffer->bitcount - 1);
	fbuffer->bitcount--;
	return bit;
}

void buffer_flip(FileBuffer* fbuffer) {
	fbuffer->pointer = 0;
}

void buffer_write_string(FileBuffer* fbuffer, char* string, int length) {
	int i;
	for (i = 0; i < length; i++) {
		buffer_write_char(fbuffer, string[i]);
	}
}

unsigned long long buffer_next_bits(FileBuffer* fbuffer, int amount) {
	unsigned long long value = 0;
	int i;
	for (i = 0; i < amount; i++) {
		value = value << 1 | buffer_next_bit(fbuffer);
	}
	return value;
}

void buffer_compact(FileBuffer* fbuffer) {
	fbuffer->buffer = realloc(fbuffer->buffer, fbuffer->size * sizeof(char));
}