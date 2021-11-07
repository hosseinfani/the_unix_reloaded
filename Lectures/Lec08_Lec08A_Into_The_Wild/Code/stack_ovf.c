#include <stdio.h>
int a = 10;
int foo(){
	a = a - 1;
	printf("%d\n", a);
	if(a > 0)
		main();
	return 1;
}
void main(void){
	//main();
	foo();

}
