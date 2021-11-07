#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]){
	printf("I am a lonely process, pid=%d\n", getpid());	
	int child_pid = fork();
	if(child_pid == -1){
		perror("impossible to have a child!");
		exit(1);
	}
	if(child_pid >= 0){//(child_pid != -1)
		if(child_pid > 0)
			printf("I am the parent, pid=%d\n", getpid());
		else{//(child_pid == 0)
			printf("I am the child, pid=%d\n", getpid());
			printf("My parent is pid=%d\n", getppid());
		}
	}
	exit(0);
}
