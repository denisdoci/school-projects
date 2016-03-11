

/*
Lab 14:

In this lab, we will have additional practise on linkedlist by
solving some common problems on linkedlist.

Download the starter code and follow the instructions to complete this lab

Tasks
-----

1. Complete the function displayListLength - 1 point

Here we will find the length of a given LinkedList

- Traverse the linkedllist from the beginning.
- Count how many nodes are there on the list
- Display the length of the list

2. Complete the function displayMiddleNode - 1 point

Given a list of even length (e.g. 2,4,6,8,etc) display the middle node.
For a list of length 4 it would be node 2 (the 2nd node).  For a list of length
6 it would be node 3 (the 3rd node).  While there are different ways to do this,
one approach is to have 2 pointers going through the list.  The "fast" pointer
advances by 2 nodes on each step, and the "slow" pointer advances by only 1 node
on each step.  When the "fast" one reaches the end, the "slow" one is at the node
we want.

3. Complete the function displayNthNodeFromEnd

Display the nth from the end node for a list of length n or greater.
E.g for the following list of length 7:  [ 4, 9, 2, 5, 9, 1, 3] the 3rd
from the end would be 9, and the 4th from the end would be 5.

 */

#include <iostream>
using namespace std;

// Struct for linked list nodes
struct Node {
   int data;
   Node *pNext;   // pointer to next Node.  In C this would be: struct Node *pNext
};


//-------------------------------------------------------------------------------------

// Question 1
void displayListLength(Node *pHead) {
    int count = 0;
    Node *pTemp = pHead;
    while(pTemp != NULL){
        count++;
        pTemp = pTemp->pNext;		// advance to next node
    }
    printf("\nThe count is : %d\n", count);
}

// Question 2
void displayMiddleNode(Node *pHead){

 Node *pFast = pHead;
 Node *pSlow = pHead;
 int middle = 0;

 while(pFast != NULL){
     pFast = pFast->pNext;
     if(pFast != NULL){
      pSlow = pSlow->pNext;
      pFast = pFast->pNext;
     }
     middle = pSlow -> data;
 }

 printf("\nThe middle node is: %d\n", middle);
}

//Question 3
void displayNthNodeFromEnd(Node *pHead, int n){

    int target = 0;
    int count = 0;
    int dum = 0;
    int tarVal = 0;
    Node *pTemp = pHead;
    Node *pTemp2 = pHead;


    while(pTemp != NULL){
        count++;
        pTemp = pTemp->pNext;		// advance to next node
    }

    target = count - n;
    while(dum < target){
         pTemp2 = pTemp2->pNext;
         dum++;
         tarVal = pTemp2 -> data;
    }

    printf("\nThe target integer is: %d\n", tarVal);

}


void displayList( Node *pHead)
{
   Node *pTemp = pHead;  // Used to traverse list.  What would happen if we used pHead instead?
   cout << "\nList contains: ";
   while( pTemp != NULL) {
      cout << pTemp->data << " ";  	// display the data at this node
      pTemp = pTemp->pNext;		// advance to next node
   }
   cout << "\n\n";
}

//append new node to the end of the list
void appendToLast( Node * &pHead, int number) {
    if (pHead == NULL) {
        Node* pTemp = new Node;
        pTemp->data = number;
        pTemp->pNext = NULL;
        pHead = pTemp;
    }else {
        //tranverse pointer to the last
        Node* cur = pHead;
        while (cur->pNext != NULL) {
            cur = cur->pNext;
        }// cur now point to the last node
        Node* pTemp = new Node;
        pTemp->data = number;
        pTemp->pNext = NULL;
        cur->pNext = pTemp;
    }
}


// build the list
void buildTheList( Node * &pHead)
{
    int number; 		   // stores user input
    Node *pTemp;		   // used to allocate new nodes

    // Prompt for numbers to be stored in linked list
    cout << "Linked list sample program, prepending to head of list. \n";
    cout << "Enter as many integers > 0 as you would like, followed by -1:  ";

    // Read in values, creating nodes as we go and prepending them to list
    while ( number != -1) {
        cin >> number;
        if (number != -1) {
            appendToLast(pHead, number);
        }
    }
}


//-------------------------------------------------------------------------------------
int main()
{
    Node *pHead = NULL;	   // keeps track of head of list
    int n;

    buildTheList( pHead);

    cout << "Back in main, list is: ";
    displayList( pHead);

    displayListLength( pHead);
    displayMiddleNode( pHead);
    printf("\nHow many integers back are you looking\n");
    scanf("%d", &n);
    displayNthNodeFromEnd(pHead, n);

    cout << "Ending Linked List program.  Exiting ...";
}

