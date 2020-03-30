#pragma once
#ifndef FILE_WRITER
#define FILE_WRITER

#define _CRT_SECURE_NO_WARNINGS
#include "datastructs.h"

/*
* Schrijf een buffer naar een bestand met naam 'filename'.
*/
void write_file(char* filename, FileBuffer* fbuffer);

#endif
