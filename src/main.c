#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>

#include "socklib.h"
#include "file.h"

int check_errors(int s, int c)
{
	if(s<=0){
		printf("%s","Server Bind Error\n");
		return 0;
	}
	if(c<=0){
		printf("%s","Client Bind Error\n");
		return 0;
	}
	return 1;
}

void handle_client_response(int sockfd){	
	char *headers = "HTTP/1.1 200 OK\nContent-Type: text/html\n";

	struct FileBuffer *f = file_read("index.html");

	char *length = malloc(32);
	bzero(length,32);
	snprintf(length,32,"%d",f->size);

	char *ContentLength = "Content-Length: ";
	char *end = "\n\n";
	
	write(sockfd,headers,strlen(headers));
	write(sockfd,ContentLength,strlen(ContentLength));
	write(sockfd,length,strlen(length));
	write(sockfd,end,strlen(end));	
	write(sockfd,f->data,f->size);
	write(sockfd,end,strlen(end));

}

void handle_client_request(int sockfd){
	
}

void handle_client(int sockfd){
	handle_client_request(sockfd);
	handle_client_response(sockfd);
}

void run_server(){	
	int server_sock, client_sock;
	struct sockaddr *server_addr, *client_addr;
	
	server_sock = sl_tcp_server(sl_sockaddr_server(1025));	
	client_addr = sl_sockaddr();
	
	signed char running = 1;
	
	while(running){
		client_sock = sl_accept(server_sock,client_addr);
		running = check_errors(server_sock,client_sock);
		handle_client(client_sock);
		close(client_sock);	
	}

	free(server_addr);
	free(client_addr);
}

int main(char argc, char **argv){
	
	run_server();

	return 0;
};

