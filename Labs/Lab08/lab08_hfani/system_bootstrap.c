#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(void){
	printf("system_bootstrap pid:%d\n", getpid());
	system("./main_add 2 6");
}
