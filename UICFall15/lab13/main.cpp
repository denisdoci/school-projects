// ticTacToeForLab.cpp
/*
Today's lab is about using Linked List with Struct(recording game progress) for Tic-tac-toe game.
This lab is prelude of program 6, think about how use the similiar idea in program 6.

During playing game, the print out in the screen should be like below:

Welcome to Tic-tac-toe. On each move enter 1-9, corresponding to the location
into which you want to place a piece.  The locations are:
1 2 3
4 5 6
7 8 9

. . .
. . .
. . .
1. Location 1-9 for X: 5

List is:
. . .
. . .
. . .

. . .
. X .
. . .
2. Location 1-9 for O: 7

List is:
. . .
. . .
. . .

. . .
. X .
. . .

. . .
. X .
O . .
3. Location 1-9 for X: 4


List is:
. . .
. . .
. . .

. . .
. X .
. . .

. . .
. X .
O . .

. . .
X X .
O . .
4. Location 1-9 for O: ...


TODO tasks for today:
Point 1. Finish function displayList( char board[]).
Point 2. Finish the definition of struct Node, following the comment of the fields in the struct declaration.
Point 3. Finish function appendToList(Node *&pHead, Node *&pTail, char board[], char playerToMove, int moveNumber)
*/



#include <iostream>
#include <string.h>
using namespace std;

struct Node {
    char board[9];
    char player;
    int move;
    Node * nextPtr;
};


void displayBoard( char board[]){
    printf("\n");
    printf(" %c %c %c \n", board[0], board[1], board[2]);
    printf(" %c %c %c \n", board[3], board[4], board[5]);
    printf(" %c %c %c \n", board[6], board[7], board[8]);
}//end printBoard()

/*
 * Function: displayList
 * -------------------------------
 * Traverse the whole linked list, print information in each node in order to print each steps when playing the game,
 * as you could see in the print out demo in the instruction above.
 */
void displayList( Node *&pHead)
{
    //cout << "in display list" << endl;
   Node *tempPtr = pHead;  // Used to traverse list without destroying head
   cout << "\n List contains: ";
   while( tempPtr != NULL) {
      displayBoard(tempPtr->board);
      tempPtr = tempPtr->nextPtr;
   }
   cout << "\n\n";

}

/*
 * Function: appendToList
 * -------------------------------
 * Make a new Node and append it to the tail of the linked list, so that when you print the list, you could traverse print
 * from the head to tail to print each step in sequence.
 * You must use pHead and pTail pointer to keep track of the head and tail of the linked list.
 * Note: you need to be careful to deal with the bounary case, when initial linked list is empty. Make sure you update the
 * head and tail pointer in the right way.
 */
void appendToList( Node *&pHead, Node *&pTail, char board[], char playerToMove, int moveNumber)
{
     Node *tempPtr;

    // if the linked list is empty
    if(pHead == NULL)
    {
         tempPtr = new Node;
         //copy a string of an array
         strncpy(tempPtr->board,board,9);
         tempPtr->move = moveNumber;
         tempPtr->player = playerToMove;
         tempPtr->nextPtr = NULL;
         pHead = tempPtr;
         pTail = tempPtr;
    }
    else
    {
        tempPtr = new Node;
        strncpy(tempPtr->board,board,9);
        tempPtr->move = moveNumber;
        tempPtr->player = playerToMove;
        tempPtr->nextPtr = NULL;
        //pHead = tempPtr;
        pTail ->nextPtr = tempPtr;
        pTail = tempPtr;
    }
}


int main()
{
    char board[ 9] = {'.', '.', '.',
                      '.', '.', '.',
                      '.', '.', '.'};
    int moveNumber = 1;
    char playerToMove = 'X';
    int userInput;

    // Variables for linked list
    Node *pHead = NULL;
    Node *pTail = NULL;

    cout << "Welcome to Tic-tac-toe. On each move enter 1-9, corresponding to the location \n"
         << "into which you want to place a piece.  The locations are: \n"
         << " 1 2 3 \n"
         << " 4 5 6 \n"
         << " 7 8 9 \n";



    appendToList( pHead, pTail, board, playerToMove, moveNumber);

    displayBoard(board);
    // Infinite loop.  To be complete, program should check for a win,
    // but we are not worrying about that for this version.
    for( int i=0; i<9; i++) {

        // Prompt for and get user input.  Assume perfect input
        cout << moveNumber << ". " << "Location 1-9 for " << playerToMove << ": ";
        cin >> userInput;
        board[ userInput-1] = playerToMove;

        // change the playerToMove
        if( playerToMove == 'X') {
            playerToMove = 'O';
        }
        else {
            playerToMove = 'X';
        }

        moveNumber++;

        appendToList( pHead, pTail, board, playerToMove, moveNumber);

        // Display the list
        displayList( pHead);

    }

    return 0;
}
