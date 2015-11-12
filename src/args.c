#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "args.h"

#define ARGS_LIST "pv"
#define ARGS_LIST_PARAMETER "p"

void args_set_option( struct ArgBuffer *args, char type, int param){
	if(type == 'p'){
		args->port = param;
	}
	if(type == 'v'){
		args->verbose = 1;
	}	
}

int args_match(char c, char *s){
	int i;
	for(i=0;i<strlen(s);i++)
		if(s[i]==c)
			return 1;
	return -1;
}

int args_valid(char option_type){
	return args_match(option_type,ARGS_LIST);
}

int args_has_parameter(char option_type){
	return args_match(option_type, ARGS_LIST_PARAMETER);
}
	
void args_error(char *reason, char *option){
	printf("[*] args_error '%s' (%s).\n", reason, option);
}

int args_parse_parameter(char type, char *param){
	int result = atoi(param);
	if(result > 0){
		return result;
	}else{
		return -1;
	}
}

/* If an option is valid, returns it's type
 * else returns 0.
 */
char args_parse_option(char *option){
	if(strlen(option) >= 2){
		if(option[0] == '-' && args_valid(option[1])){
			return option[1];
		}
	} 
	return 0;
}

struct ArgBuffer *args_parse(char argc, char *argv[]){
	struct ArgBuffer *args; 
	args = malloc(sizeof(*args));
	args->port = -1;
	args->verbose = -1;

	int i;
	for(i=1;i<argc;i++){
		char type = args_parse_option(argv[i]);
		if( type != 0 ){
			if(args_has_parameter(type) != -1){
				if( argc > (i+1) ){
					int param = args_parse_parameter(type, argv[i+1]);
					if( param != -1 ){
						args_set_option(args, type, param);	
						i += 1; // Skip the parameter (we just parsed it)
					}
					else
					args_error("Invalid Parameter", argv[i+1]);
				} 
				else 
				args_error("Missing Parameter", argv[i]);
			} 
			else 
			args_set_option(args, type, 0);	
		}
		else 
		args_error("Invalid Option", argv[i]);
	}
	
	return args;
}





