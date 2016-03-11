#include <iostream>
/*
Lab instruction:
Please follow this instruction step by step to finish today's lab.
Today's lab is about modifying a Tic-Tac-Toe game sample code to get familiar with
our new programing knowledge:
(1) use array to store Tic-Tac-Toe board; initialization of array
(2) read information from file to initialize Tic-Tac-Toe board

FYI, Tic-Tac-Toe wiki: https://en.wikipedia.org/wiki/Tic-tac-toe
     Tic-Tac-Toe online game: http://www.calculatorcat.com/games/tic_tac_toe.phtml

Stage1 (1 point):
    1. read and play with this sample code to know the code structure.
       if you play the game, the output should be like this:
--------------------------------screen shot---------------------------------------

=====================================
Welcome to TicTacToe
Board positions are numbers:
        1  2  3
        4  5  6
        7  8  9
=====================================

-------
 . X .
 O . O
 X X .
-------
Step count: 1
Player to move is (X/O): X
Enter position for placement (1-9): 5

-------
 . X .
 O X O
 X X .
-------
Player X has won the game.

------------------------------screen shot-----------------------------------------

    2. you could see that the sample code use 9 global variable to store board information,
       the board is initialized in initializeBoard().
       Please modify the code to use a global array to store board information. Importantly,
       the board should be initialized in the same way as original sample code.

       After you finish this stage, please call your TA to give you partial score, since next
       stage, you need to modify this function.


Stage2 (1 point):
    There is a board.txt file provided.
    Please refer to the sample code readFile.cpp to read board information from file and
    initialize the board using information in the file.
    All you need to do is to modify and write a new initializeBoard() function.


Stage3 (1 point):
    This game has a while loop without checking if one of the player X or O win the game.
    Search "TODO: stage3" in this file.
    Please finish checkWin() function and call it in main(), so that when one of the player
    win the game, immeditately terminate the loop and finish the game.

    The output should be exactly like:
    "Player X has won the game." or "Player O has won the game."
 */
//global array for board information
char boardInfo[9];

// User placement position
int position;
char player;
int stepCounter = 0;


/* Function: displayGameInfo
 * ----------------------------------
 *   display game information and instructions.
 */
void displayGameInfo(){
    printf("%20s\n", "=====================================");
    printf("%20s\n", "Welcome to TicTacToe");
    printf("%20s\n", "Board positions are numbers:");
    printf("%15s\n", " 1  2  3");
    printf("%15s\n", " 4  5  6");
    printf("%15s\n", " 7  8  9");
    printf("%30s\n\n\n", "=====================================");
}//end displayGameInfo


/* Function:  initializeBoard
 * ----------------------------------
 *   Initialize the board as :
 *        . X O
 *        O . X
 *        X . O
 */
void initializeBoard(){
    FILE *boardFile;
    boardFile = fopen("board.txt", "r");

    //verify that file open worked
    if(boardFile == NULL){
    printf("Can't open %s. Verify it is incorrect location\n", "board.txt");
    exit(-1);
    }

    // read from file
    for(int i = 0; i<9; i++){
    fscanf(boardFile, " %c", &boardInfo[i]);
    }


    fclose(boardFile);   //close the input file
}//end initializeBoard()


/* Function:  printBoard
 * -----------------------------------
 *   Print board on the screen.
 *
 */
void printBoard(){
    printf("\n\n%.7s\n", "--------------------");
    printf(" %c %c %c \n", boardInfo[0], boardInfo[1], boardInfo[2]);
    printf(" %c %c %c \n", boardInfo[3], boardInfo[4], boardInfo[5]);
    printf(" %c %c %c \n", boardInfo[6], boardInfo[7], boardInfo[8]);
    printf("%.7s\n", "--------------------");
}//end printBoard()


/* Function: scanUserInput
 * -----------------------------------
 *   Scan user input command for playing game.
 */
void scanUserInput(){
    stepCounter++;  //add one to step counter
    printf("Step count: %d\n", stepCounter);
    printf("%s", "Player to move is (X/O): ");
    scanf(" %c", &player);
    printf("%s", "Enter position for placement (1-9): ");
    scanf(" %d", &position);
}//end scanUserInput


/* Function: testUserInput
 * -----------------------------------
 *   Test scanUserInput() function
 */
void testUserInput(){
    printf("\n--Test--\n");
    printf("player is %c\n", player);
    printf("position is %d\n", position);
    printf("--Test End--\n\n");
}//end testUserInput


/* Function: makeMoveInBoard
 * -----------------------------------
 *   Make movement in the board, after a user gives the placement instructions.
 */
void makeMoveInBoard(){
    switch(position){
        case 1:
            if(player == 'O'){ boardInfo[0] = 'O'; } else if (player=='X'){ boardInfo[0] = 'X'; };
            break;
        case 2:
            if(player == 'O'){ boardInfo[1] = 'O'; } else if (player=='X'){ boardInfo[1] = 'X'; };
            break;
        case 3:
            if(player == 'O'){ boardInfo[2] = 'O'; } else if (player=='X'){ boardInfo[2] = 'X'; };
            break;
        case 4:
            if(player == 'O'){ boardInfo[3] = 'O'; } else if (player=='X'){ boardInfo[3] = 'X'; };
            break;
        case 5:
            if(player == 'O'){ boardInfo[4] = 'O'; } else if (player=='X'){ boardInfo[4] = 'X'; };
            break;
        case 6:
            if(player == 'O'){ boardInfo[5] = 'O'; } else if (player=='X'){ boardInfo[5] = 'X'; };
            break;
        case 7:
            if(player == 'O'){ boardInfo[6] = 'O'; } else if (player=='X'){ boardInfo[6] = 'X'; };
            break;
        case 8:
            if(player == 'O'){ boardInfo[7] = 'O'; } else if (player=='X'){ boardInfo[7] = 'X'; };
            break;
        case 9:
            if(player == 'O'){ boardInfo[8] = 'O'; } else if (player=='X'){ boardInfo[8] = 'X'; };
            break;
        default:
            printf("%s", "WARNING: the position is out of range of the board!\n");
            printf("%s", "Hint: you might input character rather than number.\n\n");
    }
}// end makeMoveInBoard()


/* TODO: stage3
 * Function:  checkWin
 * ----------------------------------
 *   Check the board and see if one of the player has win
 *        . X O
 *        O . X
 *        O O O
 */
bool checkWin(){
    //horizontal first row
    if((boardInfo[0] =='X' && boardInfo[1] == 'X' && boardInfo[2] == 'X'))
        return false;
    else if(boardInfo[0] =='O' && boardInfo[1] == 'O' && boardInfo[2] == 'O')
        return false;
    else if(boardInfo[3] =='X' && boardInfo[4] == 'X' && boardInfo[5] == 'X')
        return false;
    else if(boardInfo[3] =='O' && boardInfo[4] == 'O' && boardInfo[5] == 'O')
        return false;
    //horizontal second row
    else if(boardInfo[6] =='X' && boardInfo[7] == 'X' && boardInfo[8] == 'X')
        return false;
    else if(boardInfo[6] =='O' && boardInfo[7] == 'O' && boardInfo[8] == 'O')
        return false;
    //vertical first row
    else if (boardInfo[0] =='X' && boardInfo[3] == 'X' && boardInfo[6] == 'X')
         return false;
     else if (boardInfo[0] =='O' && boardInfo[3] == 'O' && boardInfo[6] == 'O')
        return false;
    else if(boardInfo[1] =='X' && boardInfo[4] == 'X' && boardInfo[7] == 'X')
        return false;
    else if (boardInfo[1] =='O' && boardInfo[4] == 'O' && boardInfo[7] == 'O')
        return false;
    else if(boardInfo[2] =='X' && boardInfo[5] == 'X' && boardInfo[8] == 'X')
        return false;
    else if (boardInfo[2] =='O' && boardInfo[5] == 'O' && boardInfo[8] == 'O')
        return false;
    //diagonal left - right
    else if(boardInfo[0] =='X' && boardInfo[4] == 'X' && boardInfo[8] == 'X')
        return false;
    else if (boardInfo[0] =='O' && boardInfo[4] == 'O' && boardInfo[8] == 'O')
        return false;
    //diagonal right - left
    else if(boardInfo[2] =='X' && boardInfo[4] == 'X' && boardInfo[6] == 'X')
        return false;
    else if (boardInfo[2] =='O' && boardInfo[4] == 'O' && boardInfo[6] == 'O')
        return false;
    else
        return true;
}//end checkWin()


int main() {
    bool win = true;
    displayGameInfo();
    initializeBoard();
    printBoard();

    while(win){
        scanUserInput();
        makeMoveInBoard();
        printBoard();
        win = checkWin();
    }
    printf("\nGame OVER!!!!\n\n");
    return 0;
}

