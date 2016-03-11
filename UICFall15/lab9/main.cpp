/*

 Lab 9: Amazon music service - Using Dynamic Arrays

 In this lab, you will learn to use "dynamic arrays"

 The problem
 ============

 Amazon music service was launched recently. As a promotional
 offer, they allow users to upload unlimited how_many_times_played_dyn of songs to their
 online music library. However, after a year, they restrict
 the how_many_times_played_dyn of free songs to 10. In addition to promotion, Amazon has
 pre-loaded 10 popular songs to the user library.

 So, ideally, you would like to store as many songs as you like, in your library,
 during the promotional offer and then reduce your library to hold only 10 songs.

 In this lab, we will implement a modified version of your Amazon music library.
 We will not store any information about the actual song like title, artists etc.
 Instead, we will store how many times a song was played

 What is given
 ==============

 You are given an integer array containing, randomly intitalized
 how_many_times_played values for 10 popular songs that
 Amazon pre-loaded to your account.

 What you have to to do
 ======================

 Download the starter file given as an attachment.

 1. Create and intialize a dynamic array how_many_times_played_dyn
 and copy the contents of how_many_times_played to it ( 0.5 points )

 2. Implement the grow function ( 0.5 points )
 a. Ask the user how many songs he/she wants to add
 b. Randomly choose values for "how many times played" for those many songs
 and add it to the how_many_times_played_dyn array

 3. Implement the shrink function ( 1 point )
 a. Shrink the how_many_times_played_dyn to contain only
 the first 10 elements

 4. Implement the shrink_sorted function ( 1 point ) - Extra Credit
 a. Sort the how_many_times_played_dyn array in descending order
 b. Shrink the array to contain only the first 10 elements

 */

#include <iostream>
#include <stdlib.h>

using namespace std;

// Display the dynamic array

void displayArray( int theArray[], int size)
{
    cout << "\n";

    for( int i=0; i<size; i++) {
        cout << theArray[ i] << " ";
    }
    cout << "\n";
}


// 2. Implement the grow function

void grow(int how_many_times_played_dyn[], int how_many_times_played[], int size){

   int growth;
   cout << "\nHow many items would you like to grow the array by??\n";
   cin >> growth;

   how_many_times_played_dyn = (int*)realloc(how_many_times_played_dyn, sizeof(int) * (size+growth));
   cout << "Grown array is: ";

   for(int i = (size); i<(size+growth); i++){
       how_many_times_played_dyn[i] = how_many_times_played[random() % 10];
   }
   displayArray(how_many_times_played_dyn, size+growth);


}


// 3. Implement the shrink function

void shrink(int how_many_times_played_dyn[], int size){

    how_many_times_played_dyn = (int*)realloc(how_many_times_played_dyn, sizeof(int) * (size));
    cout << "Shrunk array is: ";
    displayArray(how_many_times_played_dyn, size);

}

void sort(int how_many_times_played_dyn[], int size){

int i;
int j;
int a;

cout << "Sorted array is :";
for (i = 0; i < size; ++i)
   {
       for (j = i + 1; j < size; ++j)
       {
           if (how_many_times_played_dyn[i] < how_many_times_played_dyn[j])
           {
               a = how_many_times_played_dyn[i];
               how_many_times_played_dyn[i] = how_many_times_played_dyn[j];
               how_many_times_played_dyn[j] = a;
           }
       }
   }
displayArray(how_many_times_played_dyn, size);

}
// 4. Implement the shrinkSorted function

void shrinkSorted(int how_many_times_played_dyn[], int size){
    how_many_times_played_dyn = (int*)realloc(how_many_times_played_dyn, sizeof(int) * (size));
    cout << "Shrunk array is after sorting is: ";
    displayArray(how_many_times_played_dyn, size);
}



int main(){

    int how_many_times_played[10]; // Contains the pre-loaded songs
    int size = 10;
    int* how_many_times_played_dyn = (int*)malloc(sizeof(int) * size); // Dynamic array


    for (int i=0; i<size; i++) {
        how_many_times_played[i] = rand() % 10; // Randomly intitializing values of how_many_times_played
    }

    cout << "Original array is: ";
    displayArray( how_many_times_played, 10);

    for(int i=0; i < 10; i++){
        how_many_times_played_dyn[i] = how_many_times_played[i];
    }

    // 2. Grow the array

    grow(how_many_times_played_dyn, how_many_times_played, size);

    // 3. Shrink the array

    shrink(how_many_times_played_dyn, size);

    // Extra credit
    grow(how_many_times_played_dyn, how_many_times_played, size);
    sort(how_many_times_played_dyn, size);
    shrinkSorted(how_many_times_played_dyn, size);


    return 0;
}


