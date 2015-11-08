#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

/***
 * 1. Open file
 * 2. Find length of file
 * 3. Allocate buffer
 * 4. Read file bytes to buffer
 * 5. Return pointer to buffer
 ***/
struct FileBuffer *file_read(char *filename){
	struct FileBuffer *fd = malloc(sizeof(*fd));
	int i, length;

	FILE *f = fopen(filename,"r");
	if( f == NULL ){
		return NULL;
	}

	fseek(f,0L,SEEK_END);
	length = ftell(f);
	fseek(f,0l,0);

	fd->data = malloc(length);
	bzero(fd->data,length);

	fd->size = length;

	for(i=0; i<length; i++){
		fd->data[i] = fgetc(f);
	}

	return fd;
}


