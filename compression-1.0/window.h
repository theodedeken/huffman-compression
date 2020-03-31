#pragma once
#ifndef WINDOW
#define WINDOW

#include "datastructs.h"
#define G 256

typedef struct {
	int pos;
	int length;
	char next;
} Match;

typedef struct {
	char* window_buffer;
	int length;
	int pointer;
} Window;

Window* window_alloc();

void window_free(Window* window);

Match window_find_match(Window* window, FileBuffer* fbuffer);

char* window_get_match(Window* window, Match match);

void window_slide(Window* window, int distance, FileBuffer* fbuffer);

#endif
