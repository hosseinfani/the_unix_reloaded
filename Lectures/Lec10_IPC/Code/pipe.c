#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
	
	if (pipe(fd) < 0){
		printf("pipe error.\n");
		exit(1);
	}
	
	int child_pid = fork();
	if(child_pid == -1){
		perror("impossible to have a child!\n");
		exit(1);
	}
	if(child_pid >= 0){//(child_pid != -1)
		if(child_pid > 0)
			printf("I am the parent, pid=%d\n", getpid());
		else{//(child_pid == 0)
			printf("chile: I am the child, pid=%d and given the fd %d\n", getpid(), fd);
			printf("child: I want to be the producer.\n");
			close(fd[0]);
			int Y[1] = {-1};
			int X;
			while(1){
				printf("child: enter a positive number:\n");
				scanf("%d", &X);
				if(X == -1){
					printf("child: the user wants to end the program.\n");
					exit(0);
				}
				Y[0] = X * X;
				int byte_write = write(fd[1], Y, sizeof(Y));
				printf("child write %d bytes.\n", byte_write);
				printf("child: I brought the number to the power 2 and wrote the result: %d.\n", Y[0]);
			}
		}
	}
	printf("parent: I want to be the consumer.\n");
	close(fd[1]);
	while(1){
		int Y[1];
		int byte_read = read(fd[0], Y, sizeof(Y));
		if (byte_read == 0){
			printf("parent: there is no more data and no producer. I exit.\n");
			exit(0);
		}
		printf("parent read %d bytes\n", byte_read);
		int result = Y[0] + 5;
		printf("here is the result: %d\n", result);
	}
}
