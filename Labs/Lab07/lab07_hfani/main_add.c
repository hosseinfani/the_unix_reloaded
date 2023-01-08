#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int result;
int main(int argc, char *argv[]){
	printf("main_add pid: %d\n", getpid());
	int a = 0;
	int b = 0;
	//printf("%s\n", argv[1]);
	//printf("%s\n", argv[2]);
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	
	result = a + b;
	
	printf("%d + %d = %d\n", a, b, result);
	return 0;
}
