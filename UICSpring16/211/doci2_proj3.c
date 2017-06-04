#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1

typedef struct NODE{
  int x;
  int y;
  struct NODE* next;
}node;

typedef struct MAZE{
  int xsize, ysize; //how large maze is
  int xstart, ystart; //x,y index of start position
  int xend, yend; // x index of end position
  char **array; // actual content of the maze
}maze;


/* These are pretty basic stack functions I dont 
   really think it's necessary to descibe all of them */

void push(node ** top, int x, int y){
  node * temp = (node*) malloc(sizeof(node));
  temp->x = x;
  temp->y = y;
  temp->next = *top;
  *top = temp;
}
void pop(node **top){
  if(*top != NULL){
    node * temp;
    temp = *top;
    *top = (*top)->next;
    free(temp);
  }
}
 
//function to remove stack from memory
void rmStack(node ** n){
  while(*n != NULL)
      pop(n);
}
//This actually prints stack in reverse
void printSt(node * top){
  if(top==NULL){
  return;
  }
  printSt(top->next);
  printf("(%d, %d) ", top->x, top->y);
}

void setTop(node * p, int *x, int *y){
   if(p != NULL){
	*y = p->y;
	*x = p->x;
   }
   else{
	printf("\nStack is Empty\n");
	exit(-1);
   }
}

//Function to dynamically free maze array
void rmMaze(maze m){
  int i;
  for(i=0; i < m.xsize+2; i++){
    free(m.array[i]);
  }
}
//Function to solve maze 
node * solve(maze m, int debugMode){

  node* stack = NULL;
  int stop=false; // to stop while loop
  int i,j;
  char ** reset; //resets maze to get rid of all of the X's

  //reset is memory allocated similarily to maze
  reset = (char**) malloc(sizeof(char*) * (m.xsize + 2));
  for(i=0; i<(m.ysize+2); i++){
   reset[i] = (char*)malloc(sizeof(char)*(m.ysize+2));
  }
  for(i=0; i < m.xsize+2; i++){
    for(j=0; j<m.ysize+2; j++){
       reset[i][j]= m.array[i][j];
    }
  }
  //push start value on to stzck 
  push(&stack, m.xstart, m.ystart);

  while(stack != NULL && stop == false){
   if(debugMode==true){
    printf("Current Stack: ");
    printSt( stack ); //debug mode true  so print stack as it changes
    printf("\n");
   }
   int x= -1; //x and y set to -1 so they're not initially on maze
   int y= -1;
   setTop(stack, &x, &y);
   if(m.xend == x && m.yend == y){//found end position and solved maze
	stop = true;
	break;   
   }
   int left = x - 1; 
   int right = x + 1;
   int down = y - 1;
   int up = y+1;

   if(m.array[right][y] == '.' || m.array[right][y] == 'e'){
        push(&stack,right, y);
        m.array[right][y] = 'x';
   }
   else if(m.array[x][down] == '.' || m.array[x][down] == 'e'){
        push(&stack, x,down);
        m.array[x][down] = 'x';
   }
   else if(m.array[x][up] == '.' || m.array[x][up] == 'e'){
        push(&stack, x, up);
        m.array[x][up] = 'x';
   }
   else if(m.array[left][y] == '.' || m.array[left][y] == 'e'){
        push(&stack, left, y);
        m.array[left][y] = 'x';
   }
   else{
    pop(&stack); //no viable moves
   }
  }
 //reset maze to it's original position 
  for(i=0; i < m.xsize+2; i++){
    for(j=0; j<m.ysize+2; j++){
       m.array[i][j]=reset[i][j];
    }
  }
  //free reset array
  for(i=0; i < m.xsize+2; i++){
   free(reset[i]);
  }
  return stack; 
}


//function to initialize maze with
//given file from the command line
maze createMaze(char *file){
  
  maze m;
  int xpos, ypos;
  int i, j;
  FILE *src;

  if ( ( src = fopen( file, "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", file);
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m.xsize, &m.ysize);
  fscanf (src, "%d %d", &m.xstart, &m.ystart);
  fscanf (src, "%d %d", &m.xend, &m.yend);
   
  //allocate first dimension of array 
  m.array = (char**) malloc(sizeof(char*) * (m.xsize + 2));
 
  //allocate second dimension with a for loop
  for(i=0; i<(m.ysize+2); i++){
  m.array[i] = (char*)malloc(sizeof(char)*(m.ysize+2));
  }
  
  //initialize all elements of maze to be .
  for(i=0; i < m.xsize+2; i++){
    for(j=0; j<m.ysize+2; j++){
	m.array[i][j] = '.';
    }
  }

  /* mark the borders of the maze with *'s */
  for (i=0; i < m.xsize+2; i++)
    {
     m.array[i][0] = '*';
     m.array[i][m.ysize+1] = '*';
    }
  for (i=0; i < m.ysize+2; i++)
    {
     m.array[0][i] = '*';
     m.array[m.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m.array[m.xstart][m.ystart] = 's';
  m.array[m.xend][m.yend] = 'e';
		  
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
      m.array[xpos][ypos] = '*';
    }
 return m; 
}


//Function to print out maze using nested for loops
void printMaze(maze m){
   int i,j;
   for (i=0; i<m.xsize+2; i++){
     for(j=0;j<m.ysize+2; j++)
	printf("%c", m.array[i][j]);
     printf("\n");
  }
}



int main(int argc, char** argv)
{ 
  maze m1;
  node * stack=NULL; // stack pointer
  node * temp; //temporary node
  int px, py; // previous x and y positions
  int x, y;  //x and y positions
  int i,j;
  int debugMode = false;
  char *file;

 /* verify the proper number of command line arguments were given */
  if( argc > 3 ) {
    printf("Usage: %s [-d] <maze data file>\n", argv[0]);
    exit(-1);
  }
   
  if( 2 == argc ) {//2 arguements, no debug
    file = argv[1];
  }

  if( 3 == argc ) { //three arguements provided with debug
    if( argv[1][0] == '-' && argv[1][1] == 'd' ) {
      debugMode = true;  // ./a.out -d mazeInput.txt
      file = argv[2];  
    }
    else if(argv[2][0] == '-' && argv[2][1] == 'd'){
      debugMode = true;  // ./a.out mazeInput.txt -d
      file = argv[1];
    }
  }


  m1 = createMaze(file); //initialize maze

  printf("Input Maze\n");
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  printMaze(m1);
  
  stack = solve(m1, debugMode);

  if(stack == NULL){ //nothing on stack
  	printf("\n This maze is unsolvable!!!\n");
  }
  else{
	px= -1; //previous x and y set to -1 as to not be in maze
	py= -1;

	temp = stack;
	
	while(temp != NULL){
	  x = temp->x;
	  y = temp->y;
	  if(m1.array[x][y] != 'e' &&  m1.array[x][y] != 's') {
	    if(px == x+1)
		m1.array[x][y] = 'V'; //down
	    else if (px == x-1)
		m1.array[x][y] = '^'; //up
	    else if(py == y+1)
		m1.array[x][y] = '>'; //right
	    else if(py == y-1)
		m1.array[x][y] = '<'; //left
	    else{
		printf("\nValue not available in stack (%d, %d)\n", x,y);
	    }
	  }
	  px = x; //set previous x and y to the node's values
	  py = y;
	  temp = temp->next; //move along stack
	}
  }
  printMaze(m1); // reprint maze with solution
  printf("\nSolution coordinates: \n");
  printSt( stack); 
  printf("\n");

  rmStack(&stack);
  rmMaze(m1);

  return(0);
}
