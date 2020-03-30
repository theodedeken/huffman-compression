#include "prediff_window.h"
#include <math.h>
#include <stdlib.h>

PDWindow* window_create(unsigned long long first, unsigned long long second) {
	PDWindow* window = (PDWindow*)calloc(1, sizeof(PDWindow));
	window->window_buffer = calloc(G, sizeof(long long));
	window->window_buffer[0] = first;
	window->window_buffer[1] = second;
	window->length = 2;
	window->pointer = 1;
	return window;
}

void window_free(PDWindow* window) {
	free(window->window_buffer);
	window->length = 0;
	window->pointer = 0;
	free(window);
}

Match* window_search_match(PDWindow* window, unsigned long long next) {
	unsigned long long dif = next - window->window_buffer[window->pointer];
	int a = 1;
	Match* match = (Match*)calloc(1, sizeof(Match));
	match->difference = dif;
	while (a != window->length) {
		long long difference = dif - (window->window_buffer[window->pointer] - window->window_buffer[(window->pointer + window->length - a)%window->length]);
		if (match->difference > llabs(difference)) {
			if (difference > 0) {
				match->a = a;
				match->neg = 0;
				match->difference = difference;
			}
			else {
				match->a = a;
				match->neg = 1;
				match->difference = -difference;
			}
			
		}
		if (-difference > dif) {
			a = window->length;
		}
		else {
			a++;
		}
	}
	int bytes = long_num_bytes(match->difference);
	match->bytes = bytes -1;
	window_add(window, next);
	return match;
}

int long_num_bytes(unsigned long long l) {
	int i = 1;
	while (i <= 8) {
		if (pow(2, i * 8) -1 < l) {
			i++;
		}
		else {
			break;
		}
	}
	return i;
	
}

unsigned long long window_retrieve_match(PDWindow* window, Match* match) {
	unsigned long long next;
	if (match->a != 0) {
		if (!match->neg) {
			unsigned long long dif = match->difference + window->window_buffer[window->pointer] - window->window_buffer[(window->pointer + window->length - match->a) % window->length];
			next = window->window_buffer[window->pointer] + dif;
		}
		else {
			unsigned long long dif = window->window_buffer[window->pointer] - window->window_buffer[(window->pointer + window->length - match->a) % window->length] - match->difference;
			next = window->window_buffer[window->pointer] + dif;
		}
	}
	else {
		next = window->window_buffer[window->pointer] + match->difference;
	}
	window_add(window, next);
	return next;
}

void window_add(PDWindow* window, unsigned long long next) {
	if (window->length < G) {
		window->length++;
		window->pointer++;
	}
	else {
		window->pointer = (window->pointer + 1) % window->length;
	}
	window->window_buffer[window->pointer] = next;
}