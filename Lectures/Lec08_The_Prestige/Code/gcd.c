//from https://www.javatpoint.com/gcd-of-two-numbers-in-c
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])  
{  
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int i, gcd;
    // use for loop  
    for( i = 1; i <= n1 && i <= n2; ++i)  
    {  
        if (n1 % i ==0 && n2 % i == 0)  
            gcd = i; /* if n1 and n2 is completely divisible by i, the divisible number will be the GCD_Num */  
    }  
    // print the GCD of two numbers  
    printf ("PID: %d => gcd of %d and %d is %d\n", getpid(), n1, n2, gcd);  
    return 0;  
} 
