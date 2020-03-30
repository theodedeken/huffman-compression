
#include "../file_reader.h"
#include "../file_writer.h"
#include "../huffman.h"
#include "../file_buffer.h"
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

	if (mode == 'c') {
		FileBuffer* file = read_file(input);
		LongBuffer* lbuffer = convert_to_lbuffer(file);
		buffer_free(file);
		FileBuffer* prediff = prediff_encode(lbuffer);
		lbuffer_free(lbuffer);
		buffer_flip(prediff);
		FileBuffer* huffman = huffman_encode(prediff);
		buffer_free(prediff);
		write_file(output, huffman);
		buffer_free(huffman);
	}
	else if (mode == 'd') {
		FileBuffer* huffman = read_file(input);
		FileBuffer* prediff = huffman_decode(huffman);
		buffer_free(huffman);
		buffer_flip(prediff);
		LongBuffer* lbuffer = prediff_decode(prediff);
		buffer_free(prediff);
		FileBuffer* file = convert_to_fbuffer(lbuffer);
		lbuffer_free(lbuffer);
		write_file(output, file);
		buffer_free(file);
	}
	else {
		printf("Foute modus, juist gebruik van deze functie is: \ncomprimeren: comprimeer1 -c <input> <output> \ndecoderen: comprimeer1 -d <input> <output>");
		return 1;
	}

	return 0;
}

