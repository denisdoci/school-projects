
/* Lab 8: Arrays of Structs Again
 *
 * In this lab, you will have more practice about arrays of structs.
 * We have a database contains peoples' genders, first and last names, their ranking for beach, food, and travel.
 * Your mission is to find the closest match for the user.
 * The closest match is the people whose sum of rankings for beach, food, and travel is the closest to the the user's.
 *
 *
 * 1 point:
 * Complete the struct to make the array definition we've given in main() work correctly.
 * Complete the "displayList" function to display the list of all people
 *
 * 2 points:
 * According to the user input, find the first closest match from the database and display it.
 * If there are more than one closest match in the database, simply choose the first one.
 *
 * 3 points:
 * If there are more than one closest match in the database, display all of them.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int NAME_LENGTH = 50;

// Complete the struct so that the array definition we've given in main() works correctly.
typedef struct Person_struct{
    char gender;
    char name[NAME_LENGTH];
    char lastname[NAME_LENGTH];
    int beach;
    int food;
    int travel;
}Person;


// Implement the function to display the list of all people
// Note: You need to pass parameters to the function
// pass "Person allPeople[10]" as the first parameter
void displayList(Person allpeople[10], int numPeople) {
    for(int i = 0; i < numPeople;  i++){
        printf("\nName %s %s, Gender %c\n", allpeople[i].name, allpeople[i].lastname, allpeople[i].gender);
        printf("Intrest in beach %d\n",allpeople[i].beach);
        printf("Intrest in food %d\n", allpeople[i].food);
        printf("Intrest in travel %d\n", allpeople[i].travel);
    }
}


// Implement the function to find the first closest match
// Note: You need to pass parameters to the function
// TODO :
// 1. pass "Person allPeople[10]" as the first parameter
// 2. When you found the best match person for user, return the index of that person for future use
//int findMatch("pass allPeople list here", int numPeople, char gender, int beach, int food, int travel) {

// Add your code here
// ...
void closestMatch(Person allpeople[10], int numpeople, char gr, int br, int fr, int tr){

    int i;
    int j;
    int closeness_score[10];
    int temp;
    Person temp1;


    for(i=0; i < numpeople; i++){
        closeness_score[i] = (abs(br-allpeople[i].beach) +
                              abs(fr-allpeople[i].food)+
                              abs(tr-allpeople[i].travel));
    }

    for(i=0; i<numpeople-1; i++){
        j = 0;
        if (closeness_score[i] > j){
           j = i;
        }

    }

            printf("\nThe closest match was %s %s\n", allpeople[j].name, allpeople[j].lastname);


}


int main(){

    // Define the struct array
    // Each entry is gender(M,F), firstName, lastName, beach interest, food interest, travel interest.
    // We hard-code the explicit array declaration with 10 different entries as the database.
    // You will create the struct so that the array definition we've given works correctly.
    Person allPeople[10] = { {'M', "Tom", "Cruise", 4, 5, 3},
                             {'F', "Jennifer", "Aniston", 2, 5, 4},
                             {'F', "Julia", "Roberts", 5, 4, 1},
                             {'M', "Johnny", "Depp", 2, 4, 3},
                             {'F', "Angelina", "Jolie", 3, 5, 4},
                             {'M', "Brad", "Pitt", 4, 3, 2},
                             {'M', "Leonardo", "DiCaprio", 5, 2, 3},
                             {'F', "Jennifer", "Lawrence", 4, 1, 2},
                             {'M', "Tom", "Hanks", 1, 5, 3},
                             {'F', "Natalie", "Portman", 3, 2, 1} };


    /****************** Credit: 1 point ******************/
    // Displays the list of all people
    printf("\nDisplays the list of all people: \n");
    displayList(allPeople, 10);
    // ...
    /*****************************************************/


    /****************** Credit: 2 points ******************/
    // Get the user input
    char g;  // gender
    int br, fr, tr;  // beachRank, foodRank, and travelRank

    printf(" \nChoose your interest in gender (M or F): ");
    scanf(" %c", &g);

    printf(" \nChoose your interest in 'Walking on the beach' (1 to 5): ");
    scanf(" %d", &br);

    printf(" \nChoose your interest in 'Eating ethnic food' (1 to 5): ");
    scanf(" %d", &fr);

    printf(" \nChoose your interest in 'Traveling' (1 to 5): ");
    scanf(" %d", &tr);

    // Read and understand the definition of closeness score, if you do not understand raise your hand and ask for help.
    // Implement the function findMatch(), and call it here to find the first closest match
    // ...

    // Display the first closest match
    closestMatch(allPeople, 10, g, br, fr, tr);
    // ...
    /*******************************************************/


    /*************** Extra Credit: 3 points ***************/
    // If there are more than one closest match, display all of them.
    printf(" \nAll of the closest matches are: \n");
    // Add your code here to find all the closet matches and display them
    // ...
    /******************************************************/

    return 0;
}
