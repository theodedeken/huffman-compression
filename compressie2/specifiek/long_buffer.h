#pragma once
#ifndef LONG_BUFFER
#define LONG_BUFFER
#define _CRT_SECURE_NO_WARNINGS

#include "../datastructs.h"

/*
* struct die een buffer van long long getallen voorstelt.
* buffer: de getallen
* max_size: maximaal aantal getallen waarvoor geheugen is gealloceerd
* size: hoeveelheid getallen in buffer
* pointer: wijst huidige getal, wordt gebruikt voor iteratie van getallen
*/
typedef struct
{
	unsigned long long* buffer;
	unsigned int max_size;
	unsigned int size;
	unsigned int pointer;
}LongBuffer;

/*
* Converteert een FileBuffer naar een Longbuffer door de tekstuele voorstellingen van de getallen
* in te lezen en om te zetten naar long long.
*/
LongBuffer* convert_to_lbuffer(FileBuffer* fbuffer);

/*
* Alloceer geheugen voor een LongBuffer.
*/
LongBuffer* longbuffer_alloc();

/*
* Converteer een Longbuffer naar een FileBuffer door ieder getal om te zetten naar zijn tekstuele representatie
* en deze in de buffer te schrijven.
*/
FileBuffer* convert_to_fbuffer(LongBuffer* lbuffer);

/*
* Geef het volgende getal terug in de iteratie van de buffer.
*/
unsigned long long buffer_next_long(LongBuffer* lbuffer);

/*
* Schrijf een getal in de buffer, realloceer als het nodig is.
*/
void buffer_write_long(LongBuffer* lbuffer, unsigned long long l);

/*
* Geef het geheugen vrij die wordt ingenomen door de buffer.
*/
void lbuffer_free(LongBuffer* lbuffer);

/*
* Geef terug of deze buffer volledig geïtereerd is of niet.
*/
int buffer_has_next(LongBuffer* lbuffer);

#endif