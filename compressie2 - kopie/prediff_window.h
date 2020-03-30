#pragma once
#define G 256

typedef struct {
	int a;
	int b;
	unsigned long long difference;
} Match;

typedef struct {
	unsigned long long* window_buffer;
	int length;
	int pointer;
} PDWindow;

PDWindow* window_create(unsigned long long first,unsigned long long second);

Match* window_search_match(PDWindow* window, unsigned long long next);

unsigned long long window_retrieve_match(PDWindow* window, Match* match);

void window_free(PDWindow* window);

void window_add(PDWindow* window, unsigned long long next);

int long_num_bytes(unsigned long long l);