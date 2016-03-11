/*
 *
 * Denis Doci
 * Brandon Goodman-Gibis
 * Class: CS 141
 * Fall 2015
 * Lab: Tues. 11AM
 * TA - Vignesh Ganapathiraman
 *
 * This is a program is a board game originally created
 * by Alex Randolph. The object of the game is to get the
 * designated numbered robot to the designated alphabetical
 * terminal.
 *
 * This was orginally designed with a random number generator
 * but, as per the directions on the course site, this was edited
 * and hardcoded instead.
 *
 *
 *
*/

#include <iostream>
#include <cstdlib>      // for the system command
#include <cctype>       // For the letter checking functions, e.g. toupper( )
#include <fstream>      // For file input and output
using namespace std;

// Global data structure for board
const int BOARD_EDGE = 16;
const int BOARD_SIZE = BOARD_EDGE * BOARD_EDGE;

char theBoard[ BOARD_SIZE][ 5];        // global array of board display characters
// declare constants to later use instead of numbers to select values from theBoard
const int PIECE = 0;    // to reference the character, such as in: theBoard[ i][ PIECE]
const int LEFT  = 1;    // to reference the left wall character, such as in: theBoard[ i][ LEFT]
const int ABOVE = 2;    // to reference the above wall character, such as in: theBoard[ i][ ABOVE]
const int RIGHT = 3;    // to reference the right wall character, such as in: theBoard[ i][ RIGHT]
const int BELOW = 4;    // to reference the below wall character, such as in: theBoard[ i][ BELOW]

// Declare the 4 robots, which will store the board position of where they are found
// Robots are displayed using values 1-4.  We declare 5 robots, though we will never use
// the 0th robot in the array.
const int NUMBER_OF_ROBOTS = 4;
int theRobots[ NUMBER_OF_ROBOTS + 1] = {0,0,0,0,0};

// YOU MAY NOT HAVE ANY OTHER GLOBAL VARIABLES, though you can have other global constants.


//function to display our identifying information
void displayIdInformation()
{
    // Display identifying information
    cout << "\n\nAuthor: Denis Doci and Brandon Goodman-Gibis\n"
         << "Program 3: Robots in C \n"
         << "TA: Vignesh Ganapathiraman, T 11:00 AM \n"
         << "UIC CS 141, October 2015\n"
         << endl;
}//end displayIdInformation()


//function to display instructions of game
void displayInstructions()
{
    // Display Instructions
    cout << "Welcome to Ricochet Robots. \n"
         << "This was originally a board game created by Alex Randolph. \n"
         << "\n"
         << "The object of the game is to get the designated numbered robot (2) \n"
         << "to the indicated letter position (M). \n"
         << "The numbered squares are all robots.  They unfortunately have \n"
         << "no brakes, and so will continue in whatever direction they are \n"
         << "moving until they encountar an obstacle. \n"
         << "For each move enter the robot number and the desired direction. \n"
         << "For instance entering \n"
         << "   1 U \n"
         << "would move the #1 robot as far up as it can go. \n"
         << "The first letter of input is the robot number (1 - 4), \n"
         << "and the second letter is the direction (L=left, U=up, R=right, D=down) \n"
         << "Enter x to exit.  Have fun!\n"
         << "\n";
}//end displayInstructions()


//function to  create the default settings of the board
void createBoard()
{
    for( int i=0; i<BOARD_SIZE; i++) {
        theBoard[ i][ PIECE]= '.';    // Set each playing piece default
        // set the default wall values to be blank
        theBoard[ i][ LEFT]=  ' ';
        theBoard[ i][ ABOVE]= ' ';
        theBoard[ i][ RIGHT]= ' ';
        theBoard[ i][ BELOW]= ' ';

        // reset the edge pieces
        // reset the left wall if piece is on left edge
        if( (i % BOARD_EDGE) == 0) {
            theBoard[ i][ LEFT]= '|';
        }
        // reset the above wall if piece is on top edge
        if( i < BOARD_EDGE) {
            theBoard[ i][ ABOVE]= '-';
        }
        // reset the right wall if piece is on right edge
        if( ((i+1) % BOARD_EDGE) == 0) {
            theBoard[ i][ RIGHT]= '|';
        }
        // reset the below wall if piece is on bottom edge
        if( i >= (BOARD_SIZE - BOARD_EDGE) ) {
            theBoard[ i][ BELOW]= '-';
        }
    }//end for( int i...

}//end createBoard()


//-------------------------------------------------------------------------------------
// readFromFileAndModifyBoard() - Read from data file, updating board accordingly.
//
//    For this program to work in Qt Creator, put a copy of the data file (board.txt)
//    in the build directory.
//
// This function should change parts of the blank board:
//     |- - - - - - - - - - - - - - - -|
//     |. . . . . . . . . . . . . . . .|
//     |                               |
//     |. . . . . . . . . . . . . . . .|
//     |                               |
//     |. . . . . . . . . . . . . . . .|
//     |                               |
//     ... and so on ...
// to have destination letters placed, with "corner lines" around them, such as:
//     |- - - - - - - - - - - - - - - -|
//     |. . . . .|. . . . . .|. . . . .|
//     |                               |
//     |. . A|. . . . . .|B . . . . . .|
//     |    -             -         -  |
//     |. . . . . . . . . . . . . . C|.|
//     ... and so on ...
// The information for these changes comes from the data file (board.txt)
// The first few lines of that file look like:
//     15
//     29
//     5 1000
//     11 1000
//     18 0011 A
//     25 1001 B
//     46 0110 C
//     49 1001 D
//     64 1001
//     ... and so on ...
// The first line of the file (15) has the number of possible destination pieces,
// corresponding to the letters 'A'..'O'
// The second line (29) is the total number of squares where surrounding pieces
// need to be adjusted.
// The last 4 lines of the file are the positions for the 4 robots.
void readFromFileAndModifyBoard(int &numberOfDestinationPieces)
{
    int numberOfSpecialSquares;     // read from file, denotes number of pieces with some kind of wall
    FILE *pInputFile;               // file pointer
    char c;                         // For reading input characters

    // Associate the actual file name with file pointer and try to open it
    pInputFile = fopen("board.txt", "r");
    // verify that file open worked
    if (pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", "board.txt");
        exit(-1);
    }

    // read from file
    fscanf(pInputFile, " %d", &numberOfDestinationPieces);  // read how many destination pieces there are
    fscanf(pInputFile, " %d", &numberOfSpecialSquares);    // number of square with walls around them somewhere

    int pieceNumber;                            // pieceNumber for each square defined in data file
    char left, above, right, below;             // variables to store possible walls indicators
    char letterToDisplay[ 2];                   // array to store possible letter to be displayed

    // Process the special squares, updating the board
    for( int i=0; i<numberOfSpecialSquares; i++) {
        // read the piece number
        fscanf(pInputFile, " %d", &pieceNumber);
        // read the information on whether or not there is each of the potential 4 walls
        fscanf(pInputFile, " %c%c%c%c", &left, &above, &right, &below);
        // store the corresponding walls
        if( left=='1') {
            theBoard[ pieceNumber][ LEFT] = '|';
        }
        if( above=='1') {
            theBoard[ pieceNumber][ ABOVE] = '-';
        }
        if( right=='1') {
            theBoard[ pieceNumber][ RIGHT] = '|';
        }
        if( below=='1') {
            theBoard[ pieceNumber][ BELOW] = '-';
        }
        // Read the next character.  If is not a newline, then there is still a letter to be displayed
        // that needs to be read from this line.
        fscanf(pInputFile, "%c", &c);
        if( c==' ') {
            fscanf(pInputFile, "%s\n", letterToDisplay);
            // place the input character on the board if there was one
            theBoard[ pieceNumber][ PIECE] = letterToDisplay[ 0];
        }
    }//end for( int i...

    // process the 4 robots, updating the board
    // Loop starts counting from 1 (rather than 0), since we ignore the 0th position
    // of the robots array, so that robot numbers correspond to what is shown
    // on the board.
    for( int i=1; i<=NUMBER_OF_ROBOTS; i++) {
        fscanf(pInputFile, " %d\n", &theRobots[ i]);
        // set robot on board, converting the integer value to a character
        theBoard[ theRobots[ i]][ PIECE] = (char)('0'+i);     // record the robot number in place on board
    }

    fclose( pInputFile);         // close the input file

}//end readFromFileAndModifyBoard()



//-------------------------------------------------------------------------------------
// display the current board
//
void displayBoard()
{
    int row;
    int col;
    // display the top row
    printf("|");      // display leading (left) edge
    for( int i=0; i<BOARD_EDGE; i++) {
        printf("%c", theBoard[ i][ ABOVE]);
        // only display the space if it is not at the end of the row
        if( i < (BOARD_EDGE - 1) ) {
            printf(" ");
        }
    }
    printf("|\n");      // display trailing (right) edge
    // display the "body" of the board
    for(row = 0; row< BOARD_EDGE; row++){
        printf("|");
        for(col = 0; col < BOARD_EDGE; col++){
            printf("%c", theBoard[ (row * BOARD_EDGE) + col][ PIECE]);
            if(theBoard[ (row*BOARD_EDGE) + col][ RIGHT] == '|' || theBoard[ (row*BOARD_EDGE) + col + 1][ LEFT] == '|'){
                if(col < 15){
                    printf("|");
                }

            }
            else{
                printf(" ");
            }
        }

        printf("|\n");

        //display empty rows containing '-' walls
        if(row != 15){
            printf("|");
            for(col = 0; col < BOARD_EDGE; col++){

                if(theBoard[ (row*BOARD_EDGE) + col][ BELOW] == '-' ||theBoard[ ((row+1)*BOARD_EDGE) + col][ ABOVE] == '-' ){
                    printf("-");
                }
                else{
                    printf(" ");
                }
                if(col < BOARD_EDGE-1){
                    printf(" ");
                }

            }
            printf("|\n");
        }


    }

    //display bottom row
    printf("|");
    for( int i=(BOARD_SIZE-BOARD_EDGE); i < BOARD_SIZE; i++){
        printf("%c", theBoard[ i][ BELOW]);
        if(i < (BOARD_SIZE-1)){
            printf(" ");
        }
    }



    printf("|\n");

}//end displayTheBoard()


// function to clear all alphabetical characters except the winning one
int clearNonWinningAlpha(char &objectiveLetter)
{
    int j;
    for (int i=0; i < BOARD_SIZE; i++)
    {
        if(!isdigit(theBoard[i][PIECE]) && isalpha(theBoard[i][PIECE]) && theBoard[i][PIECE] != objectiveLetter){
            theBoard[i][PIECE] = '.';
        }
        if(theBoard[i][PIECE] == objectiveLetter)
            j = i;
    }
    return j;
}


//getting user move it returns int because if the user enters x the game ends
int userMove(char &robot, char &direction){

    printf("Please enter the robot to move and the direction. Eg(2 L) \n");
    scanf(" %c %c", &robot, &direction);
    printf("\n");

    if(robot == 'x' || robot == 'X' || direction == 'X' || direction == 'x'){
        return 0;
    }

    else{
        while(robot != '1' && robot != '2' && robot != '3' && robot != '4'){
            printf("Invalid move try again:\n");
            printf("Please enter the robot to move and the direction. Eg(2 L) \n");
            scanf(" %c %c", &robot, &direction);
        }
        while(direction != 'U' && direction != 'u' && direction != 'L' && direction != 'l' &&
              direction != 'R' && direction != 'r' && direction != 'D' && direction != 'd'){
            printf("Invalid move try again:\n");
            printf("Please enter the robot to move and the direction. Eg(2 L) \n");
            scanf(" %c %c", &robot, &direction);
        }
        return 1;
    }

}


//function to move the robots
void moveRobot(char &robot, char &direction, int &j, char &objectiveLetter){
    int row;
    int col;
    int position;
    //------------robot 1--------------------//
    if(robot =='1'){
        //------------left--------------------//
        if(direction == 'L' || direction =='l'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '1'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i > row*BOARD_EDGE-1; i--){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && theBoard[ i][PIECE] != '|' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i+1][ PIECE] = '1';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i-1][ RIGHT] == '|' || theBoard[ i][ LEFT] == '|' || theBoard[ i][PIECE] == '|' || isalpha(theBoard[ i][PIECE])){
                                    theBoard[ i][ PIECE] = '1';
                                    break;
                                }
                            }
                        }

                    }

                }
            }

        }
        //------------right--------------------//
        if(direction == 'R' || direction == 'r'){

            for(row = 0; row< BOARD_EDGE; row++){

                for(col = 0; col < BOARD_EDGE; col++){

                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '1'){

                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;

                        for(int i = position; i < (row+1)*BOARD_EDGE; i++){

                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][ PIECE])){

                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){

                                    theBoard[ i-1][ PIECE] = '1';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+1][ LEFT] == '|' || theBoard[ i][ RIGHT] == '|' || isalpha(theBoard[ i][ PIECE])){
                                    theBoard[ i][ PIECE] = '1';
                                    break;
                                }
                            }
                        }
                    }

                }
            }
        }
        //------------UP--------------------//
        if(direction == 'U' || direction =='u'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '1'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i >= 0; i=(i-BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i + BOARD_EDGE][ PIECE] = '1';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i][ ABOVE] == '-' || theBoard[ i - BOARD_EDGE][ BELOW] == '-' || isalpha(theBoard[ i][ PIECE])){
                                    theBoard[ i][ PIECE] = '1';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }
        //------------DOWN--------------------//

        if(direction == 'D' || direction =='d'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '1'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i < BOARD_SIZE; i=(i+BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i-BOARD_EDGE][ PIECE] = '1';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+BOARD_EDGE][ ABOVE] == '-' || theBoard[ i][ BELOW] == '-' || isalpha(theBoard[ i][PIECE])){
                                    theBoard[ i][ PIECE] = '1';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }

    }
    //-------------- robot 2 ----------------//
    if(robot =='2'){
        //------------LEFT--------------------//
        if(direction == 'L' || direction =='l'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '2'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i > row*BOARD_EDGE-1; i--){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i+1][ PIECE] = '2';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i-1][ RIGHT] == '|' || theBoard[ i][ LEFT] == '|' || theBoard[ i][PIECE] == '|' || isalpha(theBoard[ i][PIECE])){
                                    theBoard[ i][ PIECE] = '2';
                                    break;
                                }
                            }
                        }

                    }

                }
            }

        }
        //------------RIGHT--------------------//
        if(direction == 'R' || direction == 'r'){

            for(row = 0; row< BOARD_EDGE; row++){

                for(col = 0; col < BOARD_EDGE; col++){

                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '2'){

                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;

                        for(int i = position; i < (row+1)*BOARD_EDGE; i++){

                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){

                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){

                                    theBoard[ i-1][ PIECE] = '2';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+1][ LEFT] == '|' || theBoard[ i][ RIGHT] == '|'){
                                    theBoard[ i][ PIECE] = '2';
                                    break;
                                }
                            }
                        }
                    }

                }
            }
        }
        //------------UP-------------------//
        if(direction == 'U' || direction =='u'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '2'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i >= 0; i=(i-BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i+BOARD_EDGE][ PIECE] = '2';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i][ ABOVE] == '-' || theBoard[ i-BOARD_EDGE][ BELOW] == '-'){
                                    theBoard[ i][ PIECE] = '2';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }
        //------------DOWN--------------------//
        if(direction == 'D' || direction =='d'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '2'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i < BOARD_SIZE; i=(i+BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i-BOARD_EDGE][ PIECE] = '2';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+BOARD_EDGE][ ABOVE] == '-' || theBoard[ i][ BELOW] == '-'){
                                    theBoard[ i][ PIECE] = '2';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }

    }

    //-------------------- Robot 3 ----------//

    if(robot =='3'){
        //------------LEFT--------------------//
        if(direction == 'L' || direction =='l'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '3'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i > row*BOARD_EDGE-1; i--){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '1'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i+1][ PIECE] = '3';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i-1][ RIGHT] == '|' || theBoard[ i][ LEFT] == '|' || theBoard[ i][PIECE] == '|' || isalpha(theBoard[ i][PIECE])){
                                    theBoard[ i][ PIECE] = '3';
                                    break;
                                }
                            }
                        }

                    }

                }
            }

        }
        //------------RIGHT--------------------//
        if(direction == 'R' || direction == 'r'){

            for(row = 0; row< BOARD_EDGE; row++){

                for(col = 0; col < BOARD_EDGE; col++){

                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '3'){

                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;

                        for(int i = position; i < (row+1)*BOARD_EDGE; i++){

                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){

                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '1'|| theBoard[ i][ PIECE] != '4'){

                                    theBoard[ i-1][ PIECE] = '3';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+1][ LEFT] == '|' || theBoard[ i][ RIGHT] == '|'){
                                    theBoard[ i][ PIECE] = '3';
                                    break;
                                }
                            }
                        }
                    }

                }
            }
        }
        //------------UP--------------------//
        if(direction == 'U' || direction =='u'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '3'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i >= 0; i=(i-BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '1'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i+BOARD_EDGE][ PIECE] = '3';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i][ ABOVE] == '-' || theBoard[ i-BOARD_EDGE][ BELOW] == '-'){
                                    theBoard[ i][ PIECE] = '3';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }
        //------------DOWN--------------------//
        if(direction == 'D' || direction =='d'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '3'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i < BOARD_SIZE; i=(i+BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '2' ||
                                        theBoard[ i][ PIECE] != '1'|| theBoard[ i][ PIECE] != '4'){
                                    theBoard[ i-BOARD_EDGE][ PIECE] = '3';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+BOARD_EDGE][ ABOVE] == '-' || theBoard[ i][ BELOW] == '-'){
                                    theBoard[ i][ PIECE] = '3';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }

    }
    //---------------robot 4 ---------------//
    if(robot =='4'){
        //------------LEFT--------------------//
        if(direction == 'L' || direction =='l'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '4'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i > row*BOARD_EDGE-1; i--){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '2'){
                                    theBoard[ i+1][ PIECE] = '4';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i-1][ RIGHT] == '|' || theBoard[ i][ LEFT] == '|' || theBoard[ i][PIECE] == '|' || isalpha(theBoard[ i][PIECE])){
                                    theBoard[ i][ PIECE] = '4';
                                    break;
                                }
                            }
                        }

                    }

                }
            }

        }
        //------------RIGHT--------------------//
        if(direction == 'R' || direction == 'r'){

            for(row = 0; row< BOARD_EDGE; row++){

                for(col = 0; col < BOARD_EDGE; col++){

                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '4'){

                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;

                        for(int i = position; i < (row+1)*BOARD_EDGE; i++){

                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){

                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '2'){

                                    theBoard[ i-1][ PIECE] = '4';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+1][ LEFT] == '|' || theBoard[ i][ RIGHT] == '|'){
                                    theBoard[ i][ PIECE] = '4';
                                    break;
                                }
                            }
                        }
                    }

                }
            }
        }
        //------------UP--------------------//
        if(direction == 'U' || direction =='u'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '4'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i >= 0; i=(i-BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '2'){
                                    theBoard[ i+BOARD_EDGE][ PIECE] = '4';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i][ ABOVE] == '-' || theBoard[ i-BOARD_EDGE][ BELOW] == '-'){
                                    theBoard[ i][ PIECE] = '4';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }
        //------------DOWN--------------------//
        if(direction == 'D' || direction =='d'){
            for(row = 0; row< BOARD_EDGE; row++){
                for(col = 0; col < BOARD_EDGE; col++){
                    if(theBoard[(row*BOARD_EDGE)+col][PIECE] == '4'){
                        theBoard[(row*BOARD_EDGE)+col][PIECE] = '.';
                        position =  (row*BOARD_EDGE)+col;
                        for(int i = position; i < BOARD_SIZE; i=(i+BOARD_EDGE)){
                            if(theBoard[ i][ PIECE] != ' ' && theBoard[ i][PIECE] != '.' && !isalpha(theBoard[ i][PIECE])){
                                if(theBoard[ i][ PIECE] != '0' || theBoard[ i][ PIECE] != '1' ||
                                        theBoard[ i][ PIECE] != '3'|| theBoard[ i][ PIECE] != '2'){
                                    theBoard[ i-BOARD_EDGE][ PIECE] = '4';
                                    break;
                                }

                            }
                            else{
                                if(theBoard[ i+BOARD_EDGE][ ABOVE] == '-' || theBoard[ i][ BELOW] == '-'){
                                    theBoard[ i][ PIECE] = '4';
                                    break;
                                }
                            }

                        }

                    }

                }
            }

        }

    }
    //The robot overwrites winning position but if it isn't a digit the winning position returns returns to initial state
    if(!isdigit(theBoard[j][PIECE]))
        theBoard[j][PIECE] = objectiveLetter;
}


//function to check if the winning robot is in winning spot
int checkWin(int &j, char &objectiveRobot)
{
    if(theBoard[j][PIECE] == objectiveRobot){
        printf("\nCONGRADULATIONS! YOU WIN !!");
        return 0;
    }

    else
        return 1;
}


//-------------------------------------------------------------------------------------
// main() - main part of program, that drives everything else
//
int main()
{
    // variable declarations
    int numberOfDestinationPieces;  // Number of destination pieces.  Value comes from the data file.
    int endGame = 1;//ending game if 2 is in position M
    int endGame1 = 1;//ending game if user enters x of X
    int j;
    int count = 0;
    char robot;
    char objectiveRobot;
    char objectiveLetter;
    char direction;

    srand( 1); // Initialize random number generator using a constant for debugging
    //srand( time(0)); // Initialize random number generator using time(0) so results vary
    // Only initialize the random number generator ONCE in your program!

    objectiveRobot = (random() % 4) + 1; // find random robot between 1 and 4
    //objectiveRobot = '2'; //as per instructions hard coding it so it's 2

    objectiveLetter = 'A' + (random() % 15); //finds a random letter between A and O
   // objectiveLetter = 'M'; // as per in class instructions hard coding it so it's 2



    // Display ID information and game instructions
    displayIdInformation();
    displayInstructions();

    // create the board, initializing all pieces to their default settings
    createBoard();                // Initialize the global theBoard array

    printf("\n\nThe objective robot is %d. The winning position is %c\n\n", objectiveRobot, objectiveLetter);

    printf("Blank board is: \n");
    displayBoard();

    // read from the datafile and modify the board accordingly
    readFromFileAndModifyBoard( numberOfDestinationPieces);

    printf("Initialized board is: \n");
    displayBoard();

    printf("\nBoard displaying only winning position is: \n");


    j = clearNonWinningAlpha(objectiveLetter); //clears board of alphabetical characters that aren't the objective character
    //returns the index of the objective character

    // printf("\nThe winning index is %d\n", j); // this was used when program was randomized

    displayBoard();

    //while the endgame function is not true the game continues
    while(endGame != 0 && endGame1 != 0){
        endGame1 = userMove(robot, direction);
        moveRobot(robot, direction, j, objectiveLetter);
        displayBoard();
        endGame = checkWin(j, objectiveRobot);
        count++;
    }

    printf("\nThanks for playing \n");

    printf("\nIt took you %d moves\n", count);

    return 0;
}//end main()
