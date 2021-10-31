#include <fcntl.h>
#include <stdio.h>
void main(void){
	char filename[20]="open_rw_test.txt";
	int fd = creat(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1){
		printf("error happened in creating file %s\n", filename);
		return;
	}
	else if (fd > 0){
		printf("file %s has been created successfully and the fd is %d\n", filename, fd);
	}
	
	int result = close(fd);
	if (result == -1){
		printf("error happened in closing file %s\n", filename);
		return;
	}
	else if (result == 0){
		printf("file %s has been closed successfully\n", filename);
	}


	fd = open(filename, O_RDWR);
	if(fd==-1){
		printf("error happend in opening file %s!\n", filename);
	}
	else if (fd > 0){
		printf("file successfully opened for %d and the fd is %d\n", O_RDWR, fd);
	}

}
