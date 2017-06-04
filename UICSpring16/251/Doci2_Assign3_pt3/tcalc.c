#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tbl.h"

/*
 *doci2
 *663855180
 *
 *This program works with all tables of size 20 or lower
 *The formula file includes all of the required operators
 * does not include compound operations or error checking
 * basically the bare bones of the program
 */
// #define DEBUG

int main(int argc, char *argv[]){
Table *t;
char * usage = "tcalc <expression in prefix notation> (columns in $C format)\n";
int i=0;
FILE *f = fopen(argv[1], "r"); //open file 
char formula[200];

  if (f == NULL) { //cant open file
  fprintf(stderr, "Can't open input file file\n");
  exit(1);
  }

//read in formulas into an array
while(!feof(f)){
fscanf(f, "%c", &formula[i]);
i++;
}
//printf("\nFormulas: %s", formula);

  t= tbl_from_stream(stdin);
  if(t==NULL){
	fprintf(stderr, "Goodbye\n");
	return 0;
  }
  
#ifdef DEBUG
  fprintf(stderr, "-- BEFORE CALC ----\n");
  tbl_print(t, stderr);
  fprintf(stderr, "---------\n");
#endif
//  tbl_sort(t, col-1, !down);
  printf( "-- BEFORE TCALC ----\n"); // table before anything
  tbl_print(t, stdout);
  tbl_calc(t, formula);
  printf( "-- AFTER TCALC ----\n");
  tbl_print(t, stdout);
  tbl_free(t);
  fclose(f);
}

