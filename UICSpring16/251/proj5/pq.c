#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

typedef enum {min=1, max=0} type; //heap type could be a min or max heap

typedef struct node{
  int id;
  int pos;
  double priority;
}NODE;

typedef NODE * NODEPTR;

struct pq_struct {
  int size;
  int capacity;
  NODEPTR * heap; //double pointer
  NODEPTR * ids;  //ids double pointer to ensure runtimes
  type  htype;
};

//helper function for ids create
NODEPTR node_init(int id) {
    NODEPTR tmp = malloc (sizeof(NODE));
    tmp->id = id;
    tmp->priority = 0;
    tmp->pos=-1;
    return tmp;
}


//helper function for create
NODEPTR * ids_init(PQ * pq){

  NODEPTR *array =  malloc(sizeof(NODEPTR) * (pq->capacity+1));
  int size = pq->capacity;
  int i;
  for(i=0; i<size; i++){
    array[i+1] = node_init(i);
  }
  array[0]=NULL;
  return array;

}

//helper function for create
NODEPTR * heap_init(PQ * pq){

  NODEPTR *array =  malloc(sizeof(NODEPTR) * (pq->capacity+1));
  int size = pq->capacity;
  int i;
  for(i=0; i<size; i++){
    array[i+1] = NULL;
  }
  array[0] = NULL;
  return array;

}


/**
 * Function: pq_create
 * Parameters: capacity - self-explanatory
 *             min_heap - if 1 (really non-zero), then it is a min-heap
 *                        if 0, then a max-heap
 *
 * Returns:  Pointer to empty priority queue with given capacity and
 *           min/max behavior as specified.
 *
 */
PQ * pq_create(int capacity, int min_heap){

  PQ * pq = malloc(sizeof(struct pq_struct));
  pq->capacity = capacity;
  pq->htype = (min_heap ? min : max);
  pq->size = 0;
  pq->heap = heap_init(pq);
  pq->ids = ids_init(pq);
  return pq;

}


/**
 * Function: pq_free
 * Parameters: PQ * pq
 * Returns: --
 * Desc: deallocates all memory associated with passed priority
 *       queue.
 *
 */
void pq_free(PQ * pq){

  int i;
  int capacity = pq->capacity;
  for(i=0; i<capacity; i++){
    NODEPTR r = pq->ids[i+1];
    free(r);
  }

  free(pq->ids);
  free(pq->heap);
  free(pq);
}


//check to see if the id is within bounds
int withinBounds(PQ * pq, int id){
  if(pq==NULL || id<0 || id>pq->capacity || pq->ids[id+1]-> pos == -1) return 0;
  return 1;
}

//helper function for contains
int containsHelper(PQ * pq, int id, double * priority){
  
  if(!withinBounds(pq,id)) 
  return 0;

  if(priority != NULL) (*priority) = pq->ids[id+1]->priority;
  return 1;

}

//get parent of given node
NODEPTR getpar(PQ * pq, NODEPTR r){
  if(r==NULL) return NULL;
  int parpos = r->pos/2;
  if(parpos > 0) return pq->heap[parpos];
  else return NULL;

}

//peroclate up function: O(logn)
int percolateup(PQ * pq, NODEPTR r){

  NODEPTR par;
  par = getpar(pq,r);
  if(par==NULL || (pq->htype == min && par->priority <= r->priority) 
	     || (pq->htype == max && par->priority >= r->priority)){
    return 1;
}
  int pospar=par->pos;
  pq->heap[pospar]=r;
  pq->heap[r->pos]= par;
  par->pos = r->pos;
  r->pos = pospar;
  return percolateup(pq,r);
}


//get left child: helper for perec down
NODEPTR getLeft(PQ * pq, NODEPTR r){

  if(r==NULL) return NULL;
  int posL = r->pos*2;

  if(posL < 1 || posL > pq->size)
	return NULL;
  else 
	return pq->heap[posL];

}


//get right child: helper for perc down
NODEPTR getRight(PQ * pq, NODEPTR r){

  if(r==NULL) return NULL;
  int posR = r->pos*2+1;

  if(posR < 1 || posR > pq->size)
        return NULL;
  else
        return pq->heap[posR];
}


/*
 *percolate down
 *O(logn)
 */
int percolatedown(PQ * pq, NODEPTR r){

  NODEPTR left =  getLeft(pq,r);
  NODEPTR right = getRight(pq,r);
  NODEPTR swp;

  if(left == NULL && right == NULL) return 1;
  else if ( left == NULL || right == NULL){
    if(left == NULL) swp = right;
    else swp = left;
  }
  else{
    if(pq->htype == min){
	if(left->priority < right->priority) swp = left;
	else swp = right;
    }
    else{
      if(left->priority > right->priority) swp = left;
      else swp = right;
    }
  }
  if((pq->htype == min && swp->priority < r->priority) ||
     (pq->htype == max && swp->priority > r->priority)){
    int nextpos = swp->pos;
    pq->heap[nextpos] = r;
    pq->heap[r->pos] = swp;
    swp->pos = r->pos;
    r->pos = nextpos;
    return percolatedown(pq,r);
  }
}


/**
 * Function: pq_insert
 * Parameters: priority queue pq
 *             id of entry to insert
 *             priority of entry to insert
 * Returns: 1 on success; 0 on failure.
 *          fails if id is out of range or
 *            there is already an entry for id
 *          succeeds otherwise.
 *
 * Desc: self-explanatory
 *
 * Runtime:  O(log n)
 *
 * Runtime Completed
 *
 */
int pq_insert(PQ * pq, int id, double priority){

  if(containsHelper(pq, id, NULL) || id<0 || id>pq->capacity) return 0;
  pq->ids[id+1]->priority = priority;
  int size = ++(pq->size);
  pq->heap[size] = pq->ids[id+1];
  pq->heap[size]->pos = size;  
  percolateup(pq, pq->heap[size]); //O(logn)
  return 1;

}

/**
 * Function: pq_change_priority
 * Parameters: priority queue ptr pq
 *             element id
 *             new_priority
 * Returns: 1 on success; 0 on failure
 * Desc: If there is an entry for the given id, its associated
 *       priority is changed to new_priority and the data
 *       structure is modified accordingly.
 *       Otherwise, it is a failure (id not in pq or out of range)
 * Runtime:  O(log n)
 *
 * Runtime completed
 */

int pq_change_priority(PQ * pq, int id, double new_priority){
  if(containsHelper(pq, id, NULL) == 0) return 0;
  NODEPTR r = pq->ids[id+1];
  int temp = r->priority;
  r->priority = new_priority;
  if(new_priority == temp) return 1;
  if(pq->htype==min){
    if(new_priority < temp) percolateup(pq,r); //O(logn)
    else percolatedown(pq,r); //O(logn)
  }
  else{
    if(new_priority > temp) percolateup(pq,r); //O(logn)
    else percolatedown(pq,r); //O(logn)
  }
  return 1;
}


/**
 
 *Function: pq_remove_by_id
 
 *Parameters: priority queue pq,
 
 * element id
 
 *Returns:1 on success; 0 on failure
 
 *Desc: if there is an entry associated with the given id, it is
 
 * removed from the priority queue.
 
 * Otherwise the data structure is unchanged and 0 is returned.
 
 *Runtime: O(logn)
 
 *Runtime Requirement fufilled
 
 */
int pq_remove_by_id(PQ * pq, int id){

  if(containsHelper(pq, id, NULL) == 0) return 0;

  NODEPTR old= pq->ids[id+1];
  NODEPTR new; 

  if(pq == NULL) new = NULL; //shouldn't happen
  else new = pq->heap[pq->size];

  int oldP = old->priority;
  int newP= new->priority;
  int pos = old->pos;

  old->pos = -1;
  old->priority = 0;
  pq->heap[pos] = new;
  pq->heap[pq->size] = NULL;
  new->pos = pos;
  pq->size--;

  if(pq->htype == max){
    if(newP < oldP) percolatedown(pq, new);
    else percolateup(pq, new);
  }
  else{
    if(newP > oldP) percolatedown(pq, new);
    else percolateup(pq, new);
  }
  return 1;
}

//identical to the containsHelper function
//runtime O(1) completed
int pq_get_priority(PQ * pq, int id, double * priority){

  if(!withinBounds(pq,id))
    return 0;
  if(priority != NULL) 
    (*priority) = pq->ids[id+1]->priority;
  return 1;
    
}


//delete top function runtime completed as
//it is reliant on remove by id
int pq_delete_top(PQ * pq, int * id, double * priority){

  if(pq == NULL) return 0;
  if(id!=NULL) *id = pq->heap[1]->id;
  if(priority!=NULL) *priority = pq->heap[1]->priority;
  return pq_remove_by_id(pq, *id); //O(logn)

}


//pq contains function completed
//in O(1) runtime
int pq_contains(PQ * pq, int id){
  
  if(!withinBounds(pq,id)) return 0;
  else return 1;

}

//pq capacity function completed
//in O(1) runtime
int pq_capacity(PQ * pq){

  return pq->capacity;

}


//pq size function completed
//in O(1) runtime
int pq_size(PQ * pq){

  return pq->size;

}
