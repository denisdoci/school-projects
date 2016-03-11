/*
 *
 *
 * Denis Doci
 * Brandon Goodman-Gibis
 * Class: CS 141
 * Fall 2015
 * Lab: Tues. 11AM
 * TA - Vignesh Ganapathiraman
 *
 * This is a program designed to morph
 * a user word either randomized
 * or provided user of length that is
 * provided by the user into the end
 * word that is either randomized or provided
 * by user
 *
 * This version does not have a computer solution.
 *
 *
 *
 *
 * */
#include <iostream>
#include <string.h>
#include <ctype.h>

using namespace std;


//function to display class information
void displayInfo()
{
    // Display identifying information
    cout << "\n\nAuthor: Denis Doci and Brandon Goodman-Gibis\n"
         << "Program 4: Morph Words \n"
         << "TA: Vignesh Ganapathiraman, T 11:00 AM \n"
         << "UIC CS 141, October 2015\n"
         << endl;
}//end displayIdInformation()


//function to prompt user for the length
int promptUserInput(){
    int userLength;
    printf("\nWhat word length would you like to choose?\n");
    scanf( " %d", &userLength);
    return userLength;
}


//function to find the number of words in the file and return
//the number of words of length specified in promptUserInput
int  numberOfWordsInFile(int &userInput, int &numberOfWords){

    char fileName[] = "dictionary.txt";  // Make a C string (array of char) to store filename
    FILE *pInputFile;               // file pointer
    char inputLine[ 81];            // space for an input line
    int lengths[30];


    for(int j=0; j<31; j++){
        lengths[j] = 0;
    }
    // Associate the file pointer with the actual file name and try to open it
    pInputFile = fopen(fileName, "r");   // open with "r" for "read" access
    // verify that file open worked
    if (pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", fileName);
        exit(-1);
    }

    // Read from file a line at a time
    while( fscanf(pInputFile, "%s", inputLine) != EOF) {
        if( strlen( inputLine) < 31 ){ //since you know max word length is 30
            numberOfWords++;
        }
        for(int j=1; j<31; j++){
            if( strlen( inputLine) == j ){ //since you know max word length is 30
                lengths[j]++;
            }
        }
    }

    printf("Number of words read was %d \n", numberOfWords);
    printf("\nLetter with more than 2000 words\n");

    //prints out only the lengths with more than 2000 words
    for(int j=1; j<30; j++){
        if(lengths[j] > 2000){
            printf("\nThere are %d words with %d letters\n", lengths[ j], j) ;
        }
    }

    fclose( pInputFile);// close the input file

    userInput = promptUserInput( );

    printf("\nThere are %d words with %d letters\n",lengths[userInput], userInput);

    return lengths[userInput];
}//end readInWordsFrom


//function to populate the words array with words from the
// file of the length specified by the user
void populateArr(char ** theWords, int numChosenWords, int &userInput, int &numberOfWords){

    char fileName[] = "dictionary.txt";  // Make a C string (array of char) to store filename
    FILE *pInputFile;               // file pointer
    char inputLine[ 81];            // space for an input line
    int  j=0;

    // Associate the file pointer with the actual file name and try to open it
    pInputFile = fopen(fileName, "r");   // open with "r" for "read" access
    // verify that file open worked
    if (pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", fileName);
        exit(-1);
    }

    // Read from file a line at a time copies words of length 'userInput'
    for(int i=0; i < numberOfWords; i++){
        fgets(inputLine, 31, pInputFile);
        inputLine[strlen(inputLine)-1] = '\0';
        if(strlen( inputLine) == userInput){
            strcpy(theWords[j], inputLine);
            j++;
        }

    }
    for(int i=0; i < numChosenWords; i++){
        for(int k=0; k < userInput; k++){
            theWords[i][ k] = tolower(theWords[ i][ k]);
        }
    }

//This was a check to see if the right words were being copied
    /*
    printf("\nThe words at that length are\n");
    for(int i=0; i < numChosenWords; i++){
        printf("%d. %s\n", i+1, theWords[i]);
    }
    */
    fclose( pInputFile);         // close the input file
}


//function to choose a random word in theWords array
//if r was entered by the user
char * randomize(char ** theWords, int numChosenWords){
    char * randomWord;
    int i = rand() % numChosenWords;
    randomWord = theWords[i];
    return randomWord;
}


//function to establish the start and end word of
//the morph
void startAndEndWord(char ** theWords, int numChosenWords, int userInput, char * startWord, char * endWord){

    int inDictionarySt=0;
    int inDictionaryEd=0;
    char r[1] = {'r'};

    printf("\nEnter starting and ending words, or 'r' for either for a random word\n");
    printf("\nEnter start word: ");
    scanf(" %s", startWord);

    //this code here is reused often it just checks if the user wants to choose a random word
    if(strcmp(startWord, r) == 0){
        strcpy(startWord, randomize(theWords, numChosenWords));
    }
    else{
        while(strlen(startWord) != userInput){//checking if it's of proper length
            printf("\nPlease enter the word as length %d: ", userInput);
            scanf(" %s", startWord);
            if(strcmp(startWord, r) == 0){
                strcpy(startWord, randomize(theWords, numChosenWords));
            }
        }

        while(inDictionarySt == 0){//checking to see if it's in dictionary
            for(int i=0; i<numChosenWords; i++){
                if(strcmp(startWord, theWords[i]) == 0){
                    inDictionarySt = 1;
                    break;
                }
            }
            if(inDictionarySt == 0){
                printf("\n%s is not in the dictionary please re-enter word: ", startWord);
                scanf(" %s", startWord);
                if(strcmp(startWord, r) == 0){
                    strcpy(startWord, randomize(theWords, numChosenWords));
                }
            }
        }
    }

    printf("\nNow enter an end word: ");
    scanf(" %s", endWord);

    //same concept just checking the endward this time
    if(strcmp(endWord, r) == 0){
        strcpy(endWord, randomize(theWords, numChosenWords));
    }
    else{
        while(strlen(endWord) != userInput){
            printf("\nPlease enter the word as length %d: ", userInput);
            scanf(" %s", endWord);
            if(strcmp(endWord, r) == 0){
                strcpy(endWord, randomize(theWords, numChosenWords));
            }
        }
        while(inDictionaryEd == 0){
            for(int i=0; i<numChosenWords; i++){
                if(strcmp(endWord, theWords[i]) == 0){
                    inDictionaryEd=1;
                    break;
                }
            }
            if(inDictionaryEd == 0){
                printf("\n%s is not in the dictionary. Please re-enter word: ", endWord);
                scanf(" %s", endWord);
                if(strcmp(startWord, r) == 0){
                    strcpy(startWord, randomize(theWords, numChosenWords));
                }
            }
        }
    }
    printf("\nThe start word is %s, the end word is %s\n", startWord, endWord);
}


//computer generated solution function
//we didn't get to this part but it calls properly
void computerGenSol(){
    printf("\nThis where the computer solution would be.\n");
    return;
}


//function to establish the user's attepmt at a solution path
void userPath(char ** theWords, char * startWord, char * endWord, int numChosenWords, int userInput){
    char nextWord[userInput];
    char userWord[userInput];
    char exit[5] = {'e','x','i','t'}; // to go to the computer gen solution
    int inDictionaryNxt=0;
    int difference=0;
    int pathCount=0;
    int isOneDiff=0;

    printf("Morphing from %s to %s.\n", startWord, endWord);
    printf("On each move enter a word of the same length that is at\n");
    printf("most 1 character different and is also in the dictionary,\n");
    printf("or type in exit to exit the interactive portion of the program.\n\n");

    pathCount++; //increments after every valid move
    printf("%d. Previous word is '%s'.  Next word: ", pathCount, startWord);
    scanf(" %s", nextWord);
    strcpy(userWord, startWord);

    while(strcmp(userWord, endWord) != 0){
        if(strcmp(nextWord, exit) == 0){
            computerGenSol();
            return;
        }
        else{
            while(strlen(nextWord) != userInput){//checking length
                if(strcmp(nextWord, exit) == 0){
                    computerGenSol();
                    return;
                }
                else{
                    printf("\nPlease enter the word as length %d: ", userInput);
                    scanf(" %s", nextWord);
                }

            }
            while(inDictionaryNxt == 0){//checking to see if word is in dictionary
                if(strcmp(nextWord, exit) == 0){
                    computerGenSol();
                    return;
                }
                else{
                    for(int i=0; i<numChosenWords; i++){
                        if(strcmp(nextWord, theWords[i]) == 0){
                            inDictionaryNxt=1;
                            break;
                        }
                    }
                }
                if(inDictionaryNxt == 0){
                    if(strcmp(nextWord, exit) == 0){
                        computerGenSol();
                        return;
                    }
                    else{
                        printf("\n%s is not in the dictionary. Please re-enter word: ", nextWord);
                        scanf(" %s", nextWord);
                    }
                }
            }
        }

        while(isOneDiff == 0){//function used to check to see if the word is only one char different from previous word
            for(int i=0; i < userInput; i++){
               if( (strchr(nextWord, userWord[i]) == NULL)){
                    difference++;
                }
            }
            if(difference > 1){
                difference = 0;
                printf("\nPlease enter a word that is one char differnt: ");
                if(strcmp(nextWord, exit) == 0){
                    computerGenSol();
                    return;
                }
                else{
                    scanf(" %s", nextWord);
                }
            }
            else{
                isOneDiff = 1;
                difference = 0;
            }
        }

        isOneDiff = 0;

        strcpy(userWord, nextWord);
        pathCount++;

        if(strcmp(userWord, endWord) == 0){
            break;
        }
        printf("%d. Previous word is '%s'.  Next word: ", pathCount, userWord);
        scanf(" %s", nextWord);
    }
    printf("Congrats! You found a winning path\n");
}




int main() {

    displayInfo();

    int numChosenWords=0;
    int numberOfWords=0;
    char ** theWords;
    int userInput=0;
    char startWord[81];
    char endWord[81];

    srand(time(NULL));//used in randomize function

    numChosenWords = numberOfWordsInFile(userInput, numberOfWords);

    theWords = (char **) malloc( sizeof( char *) * numChosenWords); //veritcal size of array

    for(int i=0; i < numChosenWords; i++){
        theWords[i] = (char *) malloc( sizeof( char) * userInput);//horizontal size of array
    }

    populateArr(theWords, numChosenWords, userInput, numberOfWords);
    startAndEndWord(theWords, numChosenWords, userInput, startWord, endWord);
    userPath(theWords, startWord, endWord, numChosenWords, userInput);
}
