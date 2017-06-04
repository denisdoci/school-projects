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
    int n;
};


static void set_back(LIST *lst) {
NODE *p;

  p = lst->front;

  while(p != NULL && p->next != NULL) {
	p = p->next;
  }
  lst->back = p;
}

static void set_size(LIST *lst) {
NODE *p;

  lst->n = 0;
  p = lst->front;
  while(p != NULL) {
	(lst->n)++;
	p = p->next;
  }
}

/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  l->n = 0;
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

/**
* TODO:  print in reverse order 
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
static void p_rev(NODE *p);
void lst_print_rev(LIST *l) {
  printf("[");

  p_rev(l->front);

  printf("]\n");
}

static void p_rev(NODE *p) {
  
  if(p==NULL)
	return;
  p_rev(p->next);
  printf(FORMAT, p->val);
}

void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;

  (l->n)++;
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
	(l->n)++;
  }
}

int lst_length(LIST *l) {

  return l->n;
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
NODE *p;
int  n=0;

  p = l->front;
  while(p != NULL) {
	if(p->val == x)
	  n++;
	p = p->next;
  }
  return n; 
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
  (l->n)--;
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
NODE *p;
ElemType ret;

  if(l->front == NULL)
    return DEFAULT;

  p = l->front;
  (l->n)--;
  if(p->next == NULL) {  
	// one element: front=back
	ret = p->val;
	free(p);
	l->front = NULL;
	l->back = NULL;
	return ret;
  }
  // two or more nodes
  //   find 2nd to last node
  while(p->next != l->back) {
	p = p->next;
  }
  ret = l->back->val;
  free(l->back);
  l->back = p;
  p->next = NULL;
  return ret;
} 

/* TODO
*  For full credit, you cannot allocate any new memory!
*
* description:  self-evident
*/
void lst_reverse(LIST *l) {
NODE *p;  // "previous"
NODE *c;  // "current"
NODE *nxt;  // "next"
NODE *tmp;


  if(l->n < 2) return;

  // at least 2 nodes

  p = l->front;
  c = p->next;

  p->next = NULL;  // new last element

  while(c != NULL) {
	nxt = c->next;
	c->next = p;
	p = c;
	c = nxt;
  }

  tmp = l->front;
  l->front = l->back;
  l->back = tmp;

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
NODE *p;

  if(l->n < 2)
	return 1;
  p = l->front;

  while(p->next != NULL) {
	if(p->val > p->next->val)
	    return 0;
	p = p->next;
  }
  return 1;

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
NODE *px, *p;

  p = l->front;
  if(p == NULL || x <= p->val) 
	lst_push_front(l, x);
  else {
	// walk p til x belongs right after p
	while(p->next != NULL && p->next->val < x) {
		p = p->next;
 	}
	px = malloc(sizeof(NODE));
	px->val = x;
	px->next = p->next;
	
	p->next = px;
	if(px->next == NULL)
		l->back = px;
	(l->n)++;
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

static NODE * merge_rec(NODE *a, NODE *b) {

  if(a==NULL)
	return b;
  if(b==NULL)
	return a;

  if(a->val < b->val) {
	a->next = merge_rec(a->next, b);
	return a;
  }
  else {
	b->next = merge_rec(a, b->next);
	return b;
  }
}
void lst_merge_sorted(LIST *a, LIST *b){
NODE *m;

  m = merge_rec(a->front, b->front);

  a->front = m;

  if(b->back != NULL && b->back->next == NULL)
	a->back = b->back;
  // else: original back of a also back of merged list

  a->n += b->n;
  b->n = 0;
  b->front = NULL;
  b->back = NULL;
	
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
LIST *clone;
NODE *pa, *pclone;

  clone = malloc(sizeof(LIST));

  if(a->n==0) {
	*clone = *a;
	return clone;
  }

  
  pclone = malloc(sizeof(NODE));
  clone->front = pclone;

  pa = a->front;
  pclone->val = pa->val;

  pa = pa->next;

  while(pa != NULL) {
	pclone->next = malloc(sizeof(NODE));
	pclone = pclone->next;
	pclone->val = pa->val;
	pa = pa->next;
  }

  pclone->next = NULL;
  clone->back = pclone;
  clone->n = a->n;

  return clone;

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
LIST *lst;
int i;

  lst = lst_create();

  for(i=0; i<n; i++) {
	lst_push_back(lst, a[i]);
  }


  return lst;

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
ElemType *a;
int i;
NODE *p;

  a = malloc(lst->n * sizeof(ElemType));

  i=0;
  p = lst->front;

  while(p != NULL) {
	a[i] = p->val;
	i++;
	p = p->next;
  }
  if(i != lst->n)
	fprintf(stderr, "ERROR lst_to_array(); bad length?\n");

  return a;
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
LIST *prefix;
NODE *p;
int i;

  if(k == 0)
	return lst_create();

  prefix = malloc(sizeof(LIST));

  if(k >= lst->n) {
	*prefix = *lst;
	lst->front = NULL;
	lst->back = NULL;
	lst->n = 0;
  }
  else {  // 1 <= k < n)
	prefix->front = lst->front;
	p = lst->front;
	i = 1;
	while(i < k) {
	  p = p->next;
	  i++;
	}
	// now p points to the kth node:
	//    - last node in prefix
	//    - successor is first node in suffix
	prefix->back = p;
	lst->front = p->next;
	lst->n -= k;
	prefix->n = k;
	p->next = NULL;
  }
  return prefix;


}




/**
*
* function:  lst_filter_leq
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
static NODE * filter_leq_rec(NODE **pp, ElemType cutoff); 


LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
LIST *leq = malloc(sizeof(LIST));

  leq->front = filter_leq_rec(&(lst->front), cutoff);

  set_size(leq);
  set_size(lst);
  set_back(leq);
  set_back(lst);


  return leq;

}

static NODE * filter_leq_rec(NODE **pp, ElemType cutoff){
NODE *leq;
NODE *tail,*p;

  p = *pp;
  if(p == NULL) 
	return NULL;

  tail = p->next;
  leq = filter_leq_rec(&tail, cutoff);
  if(p->val <= cutoff) {
	p->next = leq;
	*pp = tail;
	return p;
  }
  else {
	(*pp)->next = tail;
	return leq;
  }

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

  if(a->front == NULL) {
	*a = *b;
  }
  else if(b->front != NULL) {
	a->back->next = b->front;
	a->back = b->back;
	a->n += b->n;
  }
  b->front = b->back = NULL;
  b->n = 0;
}
