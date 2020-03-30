#pragma once
#ifndef PREDIF
#define PREDIF

#include "../datastructs.h"
#include "long_buffer.h"
#include "prediff_window.h"

/*
* Encodeer een reeks van getallen met behulp van predictie en verschillen.
*/
FileBuffer* prediff_encode(LongBuffer* lbuffer);

/*
* Decodeer een reeks van bytes terug naar getallen.
*/
LongBuffer* prediff_decode(FileBuffer* fbuffer);

/*
* Lees het struct uit dat de predictie en verschil voorstelt.
*/
Match* read_match(FileBuffer* fbuffer);

/*
* Schrijf het struct in de buffer.
*/
void write_match(FileBuffer* fbuffer, Match* match);

#endif
