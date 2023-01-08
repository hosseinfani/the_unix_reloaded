#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
	printf("I am a lonely process, pid=%d\n", getpid());	
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
			//Assign child's tasks here
			//Look at Lab08
			int fd = open("./gcd", O_RDONLY);
			printf("fd of gcd: %d\n", fd);

			char *newargv[] = {"./gcd", argv[1], argv[2], NULL};
			char *newenviron[] = {NULL};

			int res = fexecve(fd, newargv, newenviron);
			printf("this lines and after never executed!");
			exit(0);//never executed!
		}
	}
	//Assign parent tasks here
	int a = 0;
	int b = 0;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	printf("parent: %d + %d = %d\n", a, b, a + b);
	int *child_exit;
	wait(child_exit);
	exit(0);
}
