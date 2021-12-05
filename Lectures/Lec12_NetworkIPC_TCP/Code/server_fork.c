#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(void){
	int domain = AF_INET;//Network Protocol: TCP/IP
	int type = SOCK_STREAM;//Connection-Oriented
	int protocol = 0;//Default transport: TCP for Internet connection-oriented

	int server_sd;//socket descriptor ~= file descriptor
	server_sd = socket(domain, type, protocol);
	if (server_sd == -1){
		printf("error in creating socket for The Server!\n");
		exit(1);
	}
	else
		printf("socket has created for The Server  with sd:%d\n", server_sd);

	//Binding to an address is a must for The Server!
	struct in_addr server_sin_address;
	server_sin_address.s_addr = inet_addr("137.207.82.51");//nslookup `hostname`
	int server_sin_port = htons(7882);//larger than 1024

	struct sockaddr_in server_sin;
	server_sin.sin_family = domain;
	server_sin.sin_addr = server_sin_address;
	server_sin.sin_port = server_sin_port;
	int result = bind(server_sd, (struct sockaddr *) &server_sin, sizeof(server_sin));
	if (result == -1){
		printf("error in binding The Server to the address:port = %d:%d\n", server_sin.sin_addr, server_sin.sin_port);
		exit(1);
	}
	else
		printf("The Server bound to the address:port = %d:%d\n", server_sin.sin_addr, server_sin.sin_port);

	//The Server ready to receive calls (up to 5 calls. More are rejected!) 
	if (listen(server_sd, 5) < 0) {
		perror("The Server's listening failed!\n");
		exit(1);
	}

	struct sockaddr_in client_sin;//I want to know who send the message
	int client_sin_len;
	while(1)
	{
		result = accept(server_sd, (struct sockaddr *) &client_sin, &client_sin_len);
		if (result == -1){
			printf("error in opening the request from client %d:%d !\n", client_sin.sin_addr, client_sin.sin_port);
			//exit(1);Do not exit. Go for the next client call
		}
		else{
			printf("The Server opened the request from client %d:%d\n", client_sin.sin_addr, client_sin.sin_port);

			int child_pid = fork();
			if(child_pid == 0){//child
				printf("Child: I The Server's child to handle the communication with the client %d:%d\n", client_sin.sin_addr, client_sin.sin_port);

				char msg[10];
				recv(result, msg, 10, 0);
				printf("%s\n", msg);
				for(int i=0; i<100; ++i){
					send(result, "hello back", 11, 0);
					sleep(1);
				}
			}
		}
	}

}
