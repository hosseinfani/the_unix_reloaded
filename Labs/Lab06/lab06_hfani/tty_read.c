#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
void main(){
	int fd_in = open("/dev/pts/9", O_RDONLY);
	
	printf("The file descriptor is: %d \n", fd_in);
	if(fd_in == -1){
		printf("Error in opening device!\n");
		return;
	}

	char buf[20];
	ssize_t bytes_read;
	
	while ((bytes_read = read(fd_in, buf, sizeof(buf))) > 0) {
      		printf("block read: \n<%s>\n", buf);
    	}

	int result = close(fd_in);
	if(result == -1){
		printf("Error in closing the device!\n");
	}
}
