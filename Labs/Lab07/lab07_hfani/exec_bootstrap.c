#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(void){	
	printf("system_bootstrap pid:%d\n", getpid());

	int fd = open("./main_add", O_RDONLY);
	printf("fd of main_add: %d\n", fd);

	char *newargv[] = {"./main_add", "3", "6", NULL};
	char *newenviron[] = {NULL};

	int res = fexecve(fd, newargv, newenviron);
	printf("%d\n", res);
}

