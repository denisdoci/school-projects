#include <stdio.h>
#include <limits.h>

int main(){

int myint;
char mychar;
int * myptr;

printf("\nHello World\n");
printf("\nusername:   \n");
printf("\npassword:    \n");

myint = INT_MAX;
printf("Maximum int value in decimals  %d\n", myint);
printf("Maximum int value in hexadecimal %04x\n", myint);
printf("Size of maximum integer is %lu bytes\n", sizeof(myint));
}
