#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

#include "socklib.h"
#include "file.h"
#include "args.h"

static int OPTION_PORT = -1;
static int OPTION_VERBOSE = -1;

void err(char *msg){
	printf("[*] error '%s'.\n",msg);
}

void say(char *msg){
	if(OPTION_VERBOSE == 1){
		printf("[*] %s\n",msg);
	}
}

void print_usage(){
	printf("%s\n", "Usage: build/app -p <port> [-v]");
}

void print_startup(int port){
	char *port_string = malloc(32);
	bzero(port_string,32);
	snprintf(port_string,32,"%d",port);
	
	printf("[*] Running server on *%s.\n", port_string);
}

void handle_client_response(int sockfd){	
	char *headers = "HTTP/1.1 200 OK\nContent-Type: text/html\n";

	struct FileBuffer *f = file_read("index.html");
	
	if( f->data == NULL){
		err("(handle_client_response) reading file");
	}

	char *length = malloc(32);
	bzero(length,32);
	snprintf(length,32,"%d",f->size);

	char *ContentLength = "Content-Length: ";
	char *end = "\n\n";

	// Writes the first two headers	
	write(sockfd,headers,strlen(headers));
	// Writes 'Content Length: '
	write(sockfd,ContentLength,strlen(ContentLength));
	// Writes the 'value' of Content Length 
	write(sockfd,length,strlen(length));
	// Two endline (aka CRLF, newline, EOL) chars to seperate the HEADERS from the BODY of the response.
	write(sockfd,end,strlen(end));	
	// The actual content. (html file)
	write(sockfd,f->data,f->size);

}

void handle_client_request(int sockfd){
	
}

void handle_client(int sockfd){
	handle_client_request(sockfd);
	handle_client_response(sockfd);
}

void run_server(int port){
	// Socket Identifier	
	int server_sock, client_sock;
	// Socket Address
	struct sockaddr *server_addr, *client_addr;
	// * Avoid Undefined Behavior
	server_addr = NULL;
	client_addr = NULL;
	// Attempt To Bind Server
	server_sock = sl_tcp_server(sl_sockaddr_server(port));	
	// Allocate a sockaddr for the client
	client_addr = sl_sockaddr();

	signed char running = 1;
	
	if(server_sock < 0){
		err("(sl_tcp_server) binding socket");
		running = 0;
	}

	if(OPTION_VERBOSE==1)
		print_startup(port);
	
	while(running){
		client_sock = sl_accept(server_sock,client_addr);
		
		if(client_sock < 0){
			err("(sl_accept) accepting connection.");
			running = 0;
		}else{
			say("Accepted Connection.");
		}
		
		handle_client(client_sock);
		close(client_sock);	
		say("Closed Connection.");
	}
	
	// We check != NULL here incase our addr's failed to be allocated -
	// which happens for server_addr if sl_tcp_server fails to bind.
	if(server_addr!=NULL) free(server_addr);
	if(client_addr!=NULL) free(client_addr);
}

int export_args( struct ArgBuffer *args ){
	if(args->port > 0){
		OPTION_PORT = args->port;
	}else{
		err("port not set");
		print_usage();	
		return -1;
	}

	OPTION_VERBOSE = args->verbose;
	return 1;
}

int main(char argc, char *argv[]){	
	int result = export_args(args_parse(argc, argv));

	if(result != -1)
	run_server(OPTION_PORT);

	return 0;
};

