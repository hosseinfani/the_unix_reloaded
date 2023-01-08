#include <fcntl.h>
#include <unistd.h>
void main(void){
	int fd = open("./hole_test.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	int cur_offset = lseek(fd, 10, SEEK_SET);
	char buf[20] = "write after the hole.";
	write(fd, buf, 20);
}
