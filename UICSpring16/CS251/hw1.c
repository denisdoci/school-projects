#include <stdio.h>

int square(int *n)
{
 if (*n <= 1)
	return 1;
 else 
   return(*n + square(n-1));
}
int main(){
int n=0;

printf("\nEnter a number: ");

scanf("%d", &n);

n=square(&n);
 printf("\n n squared is %d ", n);

}
