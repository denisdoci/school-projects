#include<stdio.h>

#define  DIM 100


/*    
 *This code includes a 4x loop unrolling. It also gets rid of the inner loop
 *because d is a constant in the for loop. So by setting it d = 0 we can get
 *rid of the middle for loop. The overall runtime of this code is less.
 */

void matrixvector(int first[][DIM], int second[][1], int result[][1])
{
int c;
int d=0;
int k;
int result1;
int resultc;
for ( c = 0 ; c < DIM ; c++ )
    {

        for ( k = 0 ; k < DIM ; k+=4 )
        {
          result[c][d]+= first[c][k]*second[k][d];
          result[c][d]+= first[c][k+1]*second[k+1][d];
          result[c][d]+= first[c][k+2]*second[k+2][d];
          result[c][d]+= first[c][k+3]*second[k+3][d];
        }
      }

}
int main() {
	
int first[DIM][DIM];
int second[DIM][1];
int result[DIM][1];
int i=0;
int j=0;	
 for (i=0;i<DIM;i++) 
    for (j=0;j<DIM;j++)
	 {
	 	first[i][j]=i+j;
	 	second[i][0]=(i+1)*(j+1);
	 	result[i][0]=0;
	 }


    matrixvector(first,second,result);
 
 for (i=0;i<DIM;i++) 
 printf("%d ",result[i][0]);
    
}

