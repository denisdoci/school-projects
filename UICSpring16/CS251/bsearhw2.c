#include <stdio.h>

int COUNT=0;

int bsearch(int a[], int lo, int hi, int key) {

int m;
COUNT++;

printf("TICK%d\n",COUNT);

if(hi < lo)
    return 0;

m = (lo+hi)/2;

if(a[m]==key)
   return 1;

if(key < a[m])
   return bsearch(a, lo, m-1, key);

else
   return bsearch(a, m+1, hi, key);
}

int main()
{  
   int size=80;
   int a[size];
   int lo=0;
   int hi=size-1;
   int key = 1000;
   int i;

   for(i=0; i<size; i++)
   {
     a[i] = 1;
   }
   bsearch(a, lo, hi, key);

}


