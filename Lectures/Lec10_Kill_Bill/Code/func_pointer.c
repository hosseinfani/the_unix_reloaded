#include <stdio.h>
void say_hi(int times){
	for(int i = 0; i < times; ++i)
		printf("Hi!\n");
}
int main() {
	
	printf("saying hi by calling the function's name:\n");
	say_hi(3);


	printf("saying hi by calling the function's address:\n");
	void (*func_ptr)(int);  /* function pointer declaration */
	func_ptr = say_hi;  /* pointer assignment */
	func_ptr(3);  /* function call */

	return 0;
}
