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
			printf("%d\n", 1/0);
			exit(0);
		}
	}
	int child_exit;
	wait(&child_exit);
	if (WIFEXITED(child_exit))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(child_exit));
	else if (WIFSIGNALED(child_exit))
		printf("abnormal termination, signal number = %d\n", WTERMSIG(child_exit));

	exit(0);
}
