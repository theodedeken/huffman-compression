#include "file_reader.h"
#include "file_buffer.h"
#include <stdlib.h>
#include <stdio.h>

FileBuffer* read_file(char* filename) {
	FileBuffer* fbuffer = NULL;
	FILE* fp = fopen(filename, "rb");
	if (fp != NULL) {
		if (fseek(fp, 0L, SEEK_END) == 0) {
			long size = ftell(fp);
			if (size == -1) { 
				printf("ERROR: could not read file \n");
				exit(1);
			}
			fbuffer = buffer_alloc_size(size);
			rewind(fp);
			fread(fbuffer->buffer, sizeof(char), size, fp);
		}
		fclose(fp);
	}
	else {
		printf("ERROR: could not open inputfile \n");
		exit(1);
	}
	fclose(fp);
	return fbuffer;
}