#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
	printf("I am a lonely process, pid=%d\n", getpid());	
	char filename_2_share[] = "child_results.txt";

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
			printf("I am the child, pid=%d\n", getpid());

			int Y[1];
			Y[0] = X * X;
			int fd = open(filename_2_share, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			printf("child opens the file with fd: %d\n", fd);
			int byte_write = write(fd, Y, sizeof(Y));
			printf("child write %d bytes.\n", byte_write);
			close(fd);

			printf("I brough the number to the power 2 and wrote the result: %d.\n", Y[0]);
			exit(0);
		}
	}
	int child_exit;
	wait(&child_exit);//wait for the child to X^2

	int fd = open(filename_2_share, O_RDONLY);
	printf("parent opens the file with fd: %d\n", fd);
	int Y[1];
	int byte_read = read(fd, Y, sizeof(Y));
	printf("parent read %d bytes\n", byte_read);
	close(fd);

	int result = Y[0] + 5;
	printf("here is the result: %d\n", result);
	exit(0);
}
