//Denis Doci
//Katarzyna Krawczyk

#include "inst_none.h"
#include <iostream>
using namespace std;


const int matrixSize = 1000;
int a[matrixSize][matrixSize];
int b[matrixSize][matrixSize];
int c[matrixSize][matrixSize];
int main() {
clock_t begin, end;
double time_spent;

int i, j, k, jj, kk, r;
// Initialise the matrices arbitrarily
for (i=0; i < matrixSize; i++)
for (j=0; j < matrixSize; j++) {
b[i][j] = i + j; c[i][j] = i - j; a[i][j] = 0;
}


// Work out a = b * c, using a blocking algorithm
for(i=0;i<matrixSize;i++){
	for(j=0;j<matrixSize;j++){
		for(k=0;k<matrixSize;k++){
			INST_R(a[i][j]);
			INST_R(b[i][k]);
			INST_R(c[k][j]);
			INST_W(a[i][j]);
			a[i][j]+= b[i][k] * c[k][j];
		}
	}
}

// Display the product
/*for (i=0; i < matrixSize; i++) {
for (j=0; j < matrixSize; j++) cerr << a[i][j] << ' ';
cerr << endl;
}*/

}


