#include "lz77.h"
#include "window.h"
#include "file_buffer.h"

FileBuffer* lz77_encode(FileBuffer* fbuffer) {
	//maak window aan
	Window* window = window_alloc();
	//maak nieuwe buffer aan
	FileBuffer* encoded = buffer_alloc();
	//lees nieuwe char
	while (fbuffer->pointer < fbuffer->size) {
		Match match = window_find_match(window, fbuffer);
		write_match(encoded, match);
		window_slide(window, match.length, fbuffer);
	}
	//geef window vrij
	window_free(window);
	//return buffer
	return encoded;
}

void write_match(FileBuffer* fbuffer, Match match) {
	buffer_write_char(fbuffer, match.pos);
	buffer_write_char(fbuffer, match.length);
	buffer_write_char(fbuffer, match.next);
}

Match read_match(FileBuffer* fbuffer) {
	Match match;
	match.pos = buffer_next_char(fbuffer);
	match.length = buffer_next_char(fbuffer);
	match.next = buffer_next_char(fbuffer);
	return match;
}

FileBuffer* lz77_decode(FileBuffer* fbuffer) {
	//maak window aan
	Window* window = window_alloc();
	//maak nieuwe buffer aan
	FileBuffer* decoded = buffer_alloc();
	//lees een drietal en blijf lezen tot buffer op is
	Match match = read_match(fbuffer);
	//achterhaal het woord mbv window en drietal
	char* string = window_get_match(window, match);
	//schrijf dat in de buffer
	buffer_write_string(decoded, string, match.length + 1);
	//geef window vrij
	window_free(window);
	//return buffer
	return decoded;
}