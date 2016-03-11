// finalExamInLab.cpp
//
// There are two parts to this program, each worth 15 points.
//
// 1. Implement function  concatenateLists()  so that it takes two lists as parameters and
//    concatenates the second to the first.  Also uncomment the call to this function from
//    within main().
//    Running this part of the program should look like:
//
// 2. Implement function   createListInOrder()  so that it takes two lists as parameters.
//    It should use the first list to create the second list, where the second list has
//    all the list nodes in ascending order.
//    Running this part of the program should look like:
//
// Sample output:
/* Enter as many integers > 0 as you would like for list A, followed by -1:  1 2 3 -1
List A contains:
3 2 1  (because the node is prepended to the existing list, so the list is created in reverse order of the input)

Enter as many integers > 0 as you would like for list B, followed by -1:  4 5 6 -1
List B contains:
6 5 4  (because the node is prepended to the existing list, so the list is created in reverse order of the input)

Concatenated list contains:
3 2 1 6 5 4

All concatenated list elements in ascending order are:
1 2 3 4 5 6
*/

#include <iostream>
using namespace std;

// Struct for linked list nodes
struct Node {
    int data;
    Node *pNext;   // pointer to next Node.  In C this would be: struct Node *pNext
};


//-------------------------------------------------------------------------------------
void displayList( Node *pHead)
{
    cout << "\n";
    while( pHead != NULL) {
        cout << pHead->data << " ";  	// display the data at this node
        pHead = pHead->pNext;		// advance to next node
    }
    cout << "\n\n";
}//end displayList()


//-------------------------------------------------------------------------------------
// build the list
void prependNodeToList( Node * &pHead, int number)
{
    Node *pTemp;		   // used to allocate new nodes

    // Read in values, creating nodes as we go and prepending them to list
    if (number != -1) {
        pTemp = new Node;			// allocate a new node
        // Insert as new head of list
        pTemp->data = number;
        pTemp->pNext = pHead;
        pHead = pTemp;
    }

}//end prependNodeToList()


// build the list
void insertNodeInOrder( Node * &pHead, int number)
{
    Node *pTemp;		   // used to allocate new nodes
    Node *pTail;

    // Read in values, creating nodes as we go and prepending them to list
    if (number != -1) {
        pTemp = new Node;			// allocate a new node

        // handle case when it is first node
        if( pHead == NULL) {
            // Insert as new head of list
            pTemp->data = number;
            pTemp->pNext = pHead;
            pHead = pTemp;
            pTail = pTemp;
        }
        else {
            // there is already at least one node, and pTail points to it
            // Insert at the end of list
            pTemp->data = number;
            pTemp->pNext = NULL;
            pTail->pNext = pTemp;    // connect it into the list
            pTail = pTemp;           // advance tail pointer
        }
    }//if( number...
}//end insertNodeInOrder()


//-------------------------------------------------------------------------------------
//  Create whatever parameters you need for two lists, and write the code so that
//  the second list is concatenated onto the end of the first list.
void concatenateLists(Node * &pA, Node * &pB)
{

    Node * pTemp = new Node;
    pTemp = pA;


    while(pTemp != NULL){

        if(pTemp->pNext == NULL){
            pTemp->pNext = pB;
            break;
        }

        pTemp = pTemp -> pNext;
    }
}



//-------------------------------------------------------------------------------------
// Create whatever return type and parameters you need to catch the head of a new list.
// The effect of this function should be to create a list that has all the nodes in
// ascending order, which will then be used to print out the list from within main()
void createListInOrder( )
{

}


//-------------------------------------------------------------------------------------
int main()
{
    Node *pA = NULL;	   // head of list A
    Node *pB = NULL;       // head of list B
    Node *pC = NULL;       // head of list C
    int number;            // for user input

    // Make list A
    cout << "Enter as many integers > 0 as you would like for list A, followed by -1:  ";
    do {
        cin >> number;
        if( number != -1) {
            prependNodeToList( pA, number);
        }
    } while (number != -1);
    cout << "List A contains: ";
    displayList( pA);

    // Make list B
    cout << "Enter as many integers > 0 as you would like for list B, followed by -1:  ";
    do {
        cin >> number;
        if( number != -1) {
            prependNodeToList( pB, number);
        }
    } while (number != -1);
    cout << "List B contains: ";
    displayList( pB);

    // Uncomment the next line when implementing part 1, to concatenate pB onto the end of pA
    concatenateLists( pA, pB);
    cout << "Concatenated list contains: ";
    displayList( pA);

    // Uncomment the next line when implementing part 2, to create list pC, containing
    //    all the concatenated nodes from pA, now in ascending order
    // createListInOrder( pA, pC);
    cout << "All concatenated list elements in ascending order are: ";
    displayList( pC);

    cout << "Ending Linked List program.  Exiting ...";
}
