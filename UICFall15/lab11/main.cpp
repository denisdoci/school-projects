/**
 * Topic: recursion
 *
 * There are 3 simple recursion problems for you to solve during the lab. Theoretically, any recursion problem
 * could be converted into iterative fashion. Although some of these problem could be easily implement iteratively,
 * to train yourself with the sense of recursion, you need to write the recursion version to get points in this lab.
 * Each problem worth one point, you are free to decide which one you want to do first, though they are put in the
 * increasing order of difficulty (it is subjective).
 *
 * 1. Reverse array
 * Design a function with exactly the signature and return type as below:
 * // numbers[] : the array you need to reverse
 * // leftIndex and rightIndex : the indexes of the element you want to swap
 * void reverseArray (int numbers[], int leftIndex, int rightIndex)
 *
 * Example:
 * Input: int array -->  1, 2, 3
 * Output: int array --> 3, 2, 1
 *
 * 2. Count how many times a key value is found in an array of numbers.
 * Design a function with exactly the signature and return type as below:
 * // numbers : the array you want to tranverse to count key
 * // size : the range of the array you want to count. Given size, you want to traverse from 0 - (size-1) to count number of key
 * // &count : count is pass by reference, so that you could modify count, do not need to return in the function. (You do not have to do in this way,
 *    of course you could return the count, but we make in this way on purpose, so that you could practice pass by reference)
 * void count(int numbers[], int size, int key, int &count)
 *
 * 3. Fibonacci number
 * Fibonacci number wiki : https://en.wikipedia.org/wiki/Fibonacci_number
 * Design a function with exactly the signature and return type as below:
 * // index : the index of Fibonacci number sequence
 * int fib(int index)
 * Start from index 0, Fibonacci number are: 1, 1, 2, 3, 5, 8 ...
 * So fib(0) = 1, fib(1) = 1, fib(2) = 2, fib(3) = 3, fib(4) = 5 ...
 * And it has property that fib(n) = fib(n - 1) + fib(n - 2)
 * Think about how do you design base case and general case.
 */

#include <iostream>
#include <stdlib.h>

using namespace std;


//TODO 1:
void reverseArray(int number[], int leftIndex, int rightIndex) {

    int temp = number[0];

    number[0] = number[rightIndex];
    number[rightIndex] = temp;

    if (rightIndex > leftIndex)
    {
        reverseArray(number, leftIndex + 2, rightIndex-2);
    }
}

//print the numbers in the integer array
void print(int number[], int size) {
    printf("\n\n");

    //calculate the size of the array
    for (int i = 0; i < size; i++) {
        printf("%d ", number[i]);
    }
    printf("\n");
}


//TODO 2:
void countKey(int numbers[], int size, int key, int index, int &count) {
    if(size == index){
        return;
    }
    else{
        if(numbers[index] == key){
            count++;
        }
    }
    countKey(numbers, size, key, index+1, count);
}

//TODO 3:
int fib(int index) {
    if (index==0)
        return 0;
    else if (index==1)
        return 1;
    else
        return (fib(index-1)+fib(index-2));

}


int main() {
    int numbers[] = {1, 2, 3, 5, 7, 9};
    int rightIndex=5;
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int leftIndex=0;
    int count=0;
    int index=0;
    int key=0;


    print(numbers, size);
    reverseArray(numbers,leftIndex, rightIndex);
    print(numbers, size);

    cout << "What would you like to count today: ";
    scanf(" %d", &key);

    countKey(numbers, size, key, index, count);

    cout << "\n";

    printf("The number %d occurs %d times\n", key, count);


    int n, c;

    printf("Enter the number of terms\n");
    scanf("%d",&n);

    printf("First %d terms of Fibonacci series are : \n",n);

    for ( c = 1 ; c <= n ; c++ ){
        printf("%d\n",fib(index));
        index++;
    }
}




