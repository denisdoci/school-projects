#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define false 0;
#define true 1;

typedef struct{
    int top;
    int size;
    char  * stk;
} stack;

void initstk(stack *s)

{
   s->top = -1;
   s->size=2;
   s->stk = (char*) malloc(sizeof(char)*2);
}

int isFull(stack * s) {
    if (s->top == s->size - 1)
        return true; 

        return false;
}

int isEmp(stack * s) {
    if (s->top == -1) 
        return true; 

        return false;
}

char top(stack * s) {
    return s->stk[ s->top ];
}

char pop(stack * s, int dbug) {
    
    if( isEmp(s) ) {
        printf("Cannot pop from empty stack\n");    
        exit(-1);
    }
    char tpstk;
    tpstk = s->stk[s->top];
    if(dbug == 1){
       printf("\n %c being popped off of stack\n", tpstk);
    }
    s->top--;
    return tpstk;
}

void grow(stack * s, int dbug)
{
    
    char *temp;
    temp = (char*)malloc( sizeof(char) * (s->size + 2) );
    memcpy(temp, s->stk, s->size);
    free(s->stk);
    s->stk = temp;
    s->size += 2;
    if(dbug == 1){
      printf("\nGrowing the stack\n");
      printf("\nIncreased size by 2\n");
      printf("\nOld stack size is: %d\n", s->size-2);
      printf("\nNew stack size is: %d\n", s->size);
      printf("\nAmount of values copied onto new stack is: %d\n", s->size-2);
    }
}


void push(stack * s, char c, int dbug)
{
    if(isFull(s)){
        grow(s, dbug);
    }
    s->top ++;
    s->stk[s->top] = c;

    if(dbug == 1){
	printf("\n %c being pushed onto stack\n", c);	
    }
}

void printStack(stack * s) {
    if( !isEmp(s) ) {
        printf("Stack: ");
        int i = 0;
        for(i=0; i <= s->top; i++) {
            printf(" %c", s->stk[ i ] );
        }
        printf("\n");
    }
}

int openingChar(char c) {
    if(c == '(' || c == '{' || 
            c == '[' || c == '<' ) {              
        return true;
    }              
    else
        return false;
}


int closingChar(char c) {
    
    if(c == ')' || c == '}' || 
            c == ']' || c == '>') {
        return true;
    }
    
    else
        return false;
}

char opposite( char c)

{
    if( c == '(' )
        return ')';
    
    else if(c == '{')
        return '}';
    
    else if(c =='[')
        return  ']';
    
    else if(c == '<')
        return '>';   
    
    else if(c == ')')
        return '(';
    
    else if(c == '}')
        return  '{';   
    
    else if(c == ']' )
        return  '[';   
    
    else if(c == '>')
        return  '<';
    
    else{
        
        printf("\nError\n");
        return ' ';
    }
    
}



int isBalanced(char * expression, char *unbal, int *unbalIndex,
	       int *expecting, int *missing, int dbug)

{   stack s;
    *unbal = ' ';
    *unbalIndex = -1;
    int i;
    int length;
    char c;
    char topchar;
    length = strlen(expression);
    
    initstk(&s);
    
    for(i=0; i< length; i++) {
        
        char c = expression[i];
        if( openingChar( c)){
            push(&s, c, dbug); 
        }
        
        else if(closingChar(c)){
            if( isEmp(&s)){
                *unbalIndex = i;
                *unbal = opposite(c);
                *missing = 1;
                return false;
            }
            topchar = top(&s);
            
            if(topchar != opposite(c))
                
            {
                *unbalIndex = i;
                *unbal = opposite(c);
                *expecting = 1;
                return false;
            }
           pop(&s, dbug); 
        }
 	if( dbug == 1) {
        printStack( &s );
        }
    }
    
    if( !isEmp(&s)){
        topchar = top(&s);
        *missing = 1;  
        *unbal = opposite(c);
        *unbalIndex = i;
        return false; 
        
    }
    return true;
}

void input(char * expression)

{
    printf("\nEnter expression. Enter q or Q to quit:\n");
    fgets(expression, 301, stdin);
    int len;    
    len = strlen(expression);   
}

int main(int argc, char **argv){
    
    int mxInput = 300;    
    char expression[mxInput];  
    int expecting=0;  
    int missing = 0;
    char unbal;
    int unbalIndex;
    int i,j;
    int loop = 1;
    int dbug = 0;
    
    if( argc > 1){
	for(j = 0; j < argc; j++){
	  if(strcmp(argv[j], "-d") == 0)
	  dbug = true;
        }
   }      
    while(loop)
        
    {   
        input ( expression);
        
        if(strcmp(expression, "q\n")==0 || strcmp(expression, "Q\n")==0){
            printf("\nQuitting program\n");
            exit(0);
        }
       
        if(dbug == 1){
	  printf("Your expression is: %s\n", expression);
	} 
        if(isBalanced(expression, &unbal, &unbalIndex, &expecting, &missing, dbug)){
            
            printf("\nThe expression is balanced\n");
            
        }  
        else{
            printf("\n%s\n", expression);
            for(i=0; i<unbalIndex; i++){
                printf(" ");
            }
            if( missing == 1){
                printf("^ %c is missing from the expression\n", unbal);
            }
            else{
                printf("^ expecting %c in expression\n", unbal);
            }
        }
      }
 
  return 0;   
}
