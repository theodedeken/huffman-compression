#include "file_writer.h"
#include "file_buffer.h"

#include <stdio.h>
#include <stdlib.h>

write_file(char* filename, FileBuffer* fbuffer) {
	FILE* fp = fopen(filename, "wb");
	if (fp != NULL) {
		int ret = fwrite(fbuffer->buffer, sizeof(char), fbuffer->size, fp);		
		if (ret != fbuffer->size) {
			printf("ERROR: error writing to outputfile \n");
			exit(1);
		}
	}
	else {
		printf("ERROR: could not open outputfile \n");
		exit(1);
	}
	fclose(fp);
}