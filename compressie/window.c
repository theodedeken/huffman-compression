#include "window.h"
#include "file_buffer.h"

#include <stdlib.h>

Window* window_alloc() {
	Window* window = (Window*)calloc(1, sizeof(Window));
	window->window_buffer = calloc(G, sizeof(char));
	return window;
}

void window_free(Window* window) {
	free(window->window_buffer);
	window->length = 0;
	window->pointer = 0;
	free(window);
}

Match window_find_match(Window* window, FileBuffer* fbuffer) {
	//TODO implement

}

char* window_get_match(Window* window, Match match) {
	//TODO implement
}

void window_slide(Window* window, int distance, FileBuffer* fbuffer) {
	int i;
	if (window->length < G) {
		int newlength = window->length + distance;
		if (newlength > G) {
			window->length = G;
		}
		else {
			window->length = newlength;
		}
	}
	for (i = 0; i < distance; i++) {
		window->window_buffer[window->pointer] = buffer_next_char(fbuffer);
		window->pointer = (window->pointer + 1) % G;
	}
}