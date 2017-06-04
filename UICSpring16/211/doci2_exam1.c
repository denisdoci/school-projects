/*
 *Denis Doci
 *Net ID: doci2
 *UIN: 663855180
 *3pm section
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  float val;
  struct node *next;
}NODE;

typedef struct list_struct{
  NODE * front;
}list;

int isEmpty(list * stack){
   if(stack->front == NULL)
	return 0;
   else
        return 1;
}

float top(list * stack){
  return stack->front->val;
}

void pop (list * stack){
  NODE * p;
     p = stack->front;
     stack->front = stack->front->next;
     free(p);
}

void push (list * stack, float  data){
  NODE * p = malloc(sizeof(NODE));

  p->val = data;
  p->next = stack->front;
  stack->front = p;
}

//error check function
void lst_print(list *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(" %.1f, ", p->val);
    p = p->next;
  }
  printf("]\n");
}
int main(int argc, char **argv){

  //allocating memory for linked lists
  list * stkPos = malloc(sizeof(list));
  list * stkNeg = malloc(sizeof(list));

  //read in file 
  FILE *src;
  float input;

  //intitializing stack
  stkPos->front= NULL;
  stkNeg->front= NULL;


  /* verify the proper number of command line arguments were given */
  if(argc != 2) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  while(fscanf(src, "%f", &input) != EOF){
    //printf("\n%.1f", input); error check 
   if(input > 0){
     push(stkPos, input);
   }
   if(input < 0){
     push(stkNeg, input);
   }
  }
//read in error check
//  lst_print(stkPos);
// lst_print(stkNeg);

int count=0;
//print positive 
printf("\nPositive values in reverse order\n");
 while(isEmpty(stkPos) != 0){
   float d = top(stkPos);
   printf("%f ", d);
   pop(stkPos);
   count++;
   if(count % 6 ==0) //print newline after six values for read-ability
   printf("\n");
 }
count = 0; //reset count;
printf("\nNegative values in reverse order\n");
while(isEmpty(stkNeg) != 0){
   float d = top(stkNeg);
   printf("%f ", d);
   pop(stkNeg);
   count++;
   if(count % 6 ==0) //print newline after six values for read-ability
   printf("\n");
 }
printf("\n");
//free lists to avoid memory leak
free(stkPos);
free(stkNeg);
}

