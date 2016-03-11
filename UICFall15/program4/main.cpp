/*
 *
 *
 * Denis Doci
 * Class: CS 141
 * Fall 2015
 * Lab: Tues. 11AM
 * TA - Vignesh Ganapathiraman
 *
 * This is program is a game called tic tac two
 * It is simialar to the well known tic tac tow
 * with the distinct differences in the fact that
 * the grid can be moved in a given space and the
 * pieces can be moved within the grid after two moves have
 * occured.
 *
 * Also this program differs in the fact that
 * moving the pieces is only allowed after
 * 4 completed moves.
 *
 *
 * */

#include <iostream>
#include <cstdlib>      // for the system command
#include <cctype>       // For the letter checking functions, e.g. toupper( )

using namespace std;


//function to display class information
void displayInfo()
{
    // Display identifying information
    cout << "\n\nAuthor: Denis Doci\n"
         << "Program 5: Tic Tac Two\n"
         << "TA: Vignesh Ganapathiraman, T 11:00 AM \n"
         << "UIC CS 141, November 2015\n"
         << endl;
}//end displayIdInformation()


//function to display the board
void displayBoard(int &boardEdge, int &gridHozPos, char * &theBoard, int &gridHoz, int &gridVert)

//these variables are used as they can be changed later and the display won't change
//naming conventions are explained below
{
    int row;        //board rows
    int col;        //board columns

    //display top edge
    printf(" ");
    for( int i=0; i < 19; i++){
        printf("-");

    }
    printf("\n");


    // display the "body" of the board
    for(row = 0; row< boardEdge; row++){
        if(row == gridVert || row == gridVert+1 || row == gridVert+2){
            printf("|");
            for(col = 0; col < boardEdge; col++){
                if(col == gridHozPos || col == gridHozPos-1){
                    printf(" %c |", theBoard[((row*5)+col)]);   //grid vertical lines
                }
                else if (col == boardEdge-1){
                    printf(" %c ", theBoard[ ((row*5)+col)]);
                }
                else{
                    printf(" %c  ", theBoard[((row*5)+col)]);
                }
            }
            printf("|\n");
        }
        else{
            printf("|");
            for(col = 0; col < boardEdge; col++){
                if(col < boardEdge-1){
                    printf(" %c  ", theBoard[ ((row*5) + col)]);
                }
                else{
                    printf(" %c ", theBoard[((row*5) + col)]);
                }
            }
            printf("|\n");
        }



        //display empty rows containing '-' of grid
        if(row < 4){
            printf("|");
            if(row == gridVert || row == gridVert+1){
                for(col = 0; col < gridHoz; col++){
                    printf(" ");
                }
                for(col = 0; col < 9; col++){
                    printf("-");
                }
                for(col = 0; col < (19-gridHoz-9); col++){
                    printf(" ");
                }
            }
            else{
                for(col = 0; col < 19; col++){
                    printf(" ");
                }
            }
            printf("|\n");
        }


    }

    //display bottom edge
    printf(" ");
    for( int i=0; i < 19; i++){
        printf("-");

    }
    printf("\n");

}//end displayTheBoard()


//function to display the pieces for each player and the
//grid destination squares
void displayRemaining(char player1[4], char player2[4]){

    printf("\nPieces remaining for:\n");
    printf("   Player 1:");
    for(int i=0; i<4; i++){
        printf(" %c ", player1[i]);
    }
    printf("\n");

    printf("   Player 2:");
    for(int i=0; i<4; i++){
        printf(" %c ", player2[i]);
    }
    printf("\n\n");

    printf("Grid destination squares:\n");
    printf("     1 2 3\n");
    printf("     4 5 6\n");
    printf("     7 8 9\n");

}//end displayremaining()


//function to move the grid
void movegrid(char *&theBoard, int &gridHozPos, int &gridVert, int &moveInt, int &gridHoz){

    if(moveInt ==1){ //up and to the left
        gridVert = gridVert-1;
        gridHozPos = gridHozPos -1;
        gridHoz = gridHoz -4;
    }

    if(moveInt == 2){ //up
        gridVert = gridVert - 1;
    }

    if(moveInt == 3){//up and right
        gridVert = gridVert-1;
        gridHozPos = gridHozPos + 1;
        gridHoz = gridHoz + 4;
    }

    if(moveInt == 4){//left
        gridHozPos = gridHozPos - 1;
        gridHoz = gridHoz - 4;
    }

    if(moveInt == 6){//right
        gridHozPos = gridHozPos + 1;
        gridHoz = gridHoz + 4;
    }

    if(moveInt ==7){//left and down
        gridVert = gridVert+1;
        gridHozPos = gridHozPos -1;
        gridHoz = gridHoz - 4;
    }
    if(moveInt == 8){//down
        gridVert = gridVert + 1;
    }

    if(moveInt == 9){//right and down
        gridVert = gridVert+1;
        gridHozPos = gridHozPos + 1;
        gridHoz = gridHoz + 4;
    }
}



//function to check if the user's move was valid
void moveCheck(char &moveChar, int &moveInt, char player1[4],
               char player2[4], int &moveCount, int movePos,
               char * &theBoard, int &gridHozPos,
               int &gridVert, int &gridHoz)
{

    int invalid = 1; //used for while loop
    if(moveCount > 4){//for moves greater than 4 this is the
        //portion of the code that allows the grid itself to move

        if(moveChar == 'm' && moveInt != 5){
            if (moveInt == 1 ){ //up and to the left
                if(gridVert < 1 || gridHozPos < 1 || gridHoz < 5){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 2 ){ //up and to the left
                if(gridVert < 1){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 3 ){ //up and to the left
                if(gridVert < 1 || gridHoz > 8){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 4 ){ //up and to the left
                if(gridHoz < 5){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 6 ){ //up and to the left
                if(gridHoz > 8){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 7 ){ //up and to the left
                if(gridHoz < 5 || gridVert > 1 ){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 8){ //up and to the left
                if(gridVert > 1 ){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
            if (moveInt == 9){ //up and to the left
                if(gridVert > 1 || gridHozPos > 8){
                    printf("Invalid grid move. \nPlease Retry: ");
                    scanf(" %c %d", &moveChar, &moveInt);
                    moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);
                }
                else{
                    movegrid(theBoard, gridHozPos, gridVert, moveInt, gridHoz);
                }
            }
        }

        else{
            if(moveCount % 2 == 1){     //player1 check
                while(invalid == 1){
                    for(int i = 0; i < 4; i++){ //if user character is in possible characters
                        if(player1[i] == moveChar){
                            for(int j = 1; j<10; j++){ // if its between 1-9 i.e. possible grid spaces
                                if(moveInt == j && theBoard[ movePos] == '.'){
                                    invalid = 0;
                                    break;
                                }
                            }
                        }
                        else{
                            //moving the pieces within the grid
                            if(isupper(moveChar)){
                                //1
                                if(moveChar == theBoard[(((gridVert*5)+gridHozPos)-1)]){
                                    theBoard[(((gridVert*5)+gridHozPos)-1)] = '.';
                                    invalid = 0;
                                    break;
                                }
                                //2
                                if(moveChar ==  theBoard[(((gridVert*5)+gridHozPos))]){
                                    theBoard[(((gridVert*5)+gridHozPos))] = '.';
                                    invalid = 0;
                                    break;
                                }
                                //3
                                if(moveChar ==  theBoard[(((gridVert*5)+gridHozPos)+1)]){
                                    theBoard[(((gridVert*5)+gridHozPos)+1)]= '.';
                                    invalid = 0;
                                    break;
                                }

                                //4
                                if(moveChar == theBoard[((((gridVert+1)*5)+gridHozPos)-1)]){
                                    theBoard[((((gridVert+1)*5)+gridHozPos)-1)] = '.';
                                    invalid = 0;
                                    break;
                                }

                                //5
                                if(moveChar == theBoard[(((gridVert+1)*5)+gridHozPos)]){
                                    theBoard[(((gridVert+1)*5)+gridHozPos)] = '.';
                                    invalid = 0;
                                    break;
                                }

                                //6
                                if(moveChar == theBoard[((((gridVert+1)*5)+gridHozPos)+1)]){
                                    theBoard[((((gridVert+1)*5)+gridHozPos)+1)] = '.';
                                    invalid = 0;
                                    break;
                                }

                                //7
                                if(moveChar == theBoard[((((gridVert+2)*5)+gridHozPos)-1)]){
                                    theBoard[((((gridVert+2)*5)+gridHozPos)-1)] = '.';
                                    invalid = 0;
                                    break;
                                }

                                //8
                                if(moveChar == theBoard[(((gridVert+2)*5)+gridHozPos)]){
                                    theBoard[(((gridVert+2)*5)+gridHozPos)] = '.';
                                    invalid = 0;
                                    break;
                                }

                                //9
                                if(moveChar == theBoard[((((gridVert+2)*5)+gridHozPos)+1)]){
                                    theBoard[((((gridVert+2)*5)+gridHozPos)+1)] = '.';
                                    invalid = 0;
                                    break;
                                }
                            }

                        }
                    }
                    if(invalid == 1){
                        printf("%d. Player 1: Enter piece to move and destination numberenter m to move grid: ", moveCount);
                        scanf(" %c %d", &moveChar, &moveInt);

                        if(moveInt==1 || moveInt==2 || moveInt==3){
                            movePos = ((((gridVert*5)+gridHozPos)-1)+moveInt-1); //resets move position
                        }
                        else if(moveInt == 4 || moveInt==5 || moveInt==6){
                            movePos = ((((gridVert*5)+gridHozPos))+moveInt); //resets move position
                        }
                        else{
                            movePos = ((((gridVert+2)*5)+(gridHozPos-8)))+moveInt; //resets move position
                        }
                    }
                }
            }

            else{                       //player2 check same concept as player 1
                while(invalid == 1){
                    for(int i = 0; i < 4; i++){
                        if(player2[i] == moveChar){
                            for(int j = 1; j<10; j++){
                                if(moveInt == j && theBoard[movePos] == '.'){
                                    invalid = 0;
                                    break;
                                }
                            }
                        }
                        else{
                            if(islower(moveChar)){

                                if(moveChar == theBoard[(((gridVert*5)+gridHozPos)-1)]){
                                    theBoard[(((gridVert*5)+gridHozPos)-1)] = '.';
                                    invalid = 0;
                                    break;
                                }

                                if(moveChar ==  theBoard[(((gridVert*5)+gridHozPos))]){
                                    theBoard[(((gridVert*5)+gridHozPos))] = '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar ==  theBoard[(((gridVert*5)+gridHozPos)+1)]){
                                    theBoard[(((gridVert*5)+gridHozPos)+1)]= '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar == theBoard[((((gridVert+1)*5)+gridHozPos)-1)]){
                                    theBoard[((((gridVert+1)*5)+gridHozPos)-1)] = '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar == theBoard[(((gridVert+1)*5)+gridHozPos)]){
                                    theBoard[(((gridVert+1)*5)+gridHozPos)] = '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar == theBoard[((((gridVert+1)*5)+gridHozPos)+1)]){
                                    theBoard[((((gridVert+1)*5)+gridHozPos)+1)] = '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar == theBoard[((((gridVert+2)*5)+gridHozPos)-1)]){
                                    theBoard[((((gridVert+2)*5)+gridHozPos)-1)] = '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar == theBoard[(((gridVert+2)*5)+gridHozPos)]){
                                    theBoard[(((gridVert+2)*5)+gridHozPos)] = '.';
                                    invalid = 0;
                                    break;
                                }
                                if(moveChar == theBoard[((((gridVert+2)*5)+gridHozPos)+1)]){
                                    theBoard[((((gridVert+2)*5)+gridHozPos)+1)] = '.';
                                    invalid = 0;
                                    break;
                                }
                            }
                        }
                    }

                    if(invalid == 1){
                        printf("%d. Player 2: Enter piece to move and destination number enter m to move grid: ", moveCount);
                        scanf(" %c %d", &moveChar, &moveInt);

                        if(moveInt==1 || moveInt==2 || moveInt==3){
                            movePos = ((((gridVert*5)+gridHozPos)-1)+moveInt-1);
                        }
                        else if(moveInt == 4 || moveInt==5 || moveInt==6){
                            movePos = ((((gridVert*5)+gridHozPos))+moveInt);
                        }
                        else{
                            movePos = ((((gridVert+2)*5)+(gridHozPos-8)))+moveInt;
                        }
                    }
                }
            }
        }
    }

    //portion of the code specifically for the first move almost the same as above
    else{
        if(moveCount % 2 == 1){     //player1 check
            while(invalid == 1){
                for(int i = 0; i < 4; i++){ //if user character is in possible characters
                    if(player1[i] == moveChar){
                        for(int j = 1; j<10; j++){ // if its between 1-9 i.e. possible grid spaces
                            if(moveInt == j && theBoard[ movePos] == '.'){
                                invalid = 0;
                                break;
                            }
                        }
                    }
                }
                if(invalid == 1){
                    printf("%d. Player 1: Enter piece to move and destination number: ", moveCount);
                    scanf(" %c %d", &moveChar, &moveInt);

                    if(moveInt==1 || moveInt==2 || moveInt==3){
                        movePos = ((((gridVert*5)+gridHozPos)-1)+moveInt-1); //resets move position
                    }
                    else if(moveInt == 4 || moveInt==5 || moveInt==6){
                        movePos = ((((gridVert*5)+gridHozPos))+moveInt); //resets move position
                    }
                    else{
                        movePos = ((((gridVert+2)*5)+(gridHozPos-8)))+moveInt; //resets move position
                    }
                }
            }
        }

        else{                       //player2 check same concept as player 1
            while(invalid == 1){
                for(int i = 0; i < 4; i++){
                    if(player2[i] == moveChar){
                        for(int j = 1; j<10; j++){
                            if(moveInt == j && theBoard[movePos] == '.'){
                                invalid = 0;
                                break;
                            }
                        }
                    }
                }

                if(invalid == 1){
                    printf("%d. Player 2: Enter piece to move and destination number: ", moveCount);
                    scanf(" %c %d", &moveChar, &moveInt);

                    if(moveInt==1 || moveInt==2 || moveInt==3){
                        movePos = ((((gridVert*5)+gridHozPos)-1)+moveInt-1);
                    }
                    else if(moveInt == 4 || moveInt==5 || moveInt==6){
                        movePos = ((((gridVert*5)+gridHozPos))+moveInt);
                    }
                    else{
                        movePos = ((((gridVert+2)*5)+(gridHozPos-8)))+moveInt;
                    }
                }
            }
        }
    }
}
// end moveCheck()


//function to check if the game is won
int checkWin(int gridHozPos, int gridVert, char * theBoard){

    //check player1

    //check horizontal
    //row 1
    if( isupper(theBoard[(((gridVert*5)+gridHozPos)-1)]) && isupper(theBoard[(((gridVert*5)+gridHozPos))]) && isupper(theBoard[(((gridVert*5)+gridHozPos)+1)]))
    {
        printf("Player 1 Wins");
        return 0;

    }

    //row 2
    if( isupper(theBoard[(((gridVert+1)*5)+gridHozPos)-1]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos)]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos+1)]))
    {
        printf("Player 1 Wins");
        return 0;

    }

    //row 3
    if( isupper(theBoard[(((gridVert+2)*5)+gridHozPos)-1]) && isupper(theBoard[(((gridVert+2)*5)+gridHozPos)]) && isupper(theBoard[(((gridVert+2)*5)+gridHozPos+1)]))
    {
        printf("Player 1 Wins");
        return 0;

    }

    //check vertical

    //column 1
    if( isupper(theBoard[(((gridVert*5)+gridHozPos)-1)]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos)-1]) && isupper(theBoard[(((gridVert+2)*5)+gridHozPos)-1]))
    {
        printf("Player 1 Wins");
        return 0;

    }

    //column2
    if( isupper(theBoard[(((gridVert*5)+gridHozPos))]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos)]) && isupper(theBoard[(((gridVert+2)*5)+gridHozPos)]))
    {
        printf("Player 1 Wins");
        return 0;

    }

    //column 3
    if( isupper(theBoard[(((gridVert*5)+gridHozPos))+1]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos)+1]) && isupper(theBoard[(((gridVert+2)*5)+gridHozPos)+1]))
    {
        printf("Player 1 Wins");
        return 0;

    }

    //check diagonal
    //top-bottom
    if( isupper(theBoard[(((gridVert*5)+gridHozPos)-1)]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos)]) && isupper(theBoard[(((gridVert+2)*5)+gridHozPos+1)]))
    {
        printf("Player 1 Wins");
        return 0;
    }

    //bottom-top
    if( isupper(theBoard[(((gridVert+2)*5)+gridHozPos)-1]) && isupper(theBoard[(((gridVert+1)*5)+gridHozPos)]) && isupper(theBoard[(((gridVert*5)+gridHozPos)+1)]))
    {
        printf("Player 1 Wins");
        return 0;
    }


    //check player 2
    //row 1
    if( islower(theBoard[(((gridVert*5)+gridHozPos)-1)]) && islower(theBoard[(((gridVert*5)+gridHozPos))]) && islower(theBoard[(((gridVert*5)+gridHozPos)+1)]))
    {
        printf("Player 2 Wins");
        return 0;

    }

    //row 2
    if( islower(theBoard[(((gridVert+1)*5)+gridHozPos)-1]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos)]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos+1)]))
    {
        printf("Player 2 Wins");
        return 0;

    }

    //row 3
    if( islower(theBoard[(((gridVert+2)*5)+gridHozPos)-1]) && islower(theBoard[(((gridVert+2)*5)+gridHozPos)]) && islower(theBoard[(((gridVert+2)*5)+gridHozPos+1)]))
    {
        printf("Player 2 Wins");
        return 0;

    }

    //check vertical

    //column 1
    if( islower(theBoard[(((gridVert*5)+gridHozPos)-1)]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos)-1]) && islower(theBoard[(((gridVert+2)*5)+gridHozPos)-1]))
    {
        printf("Player 2 Wins");
        return 0;

    }

    //column2
    if( islower(theBoard[(((gridVert*5)+gridHozPos))]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos)]) && islower(theBoard[(((gridVert+2)*5)+gridHozPos)]))
    {
        printf("Player 2 Wins");
        return 0;

    }

    //column 3
    if( islower(theBoard[(((gridVert*5)+gridHozPos))+1]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos)+1]) && islower(theBoard[(((gridVert+2)*5)+gridHozPos)+1]))
    {
        printf("Player 2 Wins");
        return 0;

    }

    //check diagonal
    //top-bottom
    if( islower(theBoard[(((gridVert*5)+gridHozPos)-1)]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos)]) && islower(theBoard[(((gridVert+2)*5)+gridHozPos+1)]))
    {
        printf("Player 2 Wins");
        return 0;
    }

    //bottom-top
    if( islower(theBoard[(((gridVert+2)*5)+gridHozPos)-1]) && islower(theBoard[(((gridVert+1)*5)+gridHozPos)]) && islower(theBoard[(((gridVert*5)+gridHozPos)+1)]))
    {
        printf("Player 2 Wins");
        return 0;
    }

    else{
        return  1;
    }

} //end checkWin()


//function for user to make a move
void userMove(char * &theBoard, char player1[4], char player2[4],
              int &gridHozPos, int &gridHoz, int &gridVert,
              int &moveCount, int &boardEdge)
{

    char moveChar; //users move character
    int moveInt;   // users move integer
    int movePos=0; // the position that the user make the move
    int winCheck=1; //to check if someone has won the game and it's over

    printf("%d. Player 1: Enter piece to move and destination number: ", moveCount);
    scanf(" %c %d", &moveChar, &moveInt);
    printf("\n");


    while(moveChar != 'X' && moveChar != 'x' && moveInt != 120 && moveInt != 88 && winCheck==1){ //check if user inputs x or X

        moveCheck(moveChar, moveInt, player1, player2, moveCount, movePos, theBoard, gridHozPos, gridVert, gridHoz);

        if(moveChar != 'm'){
            if(moveInt==1 || moveInt==2 || moveInt==3){
                theBoard[(((gridVert*5)+gridHozPos)-1)+moveInt-1] = moveChar;
            }
            else if(moveInt == 4 || moveInt==5 || moveInt==6){
                theBoard[(((gridVert*5)+gridHozPos))+moveInt] = moveChar;
            }
            else{
                theBoard[((((gridVert+2)*5)+(gridHozPos-8)))+moveInt] = moveChar;
            }

            if(moveCount % 2 ==1){
                for(int i = 0; i<4; i++){
                    if(player1[i]==moveChar){
                        player1[i]=' ';
                    }
                }
            }

            else{
                for(int i = 0; i<4; i++){
                    if(player2[i]==moveChar){
                        player2[i]=' ';
                    }
                }
            }
        }

        displayBoard(boardEdge, gridHozPos, theBoard, gridHoz, gridVert);
        displayRemaining(player1, player2);
        moveCount++;

        winCheck = checkWin(gridHozPos, gridVert, theBoard);

        if(winCheck==1 ){
            if(moveCount < 5){
                if(moveCount % 2 ==1){
                    printf("%d. Player 1: Enter piece to move and destination number: ", moveCount);
                    scanf(" %c %d", &moveChar, &moveInt);
                }
                else{
                    printf("%d. Player 2: Enter piece to move and destination number: ", moveCount);
                    scanf(" %c %d", &moveChar, &moveInt);
                }
            }
            else{
                if(moveCount % 2 ==1){
                    printf("%d. Player 1: Enter piece to move and destination number enter m to move grid: ", moveCount);
                    scanf(" %c %d", &moveChar, &moveInt);
                }
                else{
                    printf("%d. Player 2: Enter piece to move and destination number enter m to move grid: ", moveCount);
                    scanf(" %c %d", &moveChar, &moveInt);
                }
            }

            if(moveInt==1 || moveInt==2 || moveInt==3){
                movePos = ((((gridVert*5)+gridHozPos)-1)+moveInt-1);
            }
            else if(moveInt == 4 || moveInt==5 || moveInt==6){
                movePos = ((((gridVert*5)+gridHozPos))+moveInt);
            }
            else{
                movePos = ((((gridVert+2)*5)+(gridHozPos-8)))+moveInt;
            }
        }

    }

    printf("\nGame Over\n");

} //end userMove()



int main()
{
    displayInfo();

    int boardEdge = 5;  // one row of the board
    int boardSize = boardEdge * boardEdge; //total size of board
    int gridHozPos = 2;  //position of grid based on dots from left side
    int gridHoz = 5;      // position of grid based on spaces relative to left wall
    int gridVert = 1;      // gridRow (it's one initiall because the first row = 0)
    char * theBoard;
    char player1[4]={'A', 'B', 'C', 'D'};
    char player2[4]={'a', 'b', 'c', 'd'};
    int moveCount = 1;

    theBoard = (char *) malloc( sizeof( char) * boardSize); //veritcal size of array
    for(int i=0; i<boardSize; i++){
        theBoard[i]= '.';
    }

    displayBoard(boardEdge, gridHozPos, theBoard, gridHoz, gridVert);
    displayRemaining(player1, player2);
    userMove(theBoard, player1, player2, gridHozPos, gridHoz, gridVert, moveCount, boardEdge);

}

