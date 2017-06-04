#include "stdlib.h"
#include "stdio.h"
#include "pq.c"
#include "time.h"
#include "assert.h"


static void indent(int m) {
    int i;
    
    for(i=0; i<m; i++)
        printf("-");
}

static void preorder(PQ * pq, int margin, int n) {
  if(n>pq->size) {
//    indent(margin);
  //  printf("\nNULL \n");
  //  return;
 } 
  
    else {
        indent(margin);
        printf("Priority: %f, ID: %d\n", pq->heap[n]->priority, pq->heap[n]->id);
        preorder(pq, margin+3, n*2);
        preorder(pq, margin+3, n*2+1);
    }
}

void pq_preorder(PQ * pq) {
    printf("========BEGIN PREORDER============\n");
    preorder(pq, 0, 1);
    printf("=========END PREORDER============\n");
}

// Validates heap from top-down
int test_heap_associations_helper(PQ * pq, NODEPTR r) {
    if (r==NULL) return 1;
    NODEPTR left_child = getLeft(pq,r);
    NODEPTR right_child = getRight(pq,r);
    
    if (left_child != NULL)
        pq->htype==min ? assert(r->priority <= left_child->priority): assert(r->priority >= left_child->priority);
    
    test_heap_associations_helper(pq, left_child);
    
    if (right_child != NULL)
        pq->htype==min ? assert(r->priority <= right_child->priority) : assert(r->priority >= right_child->priority);
    
    test_heap_associations_helper(pq, right_child);
}

// Random test generator for priority queue
int test_heap_associations() {
    srand(time(NULL));
    int i, size = 50, psize = size*5;
    int j=1;
    double k=1;
    PQ * pq = pq_create(size, 1);
    printf("\n\n\nBefore Insert\n\n");
      pq_preorder(pq);

    for (i=0; i<size; i++) {
        pq_insert(pq, i, rand()%psize);
        test_heap_associations_helper(pq, pq->heap[1]);
    }
    printf("\n\n\nAfter Insert\n\n");

    pq_preorder(pq);

    printf("\n\n\nChange priority of id 1 to : 12\n\n");
    pq_change_priority(pq, 1, 12);
    pq_preorder(pq);
    printf("\n\n\nSize:");
    printf("%d\n\n", pq->size);
    printf("\n\n\nCapacity:");
    printf("%d\n\n", pq->capacity);


    printf("\n\n\nRemove ID 2\n\n");
    printf("\nDelete Top\n\n");
    pq_delete_top(pq, &j, &k);
    pq_remove_by_id(pq,2);
    pq_preorder(pq);
    if(pq_contains(pq,3)){printf("\nProgram contains 3\n\n");}
    else{printf("\nProgram doesn't contain 3\n\n");}
    for (i=size-1; i>=0; i--) {
        pq_remove_by_id(pq,i);
      test_heap_associations_helper(pq, pq->heap[1]);
    }
    
    printf("\n\n\nAfter remove\n\n");
    pq_preorder(pq);
    printf("\n\n\nSize:");
    printf("%d\n\n", pq->size);
    printf("\n\n\nCapacity:");
    printf("%d\n\n", pq->capacity);
    if(pq_contains(pq,3)){printf("\nProgram contains 3\n\n");}
    else{printf("\nProgram doesn't contain 3\n\n");}

   pq_free(pq);
    printf("\n\n\nAfter Free\n\n");
    pq_preorder(pq);

    
    return 1;
}

int main () {
    test_heap_associations();
    return 1;
}
