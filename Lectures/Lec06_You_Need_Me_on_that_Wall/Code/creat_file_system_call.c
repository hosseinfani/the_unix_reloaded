#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <string.h>

#include <stdio.h>
void main(void){
	int fd;//file descriptor
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;//for permisison settings
	char *filename = "./my_new_file.txt";

	fd = creat(filename, mode);
	printf("The file descriptor is: %d \n", fd);

	if(fd == -1){
		printf("Error in creating file!\n");
		return;
	}
	
	char buf[20];
	size_t nbytes;
	ssize_t bytes_written;

	strcpy(buf, "Hello File!\n");
	nbytes = strlen(buf);

	bytes_written = write(fd, buf, nbytes);
	if(bytes_written != nbytes){
		printf("Error in writing to the file!");
	}


	int result = close(fd);
	if(result == -1){
		printf("Error in closing the file!");
	}

}

