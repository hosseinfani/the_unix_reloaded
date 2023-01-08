#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[]){
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
	server_sin_address.s_addr = inet_addr(argv[1]);//nslookup `hostname`
	int server_sin_port = htons(atoi(argv[2]));//larger than 1024

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
				printf("Child pid %d: I The Server's child to handle the communication with the client %d:%d\n", getpid(), client_sin.sin_addr, client_sin.sin_port);

				char msg[10];
				recv(result, msg, 10, 0);
				printf("%s\n", msg);
				char c[1000];
				for(int i=0; i<100; ++i){
					char response[] = "I will look into ";
					snprintf (c, sizeof(c), "%d", i);
					strcat(c, response);
					strcat(c, msg);
					send(result, c, strlen(c), 0);
					sleep(1);
				}
			}
		}
	}

}
