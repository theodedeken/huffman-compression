#include "long_buffer.h"
#include "file_buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LongBuffer* convert_to_lbuffer(FileBuffer* fbuffer) {
	LongBuffer* lbuffer = longbuffer_alloc();
	buffer_next_char(fbuffer);
	unsigned char next = buffer_next_char(fbuffer);
	unsigned char* buf = calloc(20, sizeof(char));
	int i = 0;
	while (next != ']') {
		if (next == ',') {
			buf = realloc(buf, i);
			unsigned long long l = atoll(buf);
			buffer_write_long(lbuffer, l);
			free(buf);
			buf = calloc(20, sizeof(char));
			i = 0;
		}
		else {
			buf[i] = next;
			i++;
		}
		next = buffer_next_char(fbuffer);
	}
	buf = realloc(buf, i);
	unsigned long long l = atoll(buf);
	buffer_write_long(lbuffer, l);
	free(buf);
	return lbuffer;
}

LongBuffer* longbuffer_alloc() {
	LongBuffer* res = (LongBuffer*)calloc(1, sizeof(LongBuffer));
	if (res == NULL) {
		printf("ERROR: could not allocate buffer \n");
		exit(1);
	}
	res->buffer = calloc(8, sizeof(long long));
	if (res->buffer == NULL) {
		printf("ERROR: could not allocate buffer \n");
		exit(1);
	}
	res->max_size = 8;
	return res;
}

FileBuffer* convert_to_fbuffer(LongBuffer* lbuffer) {
	FileBuffer* fbuffer = buffer_alloc();
	buffer_write_char(fbuffer, '[');
	unsigned long long next = buffer_next_long(lbuffer);
	while (buffer_has_next(lbuffer)) {
		char buf[20];
		sprintf(buf, "%llu", next);
		buffer_write_string(fbuffer, buf, strlen(buf));
		buffer_write_char(fbuffer, ',');
		next = buffer_next_long(lbuffer);
	}
	char buf[20];
	sprintf(buf, "%llu", next);
	buffer_write_string(fbuffer, buf, strlen(buf));
	buffer_write_char(fbuffer, ']');
	return fbuffer;
}

unsigned long long buffer_next_long(LongBuffer* lbuffer) {
	unsigned long long ret = lbuffer->buffer[lbuffer->pointer];
	lbuffer->pointer++;
	return ret;
}

void buffer_write_long(LongBuffer* lbuffer, unsigned long long l) {
	if (lbuffer->size < lbuffer->max_size) {
		lbuffer->buffer[lbuffer->size] = l;
		lbuffer->size++;
	}
	else {
		lbuffer->buffer = (unsigned long long*)realloc(lbuffer->buffer, lbuffer->max_size * 2 * sizeof(long long));
		if (lbuffer->buffer == NULL) {
			printf("ERROR: could not reallocate buffer \n");
			exit(1);
		}
		lbuffer->max_size = lbuffer->max_size * 2;
		buffer_write_long(lbuffer, l);
	}
}

lbuffer_free(LongBuffer* lbuffer) {
	free(lbuffer->buffer);
	lbuffer->max_size = 0;
	lbuffer->pointer = 0;
	lbuffer->size = 0;
	free(lbuffer);
}

int buffer_has_next(LongBuffer* lbuffer){
	return lbuffer->pointer < lbuffer->size;
}

