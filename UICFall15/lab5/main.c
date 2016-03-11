#include <stdio.h>
#include <string.h>

/*
 * Lab5:
 * ----
 * In today's lab, you will modify the given program
 * to search in strings using string functions.
 *
 * 1. 0.5 points:
 * --------
 *
 * Prompt the usr for a string and store the string in a
 * global character array and display the length of the string
 *
 * Sample output:
 *
 * Please enter a lower-case string (max length = 80):
 *   >all generalizations are all false
 *   Length of your input is: 33
 *
 * 2: 0.5 points:
 * -------
 * Prompt the user for a character and
 * search for the character in the string.
 *
 *
 * Sample output:
 *
 * Please enter a character that you want to find in the input string:
 *   >z
 *   Character [z] is found.
 *
 * 3: (1 point):
 * --------
 *
 * Prompt the user for a new word and search the
 * string for the word
 *
 * Sample ouput:
 *
 * Please enter a word that you want to find in the input string:
 *   >all
 *   Word [all] is found.
 *
 * 4. Extra credit ( 1 point):
 * -------------------------
 *
 * Use the word entered in the previous section and check if the word
 * is the first word in the input string
 *
 * Sample Ouput:
 * Word [all] is the first word in the input string.
 *
 */


char inputString[81]; //user's input string
char USERCHAR; //user's input character
char SEARCHWORDINSTRING[81];


/* Question 1 : 0.5 points */

void getInputString(){

    int stringlength;

    printf("\nEnter a string\n");//Prompt user string
    fgets(inputString, 81, stdin);//store input string from user
    stringlength = strlen(inputString) - 1;
    printf("\nYour string is %d long\n", stringlength);//Display the length of the input string
    inputString[strlen(inputString) - 1] = '\0';

}


/* Question 2  : 0.5 points*/
void searchCharInString(){
    printf("\nEnter a character to see if it's in the string.\n\n");  // Prompt user for a character
    scanf(" %c", &USERCHAR);
    if (strchr(inputString, USERCHAR) != NULL){
        printf ("\nFound %c in string\n", USERCHAR);
    }
    else{
        printf("\nDid NOT find %c in the string\n", USERCHAR);
    }
    // Check if the character is in inputString
}

/*Question 3  1 point */
void searchWordInString(){

    printf("\nEnter a word to see if it's in the string\n");//Prompt user for a word
    scanf("%s", SEARCHWORDINSTRING);

    if(strstr(inputString, SEARCHWORDINSTRING) != NULL){//Check if word is in the inputString
       printf ("\nFound %s in string\n", SEARCHWORDINSTRING);
    }
    else{
       printf ("\nDid NOT find %s in string\n", SEARCHWORDINSTRING);
    }
}


void isFirstWord(){
  char *p;
  int pos = 0;
  p = strstr(inputString, SEARCHWORDINSTRING);
  pos = p - inputString;
  if(pos == 0){
      printf("\n%s is the first word in the string\n\n", SEARCHWORDINSTRING);
  }
  else{
      printf("\n%s is NOT the first word in the sting\n\n", SEARCHWORDINSTRING);
  }

}



int main(void)
{

    //Main function call

    // Get Input String
    getInputString();

    // Search for a character in the input String
    searchCharInString();

    // Search for a word in the input String
    searchWordInString();

    // check if the word entered above is the first word in the intput String
    isFirstWord();


    printf("\nDone with program");

    return 0;
}

