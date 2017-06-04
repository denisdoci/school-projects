#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tbl.h"


// recommended utility function that "trims" leading and trailing
//   whitespace from the string s.
//
// Examples:  
//
//		"   abc  " would be trimmed to "abc"
//		"   abc 123  " would be trimmed to "abc 123" (embedded whitespace preserved).
//
//   
// Note that, as specified, the modification is "in-place" -- no new string buffer
//    is created or allocated.  This is functionally fine because the string can only
//    get shorter.
//
// Purpose:  input files may be formatted for easy visual display and so various strings 
//    (column labels and row names) may be "padded" with white space for alignment purposes.
//    Such padding should not be considered part of a row name or column label.
//
// Comment:  the library function isspace should be handy.  (In principle, the input file
//    could use different types of whitespace characters -- such as tabs; isspace figures
//    this out for you.
//
// Comment:  this is actually kind of an interesting little programming exercise -- 
//    eliminating leading and trailing whitespace without an additional buffer (and 
//    presumably in one-pass.
// 
static char * trim_string(char *s) {

  char* i = s;
  char* j = s;     
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
 
  return s;
}


static char * str2row(Table *t, char *buf); 

Table * tbl_init() {
int r, c, i;

  Table *t = malloc(sizeof(Table));

  t->sort_by = 0; // set it to something
  t->direction = 1; // default increasing

  t->ncols = -2;
  t->first = 1;
  t->nrows = 0;
  //mallocing number of column names
  t->cname = malloc(30 * sizeof(char *));

  //mallocing 30 chars for each column name
  for(i=0; i<30; i++){ t->cname[i] = malloc(30 * sizeof(char)); }
  t->rows = malloc(100 * sizeof(Row));

  for(r=0; r<100; r++){
	t->rows[r].rownum = r;
	t->rows[r].vals = NULL;
	t->rows[r].sort_by_ptr = &(t->sort_by);
	t->rows[r].dir_ptr = 
		&(t->direction);
   //malloc on for each row name
        t->rows[r].name = malloc(30 * sizeof(char));
  }
  return t;
}

void tbl_free(Table *t) {
int i;

  for (i=0; i<t->ncols;i++)
	free(t->cname[i]);
  for(i=0; i<t->nrows; i++){ 
	free(t->rows[i].vals);
	free(t->rows[i].name);
  }
  free(t->rows);
  free(t);
}

int whitespace(char *s) {

  while(*s != '\0') {
	if(!isspace(*s))
	  return 0;
	s++;
  }
  return 1;
}
void growing(Table * t, int * grow){

 int r;
 Row * Temp = malloc((*grow) * 2 * sizeof(Row));

 for(r=0; r<(*grow); r++){
        Temp[r].rownum = t->rows[r].rownum;
        Temp[r].vals = t->rows[r].vals;
        Temp[r].sort_by_ptr = t->rows[r].sort_by_ptr;
        Temp[r].dir_ptr = t->rows[r].dir_ptr;
   //malloc on for each row name
        Temp[r].name = t->rows[r].name;
  }
 (*grow) *= 2;

  for(; r<(*grow); r++){
        Temp[r].rownum = r;
        Temp[r].vals = NULL;
        Temp[r].sort_by_ptr = &(t->sort_by);
        Temp[r].dir_ptr =
                &(t->direction);
   //malloc on for each row name
        Temp[r].name = malloc(30 * sizeof(char));;
 }
 t->rows = Temp;
}
Table * tbl_from_stream(FILE *stream) {
int lno;
Table *t;
char buf[MAX_LINE_LEN+1];
char *res;
int n;
char * temp;
int i=0;
int j=0;
int grow = 100;


  t = tbl_init();
  lno = 0;
  while(fgets(buf, MAX_LINE_LEN, stream)!=NULL){

    lno++;
    n = strlen(buf);

    if(t->nrows >= grow-1){
	growing(t, &grow);
    }

    if(buf[n-1] != '\n') {
	    // FIX ADDED 3/13/16 -- allows last line of input to not be terminated
	    //   by '\n' and not incorrectly flag it as being too long.
	    //   The test below confirms that if there is indeed no '\n' terminating
	    //   the input, that we are also at the end of the input.
	    // FWIW, text files edited with vim seem to always have a newline
	    //   at the end of the last line... perhaps not necessarily true 
	    //   with other editors.
	    if(getc(stream) != EOF) {
		    tbl_free(t);		
		    fprintf(stderr, "line %i too long\n", lno);
		    fprintf(stderr, "line: %s\n", buf);
		    return NULL; 
	    }
    }

//column copy code
    if(t->first == 1 && !whitespace(buf) && buf[0] != '#'){
      temp = strtok(buf, ":");
      while(temp != NULL){
        strcpy(t->cname[j], temp);
        temp = strtok(NULL, ":");
        t->ncols++;
        j++;
      }
      t->first = 0;
    }
    // skip blank lines and lines beginning with '#'
    //    which are interpreted as comments

    // FIX ADDED 3/13/16.  Now smarter about what qualifies
    //   as a "blank line" that should be skipped.
    // :New rule is:  any string that contains only white 
    //   space (including the empty string).
    else if(!whitespace(buf) && buf[0] != '#' && t->first != 1) {
	    char * c;
	    c = strtok(buf, ":");
	    strcpy(t->rows[i].name, c);
            c = strtok(NULL, ":");
	    trim_string(buf);
	    //printf("Name: %s\n", buf);
            //printf("\nNrows %d\n", t->nrows);
	    res = str2row(t,c);
	    if(res != NULL) {
		    fprintf(stderr, "line %i: %s\n", lno, res);
		    tbl_free(t);
		    return NULL;
	    }
      i++;
    }
  }
  return t;
}







static void tbl_set_rownums(Table *t) {
int i;

  for(i=0; i<t->nrows; i++) 
	t->rows[i].rownum = i;
}

/**
* static:  file scope
*/
static int cmp(const void *a, const void *b) {
Row *ra = (Row *)a;
Row *rb = (Row *)b;
int col = *(ra->sort_by_ptr);
int dir = *(ra->dir_ptr);

  if(ra->vals[col] < rb->vals[col])
	return -dir;
  if(rb->vals[col] < ra->vals[col])
	return dir;
  // return 0;  // not nec stable
  return ra->rownum - rb->rownum;  // ensures stable sort
}

static int cmp2(const void *a, const void *b) {
Row *ra = (Row *)a;
Row *rb = (Row *)b;
int col = *(ra->sort_by_ptr);
int dir = *(ra->dir_ptr);

  return strcmp(ra->name, rb->name);  // ensures stable sort
}
  
void tbl_print(Table *t, FILE *stream) {
int i, j;

  if(t==NULL) {
	fprintf(stream, "# attempted to print non-existing table\n");
  	return;
  }
  for(i=0; i<=t->ncols; i++){
      trim_string(t->cname[i]);
       printf("%s:  ", t->cname[i]);
  }
  printf("\n");
  for(i=0; i<t->nrows; i++){
    trim_string(t->rows[i].name);
    printf("%s:", t->rows[i].name);
    for(j=0; j<t->ncols; j++) {
	fprintf(stream, "%10.2f", t->rows[i].vals[j]);
    }
    fprintf(stream, "\n");
  }
}

void tbl_sort(Table *t, int col, int incr){

  t->direction = incr ? 1 : -1;
  t->sort_by = col;
  if(col == -1) {qsort(t->rows, t->nrows, sizeof(Row), cmp2);}
  else {qsort(t->rows, t->nrows, sizeof(Row), cmp);}

  tbl_set_rownums(t);
} 



  
/**
* success:  returns NULL
*
* failure:  returns error message
*/
static char * str2row(Table *t, char *buf) {
int r, j;
int nchars;
double x;
int count;
char *temp;
  t->nrows++;

  r = t->nrows-1;
  j=0;

  if(t->nrows == 1) {
	t->rows[r].vals = malloc(t->ncols+12*sizeof(double));
  }
  else {
	t->rows[r].vals = malloc(t->ncols+12*sizeof(double));
  }
 while( sscanf(buf, "%lf%n",&x, &nchars) == 1){
    if(j==MAX_COLS || (r>0 && j==t->ncols))
	return "line too long";
    t->rows[r].vals[j] = x;
    buf += nchars;
//    printf("\nin str 2 row everything aok\n");
    j++;
  }
  if(j < t->ncols) // too few columns
	return "line too short";
  return NULL;
}

	

  
static int NumCmps = 0;


ROW_CMP cmp_rows(Row *a, Row *b, Table * t) {

  int i;
  int eq=0;
  int bovA =0;
  int aovB = 0;

  NumCmps++;    // DO NOT DELETE THIS LINE!!!

  for(i=0; i < t->ncols; i++){
    
    if(a->vals[i] == b->vals[i])
	eq++;
    if(a->vals[i] < b->vals[i])
 	bovA++;
    if(a->vals[i] > b->vals[i])
	aovB++;
  }
  /**
  *  TODO
  *  replace code below with your solution...
  * fprintf(stderr, "cmp_rows not implemented... returning 'equal'\n");
  */
if(eq == t->ncols)
  return equal;  // placeholder...
else if(bovA < aovB)
  return a_dom_b;
else if(aovB < bovA)
  return b_dom_a;
else 
  return incomparable;
}



Table * tbl_minima(Table *t) {

  NumCmps = 0;   // DO NOT DELETE THIS LINE!!!
 
  /**
  *  TODO
  *  replace code below with your solution...
  */

printf("\nDidn't do minima so dont bother\n");

 return t;
}
/*
this was meant to be a grow operation depending on how big the actual
formula table was.
I did not end up using it, as the formula table was pretty small and fit
into the ADT as it stood\


void growbytwlv(Table * t){

 int r;
 int n = t->numcols + 12;
 double * Temp = malloc(n * sizeof(double));
 char ** colname = malloc(n * sizeof(char *));

  //mallocing 30 chars for each column name
  for(i=0; i<30; i++){ colname[i] = malloc(30 * sizeof(char)); }
 
   for(r=0; r< t->numcols; r++){
        Temp[r] = t->rows[r].name;
  }

  for(; r<n; r++){
        Temp[r].rownum = r;
        Temp[r].vals = NULL;
        Temp[r].sort_by_ptr = &(t->sort_by);
        Temp[r].dir_ptr =
                &(t->direction);
   //malloc on for each row name
        Temp[r].name = malloc(30 * sizeof(char));;
 }
 t->rows = Temp;
}
*/

/*
 *My favorite recursion!!!
 *Basically what it does is complete and return the operations at the base cases
 *until that point is achieved, it uses pointer arithmetic to recursively solve
 *formulas given. After one is solved the pointer is reset so the for loop can continue
 *to giveprover values
 *
 */
double eval(Table *t, int j, char * operation){

//base: constant number
     if(isdigit(operation[0])){
	 double i = atoi(&operation[0]);
	 return i;
     }

//base: column
   else if(operation[0] == '$'){
	int i = atoi(&operation[1]);
//	printf("\nIn column identifier\n");
	return t->rows[j].vals[i-1];
     }

//addition
   else if(operation[0] == '+'){      
//	printf("\nCurrent String%s\n", operation);
	operation++;

	double first = eval(t,j, operation);

	operation++;

        double second = eval(t,j, operation);

       // printf("\nSecond value %f: \n", second);
	operation--;

	return (first+second);
   }

//subtraction
   else if(operation[0] == '-'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);
	
	operation--;
       // printf("\nSecond value %f: \n", second);
        return (first-second);
   }

//multiplication
   else if(operation[0] == '*'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
       // printf("\nSecond value %f: \n", second);
        return (first*second);
   }

//division
   else if(operation[0] == '/'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
	if(second == 0){printf("\nError cant divide by zero!!!\n\n"); return -999;}
       // printf("\nSecond value %f: \n", second);
        return (first/second);
   }

//less than
   else if(operation[0] == '<'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
	if(first < second) return 1;
	else return 0;
       // printf("\nSecond value %f: \n", second);
   }

//greater than
   else if(operation[0] == '>'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
        if(first > second) return 1;
        else return 0;
       // printf("\nSecond value %f: \n", second);
   }

//equal to
   else if(operation[0] == '='){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
        if(first == second) return 1;
        else return 0;
       // printf("\nSecond value %f: \n", second);
   }

//and operator
 else if(operation[0] == '&'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
        return (first && second);
   }

//or operator
 else if(operation[0] == '|'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation++;

        double second = eval(t,j, operation);

        operation--;
        return (first || second);
   }

//not operator
 else if(operation[0] == '!'){

//        printf("\nCurrent String%s\n", operation);
        operation++;

        double first = eval(t,j, operation);

        operation--;
        return (!first);
   }


//base case invalid operation or expression
 else{
   printf("\nInvalid formula expression exiting program");
   return 0;
 }
}

void tbl_calc(Table *t, char *formula){
  
  char * cname;
  char * expres;
  int j = t->ncols+1;
  int i;
  double ret;
  int k = t->ncols+13; //extend number of columns

  
  cname = strtok(formula, ":"); //get name from passed array
  strcpy(t->cname[j], cname);
  expres = strtok(NULL, "\n"); //get next operation
  trim_string(expres);
  for(i=0; i<t->nrows; i++){  //set row values
        ret = eval(t, i, expres);
        t->rows[i].vals[j-1] = ret;
  } 
  t->ncols=t->ncols+=2;
  j++;


 while(j < k){
  cname = strtok(NULL, ":");
  //printf("\nCname: %s:\n", cname);
  strcpy(t->cname[j], cname);
  expres = strtok(NULL, "\n");
  trim_string(expres);
 // printf("\nExpress: %s:\n", expres);
  for(i=0; i<t->nrows; i++){
        ret = eval(t, i, expres);
        t->rows[i].vals[j-1] = ret;
  }
  t->ncols++;
  j++;
 }
  t->ncols--;

}

// DO NOT CHANGE THIS FUNCTION!!
int tbl_num_comparisons() {

  return NumCmps;

}
