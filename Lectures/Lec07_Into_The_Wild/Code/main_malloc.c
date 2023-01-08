#include <stdio.h>
#include <stdlib.h>
int result;
int main(int argc, char *argv[]){
	int size_a = 0;
	int size_b = 0;
	size_a = atoi(argv[1]);
	size_b = atoi(argv[2]);

	int *a = malloc(size_a * sizeof(int));
	printf("enter the first number with %d digits:\n", size_a);
	for(int i = 0; i < size_a; ++i){
		scanf("%d", a + i);
	}

	int *b = malloc(size_b * sizeof(int));
	printf("enter the first number with %d digits:\n", size_b);
	for(int i = 0; i < size_b; ++i){
		scanf("%d", b + i);
	}

	for(int i = 0; i < size_a; ++i)
		printf("%d", *(a + i));
	printf(" + ");
	for(int i = 0; i < size_b; ++i)
		printf("%d", *(b + i));
	printf("\n");
	return 0;
}

