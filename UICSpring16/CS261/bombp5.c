#include <stdio.h>

int main()
{
int array[15] = { 10, 2, 14, 7, 8, 12, 15, 11, 0, 4, 1, 13, 3, 9, 6 };
    int a, b;
    scanf(" %d", &a);
    scanf(" %d", &b);
    a &= 0xf;
    if (a != 0xf) {
        int c = 0, d = 0;
        do {
            d++;
            a = array[a];
            c += a;
        } while (a != 0xf);
        if (d == 15 && c == b){
	printf("\nDefuse\n");
	printf("\n%d\n", c);
	printf("\n%d\n", d);
 	}

	else{	 
        printf("\n\nBOOM 2\n");
        printf("\n%d ", c);
        printf("\n%d\n", d);
 	}
    }
   else 
   printf("\n\nBOOM 1\n");


}
