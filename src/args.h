
#ifndef ARGS_H
#define ARGS_H

struct ArgBuffer{
	int port;
	int verbose;
};

int args_handle(char argc, char *argv[]);

#endif
