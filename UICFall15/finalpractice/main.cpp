#include <iostream>

using namespace std;

struct Node{
    int data;
    Node * pNext;
};

void fcn31a(Node * pHead)
{
    while( pHead != NULL){
        cout << pHead->data << " ";
        pHead = pHead ->pNext;
    }
}

Node * fcn31( Node * pHead)
{
    Node *pTemp;

    if(pHead->pNext == NULL){
        return pHead;
    }
    else{
        pTemp = fcn31(pHead->pNext);
        pHead -> pNext ->pNext = pHead;
        return pTemp;
    }
}

int main()
{
    int number = 0;
    Node *pHead = NULL;
    Node *pTemp;

    cout << "Enter numbers, then -1: ";

    while( number != -1){
        cin >> number;
        if(number != -1){
            pTemp = new Node;
            pTemp -> data = number;
            pTemp ->pNext = pHead;
            pHead = pTemp;
        }
    }
    pTemp = pHead;
    pHead = fcn31(pHead);
    fcn31a( pHead);
}


