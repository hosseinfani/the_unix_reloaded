#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(void){
	printf("system_bootstrap pid:%d\n", getpid());
	char *program = "#include <stdio.h>\n"
			"#include <stdlib.h>\n"
			"#include <unistd.h>\n"
			"int result;\n"
			"int main(int argc, char *argv[]){\n"
			"printf(\"main_add pid: %d\\n\", getpid());\n"
			"int a = 0;\n"
		 	"int b = 0;\n"
			"a = atoi(argv[1]);\n"
			"b = atoi(argv[2]);\n"
	
			"result = a + b;\n"
	
			"printf(\"%d + %d = %d\\n\", a, b, result);\n"
			"return 0;\n"
			"}\n";
	//printf("%s\n", program);
	int fd = creat("./math.c", S_IRUSR | S_IWUSR);
	printf("fd for math.c file:%d\n", fd);
	write(fd, program, strlen(program));

	system("cc ./math.c -o math");
	system("./math 10 40");
}
