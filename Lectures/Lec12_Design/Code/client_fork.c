#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
	int domain = AF_INET;//Network Protocol: TCP/IP
	int type = SOCK_STREAM;//Connection-Oriented
	int protocol = 0;//Default transport: TCP for Internet connection-oriented

	int client_sd;//socket descriptor ~= file descriptor
	client_sd = socket(domain, type, protocol);
	if (client_sd == -1){
		printf("error in creating socket for the client!\n");
		exit(1);
	}
	else
		printf("socket has created for the client with sd:%d\n", client_sd);

	//Binding to an address is optional for the client. 
	//We don't do that because the client might be in any other computers
	//We let the kernel does that for us for the host computer of the client
	
	struct in_addr server_sin_address;
	server_sin_address.s_addr = inet_addr(argv[1]);//ask!
	int server_sin_port = htons(atoi(argv[2]));//larger than 1024

	struct sockaddr_in server_sin;
	server_sin.sin_family = domain;
	server_sin.sin_addr = server_sin_address;
	server_sin.sin_port = server_sin_port;
	int result = connect(client_sd, (struct sockaddr *) &server_sin, sizeof(server_sin));
	if (result == -1){
		printf("error in connecting to The Server at address:port = %d:%d\n", server_sin.sin_addr, server_sin.sin_port);
		exit(1);
	}
	else
		printf("client is connected to The Server at address:port = %d:%d\n", server_sin.sin_addr, server_sin.sin_port);

	char response[100];
	send(client_sd, argv[3], strlen(argv[3]), 0);
	while(recv(client_sd, response, 100, 0) > 0){
		printf("%s\n", response);
	}

}
