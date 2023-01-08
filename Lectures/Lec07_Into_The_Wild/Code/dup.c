#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
void main(void){
	char buf[20] = "hello world!";
	int fd_rd = open("dup_test.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	int res = write(fd_rd, buf, 20);
	if (res == -1){
		char error[20] = "error writing using readable fd!\n";
		write(STDOUT_FILENO, error, 20);
	}

	int fd_wr = open("dup_test.txt", O_WRONLY);
	res = write(fd_wr, buf, 20);
	
	int offsets[2];
	offsets[0] = lseek(fd_wr, 0, SEEK_CUR);
	offsets[1] = lseek(fd_rd, 0, SEEK_CUR);	
	//res = write(STDOUT_FILENO, offsets, 2 * sizeof(int));
	printf("%d %d", offsets[0], offsets[1]);


	int fd_wr2 = dup(fd_wr);

	lseek(fd_wr2, 10, SEEK_CUR);
	offsets[0] = lseek(fd_wr, 0, SEEK_CUR);

	printf("%d", offsets[0]);

}
