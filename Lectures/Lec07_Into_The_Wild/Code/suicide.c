#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
void main(void){

	int fd;
	do{
		fd = open("./not_exist/test.txt", O_WRONLY | O_CREAT, S_IWUSR);
		if (fd == -1){
			printf("kernel rejected to open the file!\n");
		        printf("the error is %d\n and the erro string is %s\n", errno, strerror(errno));
			if(errno == 2){
				_exit(1);
			}
		}
	}while(fd > -1);



}
