#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

// A macro to print debug messages only if debug mode is TRUE
// This macro behaves like a printf() function
// The \ character at end of each line of this macro is necessary
#define debug(...)				\
  if( debugMode ) {				\
    printf(__VA_ARGS__);			\
  } 

#define debugPrintStack(stack)			\
  if( debugMode == 1 ) {			\
    printf("Current Stack: ");			\
    printStack( stack );                        \
    printf("\n");                               \
  }  

#define VISITED 'x'
#define START 'S'
#define END 'E'
#define OBSTACLE '*'
#define FREE '.'

// Define bool user defined datatype
typedef int bool;

// Initialize debug mode to be false
int debugMode = FALSE;

typedef struct node {
  struct node* next;
  int x, y;
} NODE;

typedef NODE * NODEPTR;

typedef struct mazeStruct
{
  char *arr;  /* allows for a maze of size 30x30 */
  int xsize, ysize;
  int xstart, ystart;
  int xend, yend;
  int rows, cols;
} MAZE;

/* Maze Function Declarations */
MAZE createMazeFromFile(char *);
void printMaze(MAZE);
NODEPTR solveMaze(MAZE);
void freeMaze(MAZE);

/* Stack Functions */
void push(NODEPTR *top, int x, int y) {
  NODEPTR temp = (NODEPTR) malloc( sizeof(NODE) );
  temp->x = x;
  temp->y = y;
  temp->next = *top;
  *top = temp;
}

void pop(NODEPTR *top) {
  if( NULL != *top ) {
    NODEPTR temp = *top;
    *top = (*top)->next;
    free(temp);
  }
}

void top(NODEPTR t, int *x, int *y) {
  if( NULL != t ) {
    *x = t->x;
    *y = t->y;
  } else {
    printf("Stack is Empty\n");
    exit(-1);
  }
}

void clearStack(NODEPTR *top) {
  while( NULL != *top ) {
    pop(top);
  }
}

bool isEmpty(NODEPTR top) {
  return (NULL == top);
}

void printStack(NODEPTR top) {
  if( NULL != top ) {
    printStack( top->next );
    printf("(%d, %d) ", top->x, top->y );
  }
}

int main (int argc, char **argv)
{
  int i,j;

  debugMode = FALSE;

  char *fileName = NULL;

  /* verify the proper number of command line arguments were given */
  if( argc > 3 ) {
    printf("Usage: %s [-d] <maze data file>\n", argv[0]);
    exit(-1);
  }

  /* Identify the file name argument and debug mode argument */
  if( 2 == argc ) {
    // No debug mode argument
    fileName = argv[1];
  }

  if( 3 == argc ) {
    // second argument is flag. third argument is filename
    fileName = argv[2];
    if( argv[1][0] == '-' && argv[1][1] == 'd' ) {
      debugMode = TRUE;
    }
  }

  MAZE m1 = createMazeFromFile( fileName );

  /* print them out to verify the input */
  printf("Input Maze\n");
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  /* print out the initial maze */
  printMaze( m1 );

  // Solve the maze
  NODEPTR stack = solveMaze( m1 );

  // print the solution
  if( isEmpty( stack ) ) {
    printf("\n\n The maze has NO SOLUTION\n");
  } else {
    printf("\n\nThere is a path through the maze.\n");
    
    // Mark the path in the maze
    int prevX = -1;
    int prevY = -1;
    NODEPTR temp = stack;
    while( NULL != temp ) {
      int x = temp->x;
      int y = temp->y;
      int coord = x*m1.cols + y;

      if( END != m1.arr[coord] && START != m1.arr[coord] ) {
	if( prevX == x+1 ) {
	  m1.arr[coord] = 'v';
	} else if(prevX == x-1 ) {
	  m1.arr[coord] = '^'; 
	} else if( prevY == y+1 ) {
	  m1.arr[coord] = '>';
	} else if( prevY == y-1 ) {
	   m1.arr[coord] = '<';
	} else {
	  printf("\n Illegal value in stack (%d, %d)\n", x, y);
	  exit(-1);
	}
      }

      prevX = x;
      prevY = y;

      temp = temp->next;
    }

    printMaze( m1 );

    // Print the stack in reverse order
    printf("\n The list of maze co-ordinates in the path are:\n");
    printStack( stack );
    printf("\n");
  }

  // Free stack
  clearStack( &stack );

  // Free maze memory
  freeMaze( m1 );

  return 0;
}

NODEPTR solveMaze(MAZE m) {
  // Initalize stack
  NODEPTR stack = NULL;

  // Hack to ensure that m.arr is not changed during solving
  int bkpSize = m.rows * m.cols;
  char *bkp = (char *) malloc(sizeof(char) * bkpSize );
  memcpy(bkp, m.arr, bkpSize);

  // push start onto stack
  push( &stack, m.xstart, m.ystart );

  bool atEnd = FALSE;

  while( !isEmpty( stack ) && !atEnd ) {

    // debugPrintStack
    debugPrintStack( stack );

    int x = -1, y = -1;
    top( stack, &x, &y );
    int coord = x*m.cols + y;
    
    // Check if END has been reached
    if( m.xend == x && m.yend == y ) {
      atEnd = TRUE;
      break;
    }

    // Go to next free co ordinate in maze
    // Depending upon the order in which the if conditions are written,
    // the solutions will differ even for the same maze. This is a 
    // property of the DEPT FIRST SEARCH algorithm.
    int east = coord+1;
    int south = coord + m.cols;
    int west = coord - 1;
    int north = coord - m.cols;
    if( FREE == m.arr[east] || END == m.arr[east] ) {
      push( &stack, east/m.cols, east%m.cols );
      m.arr[east] = VISITED;
    } else if( FREE == m.arr[south] || END == m.arr[south] ) {
      push( &stack, south/m.cols, south%m.cols );
      m.arr[south] = VISITED;
    } else if( FREE == m.arr[west] || END == m.arr[west] ) {
      push( &stack, west/m.cols, west%m.cols );
      m.arr[west] = VISITED;
    } else if( FREE == m.arr[north] || END == m.arr[north] ) {
      push( &stack, north/m.cols, north%m.cols );
      m.arr[north] = VISITED;
    } else {
      pop( &stack );
    }
  }

  // Refresh maze
  memcpy(m.arr, bkp, bkpSize);

  // return stack
  return stack;
}

void printMaze(MAZE m1) {
  int i,j;
  for (i = 0; i < m1.xsize+2; i++)
    {
      for (j = 0; j < m1.ysize+2; j++)
	printf ("%c", m1.arr[i*m1.cols + j]);
      printf("\n");
    }
}

void freeMaze(MAZE m) {
  free(m.arr);
}


MAZE createMazeFromFile(char *fileName) {
  MAZE m1;
  int xpos, ypos;
  int i,j;

  FILE *src;

  /* Try to open the input file. */
  if ( ( src = fopen( fileName, "r" )) == NULL )
    {
      printf("Cannot open input file: %s\n", fileName);
      exit(-1);
    }

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  m1.rows = m1.xsize+2;
  m1.cols = m1.ysize+2;

  /* Allocate memory for the maze array */
  int size = m1.rows * m1.cols;
  m1.arr = (char *) malloc( sizeof(char) * size );
  
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
    for (j = 0; j < m1.ysize+2; j++)
      m1.arr[i*m1.cols + j] = FREE;

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
      m1.arr[i*m1.cols + 0] = OBSTACLE;
      m1.arr[i*m1.cols + m1.ysize+1] = OBSTACLE;
    }
  for (i=0; i < m1.ysize+2; i++)
    {
      m1.arr[i] = OBSTACLE;
      m1.arr[(m1.xsize+1)*m1.cols + i] = OBSTACLE;
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart*m1.cols + m1.ystart] = START;
  m1.arr[m1.xend*m1.cols + m1.yend] = END;
		  
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
      m1.arr[xpos*m1.cols + ypos] = OBSTACLE;
    }

  return m1;
}
