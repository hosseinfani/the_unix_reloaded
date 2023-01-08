#include <fcntl.h>
#include <unistd.h>
void main(void){
	char buf_rd[20];

	int fd_wr = open("./log.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	close(1);
	//now the fd with value 1 is free
	//let's get it for our log file
	int new_fd = dup(fd_wr);
	//now the value of new_fd is 1
	//both fd_wr and new_fd are pointing to log.txt

	read(STDIN_FILENO, buf_rd, 10);
	
	write(STDOUT_FILENO, buf_rd, 10);

	//write(1, buf_rd, 10);

}
