#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[]){
	printf("there are %d arguements in the shell:\n", argc);
	for(int i=0; i < argc; ++i){
		printf("arg%d: %s\n", i, argv[i]);
	}
	return 0;
}
