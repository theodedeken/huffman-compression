#pragma once
#ifndef FILE_BUFFER
#define FILE_BUFFER

#include "datastructs.h"

/*
* Geef de volgende char(byte) terug in de buffer.
*/
unsigned char buffer_next_char(FileBuffer* fbuffer);

/*
* Alloceer geheugen voor een FileBuffer
*/
FileBuffer* buffer_alloc();

/*
* Alloceer geheugen voor een FileBuffer van 'size' grootte.
*/
FileBuffer* buffer_alloc_size(int size);

/*
* Schrijf een char(byte) in de buffer.
*/
void buffer_write_char(FileBuffer* fbuffer, unsigned char c);

/*
* Geef het geheugen vrij die wordt gebruikt door de buffer.
*/
void buffer_free(FileBuffer* fbuffer);

/*
* Schrijf 'length' aantal bits weg in de buffer.
*/
void buffer_write_bits(FileBuffer* fbuffer, unsigned long long bits, int length);

/*
* Schrijf één bit in de buffer.
*/
void buffer_write_bit(FileBuffer* fbuffer, unsigned int bit);

/*
* Schrijf een woord van grootte 'length' in de buffer.
*/
void buffer_write_string(FileBuffer* fbuffer, char* string, int length);

/*
* Geef de volgende bit terug in de iteratie van de buffer.
*/
int buffer_next_bit(FileBuffer* fbuffer);

/*
* Geef de volgende 'amount' bits terug in de iteratiee van de buffer.
*/
unsigned long long buffer_next_bits(FileBuffer* fbuffer, int amount);

/*
* Zet pointer terug op 0 zodat buffer opnieuw gelezen kan worden.
*/
void buffer_flip(FileBuffer* fbuffer);

/*
* Schrijf de bitbuffer naar de buffer.
*/
void buffer_bit_flush(FileBuffer* fbuffer);

#endif