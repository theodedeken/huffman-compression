#include "datastructs.h"
#include "file_reader.h"
#include "file_writer.h"
#include "huffman.h"
#include "file_buffer.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Fout aantal argumenten, juist gebruik van deze functie is: \ncomprimeren: comprimeer1 -c <input> <output> \ndecoderen: comprimeer1 -d <input> <output>");
		return 1;
	}

	char mode = argv[1][1];
	char* input = argv[2];
	char* output = argv[3];
	//als encoding is:
	if (mode == 'c') {
		//lees bestand in buffer
		FileBuffer* file = read_file(input);
	}
	//als decoding is:
	else if (mode == 'd') {

		//lees bestand in buffer
		FileBuffer* huffman = read_file(input);
		
	}
	else {
		//fout gebruik
		printf("Foute modus, juist gebruik van deze functie is: \ncomprimeren: comprimeer1 -c <input> <output> \ndecoderen: comprimeer1 -d <input> <output>");
		return 1;
	}

	return 0;
}

