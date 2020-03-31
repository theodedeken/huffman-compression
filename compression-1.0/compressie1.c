#include "file_reader.h"
#include "file_writer.h"
#include "huffman.h"
#include "file_buffer.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	//improv: EOF als karakter in tree, blokken
	if (argc != 4)
	{
		printf("Fout aantal argumenten, juist gebruik van deze functie is: \ncomprimeren: comprimeer1 -c <input> <output> \ndecoderen: comprimeer1 -d <input> <output>");
		return 1;
	}

	char mode = argv[1][1];
	char *input = argv[2];
	char *output = argv[3];

	if (mode == 'c')
	{
		FileBuffer *file = read_file(input);
		FileBuffer *huffman = huffman_encode(file);
		buffer_free(file);
		write_file(output, huffman);
		buffer_free(huffman);
	}
	else if (mode == 'd')
	{
		FileBuffer *huffman = read_file(input);
		FileBuffer *file = huffman_decode(huffman);
		buffer_free(huffman);
		write_file(output, file);
		buffer_free(file);
	}
	else
	{
		printf("Foute modus, juist gebruik van deze functie is: \ncomprimeren: comprimeer1 -c <input> <output> \ndecoderen: comprimeer1 -d <input> <output>");
		return 1;
	}

	return 0;
}
