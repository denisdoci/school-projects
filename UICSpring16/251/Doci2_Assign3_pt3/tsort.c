#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tbl.h"


// #define DEBUG

int main(int argc, char *argv[]){
Table *t;
int i, col, down;
char * usage = "tsort -c <column> [-d]\n";
int * lsort = malloc((argc-2)*sizeof(int));
int k, limit;

  down = 0;  // FIX ADDED 3/13/16 (missing before)
  for(i=1; i<argc; i++){
    if(strcmp(argv[i], "-c") == 0){
	i++;
	if(i==argc || sscanf(argv[i], "%i", &col) != 1){
	  puts(usage);
	  return 0;
	}
    }
    k=0;
    limit = -999;
    while(i < argc && sscanf(argv[i], "%i", &lsort[k])==1){
	++i;
	if(lsort[k] > limit) limit = lsort[k];
 	++k;
    }
    col = limit-1;
    if(i<argc && strcmp(argv[i], "-d")==0) {
	down = 1;
    }
  }

  t= tbl_from_stream(stdin);
  if(t!=NULL){
	t->clargs= lsort;
	t->numsort = k;
  }
  if(t==NULL){
	fprintf(stderr, "Goodbye\n");
	return 0;
  }
  if(col < 0 || col > t->ncols-1) {  // not abstract!
	fprintf(stderr, "column out of range\n");
	return 0;
  }
  
#ifdef DEBUG
  fprintf(stderr, "-- BEFORE SORT ----\n");
  tbl_print(t, stderr);
  fprintf(stderr, "---------\n");
#endif
  tbl_sort(t, col-1, !down);
  tbl_print(t, stdout);
  tbl_free(t);

}

