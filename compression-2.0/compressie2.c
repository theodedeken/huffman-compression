#include "datastructs.h"
#include "file_reader.h"
#include "file_writer.h"
#include "huffman.h"
#include "file_buffer.h"
#include "long_buffer.h"
#include "predictive_difference.h"

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
		//converteer naar lijst van getallen
		LongBuffer* lbuffer = convert_to_lbuffer(file);
		buffer_free(file);
		//difference encoding van getallen
		FileBuffer* prediff = prediff_encode(lbuffer);
		lbuffer_free(lbuffer);
		buffer_flip(prediff);
		//huffman van de uitkomst
		FileBuffer* huffman = huffman_encode(prediff);
		buffer_free(prediff);
		//schrijf huffman naar bestand
		write_file(output, huffman);
		//free 
		buffer_free(huffman);
	}
	//als decoding is:
	else if (mode == 'd') {
		//lees bestand in buffer
		FileBuffer* huffman = read_file(input);
		//huffman decode
		FileBuffer* prediff = huffman_decode(huffman);
		buffer_free(huffman);
		buffer_flip(prediff);
		//omgekeerde difference
		LongBuffer* lbuffer = prediff_decode(prediff);
		buffer_free(prediff);
		//converteer naar filebuffer
		FileBuffer* file = convert_to_fbuffer(lbuffer);
		lbuffer_free(lbuffer);
		//schrijf buffer naar bestand
		write_file(output, file);
		//free		
		buffer_free(file);
	}
	else {
		//fout gebruik
		printf("Foute modus, juist gebruik van deze functie is: \ncomprimeren: comprimeer1 -c <input> <output> \ndecoderen: comprimeer1 -d <input> <output>");
		return 1;
	}

	return 0;
}

