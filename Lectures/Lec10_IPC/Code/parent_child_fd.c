#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
	printf("I am a lonely process, pid=%d\n", getpid());	
	int fd = open("child_results_fd.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	printf("parent opens the file for R/W with fd: %d\n", fd);

	int X = atoi(argv[1]);

	int child_pid = fork();
	if(child_pid == -1){
		perror("impossible to have a child!\n");
		exit(1);
	}
	if(child_pid >= 0){//(child_pid != -1)
		if(child_pid > 0)
			printf("I am the parent, pid=%d\n", getpid());
		else{//(child_pid == 0)
			printf("I am the child, pid=%d and given the fd %d\n", getpid(), fd);

			int Y[1];
			Y[0] = X * X;
			int byte_write = write(fd, Y, sizeof(Y));
			printf("child write %d bytes.\n", byte_write);

			printf("I brough the number to the power 2 and wrote the result: %d.\n", Y[0]);
			exit(0);
		}
	}
	int child_exit;
	wait(&child_exit);//wait for the child to X^2

	int Y[1];
	lseek(fd, 0, SEEK_SET);
	int byte_read = read(fd, Y, sizeof(Y));
	printf("parent read %d bytes\n", byte_read);
	close(fd);

	int result = Y[0] + 5;
	printf("here is the result: %d\n", result);
	exit(0);
}
