#include <signal.h>
typedef void func(int);
void terminal_sig_handler(int signo){}
void main(){
	void *res = signal(SIGINT, terminal_sig_handler);
	res = signal(SIGTSTP, terminal_sig_handler);
	while(1){}
}
