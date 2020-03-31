#include "predictive_difference.h"

#include "file_buffer.h"

FileBuffer* prediff_encode(LongBuffer* lbuffer) {
	//maak filebuffer aan
	FileBuffer* fbuffer = buffer_alloc();
	//lees eerste 2 getallen en schrijf ze in de fbuffer
	unsigned long long first = buffer_next_long(lbuffer);
	unsigned long long second = buffer_next_long(lbuffer);
	buffer_write_bits(fbuffer, first, 64);
	buffer_write_bits(fbuffer, second, 64);
	//maak window aan
	PDWindow* window = window_create(first, second);
	unsigned long long next;
	//zolang er nog getallen zijn in de lbuffer
	while (buffer_has_next(lbuffer)) {
		next = buffer_next_long(lbuffer);
		//vraag de langste match aan de window
		Match* match = window_search_match(window, next);
		//schrijf de match in de buffer
		write_match(fbuffer, match);
		free(match);
	}
	window_free(window);
	return fbuffer;	
}

LongBuffer* prediff_decode(FileBuffer* fbuffer) {
	//maak longbuffer aan
	LongBuffer* lbuffer = longbuffer_alloc();
	//lees eerste 2 getallen uit fbuffer
	unsigned long long first = buffer_next_bits(fbuffer, 64);
	unsigned long long second = buffer_next_bits(fbuffer, 64); 
	//schrijf eerste 2 getallen in longbuffer
	buffer_write_long(lbuffer, first);
	buffer_write_long(lbuffer, second);
	//maak de window aan met deze getallen
	PDWindow* window = window_create(first, second);
	//zolang er nog karakters zijn in de fbuffer
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
	unsigned char a = buffer_next_char(fbuffer);
	unsigned char b = buffer_next_char(fbuffer);
	
	Match* match = (Match*)calloc(1, sizeof(Match));
	match->a = a;
	match->b = b;
	if (a == b) {
		match->difference = buffer_next_bits(fbuffer, (a + 1) * 8);
	}
	else {
		match->difference = buffer_next_char(fbuffer);
	}
	return match;
}

void write_match(FileBuffer* fbuffer, Match* match) {
	buffer_write_char(fbuffer, match->a);
	buffer_write_char(fbuffer, match->b);
	if (match->a == match->b) {
		buffer_write_bits(fbuffer, match->difference, (match->a + 1) * 8);
	}
	else {		
		buffer_write_char(fbuffer, match->difference);
	}
}

