#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int result;
int main(int argc, char *argv[]){
	int a = 0;
	int b = 0;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	
	pid_t pid = fork();
	if (pid == -1){//not able to create child
		result = a + b;
		printf("parent PID %d => %d + %d = %d\n", getpid(), a, b, result);
	}
	else if (pid == 0) {//child
		result = a + b;
		printf("child01 PID: %d => %d + %d = %d\n", getpid(), a, b, result);
		exit(0);
	}
	//here pid > 0 => parent
	pid = fork();
	if (pid == -1){//not able to create child
		result = a - b;
		printf("parent PID %d => %d - %d = %d\n", getpid(), a, b, result);
	}
	else if (pid == 0) {//child
		result = a - b;
		printf("child01 PID: %d => %d - %d = %d\n", getpid(), a, b, result);
		exit(0);
	}
	
	//here pid > 0 => parent
	pid = fork();
	if (pid == -1){//not able to create child
		result = a / b;
		printf("parent PID %d => %d / %d = %d\n", getpid(), a, b, result);
	}
	else if (pid == 0) {//child
		result = a / b;
		printf("child01 PID: %d => %d / %d = %d\n", getpid(), a, b, result);
		exit(0);
	}
	
	//here pid > 0 => parent
	pid = fork();
	if (pid == -1){//not able to create child
		result = a * b;
		printf("parent PID %d => %d * %d = %d\n", getpid(), a, b, result);
	}
	else if (pid == 0) {//child
		result = a * b;
		printf("child01 PID: %d => %d * %d = %d\n", getpid(), a, b, result);
		exit(0);
	}
	wait(0);
	exit(0);
}