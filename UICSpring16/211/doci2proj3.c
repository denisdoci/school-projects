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

void printSt(node * top){
  if(top==NULL) return;
  printSt(top->next);
  printf("(%d, %d) ", top->x, top->y);
}

void clr(node ** top){
    while(NULL != *top)
	pop(*&top);
}

void top(node * p, int *x, int *y){
   if(p != NULL){
	*y = p->y;
	*x = p->x;
   }
   else{
	printf("\nStack is Empty\n");
	exit(-1);
   }
}
node * solve(maze m, int debugMode){

  node* stack = NULL;
  int stop=false;
  int count = 0;
  int i,j;
  char ** reset;

  reset = (char**) malloc(sizeof(char*) * (m.xsize + 2));
  for(i=0; i<(m.ysize+2); i++){
   reset[i] = (char*)malloc(sizeof(char)*(m.ysize+2));
  }
  for(i=0; i < m.xsize+2; i++){
    for(j=0; j<m.ysize+2; j++){
       reset[i][j]= m.array[i][j];
    }
  }
  push(&stack, m.xstart, m.ystart);

  while(stack != NULL && stop == false){
   if(debugMode==true){
    printf("Current Stack: ");
    printSt( stack );
    printf("\n");
   }
   int x= -1;
   int y= -1;
   top(stack, &x, &y);
   if(m.xend == x && m.yend == y){
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
    pop(&stack);
   }
  }
  for(i=0; i < m.xsize+2; i++){
    for(j=0; j<m.ysize+2; j++){
       m.array[i][j]=reset[i][j];
    }
  }
  return stack; 
}

maze createMaze(char *file){
  maze m;
  int xpos, ypos;
  int i, j;
  FILE *src;

  /* Try to open the input file. */
  if ( ( src = fopen( file, "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", file);
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m.xsize, &m.ysize);
  fscanf (src, "%d %d", &m.xstart, &m.ystart);
  fscanf (src, "%d %d", &m.xend, &m.yend);
  /* print them out to verify the input */
  
  m.array = (char**) malloc(sizeof(char*) * (m.xsize + 2));
  for(i=0; i<(m.ysize+2); i++){
  m.array[i] = (char*)malloc(sizeof(char)*(m.ysize+2));
  }
  
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
  node * stack=NULL;
  node * temp;
  int px, py;
  int x, y;
  int i,j;
  int debugMode = false;
  char *file;

 /* verify the proper number of command line arguments were given */
  if( argc > 3 ) {
    printf("Usage: %s [-d] <maze data file>\n", argv[0]);
    exit(-1);
  }

  /* Identify the file name argument and debug mode argument */
  if( 2 == argc ) {
    // No debug mode argument
    file = argv[1];
  }

  if( 3 == argc ) {
    // second argument is flag. third argument is filename
    if( argv[1][0] == '-' && argv[1][1] == 'd' ) {
      debugMode = true; 
      file = argv[2];  
    }
    else if(argv[2][0] == '-' && argv[2][1] == 'd'){
      debugMode = true;
      file = argv[1];
    }
  }


  m1 = createMaze(file);

  printf("Input Maze\n");
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  printMaze(m1);
  
  stack = solve(m1, debugMode);

  if(stack == NULL){
  	printf("\n Unsolvable \n");
  }
  else{
	px= -1;
	py= -1;

	temp = stack;
	
	while(temp != NULL){
	  x = temp->x;
	  y = temp->y;
	  if(m1.array[x][y] != 'e' &&  m1.array[x][y] != 's') {
	    if(px == x+1)
		m1.array[x][y] = 'V';
	    else if (px == x-1)
		m1.array[x][y] = '^';
	    else if(py == y+1)
		m1.array[x][y] = '>';
	    else if(py == y-1)
		m1.array[x][y] = '<';
	    else{
		printf("\nValue not available in stack (%d, %d)\n", x,y);
	    }
	  }
	  px = x;
	  py = y;
	  temp = temp->next;
	}
  }
  printMaze(m1);
  printf("\n The list of maze co-ordinates in the path are:\n");
  printSt( stack);
  printf("\n");
}
