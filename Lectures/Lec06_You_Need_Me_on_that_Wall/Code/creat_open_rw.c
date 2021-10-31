#include <fcntl.h>
#include <stdio.h>
void main(void){
	char filename[20]="open_rw_test.txt";

	int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd==-1){
		printf("error happend in creating the file %s (if not exists) or opening file!\n.", filename);
	}
	else if (fd > 0){
		printf("file successfully created (if not exist) and opened for %d and the fd is %d\n", O_RDWR, fd);
	}

}
