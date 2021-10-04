#include <stdio.h>
int increment(int a);
void main(void){	
	int a;
	scanf("%i", &a);
	a = increment(a);
	printf("%i \n", a);
	return;
}

