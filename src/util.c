#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

void util_err(char *msg){
	printf("[*] error '%s'.\n",msg);
}

void util_say(char *msg){
	if(OPTION_VERBOSE == 1){
		printf("[*] %s\n",msg);
	}
}

void util_usage(){
	printf("%s\n", "Usage: build/app -p <port> [-v]");
}

void util_startup(int port){
	char *port_string = malloc(32);
	bzero(port_string,32);
	snprintf(port_string,32,"%d",port);
	
	printf("[*] Running server on *%s.\n", port_string);
}


