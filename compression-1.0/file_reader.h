#pragma once
#ifndef FILE_READER
#define FILE_READER

#define _CRT_SECURE_NO_WARNINGS
#include "datastructs.h"

/*
* Lees een bestand uit met naam 'filename'.
*/
FileBuffer* read_file(char* filename);

#endif