#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
	printf("sender %s:%d\nreceiver %s:%d\n", argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
	int domain = AF_INET;//Network Protocol: TCP/IP
	int type = SOCK_DGRAM;//Connectionless
	int protocol = 0;//Default transport: UDP for Internet connectionless

	int sender_sd;//socket descriptor ~= file descriptor
	sender_sd = socket(domain, type, protocol);
	if (sender_sd == -1){
		printf("error in creating socket!\n");
		exit(1);
	}
	else
		printf("socket has created for sender with sd:%d\n", sender_sd);

	//Binding to an address is optional for sender!
	struct in_addr sender_sin_address;
	sender_sin_address.s_addr = inet_addr(argv[1]);//nslookup `hostname`
	int sender_sin_port = htons(atoi(argv[2]));//larger than 1024

	struct sockaddr_in sender_sin;
	sender_sin.sin_family = domain;
	sender_sin.sin_addr = sender_sin_address;
	sender_sin.sin_port = sender_sin_port;
	int result = bind(sender_sd, (struct sockaddr *) &sender_sin, sizeof(sender_sin));
	if (result == -1){
		printf("error in binding sender to the address:port = %d:%d\n", sender_sin.sin_addr, sender_sin.sin_port);
		exit(1);
	}
	else
		printf("sender bound to the address:port = %d:%d\n", sender_sin.sin_addr, sender_sin.sin_port);


	//Sending a message to the receiver at 137.207.82.52:2001
	struct in_addr receiver_sin_address;
	receiver_sin_address.s_addr = inet_addr(argv[3]);//nslookup `hostname` at the target machine (here is the same as sender)
	int receiver_sin_port = htons(atoi(argv[4]));//larger than 1024

	struct sockaddr_in receiver_sin;
	receiver_sin.sin_family = domain;//same network protocol
	receiver_sin.sin_addr = receiver_sin_address;
	receiver_sin.sin_port = receiver_sin_port;

	char *mail = "a 10 percent promotion for candian tire!";

	result = sendto(sender_sd, mail, strlen(mail), 0, (struct sockaddr *)&receiver_sin, sizeof(receiver_sin));
	if (result == -1){
		printf("error in sending message to the receiver!\n");
		exit(1);
	}
	else
	{
		printf("a mail has sent to the receiver at address:port = %d:%d\n", receiver_sin.sin_addr, receiver_sin.sin_port);
		printf("the content of the mail is <%s>\n", mail);
	}
}
