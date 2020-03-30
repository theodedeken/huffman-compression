#include "prediff_window.h"
#include <math.h>

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
	int a = 0;
	int b = 1;
	Match* match = (Match*)calloc(1, sizeof(Match));
	match->difference = dif;
	while (a != b) {
		long long difference = dif - (window->window_buffer[(window->pointer + b + 1)%window->length] - window->window_buffer[(window->pointer + a +1)%window->length]);
		if (abs(difference) < 256 && match->difference > abs(difference)) {
			if (difference > 0) {
				match->a = a;
				match->b = b;
				match->difference = difference;
			}
			else {
				match->a = b;
				match->b = a;
				match->difference = -difference;
			}
			
		}
		if (difference < 0 && a != b - 1) {
			a++;
		}
		else {
			if (b != window->length - 1) {
				b++;
			}
			else {
				a++;
			}
		}
	}
	if (match->a == match->b) {
		int bytes = long_num_bytes(match->difference);
		match->a = bytes - 1;
		match->b = bytes - 1;
	}
	window_add(window, next);
	return match;
}

int long_num_bytes(unsigned long long l) {
	int i = 1;
	while (i <= 8) {
		if (pow(2, i * 8) < l) {
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
	if (match->a == match->b) {
		next = window->window_buffer[window->pointer] + match->difference;
	}
	else {
		if (match->a < match->b) {
			unsigned long long dif = match->difference + window->window_buffer[(window->pointer + 1 + match->b) % window->length] - window->window_buffer[(window->pointer + 1 + match->a) % window->length];
			next = window->window_buffer[window->pointer] + dif;
		}
		else {
			unsigned long long dif = window->window_buffer[(window->pointer + 1 + match->a) % window->length] - window->window_buffer[(window->pointer + 1 + match->b) % window->length] - match->difference;
			next = window->window_buffer[window->pointer] + dif;
		}
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