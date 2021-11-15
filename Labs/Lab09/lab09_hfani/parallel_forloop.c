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
	char math_op[4] = {'+', '-', '/', '*'};
	
	for(int i = 0; i < sizeof(math_op); ++i){
		pid_t pid = fork();
		if (pid == -1){//not able to create child
			result = math_op[i] == '+' ? (a + b) : 
				(math_op[i] == '-' ? (a - b) : 
				(math_op[i] == '/' ? (a / b) : 
				(math_op[i] == '*' ? (a * b) : (0))));
			printf("parent PID %d => %d %c %d = %d\n", getpid(), a, math_op[i], b, result);
		}
		else if (pid == 0) {//child
			result = math_op[i] == '+' ? (a + b) : 
				(math_op[i] == '-' ? (a - b) : 
				(math_op[i] == '/' ? (a / b) : 
				(math_op[i] == '*' ? (a * b) : (0))));
			printf("child%d PID: %d => %d %c %d = %d\n", i, getpid(), a, math_op[i], b, result);
			exit(0);
		}
	}
	wait(0);
	exit(0);
}
