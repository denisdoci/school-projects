Name:   Denis Doci
	CS251
	doci2
	663855180
      

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.
-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class ans in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.  


The main difference between the heap as presented in class and the heap
for this project is the implementation of the the implementation of the IDs
as a double pointer and the double pointer of the heap nodes. The incorporation
of this was mainly to fufill runtime requirements. Instead of running 
through the list during the functions you can just access them directly.



-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?

My code for pq_insert with the new implementation is as follows:

int pq_insert(PQ * pq, int id, double priority){

  if(containsHelper(pq, id, NULL) || id<0 || id>pq->capacity) return 0;
  pq->ids[id+1]->priority = priority;
  int size = ++(pq->size);
  pq->heap[size] = pq->ids[id+1];
  pq->heap[size]->pos = size;  
  percolateup(pq, pq->heap[size]); //O(logn)
  return 1;

}

As you can see the difference is in the dirrect access to the nodes 
before the percolate function (also within). The O(logn) is within the
percolate, but the addition of the insertion is done directly before that. 


-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?

My code for delte top with my new implementations is as follows:

int pq_delete_top(PQ * pq, int * id, double * priority){

  if(pq == NULL) return 0;
  if(id!=NULL) *id = pq->heap[1]->id;
  if(priority!=NULL) *priority = pq->heap[1]->priority;
  return pq_remove_by_id(pq, *id); //O(logn)

}

As you can see the id and priority implementation allow for direct access
to the nodes which is the main difference from the normal implemenation.

-----------------------------------------------
Explain how your implementation of pq_change_priority worked,
why it is correct and why it achieves the runtime requirement.

My code for the change priority is as follows:

(I pointed out the parts of the function that are limiting the runtime)

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


As you can see the parts of the code acessing priority and id are constant
but the only limiting factors are the percolates which are in O(logn)



-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?

My code for pq_get_priority is the following:

  if(!withinBounds(pq,id))
    return 0;
  if(priority != NULL) 
    (*priority) = pq->ids[id+1]->priority;
  return 1;

As you can see the id implementation and the priority allows the runtime of 
this funcion to be O(1) as the required elements are being accessed
directly.
