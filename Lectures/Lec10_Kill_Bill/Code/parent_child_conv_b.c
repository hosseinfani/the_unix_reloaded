#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

typedef void func(int);
int child_pid;
char *filename_2_share = "file_2_share.txt";
void child_signal_handler(int signal){
	printf("child: I received a wake up signal from my parrent. The signal is %d\n", signal);
	int Y[1] = {-1};
	int X;
	printf("child: enter a positive number:\n");
	scanf("%d", &X);
	int fd = open(filename_2_share, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	printf("child opens the file with fd: %d\n", fd);
	if(X == -1){
		printf("child: the user wants to end the program.\n");
		write(fd, Y, sizeof(Y)); 
		exit(0);
	}
	Y[0] = X * X;
	int byte_write = write(fd, Y, sizeof(Y));
	close(fd);
	printf("child: write %d bytes.\n", byte_write);
	printf("child: I brought the number to the power 2 and wrote the result: %d.\n", Y[0]);
	printf("child: Ma, wake up ...\n");
	kill(getppid(), SIGUSR1);
	printf("child: I sleep.\n");
	pause();
}
void parent_signal_handler(int signal){
	printf("parent: I received a wake up signal from my child. The signal is %d\n", signal);
	int fd = open(filename_2_share, O_RDONLY);
	printf("parent: I opened the file with fd: %d\n", fd);
	int Y[1];
	int byte_read = read(fd, Y, sizeof(Y));
	printf("parent: I read %d bytes\n", byte_read);
	close(fd);
	int result = Y[0] + 5;
	printf("parent: here is the final result: %d\n", result);
	printf("parent: wake up child for another round of work ...");
	sleep(10);
	kill(SIGUSR2, child_pid);
	printf("parent: I sleep.");
	pause();
}
int main(int argc, char *argv[]){

	signal(SIGUSR1, parent_signal_handler);

	child_pid = fork();
	if(child_pid == -1){
		perror("impossible to have a child!\n");
		exit(1);
	}
	if(child_pid >= 0){//(child_pid != -1)
		if(child_pid > 0)
			printf("parent: I am the parent, pid=%d\n", getpid());
		else{//(child_pid == 0)
			printf("child: I am the child, pid=%d\n", getpid());
			signal(SIGUSR2, child_signal_handler);
			printf("child: I sleep until parent starts the work...\n");
			pause();
		}
	}
	sleep(10);
	printf("parent: wake up child. It's time to work...\n");
	kill(child_pid, SIGUSR2);
	printf("parent: I sleep till you wake me up, child.\n");
	pause();
}
