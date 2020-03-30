#include "predictive_difference.h"

#include "../file_buffer.h"

#include <stdlib.h>

FileBuffer* prediff_encode(LongBuffer* lbuffer) {
	FileBuffer* fbuffer = buffer_alloc();
	unsigned long long first = buffer_next_long(lbuffer);
	unsigned long long second = buffer_next_long(lbuffer);
	buffer_write_bits(fbuffer, first, 64);
	buffer_write_bits(fbuffer, second, 64);
	PDWindow* window = window_create(first, second);
	unsigned long long next;
	while (buffer_has_next(lbuffer)) {
		next = buffer_next_long(lbuffer);
		Match* match = window_search_match(window, next);
		write_match(fbuffer, match);
		free(match);
	}
	window_free(window);
	return fbuffer;	
}

LongBuffer* prediff_decode(FileBuffer* fbuffer) {
	LongBuffer* lbuffer = longbuffer_alloc();
	unsigned long long first = buffer_next_bits(fbuffer, 64);
	unsigned long long second = buffer_next_bits(fbuffer, 64); 
	buffer_write_long(lbuffer, first);
	buffer_write_long(lbuffer, second);
	PDWindow* window = window_create(first, second);
	while (fbuffer->pointer < fbuffer->size){
		Match* match = read_match(fbuffer);
		unsigned long long next = window_retrieve_match(window, match);
		buffer_write_long(lbuffer, next);
		free(match);
	}
	window_free(window);
	return lbuffer;
}

Match* read_match(FileBuffer* fbuffer) {
	unsigned char abytes = buffer_next_char(fbuffer);
	Match* match = (Match*)calloc(1, sizeof(Match));
	match->a = (abytes & 224) >> 5;
	match->neg = (abytes & 16) >> 4;
	match->bytes = abytes & 15;
	match->difference = buffer_next_bits(fbuffer, (match->bytes + 1) * 8);
	return match;
}

void write_match(FileBuffer* fbuffer, Match* match) {
	buffer_write_char(fbuffer, match->a << 5 | match->neg << 4 | match->bytes);
	buffer_write_bits(fbuffer, match->difference, (match->bytes + 1) * 8);
}

