#include <stdio.h>

int main()

{
    int i, j, small, temp;
    int a[20];
    int n=20;
    int count=0;

    for (i = 0; i < n-1; i++) {
        small = i;
        for (j = i+1; j < n; j++){
            if (a[j] < a[small])       // <-- THIS LINE
                small = j;
		count++;
        }
        temp = a[small];
        a[small] = a[i];
        a[i] = temp;
    }
printf("\n%d\n",count);
}
