#include <fcntl.h>
#include <stdio.h>
void main(void){
	char filename[20]="open_rw_test.txt";

	int fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(fd==-1){
		printf("error happend in creating the file %s (may be it exists) or opening file!\n.", filename);
	}
	else if (fd > 0){
		printf("file successfully created (it didn't exist) and opened for %d and the fd is %d\n", O_RDWR, fd);
	}

}
