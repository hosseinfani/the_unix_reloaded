#include <stdio.h>
#include <stdlib.h>
int result;
int main(int argc, char *argv[]){
	int a = 0;
	int b = 0;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	
	result = a + b;
	printf("%d + %d = %d\n", a, b, result);

	result = a - b;
	printf("%d - %d = %d\n", a, b, result);

	result = a / b;
	printf("%d / %d = %d\n", a, b, result);

	result = a * b;
	printf("%d * %d = %d\n", a, b, result);
	
	return 0;
}