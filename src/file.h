#ifndef FILEREADER_H
#define FILEREADER_H

struct FileBuffer{
	char *data;
	unsigned int size;
};

struct FileBuffer *file_read(char *filename);

#endif
