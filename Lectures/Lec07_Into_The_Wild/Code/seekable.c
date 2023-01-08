#include <fcntl.h>
#include <unistd.h>
void  main(void)
{
	int fd = open("/dev/pts/12", O_RDWR);
	char error[20] = "cannot seek!\n";
	if (lseek(fd, 0, SEEK_CUR) == -1){
		write(fd, error, 20);
		return;
	}
}
