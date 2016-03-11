//--------------------------------------------------------------------------------
// TicTacTwo.cpp
//
// Class: Program #5 for CS 141, Fall 2015.  Wed 5am lab.
// System: Mac OS X
// Author: Dale Reed
//
// Variant of Tic Tac Two, where the board is 5x5 and the
// playing grid can be moved.  This is an implementation of the
// board game that is available at the "Marbles the Brain Store":
//    http://www.marblesthebrainstore.com/tic-tac-two.htm
//
// An example of playing the game is shown below, followed by an
// explanation of the design choices made in representing the board
// and the 3x3 grid.
//
//
// Playing the game:
// -----------------
//         Program #5: Tic Tac Two
//         Author: Dale Reed
//         Lab: Tues 8am
//         System:  Mac OS X, xCode IDE
//
//         -------------------
//         | .   .   .   .   . |   Pieces remaining for:
//         |                   |      Player 1: A B C D
//         | .   . | . | .   . |      Player 2: a b c d
//         |     ---------     |
//         | .   . | . | .   . |   Grid destination squares:
//         |     ---------     |       1 2 3
//         | .   . | . | .   . |       4 5 6
//         |                   |       7 8 9
//         | .   .   .   .   . |
//         -------------------
//         1. Player 1: Enter piece to move and destination number: A2
//
//         .
//         .
//         .
//
//         4. Player 2: Enter piece to move and destination number: b8
//         -------------------
//         | .   .   .   .   . |   Pieces remaining for:
//         |                   |      Player 1:   B C
//         | .   . | A | .   . |      Player 2: a     d
//         |     ---------     |
//         | .   . | D | c   . |   Grid destination squares:
//         |     ---------     |       1 2 3
//         | .   . | b | .   . |       4 5 6
//         |                   |       7 8 9
//         | .   .   .   .   . |
//         -------------------
//         5. Player 1: Enter piece to move and destination number, or 'm'
//         to move the grid and move direction (1-9 except 5): m 1
//
//         -------------------
//         | . | . | .   .   . |   Pieces remaining for:
//         | ---------         |      Player 1:   B C
//         | . | . | A   .   . |      Player 2: a     d
//         | ---------         |
//         | . | . | D   c   . |   Grid destination squares:
//         |                   |       1 2 3
//         | .   .   b   .   . |       4 5 6
//         |                   |       7 8 9
//         | .   .   .   .   . |
//         -------------------
//         6. Player 2: Enter piece to move and destination number, or 'm'
//         to move the grid and move direction (1-9 except 5):
//
//
// Design Choices:
// ---------------
//
//     The playing board pieces are stored in a 5x5 array of characters.  These pieces
//     are then copied into the playing board display when it comes time to display the board.
//     The 3x3 grid is represented by an integer 1..9, representing the position of the
//     middle of the 3x3 grid within the 5x5 board
//           1 2 3
//           4 5 6
//           7 8 9
//
//     To display the individual piece positions (originally all '.'), the
//     following array of index values is used (shown at right below):
//
//             0123456789012345678
//           0| .   .   .   .   . | 18    1,   5,   9,  13,  17,
//          19|                   | 37
//          38| .   . | . | .   . | 56   39,  43,  47,  51,  55,
//          57|     ---------     | 75
//          76| .   . | . | .   . | 94   77,  81,  85,  89,  93,
//          95|     ---------     |113
//         114| .   . | . | .   . |132  115, 119, 123, 127, 131,
//         133|                   |151
//         152| .   .   .   .   . |170  153, 157, 161, 165, 169
//             0123456789012345678
//
//    These various combinations are explained in more detail below where they are used.
//--------------------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

// Global constants
#define BOARD_SIZE 25               // total number of playing squares on the board
#define ROW_SIZE 5                  // board size on a side
#define DISPLAY_BOARD_SIZE 171      // size of large array used to display the board
#define DISPLAY_BOARD_ROWS 9        // how many rows there are in the board display array
#define DISPLAY_BOARD_ROW_SIZE 19   // how many characters on each row of board display array
#define PIECES_PER_PLAYER 4         // how many pieces per player
#define TRUE 1                      // accomodate boolean values for a C compiler
#define FALSE 0                     // accomodate boolean values for a C compiler


//-----------------------------------------------------------------------------------------
// Display ID info
//

struct Node {
    char board[ BOARD_SIZE];
    char playerOnePieces[ PIECES_PER_PLAYER + 1];  // Possible pieces to be placed for player one
    char playerTwoPieces[ PIECES_PER_PLAYER + 1]; // Possible pieces to be placed for player two
    int gridCenterIndex;             // Starting index position 1..9 of the middle of the grid
    int move;                  // Move number, incremented on each player move
    int gridCenterForPreviousMove;   // Stores grid center position for immediately preceeding move.
    int player;
    Node * nextPtr;
};

void displayIdInfo()
{
    printf("\n");
    printf("Program #6: Tic Tac Two With Undo   \n");
    printf("Author: Denis Doci    \n");
    printf("Lab: Tues 11am     \n");
    printf("System:  Mac OS X, Qt Creator IDE \n");
    printf(" \n");
}//end displayIDInfo()


//-----------------------------------------------------------------------------------------
// Display instructions
//
void displayInstructions()
{
    printf("Welcome to the game of Tic-Tac-Two. \n");
    printf("As in regular tic-tac-toe, the objective of the game is \n");
    printf("to get 3 of your pieces in a row, column or diagonal inside the grid. \n");
    printf("\n");
    printf("For the first two moves each, take turns placing a piece \n");
    printf("onto the board.  After this each player has the choice of: \n");
    printf("   1. Placing another of their available pieces on the board \n");
    printf("   2. Moving one of their existing pieces within the grid on the board \n");
    printf("   3. Moving the grid one space in any direction, as long as it is not \n");
    printf("      reversing the immediately preceeding move. \n");
    printf("If moving the grid results in a win for both players, the player who is \n");
    printf("making the move wins the game. \n");
    printf(" \n");
}//end displayInstructions()


//-----------------------------------------------------------------------------------------
// Set the grid pieces within the board, in preparation for displaying the board
//
//    The center grid is placed into the board array relative to a center square
//    index value.
//
//    The 3x3 grid center position indexes are shown in the board below, with the
//    corresponding board display index values shown to the right:
//
//            -------------------
//           | .   .   .   .   . |
//           |                   |
//           | .   1 | 2 | 3   . |    43,  47,  51,
//           |     ---------     |
//           | .   4 | 5 | 6   . |    81,  85,  89,
//           |     ---------     |
//           | .   7 | 8 | 9   . |   119, 123, 127
//           |                   |
//           | .   .   .   .   . |
//            -------------------
//
//    These index values are stored into the gridCenterIndexes array, where the index
//    of the array reflects its position within the
//    larger board:
//
//                0:-1
//                1:43
//                2:47
//                3:51
//                4:81
//                5:85
//                6:89
//                7:119
//                8:123
//                9:127
//
//     Offsets from the grid center values are used to set the grid on the
//     board. Board index values are shown below here for reference:
//
//             0123456789012345678
//           0| .   .   .   .   . | 18    1,   5,   9,  13,  17,
//          19|                   | 37
//          38| .   . | . | .   . | 56   39,  43,  47,  51,  55,
//          57|     ---------     | 75
//          76| .   . | . | .   . | 94   77,  81,  85,  89,  93,
//          95|     ---------     |113
//         114| .   . | . | .   . |132  115, 119, 123, 127, 131,
//         133|                   |151
//         152| .   .   .   .   . |170  153, 157, 161, 165, 169
//             0123456789012345678
//-----------------------------------------------------------------------------------------
void setGridPosition( char boardDisplay[ DISPLAY_BOARD_SIZE],  // 1-d array of board character pieces
                      int gridCenterIndex)                     // Index into above grid center positions
//    for the current grid position
{
    // Array of index positions of the center of the 3x3 grid.  These are
    // the index positions of the center of the grid once it is placed
    // in the large boardDisplay array. For convenience and consistency
    // the values used are in the index range 1..9, so a placeholder value
    // of -1 is in the 0th slot.
    int gridCenterIndexes[ 10] = {
        -1,
        43,   47,  51,
        81,   85,  89,
        119, 123, 127
    };

    // Next set the 3x3 grid values relative to the 5x5 board index of the 3x3 grid center.
    int gridCenter = gridCenterIndexes[ gridCenterIndex];

    // Set the new vertical lines
    boardDisplay[ gridCenter - 40] = '|'; boardDisplay[ gridCenter - 36] = '|';   // top row
    boardDisplay[ gridCenter -  2] = '|'; boardDisplay[ gridCenter +  2] = '|';   // middle row
    boardDisplay[ gridCenter + 36] = '|'; boardDisplay[ gridCenter + 40] = '|';   // bottom row
    // Set the new horizontal pieces.
    // First set the upper horizontal line of the grid
    for( int i = 0; i<9; i++) {
        boardDisplay[ gridCenter - 23 + i] = '-';
    }
    // Now set the lower horizontal line of the grid
    for( int i = 0; i<9; i++) {
        boardDisplay[ gridCenter + 15 + i] = '-';
    }
}//end setGridPosition()


//-----------------------------------------------------------------------------------------
// Display the board
//
//  After a few moves, the board display could look like the following:
//
//            -------------------
//           | .   .   .   .   . |   Pieces remaining for:
//           |                   |      Player 1:     C D
//           | .   A | c | .   . |      Player 2: a b   d
//           |     ---------     |
//           | .   . | B | .   . |   Grid destination squares:
//           |     ---------     |       1 2 3
//           | .   . | . | .   . |       4 5 6
//           |                   |       7 8 9
//           | .   .   .   .   . |
//            -------------------
//
//     This board display is made up of the following components:
//            1. 5x5 board pieces
//            2. 3x3 grid
//            3. Explanatory text to the right of the board
//            4. Pieces remaining to play for the two players, also shown to the right of the board.
//     These components must all be merged to createthe board display.
//
//     The board itself is a large array of spaces, where the pieces and the grid lines are
//     stored into it, overwriting the spaces that would otherwise be there.  There is a
//     second array used to display the content to the right of the board.
//
//     The playing board display is represented using a 1-D array with index values
//     as shown below (excluding the border pieces).  In this sample we assume several
//     pieces have already been played:
//
//             0123456789012345678
//           0| .   .   .   .   . | 18
//          19|                   | 37
//          38| .   A | c | .   . | 56
//          57|     ---------     | 75
//          76| .   . | B | .   . | 94
//          95|     ---------     |113
//         114| .   . | . | .   . |132
//         133|                   |151
//         152| .   .   .   .   . |170
//             0123456789012345678
//
//     To access the individual piece positions (originally all '.'), the
//     following array of index values is used (shown at right below):
//
//             0123456789012345678
//           0| .   .   .   .   . | 18    1,   5,   9,  13,  17,
//          19|                   | 37
//          38| .   A | c | .   . | 56   39,  43,  47,  51,  55,
//          57|     ---------     | 75
//          76| .   . | B | .   . | 94   77,  81,  85,  89,  93,
//          95|     ---------     |113
//         114| .   . | . | .   . |132  115, 119, 123, 127, 131,
//         133|                   |151
//         152| .   .   .   .   . |170  153, 157, 161, 165, 169
//             0123456789012345678
//
//      Consider how we would take the following 25 board pieces from
//      the 5x5 board and map them into the larger display board shown above.
//      The 0..24 index values are also shown:
//
//                  +1  +2  +3  +4
//           0  .   .   .   .   .  4
//           5  .   A   c   .   .  9
//           10 .   .   B   .   . 14
//           15 .   .   .   .   . 19
//           20 .   .   .   .   . 24
//
//      These 25 playing pieces (all initially '.') are stored in a
//      single-dimension array indexed 0..24.  Mapping from the 0..24 index
//      values into the 0..170 board display index values shown above can
//      be accomplished using the following formula:
//
//         row = index / 5;  // integer division, truncating the remainder
//         col = index % 5;  // offset into each row
//         displayIndex = (row * 38) + 1 + (col * 4);
//
//     To the right of each row in the above board, the following array of
//     words is displayed:
//
//         Pieces remaining for:
//            Player 1: A B C D
//            Player 2: a b c d
//
//         Grid destination squares:
//             1 2 3
//             4 5 6
//             7 8 9
//
//     After each row of the board is displayed, the corresponding row of the
//     explanatory text array is also displayed.  This results in:
//
//          -------------------
//         | .   .   .   .   . |   Pieces remaining for:
//         |                   |      Player 1: A B C D
//         | .   . | . | .   . |      Player 2: a b c d
//         |     ---------     |
//         | .   . | . | .   . |   Grid destination squares:
//         |     ---------     |       1 2 3
//         | .   . | . | .   . |       4 5 6
//         |                   |       7 8 9
//         | .   .   .   .   . |
//          -------------------
//
//     The Player 1 and Player 2 pieces are respectively arrays of
//     the 4 characters "ABCD" and "abcd".
//-----------------------------------------------------------------------------------------
void displayBoard( char board[ BOARD_SIZE],     // current board pieces
                   char playerOnePieces[ ],     // starts as "ABCD"
                   char playerTwoPieces[ ],     // starts as "abcd"
                   int gridCenterIndex)         // grid center (1..9)
{
    // Create the large array used for displaying the board
    char boardDisplay[ DISPLAY_BOARD_SIZE];
    // Board information to be displayed at the right of the playing surface
    char boardInfo[ 9][ 30] = {
        {"   Pieces remaining for:     "},
        {"      Player 1:              "},
        {"      Player 2:              "},
        {"                             "},
        {"  Grid destination squares:  "},
        {"      1 2 3                  "},
        {"      4 5 6                  "},
        {"      7 8 9                  "},
        {"                             "},
    };


    // Initialize the board display to all blanks
    for( int i=0; i<DISPLAY_BOARD_SIZE; i++) {
        boardDisplay[ i] = ' ';
    }
    // Place the player playing pieces into place in the display array
    //
    //   The 25 playing pieces (all initially '.') are stored in a
    //   single-dimension array indexed 0..24.  Mapping from these index
    //   values into the board display index values shown above can be accomplished
    //   using the formula:
    //
    //      row = index / 5;  // integer division, truncating the remainder
    //      col = index % 5;  // offset into each row
    //      displayIndex = (row * 38) + 1 + (col * 4);

    for( int i=0; i<BOARD_SIZE; i++) {
        int row = i / 5;  // integer division, truncating the remainder
        int col = i % 5;  // offset into each row
        int displayIndex = (row * 38) + 1 + (col * 4);
        // Now place the character into the display array
        boardDisplay[ displayIndex] = board[ i];
    }

    // Set the grid values in place
    setGridPosition( boardDisplay, gridCenterIndex);

    // print the board top border
    printf("\n ------------------- \n");
    printf("|");   // print the starting edge of the first row

    // display all the characters inside the board
    for( int i=0; i<DISPLAY_BOARD_SIZE; i++) {
        printf("%c", boardDisplay[ i]);
        // if we're at the end of the row, display the ending character
        if( (i+1) % DISPLAY_BOARD_ROW_SIZE == 0) {
            printf("|");
            // Display the information to the right of the board
            int boardInfoRow = i/DISPLAY_BOARD_ROW_SIZE;
            // Check the special case for the Player pieces rows display
            if( boardInfoRow == 1) {
                printf("      Player %d: %c %c %c %c \n", boardInfoRow, playerOnePieces[ 0],
                        playerOnePieces[ 1], playerOnePieces[ 2], playerOnePieces[ 3]);
            }
            else if( boardInfoRow == 2) {
                printf("      Player %d: %c %c %c %c \n", boardInfoRow, playerTwoPieces[ 0],
                        playerTwoPieces[ 1], playerTwoPieces[ 2], playerTwoPieces[ 3]);
            }
            else {
                printf("%s\n", boardInfo[ i/DISPLAY_BOARD_ROW_SIZE]);
            }
            // display starting edge of next row, if not on last row
            if( i<(DISPLAY_BOARD_SIZE-1)) {
                printf("|");
            }
        }
    }

    // print the board bottom border
    printf(" ------------------- \n");
}//end displayBoard()


//-----------------------------------------------------------------------------------------
// Check to see if the piece to move has been played yet.  It has not been played
// if it is found in one of the two arrays of players-to-move pieces.
//
int pieceToMoveHasBeenPlayed(
        char pieceToMove,           // the piece to move
        char playerOnePieces[],     // pieces remaining to be moved for player one
        char playerTwoPieces[])     // pieces remaining to be moved for player two
{
    for( int i=0; i<PIECES_PER_PLAYER; i++) {
        if( pieceToMove == playerOnePieces[ i] || pieceToMove == playerTwoPieces[ i]) {
            // found it, so it has not been played
            return FALSE;
        }
    }
    return TRUE;
}//end pieceToMoveHasBeenPlayed()


//-----------------------------------------------------------------------------------------
// Given the currentGridCenterIndex 1..9 from the center of the 5x5 board, and the relative
//    3x3 board position 1..9, translate it into the actual 5x5 board index 0..24.
//
// The grid position within the 5x5 board is represented as an integer 1..9, since there are
// 9 different locations where the 3x3 grid can be within the 5x5 board.  1 represents the
// upper left, 2 represents the upper middle, 3 the upper right, and so on.  If you draw
// out these 9 positions, you see that the middle of the grid ends up in one of the 9 middle
// squares from the 5x5 board.
//
// The 5x5 board index values are:
//     0  1  2  3  4
//     5  6  7  8  9
//    10 11 12 13 14
//    15 16 17 18 19
//    20 21 22 23 24
// and the 3x3 grid center index values are:
//        1  2  3  <-- row 1
//        4  5  6  <-- row 2
//        7  8  9  <-- row 3
// We need to map the 3x3 grid center index values (1..9) to the actual middle 5x5 board values:
//        6  7  8
//       11 12 13
//       16 17 18
// Given the grid center value (1..9), the 3x3 board row is: value / 3 + 1
// Then row * 5 + 1 gives the index of the starting value in the 5x5 board (6, 11 or 16)
// Given the 3x3 board grid center value (1..9), the column (1,2 or 3) is calculated as: value % 3
// Thus given the 3x3 board grid center value (1..9) we can map to the actual board index using:
//    int row = value / 3 + 1;  // gives value 1, 2 or 3
//    int col = value % 3;      // gives value 1, 2 or 3
//    actualBoardIndex = row * 5 + col
// This gives the actual 5x5 board index of the center of the grid.
//
// The next step is to take into account the position 1..9 of a piece within the 3x3 grid.
// The user move is selected relative to the grid position:
//      1  2  3
//      4  5  6
//      7  8  9
// The center (position 5) is the center of the grid. (We already have the 5x5 board index of this
// center piece as detailed above.)  Selecting 2 is a move up.  Selecting
// 9 is a move down and to the right, and so on.  We need to correspond the 1..9 relative positions
// on the 3x3 grid to the destination offsets within the 5x5 board:
//     -6 -5 -4
//     -1  0  1
//      4  5  6
// In other words, given a position on the 5x5 board, the piece above has an index -5 from this position,
// the piece below and to the left has an index +4 from this position, and so on for all adjacent pieces,
// with the offset values shown immediately above.  These offsets are stored by creating a
// movesOffsets array to store the corresponding offset values for each 3x3 index value:
//      0:0
//      1:-6
//      2:-5
//      3:-4
//      4:-1
//      5:0
//      6:1
//      7:4
//      8:5
//      9:6
// This way the destination number is the index into the movesOffset array, indicating what
// should be added to the grid center index value (on the 5x5 board) to get the 5x5 board index of the
// move destination.
//-----------------------------------------------------------------------------------------
int convertGridValueToBoardIndex(
        int centerIndexValue,       // Grid center index value 1..9, representing where the center of
        //    the 3x3 grid is on the 5x5 board
        int destinationNumber)      // Destination within the 3x3 grid
{
    // Create offsets array, to be used once we've already mapped grid center to actual board index
    int movesOffsets[] = {0,-6,-5,-4,-1,0,1,4,5,6};
    // get the row and col of the grid center
    int centerRow = centerIndexValue / 3 + 1;  // gives value 1, 2 or 3
    int centerCol = centerIndexValue % 3;      // gives value 1, 2 or 3
    int actualBoardCenterIndex = centerRow * 5 + centerCol;

    // Find 5x5 board position using offset from index of grid center
    int actualBoardIndex = actualBoardCenterIndex + movesOffsets[ destinationNumber];

    return actualBoardIndex;
}//end convertGridValueToBoardIndex()


//-----------------------------------------------------------------------------------------
// Validate the new grid center index position by enumerating all possible combinations
// Old values must be among:
//             1   2   3
//             4   5   6
//             7   8   9
// and new values must be an adjacent value still among 1..9. For instance, assume the
// center of the 3x3 grid is in the "7" position, namely in the bottom-left 5x5 board position:
//         -------------------
//        | .   .   .   .   . |
//        |                   |
//        | .   1   2   3   . |
//        |                   |
//        | . | 4 | 5   6   . |
//        | ---------         |
//        | . | 7 | 8   9   . |
//        | ---------         |
//        | . | . | .   .   . |
//         -------------------
// With the grid in that position, from the current center of the board the only valid grid
// repositioning movements are up, diagonal-up-and-right, and right.  These directions are
// given relative to the current center of the board, so assuming the center of the board
// is 5, these directions are 2 (above), 3 (diagonal-up-and-right) and 6 (right).
//-----------------------------------------------------------------------------------------
int newGridPositionIsNotValid(
        int currentPosition,   // Index of old grid center
        int newPosition)       // Proposed index of new grid center
{
    int newPositionIsNotValid = true;

    // Set validity to true if any of the valid combinations shown below are found
    if( currentPosition == 1 &&
            (newPosition == 6 || newPosition == 9 || newPosition == 8)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 2 &&
            (newPosition == 6 || newPosition == 9 || newPosition == 8 || newPosition == 7 || newPosition == 4)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 3 &&
            (newPosition == 8 || newPosition == 7 || newPosition == 4)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 4 &&
            (newPosition == 2 || newPosition == 3 || newPosition == 6 || newPosition == 9 || newPosition == 8)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 5 &&
            (newPosition >= 1 && newPosition <= 9 && newPosition != 5)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 6 &&
            (newPosition == 8 || newPosition == 7 || newPosition == 4 || newPosition == 1 || newPosition == 2)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 7 &&
            (newPosition == 2 || newPosition == 3 || newPosition == 6)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 8 &&
            (newPosition == 4 || newPosition == 1 || newPosition == 2 || newPosition == 3 || newPosition == 6)
            ) {
        newPositionIsNotValid = false;
    }
    if( currentPosition == 9 &&
            (newPosition == 4 || newPosition == 1 || newPosition == 2)
            ) {
        newPositionIsNotValid = false;
    }
    return newPositionIsNotValid;
}//end newGridPositionIsNotValid()


//-----------------------------------------------------------------------------------------
// Verify that the piece to move is in the 3x3 grid within the larger 5x5 board
//
int pieceToMoveIsInGrid(
        char pieceToMove,       // 'A'..'D' or 'a'..'d'
        char board[],           // 5x5 array of '.' or letters 'A'..'D' or 'a'..'d'
        int gridCenterIndex)    // Index value 1..9 of the grid center, placing it
//    within the middle 3x3 section of the board.
{
    int actualBoardIndex;    // Will store 5x5 board index corresponding to grid center and 3x3 board offset

    // Given the board center and the offset, find the actual board index of each board position in turn.
    // The convertGridValueToBoardIndex(...) function gives the actual 5x5 board index, given the center
    // position of the grid and the 3x3 board relative offset.
    for( int i=1; i<=9; i++) {
        actualBoardIndex = convertGridValueToBoardIndex( gridCenterIndex, i);
        if( pieceToMove == board[ actualBoardIndex]) {
            return TRUE;
        }
    }

    return FALSE;
}//end pieceToMoveIsInGrid()


//-----------------------------------------------------------------------------------------
// Prompt for user move.  This could be either a
//   1. Piece placement move
//        a. Placing a piece on the board
//        b. Moving a piece within the grid (after the 4th move)
//   2. Grid movement (after the 4th move)
//
// Error checking is done to ensure only valid moves are made.
//-----------------------------------------------------------------------------------------
void restoreValues( Node *pHead,
                   char board[ BOARD_SIZE],
                   int &moveNumber,
                   char playerOnePieces[ PIECES_PER_PLAYER + 1], // Possible pieces to be placed for player one
                   char playerTwoPieces[ PIECES_PER_PLAYER + 1], // Possible pieces to be placed for player two
                   int &gridCenterIndex,             // Starting index position 1..9 of the middle of the grid
                   int &gridCenterForPreviousMove,  // Stores grid center position for immediately preceeding move.
                   int player)
{
    // restore the board values, element by element
    for( int i=0; i<BOARD_SIZE; i++) {
        board[i] = pHead->board[ i];
    }

    // also restore the move number
    moveNumber = pHead->move;
     for( int i=0; i<PIECES_PER_PLAYER + 1; i++) {
     playerOnePieces[ i] = pHead -> playerOnePieces[i];
     }
     for( int i=0; i<PIECES_PER_PLAYER + 1; i++) {
     playerTwoPieces[ i] = pHead -> playerTwoPieces[i];
     }
     gridCenterIndex = pHead -> gridCenterForPreviousMove,             // Starting index position 1..9 of the middle of the grid
     gridCenterForPreviousMove = pHead -> gridCenterForPreviousMove,  // Stores grid center position for immediately preceeding move.
     player = pHead->player;
}//end restoreValues()

void promptForAndGetPieceToMoveAndDestination(
        int moveNumber,           // Used to determine whose move it is (1 or 2)
        int playerToMove,         // Player to move: 1 or 2
        char &pieceToMove,        // Letter 'a'..'d' or 'A'..'D' depending on player
        int &destinationNumber,   // Integer 1..9
        char playerOnePieces[],   // Array of 4 characters, each 'A'..'D' or ' '
        char playerTwoPieces[],   // Array of 4 characters, each 'a'..'d' or ' '
        char board[],             // Array of playing pieces on the board
        int gridCenterIndex,      // Relative index 1..9 of center of grid
        int gridCenterForPreviousMove,
        Node * &pTail,
        Node * &pHead,
        int player)  // Grid center for last move
{
    Node * pTemp;
    // Prompt loop for move information, including error checking
    while( true) {
        printf("%d. Player %d: Enter piece to move and destination number: ",
               moveNumber, playerToMove);
        scanf(" %c", &pieceToMove);
        if( toupper( pieceToMove) == 'X') {
            return;   // 'X' to exit was chosen. return to calling part of program.
        }
        scanf("%d", &destinationNumber);
        // Ensure destination number is in range 1..9
        if( destinationNumber < 1 || destinationNumber > 9) {
            printf("*** Invalid destination piece.  Please retry. \n");
            continue;
        }

        // Verify piece to move is within range 'A'..'D'
        if( toupper( pieceToMove) != 'M' && toupper( pieceToMove) != 'U' &&
                (toupper( pieceToMove) < 'A' || toupper( pieceToMove) > 'D')
                ) {
            printf("*** Alphabetic value is out of range. Please retry. \n");
            continue;
        }

        // Check for possible errors where each player has not yet had 2 moves (so moveNumber still <= 4)
        if( moveNumber <= 4) {
            // Error check for attempt to move the grid before it is allowed
            if( toupper( pieceToMove) == 'M') {
                printf("*** Both players must place 2 pieces before grid can be moved.  Please retry. \n");
                continue;
            }
            else if( toupper( pieceToMove) == 'U') {

                if( moveNumber <= 1){
                    printf("*** Can't undo one move try again\n");
                    continue;
                }
                else{
                    if (pHead-> nextPtr != NULL) {
                          pTemp = pHead;          // Remember old list head so we can delete it
                          pHead = pHead->nextPtr;   // advance list head pointer
                          delete pTemp;           // Release the memory from the node no longer needed
                          restoreValues( pHead, board, moveNumber, playerOnePieces,
                                         playerTwoPieces, gridCenterIndex, gridCenterForPreviousMove, player);
                          moveNumber--;
                      }
                    break;
                }
           }
            // Error check for attempt to move a grid piece before it is allowed
           else{
                if(pieceToMoveHasBeenPlayed( pieceToMove, playerOnePieces, playerTwoPieces)) {
                printf("*** Both players must place 2 pieces before grid pieces can be moved.  Please retry. \n");
                continue;
                }
            }

        }
        else if( toupper( pieceToMove) == 'M') {
            // Grid moves are a valid option at this point in the game.  Ensure grid doesn't go out of bounds by
            //     verifying the destination is valid for a grid at this currentCenterIndex position.
            if( newGridPositionIsNotValid( gridCenterIndex, destinationNumber)) {
                printf("*** Grid may not be moved off of board or in place.  Please retry.\n");
                continue;
            }
            // Ensure player is not trying to undo the immediately preceeding grid move
            int offset = destinationNumber - 5;
            if( (gridCenterIndex + offset) == gridCenterForPreviousMove) {
                printf("*** Grid cannot be immediately moved back to original position.  Please retry.\n");
                continue;
            }
            // break out of moves checking
            break;
        }

        else if( toupper( pieceToMove) == 'U') {

                if( moveNumber <= 1){
                    printf("*** Can't undo one move try again\n");
                    continue;
                }
                else{
                    if (pHead->nextPtr != NULL) {
                          pTemp = pHead;          // Remember old list head so we can delete it
                          pHead = pHead->nextPtr;   // advance list head pointer
                          delete pTemp;           // Release the memory from the node no longer needed
                         restoreValues( pHead, board, moveNumber, playerOnePieces,
                                        playerTwoPieces, gridCenterIndex, gridCenterForPreviousMove, player);
                    }
                    continue;
                }

        }



        // It was not a "Move grid" type of move, but is a piece placement or piece relocation move.

        // Verify that players are only attempting to move their own pieces
        if( moveNumber % 2 == 1) {
            // move number is odd, which means it is player 1, which should use upper-case letters
            if( islower( pieceToMove) && (tolower( pieceToMove)!='m')  && (tolower( pieceToMove)!='u')) {
                printf("*** Player 1 can only select from upper-case pieces.  Please retry. \n");
                continue;
            }
        }
        else {
            // Move number is even, which means it is player 2, which should use lower-case letters
            if( isupper( pieceToMove) && (toupper( pieceToMove)!='M') && (toupper( pieceToMove)!='U')) {
                printf("*** Player 2 can only select from lower-case pieces.  Please retry. \n");
                continue;
            }
        }

        // Verify that the destination is not already occupied.
        int boardIndex = convertGridValueToBoardIndex( gridCenterIndex, destinationNumber);
        if( board[ boardIndex] != '.') {
            printf("*** Destination square %d is already occupied.  Please retry.\n", destinationNumber);
            continue;
        }

        // Verify that for a relocation move, the piece has already been played and is in the grid
        if( pieceToMoveHasBeenPlayed( pieceToMove, playerOnePieces, playerTwoPieces) &&
                ! pieceToMoveIsInGrid( pieceToMove, board, gridCenterIndex)
                ) {
            printf("*** Piece %c is not within the grid.  Please retry. \n", pieceToMove);
            continue;
        }

        break;   // break out of move verification loop

    }//end while( true)
}//end promptAndGetPieceToMoveAndDestination()


//-----------------------------------------------------------------------------------------
// Remove the piece that has just been played from the pieces array where it is found
//
void removePieceFromPiecesArray(
        char pieceToMove,
        char playerOnePieces[],
        char playerTwoPieces[])
{
    // Check each position in both pieces array, blanking out the pieceToMove when found.
    for( int i=0; i<PIECES_PER_PLAYER; i++) {
        if( pieceToMove == playerOnePieces[ i]) {
            playerOnePieces[ i] = ' ';
        }
        if( pieceToMove == playerTwoPieces[ i]) {
            playerTwoPieces[ i] = ' ';
        }
    }//end for...
}//end removePieceFromPiecesArray()


//-----------------------------------------------------------------------------------------
// Now that error checking for the move has already been done, so just move the grid or
// place the piece on board
// There are two types of moves: 1. Placing a piece, or 2. Moving the grid
//
//  1. Placing a piece
//      Here there is a piece to be placed and a destination.  The piece can come
//      either from the set of pieces not yet placed on the board, or from a location
//      within the grid, once the first four moves have already been made.
//      The source is blanked out, the 5x5 board index position is found, and then
//      the piece is placed there.
//
//  2. Moving the grid:
//       The grid doesn't get moved per se, but the grid center position index (1..9)
//       gets changed. This will be reflected by a different grid position once it is displayed.
//
//       The user selects moving the grid by choosing a direction relative to the current
//       position (x) within the set of numbers:
//           1 2 3
//           4 x 6
//           7 8 9
//       To move the grid straight up, 2 would be chosen.  To move it down and to the
//       right, 9 would be chosen, and so on.  The difference from 5 is used to determine
//       the offset to calculate the new gridCenterIndex value.
//       E.g. selecting 2 means the difference from 5 is: 2-5 = -3.  This value (-3) is
//       added to the current gridCenterIndex to give the new value.  So if the grid started out
//       at the bottom center of the board, its gridCenterIndex value would be 7.
//       7 plus the value -3 gives 4.
//-----------------------------------------------------------------------------------------
void makeMove(
        char board[],                  // the 5x5 board of characters
        char playerOnePieces[],        // Pieces 'A'..'D' remaining to be played for player 1
        char playerTwoPieces[],        // Pieces 'a'..'d' remaining to be played for player 2
        char pieceToMove,              // Piece to be placed on board and removed from player piece array
        int destinationNumber,         // Destination 1..9 for piece to be placed
        int &gridCenterIndex,          // 3x3 grid center index representing grid position
        int &gridCenterForPreviousMove) // 3x3 grid center index from previous move
{
    printf("\n");
    gridCenterForPreviousMove = gridCenterIndex;

    // Move the grid if that was selected
    if( toupper( pieceToMove) == 'M') {
        int offset = destinationNumber - 5;    // Find offset from current grid position
        // Set new grid center index from current 1..9 position to new position 1..9 by adding the offset
        gridCenterIndex = gridCenterIndex + offset;
    }
    else if( toupper( pieceToMove) == 'U'){
        return;
    }
    else {
        // Place a piece on the board

        // Clear that piece from the pieces array if it is there
        removePieceFromPiecesArray( pieceToMove, playerOnePieces, playerTwoPieces);

        // Clear that piece from the board if it is there
        for( int i=0; i<BOARD_SIZE; i++) {
            if( pieceToMove == board[ i]) {
                board[ i] = '.';
                break;
            }
        }

        // Given the center of the grid and the destination position in the 3x3 grid,
        //    find the location on the 5x5 board where the piece is to be placed.
        int boardIndex = convertGridValueToBoardIndex( gridCenterIndex, destinationNumber);
        // Place the piece at that position on the 5x5 board
        board[ boardIndex] = pieceToMove;

        // Clear the gridCenterForPreviousMove value, since this move is not a grid move.
        // This variable is used to prevent a user from reversing the grid movement on
        // the immediately previous move.
        gridCenterForPreviousMove = 0;
    }

}// end makeMove()


//-----------------------------------------------------------------------------------------
// See if there is a winner.
//    Check all possible three-in-a row combinations on the 3x3 board, for the player to move,
// checking all three rows, columns and both diagonals:
//    1 2 3
//    4 5 6
//    7 8 9
// The function   convertGridValueToBoardIndex(..)   takes the board center position and
// a 3x3 board position and converts it to the 5x5 board index, and then we get the 3 pieces
// at those 3 board index positions and compare those characters.
//-----------------------------------------------------------------------------------------


int thereIsAWinner(
        char board[],           // The 5x5 array of board pieces which are letters or '.'
        int gridCenterIndex,    // The index 1..9 of the center of the 3x3 grid on the 5x5 board
        int playerToMove)       // 1 for player 1 (uppercase); 2 for player 2 (lowercase)
{
    const int NumberWinningCombinations = 8;
    int playerHasWon = FALSE;     // A winning combinations was found for the player

    // Possible three-in-a-row index combinations on the 3x3 grid
    int winningCombinations[ NumberWinningCombinations][ 3] = {
        {1,2,3}, {4,5,6}, {7,8,9},    // rows
        {1,4,7}, {2,5,8}, {3,6,9},    // columns
        {1,5,9}, {7,5,3}              // diagonals
    };

    // Try each possible winning combination.  For instance the first time this will be
    // the elements in the first row, namely 1,2,3  from the entry {1,2,3} above
    for( int i=0; i<NumberWinningCombinations; i++) {
        // Get the 3x3 grid index values for a possible winning configuration
        int piece0Index = winningCombinations[ i][ 0];
        int piece1Index = winningCombinations[ i][ 1];
        int piece2Index = winningCombinations[ i][ 2];

        // Get the 5x5 board pieces corresponding to these three 3x3 grid positions
        char piece0 = board[ convertGridValueToBoardIndex( gridCenterIndex, piece0Index) ];
        char piece1 = board[ convertGridValueToBoardIndex( gridCenterIndex, piece1Index) ];
        char piece2 = board[ convertGridValueToBoardIndex( gridCenterIndex, piece2Index) ];

        // If player to move is 1 (upper-case), see if all 3 are upper-case, for a win for player 1
        if( playerToMove == 1 && isupper(piece0) && isupper(piece1) && isupper(piece2)) {
            playerHasWon = TRUE;
        }

        // If player to move is 2 (lower-case), see if all 3 are lower-case, for a win for player 2
        if( playerToMove == 2 && islower(piece0) && islower(piece1) && islower(piece2)) {
            playerHasWon = TRUE;
        }
    }//end for( int i=0...)

    // Give a message if a player has won.  Note that if *both* players win at the same time
    // because of a grid move, the player to move is the winner.
    if( playerHasWon) {
        printf("Congratulations!  Three-in-a-row for Player %d for the win! \n\n", playerToMove);
    }

    return playerHasWon;
}//end thereIsAWinner()

void appendToList(Node * &pHead,  Node * &pTail,  char board[],  int playerToMove,
                  int moveNumber, char playerOnePieces[], char playerTwoPieces[],
                  int gridCenterIndex, int gridCenterForPreviousMove)
{
    Node *tempPtr;

    // if the linked list is empty
    if(pHead == NULL)
    {
        tempPtr = new Node;
        //copy a string of an array
        strncpy(tempPtr->board,board, BOARD_SIZE);
        tempPtr->move = moveNumber;
        tempPtr->player = playerToMove;
        tempPtr->gridCenterIndex= gridCenterIndex;
        tempPtr->gridCenterForPreviousMove= gridCenterForPreviousMove;
        strncpy(tempPtr->playerOnePieces, playerOnePieces, ( PIECES_PER_PLAYER + 1));
        strncpy(tempPtr->playerTwoPieces, playerTwoPieces, ( PIECES_PER_PLAYER + 1));
        tempPtr->nextPtr = NULL;
        pHead = tempPtr;
        pTail = tempPtr;
    }
    else
    {
        tempPtr = new Node;
        strncpy(tempPtr->board,board,BOARD_SIZE);
        tempPtr->move = moveNumber;
        tempPtr->player = playerToMove;
        tempPtr->gridCenterIndex= gridCenterIndex;
        tempPtr->gridCenterForPreviousMove= gridCenterForPreviousMove;
        strncpy(tempPtr->playerOnePieces, playerOnePieces, ( PIECES_PER_PLAYER + 1));
        strncpy(tempPtr->playerTwoPieces, playerTwoPieces, ( PIECES_PER_PLAYER + 1));
        tempPtr->nextPtr = pHead;
        //pHead = tempPtr;
        tempPtr->nextPtr = pHead;
        pHead = tempPtr;
    }
}

//-----------------------------------------------------------------------------------------
// Starting point of the program
int main()
{
    // array of characters to be displayed on the board
    char board[ BOARD_SIZE] =
    {'.', '.', '.', '.', '.',
     '.', '.', '.', '.', '.',
     '.', '.', '.', '.', '.',
     '.', '.', '.', '.', '.',
     '.', '.', '.', '.', '.'
    };
    // The "+ 1" is needed in the player pieces arrays below for the NULL at the end of the string
    char playerOnePieces[ PIECES_PER_PLAYER + 1] = {"ABCD"};  // Possible pieces to be placed for player one
    char playerTwoPieces[ PIECES_PER_PLAYER + 1] = {"abcd"};  // Possible pieces to be placed for player two
    int gridCenterIndex = 5;             // Starting index position 1..9 of the middle of the grid
    int moveNumber = 1;                  // Move number, incremented on each player move
    char pieceToMove;                    // Piece to move 'a'..'d' or 'A'..'D'
    int destinationNumber;               // Destination for piece to move
    int gridCenterForPreviousMove = 5;   // Stores grid center position for immediately preceeding move.
    int playerToMove = 1;
    // Variables for linked list
    Node *pHead = NULL;
    Node *pTail = NULL;

    // Display ID info
    displayIdInfo();

    // Display instructions and display the initial board
    displayInstructions();
    appendToList(  pHead,  pTail,  board,  playerToMove,
                   moveNumber, playerOnePieces, playerTwoPieces,
                   gridCenterIndex, gridCenterForPreviousMove);
    displayBoard(pHead->board, pHead->playerOnePieces, pHead->playerTwoPieces, pHead->gridCenterIndex);

    // Game play infinite loop.  We break out of loop if there is a winner.
    while( TRUE) {
        // Prompt for and get user input, allowing retrying if there is an error in it
        promptForAndGetPieceToMoveAndDestination( moveNumber, playerToMove, pieceToMove, destinationNumber,
                                                  playerOnePieces, playerTwoPieces, board,
                                                  gridCenterIndex, gridCenterForPreviousMove, pTail, pHead, playerToMove);
        // Exit program if 'x' was given as user input
        if( toupper( pieceToMove) == 'X') {
            printf("Exiting Program... \n\n");
            break;    // break out of enclosing game play loop
        }

        // Move the grid or move the pieceToMove to the destination
        makeMove( board, playerOnePieces, playerTwoPieces, pieceToMove,
                  destinationNumber, gridCenterIndex, gridCenterForPreviousMove);
        // Display the board
        appendToList(  pHead,  pTail,  board,  playerToMove,
                       moveNumber, playerOnePieces, playerTwoPieces,
                       gridCenterIndex, gridCenterForPreviousMove);

        displayBoard(pHead->board, pHead->playerOnePieces, pHead->playerTwoPieces, pHead->gridCenterIndex);

        // See if there is a winner
        if( thereIsAWinner( board, gridCenterIndex, playerToMove)) {
            break;      // break out of enclosing game play loop
        }

        moveNumber++;       // Increment the move number

        // Swap to the other player.  If it was 1, switch to 2.  If 2, it switches back to 1
        playerToMove = playerToMove % 2 + 1;
    }//end while( true)

    printf("Thanks for playing. \n");
    return 0;
}//end main()

