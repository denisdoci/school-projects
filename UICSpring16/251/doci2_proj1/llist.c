#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  return l;
}

void lst_free(LIST *l) {
NODE *p = l->front;
NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}

void lst_print(LIST *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}

//helper function for lst_print_rev
//this simply creates a recursion 
void lst_recursion(NODE*p)
{
    if (p == NULL)
        return;

    lst_recursion(p->next);
    printf(FORMAT, p->val);
}

/**
* TODO:  print in reverse order 
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
void lst_print_rev(LIST *l) {
	printf("[");
	lst_recursion(l->front);
	printf("]\n");
}

void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;
}

void lst_push_back(LIST *l, ElemType val) {
NODE *p;

  if(l->back == NULL)   // list empty - same as push_front
	lst_push_front(l, val);
  else {  // at least one element before push
	p = malloc(sizeof(NODE));
	p->val = val;
	p->next = NULL;
	l->back->next = p;

	l->back = p;  
  }
}


int lst_length(LIST *l) {
NODE *p = l->front;
int n=0;

  while(p != NULL) {
    n++;
    p = p->next;
  }
  return n;
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
}


/** TODO
 *    function:  lst_count
*     description:  Counts number of occurrences 
*     		of x in the list and returns 
*     		that value.
*/
int lst_count(LIST *l, ElemType x) {
   NODE *p = l->front;
   int count = 0;
   while(p!=NULL){
	if(p->val == x)
	  count++;
	p = p->next;      
   }
   return count; 
}


/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/

int lst_sanity1(LIST *l) {
  if(l->front == NULL && l->back != NULL){
	fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
	return 0;
  }
  if(l->back == NULL && l->front != NULL){
	fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
	return 0;
  }
  return 1;
}

int lst_sanity2(LIST *l) {
  if(l->back != NULL && l->back->next != NULL) {
	fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
	return 0;
  }
  return 1;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l) {


  printf("lst_sanity3 not implemented\n");


  return 1;
}



ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
 

  if(lst_is_empty(l))
	return DEFAULT;   // no-op

  ret = l->front->val;
  
  if(l->front == l->back) {  // one element
	free(l->front);
	l->front = NULL;
	l->back = NULL;
  }
  else {
	p = l->front;  // don't lose node being deleted
	l->front = l->front->next;  // hop over
	free(p);
  }
  return ret;
}

     
  


/* TODO 
*    
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l) {
 
 NODE *p = l->front;
 ElemType retval;

 //case list is empty
 //returns a zero 
 if(lst_length(l) == 0)
        return DEFAULT;

 //case there is only one node in the list
//returns that value and pops value
 else if(lst_length(l) == 1)
 {
    retval=l->front->val;
    free(l->front);
    l->front = NULL;
    l->back = NULL;
    return retval;
 }
//case list nodes > 1
 else{
   while(p->next != l->back){
     p = p->next; //iterate to find next to last value
   }
   retval= l->back->val; //get return value of last node
   l->back = p; //pop last node off the list
   return retval;       
 }
 
} 

/* TODO
*  For full credit, you cannot allocate any new memory!
*
* description:  self-evident
*/
void lst_reverse(LIST *l) {
  NODE * res=NULL;  
  NODE * nex;
  NODE * cur;
  //if list is empty or has only one node
  //there is no need to reverse it
  if(lst_length(l) == 0 || lst_length(l) == 1)
     return;
  
  //case that there is only 2 nodes in the list
  //directly reverse front and back
  else if(lst_length(l) == 2){
     cur = l->front;
     l->front = l->back;
     l->back = cur;
  NODE * ddtemp; 
  }
  
   else{
    l->back=l->front;
    cur = l->front;
    while(cur != NULL){
      nex = cur ->next;
      cur->next = res;
      res = cur;
      cur = nex;
    }
   l->front = res;
  }

}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
NODE *p;
NODE *tmp;

  if(l->front == NULL) return 0;
  if(l->front->val == x) {
	lst_pop_front(l);
	return 1;
  }
  // lst non-empty; no match on 1st elem
  p = l->front;

  while(p->next != NULL) {
     if(x == p->next->val) {
	tmp = p->next;
	p->next = tmp->next;
	if(tmp == l->back) 
	    l->back = p;
	free(tmp);
	return 1;
     }
     p = p->next;
  }
  return 0;
}




int lst_remove_all_slow(LIST *l, ElemType x) {
int n=0;
  while(lst_remove_first(l, x))
	n++;
  return n;
}

/** EXERCISE SAVED FOR LECTURE DISCUSSION
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that 
 * the above function takes quadratic time to remove
* all occurrences of a specified value. 
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {

	return NULL;

}

/** EXERCISE SAVED FOR LECTURE DISCUSSION
**/
int lst_remove_all_fast(LIST *l, ElemType x) {
  return 0;
}

// TODO
int lst_is_sorted(LIST *l){
  
  NODE * p;
  p = l->front;
  if(lst_length(l) == 0 || lst_length(l) == 1)
     return 1; 
  else{
    while(p->next!=NULL){
    if(p->val > p->next->val){
      return 0;
    }
    p = p->next;
    }
    return 1;
  }
}



/** TODO
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {

  NODE * prev;
  NODE * temp = NULL; 
  NODE * newNode;

  newNode = malloc(sizeof(NODE));
  newNode->val = x;
  newNode->next = NULL;
  
  if(lst_length(l)==0)
  {
   lst_push_front(l,x);
  }
  else{
  if(x <  l->front->val){
    newNode-> next = l->front;
    l->front = newNode;
  }
  else{
  temp = l->front;
    while(temp->next != NULL && temp->val < x) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
   } 
 }
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.  
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted, 
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 * 
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
void lst_merge_sorted(LIST *a, LIST *b){
  NODE * curr;
  NODE * next;
  ElemType data;
 
  if(a->front == NULL && b->front == NULL){
  a->front = b->front;
  }
  
  else if(b->front == NULL) 
    return;
  
  else if(a->front == NULL){
    a->front = b->front;
    b->front = NULL; 
  } 
  
  else{
    a->back->next = b->front;
    NODE * bp = b->front;
    while(bp != NULL){
    
    lst_push_back(a, bp->val);
    bp = bp->next;

    } 
    curr = a->front;
    next = a->front->next;
    while(next != NULL)
	{
      	  if(curr->val > next->val){
	    data = curr->val;
	    curr->val = next->val;
	    next->val = data;
	  }
	next = next-> next;
	curr = curr -> next;
	}
  }
}

/**
*
* function:  lst_clone
*
* description:  makes a "deep copy" of the given list a
*   and returns it (as a LIST pointer).
*
*/
LIST * lst_clone(LIST *a) {
  
  NODE *p;
  NODE *q;

  LIST *l = malloc(sizeof(LIST));
  
  if(lst_length(a)==0){
    l->front=NULL;
    l->back=NULL;
    return l;
  }
  
  else{
  l->front=NULL;
  l->back=NULL;
  p = a->front;
  while(p != NULL)
  {
    lst_push_back(l, p->val);
    p = p->next;
  }
  return l;
  }

}



/**
*
* function:  lst_from_array 
*
* description:  creates a new list populated with the
*      elements of array a[] in the same order as 
*      they appear in a[] (element at a[0] will be the
*      first element in the list and so-on).  List is
*      returned as a LIST pointer.
*
*      Parameter n indicates the length of the given array.
*
* runtime requirement:  THETA(n)
*/
LIST * lst_from_array(ElemType a[], int n){
  LIST *l = malloc(sizeof(LIST));
  l->front=NULL;
  l->back=NULL;
  int i;
  
  if(n==0)
  return l;

  for(i=0;i<n;i++){
  lst_push_back(l, a[i]);
  }
  return l;

}


/**
*
* function:  lst_to_array 
*
* description:  allocates an array of ElemType and populates
*         it with the elements in the given list (as with
*         lst_from_array elements are in the same order in
*         both data structures).
*
* runtime requirement:  THETA(n)
*
*/
ElemType * lst_to_array(LIST *lst) {
  
  ElemType *arr;
  NODE *p = lst->front;
  int count=0;

  while(p!=NULL)
  {
  count++;
  p=p->next;
  }
  p=lst->front;
  arr = malloc(sizeof(ElemType)*count);
  int i;
  for(i=0; i<count;i++)
  {
    arr[i]=p->val;
    p=p->next;
  }
  return arr;
}


/**
*
* function:  lst_prefix
*
* description:  removes the first k elements from the
*               given list which are used to form a new list
*		which is then returned.
*
*		if n is the length of the given list, we have the
*		following boundary conditions:
*
*		  if k==0:
*			lst unchanged and an empty list returned
*		  if k>=n:
*			lst becomes empty and a list containing
*			all elements previously in lst is returned.
*
*		examples:
*
*		  EX1:  lst:  [2, 3, 9, 7, 8]
*			k:    3
*
*			after call:
*			   lst:  [7, 8]
*			   returned list:  [2, 3, 9]
*
*		  EX2  lst:  [2, 3, 9, 7, 8]
*			k:    0
*
*			after call:
*			   lst:  [2, 3, 9, 7, 8]  (unchanged)
*			   returned list:  []
*
*		  EX3  lst:  [2, 3, 9, 7, 8]
*			k:    5
*
*			after call:
*			   lst:  []
*			   returned list:  [2, 3, 9, 7, 8]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) worst case where n is the length of the given list
*
*       ORDERING:  the ordering of the returned prefix should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*/
LIST * lst_prefix(LIST *lst, unsigned int k) {

  LIST *l = malloc(sizeof(LIST));
  NODE *p = lst->front;
  int count = 0;

  l->front = lst->front; 
  if(lst_length(lst)==0)
 	return l; 
   
  if(k>lst_length(lst)){
    l->front = lst->front;
    lst = NULL;
    return l; 
  
  }
  if(lst_length(lst)==1)
  {   
   while(count<=k){
   p=p->next;
   count++;
  }
   l->front = p;
   return l;


  }
 
   while(count<k-1){
   p=p->next;
   count++;
  }
   lst->front = p;
   l->back=lst->front;
   lst->front= lst->front->next;
   l->back->next=NULL;
   return l;
}




/**
*
 function:  lst_filter_leq
*
* description:  removes all elements of the given list (lst) which
*		are less than or equal to a given value (cutoff)
*		
*		A list containing the removed elements is returned.
*
* examples:
*
*	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
*		cutoff:  4
*
*		after call:
*			lst:  [9, 8, 12, 7]
*			returned list:  [4, 2, 4, 3]
*
*       -----------------------------------------
*	EX2: 	lst:  [6, 5, 2, 1]
*		cutoff:  6
*
*		after call:
*			lst:  []
*	 		returned list:  [6, 5, 2, 1]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) where n is the length of the given list
*
*       ORDERING:  the ordering of the returned list should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*			
*/
LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
  LIST *l = malloc(sizeof(LIST));
  l->front=NULL;
  l->back=NULL;
  return l;
}

/**
* TODO
* function:  lst_concat
*
* description:  concatenates lists a and b; resulting
*    concatenation is reflected in list a; list b becomes
*    empty.
*
*    example:
*
*	EX1:  a: [2, 9, 1]
*	      b: [5, 1, 2]
*
*	after call:
*
*		a: [2, 9, 1, 5, 1, 2]
*		b: []
*
* REQUIREMENTS:  
*
*     runtime:  O(1)
*
*     sanity:  this operation makes sense when a and b
*		are distinct lists.  For example, we don't
*		want/allow the caller to do something like
*		this:
*
*			LIST *my_list;
*
*			lst_push_front(my_lst, 4);
*			lst_push_front(my_lst, 2);
*
*			lst_concat(my_lst, my_lst);
*
*		your implementation must detect if it is being
*		called this way.  If so the function does nothing
*		and (optionally) prints an error message to
*		stderr.
*	
*/
void lst_concat(LIST *a, LIST *b) {
  if(a->front == NULL && b->front == NULL){
  a->front = b->front;
  }

  else if(b->front == NULL)
    return;

  else if(a->front == NULL){
    a->front = b->front;
    b->front = NULL;
  } 

  else{
    a->back->next = b->front;
    NODE * bp = b->front;
    while(bp != NULL){

    lst_push_back(a, bp->val);
    bp = bp->next;

    }
    }
}
