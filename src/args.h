
#ifndef ARGS_H
#define ARGS_H

struct ArgBuffer{
	int port;
	int verbose;
};

struct ArgBuffer *args_parse(char argc, char *argv[]);

#endif
