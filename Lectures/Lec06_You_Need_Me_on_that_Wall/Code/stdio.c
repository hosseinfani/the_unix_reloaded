#include <fcntl.h>
#include <unistd.h>
void main(void){
	char buf_rd[20];

	int fd_rd = open("/dev/pts/12", O_RDONLY);
	read(fd_rd, buf_rd, 10);
	int fd_wr = open("/dev/pts/12", O_WRONLY);
	write(fd_wr, buf_rd, 10);

	read(STDIN_FILENO, buf_rd, 10);
	write(STDOUT_FILENO, buf_rd, 10);
	write(STDERR_FILENO, buf_rd, 10);

	read(0, buf_rd, 10);
	write(1, buf_rd, 10);
	write(2, buf_rd, 10);

}
