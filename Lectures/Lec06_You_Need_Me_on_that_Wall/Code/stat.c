#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main(void)
{
	struct stat sb;

	char *file = "./hfani.jpeg";
	int fd = open(file, O_RDONLY);
	
	if (fstat(fd, &sb) == -1) {
		printf("error in fetching stat on file %s", file);
		return;
	}

	printf("I-node number: %d\n", sb.st_ino);
	printf("Preferred I/O block size: %d bytes\n",  sb.st_blksize);
	printf("File size: %d bytes\n",  sb.st_size);
	printf("Blocks allocated: %d\n", sb.st_blocks);
}
