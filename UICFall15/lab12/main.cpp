/*

Lab 12
-------


In the lab we will learn to manipulate Linkedlists

Download the starter code and follow the instructions given below

Given
-----

A linkedlist  1 -> 3 -> 5 -> 7 -> 99

Tasks
-----

1. Complete the function displayBiggerThanNum - 1 point

Here we will try to find the number that is stored AFTER a given number
in the list. Follow the instructions below to complete this part.

- prompt the user for a number greater than 1 and lesser than 99
- get the number from the user and store it in a variable 'n'
- Traverse through the linked list till you see 'n'
- Print the number in the list that is stored after 'n'
s

2. Complete the function insertNth - 1 point

This function will insert an element after the nth element in the list.
for eg:
for the given list (above), calling this with:
       insertNth( pHead, 6, 3);
    would insert a new node with value 6, after the 3rd node, changing the list to now be:
       1 -> 3 -> 5 -> 6 -> 7 -> 99

So, you will,
- Traverse through the list until you reach the nth position
- insert the given element (be careful with the pointer assignments)

3. (Challenge problem) - 1 point
Given a list and only a pointer to some node in the middle of the list (with elements guaranteed to be after it), write the code to delete this node.  Call this with:
       deleteNode( Node *pCurrent)
    Note that here we are NOT sending the head of the list, ONLY a pointer to the node to be delete.  Is this, in fact impossible?  (Nianzu saw this as an interview question!)  Idea: copy the next node into the current node, then delete the next node!)

*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *nextPtr;
};

// Display the linked list
void displayList( Node *head)
{
    //cout << "in display list" << endl;
   Node *tempPtr = head;  // Used to traverse list without destroying head
   cout << "\n List contains: ";
   while( tempPtr != NULL) {
      cout << tempPtr->data << " ";
      tempPtr = tempPtr->nextPtr;
   }
   cout << "\n\n";
}

// Creates the initial list

void makeList(Node *&head, int arr[]) {
    Node *tempPtr;
    Node *last = NULL;
    head = new Node;

    head -> data = arr[0];
    head -> nextPtr = NULL;
    last = head;
    //
    for(int i=1 ; i < 5; i++){
        tempPtr = new Node;
        tempPtr -> data = arr[i];
        tempPtr -> nextPtr = NULL;
        last -> nextPtr = tempPtr;
        last = tempPtr;
    }

}

//Question 1

void displayBiggerThanNum(Node *head) {
        int number;
        // Assume that the list is sorted
        cout<<"Please choose a number: ";
        cin>>number;

        while(head !=NULL)
        {

          if(head->data >number)
          {
              printf("Number bigger: %d\n",head->data);
          }

          head = head->nextPtr;
        }


}

// Question 2

void insertNth( Node *pHead, int value, int nthPosition){

    int count = 1;
    Node *pTemp;
    while(pHead != NULL)
    {
        if(count == nthPosition)
        {
            pTemp = new Node;
            pTemp->data = value;
            pTemp->nextPtr = pHead ->nextPtr;//this will make pointer of 6 point to the next number which is 6
            //pHead -> nextPtr will point from 6 to 7 the next number
            pHead->nextPtr = pTemp;//the next node will point from 5 to 6
            break;

        }
        count++;
       pHead = pHead ->nextPtr;
    }

}

// Question 3
void deleteNode( Node *&pCurrent) {
Node *pTemp;
pCurrent->data = pCurrent->nextPtr->data;
pTemp = pCurrent->nextPtr;
pCurrent->nextPtr = pCurrent->nextPtr->nextPtr;
delete pTemp;

}

int main() {


    // Make the initial list
    int arr[] = {1,3,5,7,99};
    Node *head = NULL;
    makeList(head, arr);
    cout << "Original List\n";
    displayList(head); // Displaying the list

    // Question 1
    displayBiggerThanNum(head);

    //Question 2
    insertNth(head, 6, 3);
    cout <<"List after insertion\n";
    displayList(head); // Displaying the list

    //Question 3

    int n = 3;
    Node *middleNode;
    int c = 0;
    middleNode = head;
    while( c < n){
        middleNode = middleNode -> nextPtr; // middle node
        c++;
    }

    cout << "List after deleting the node in the middle \n";
    deleteNode(middleNode);
    displayList(head);


}
