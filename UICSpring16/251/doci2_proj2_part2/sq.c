#include <stdio.h>
#include <stdlib.h>
#include "sq.h"

typedef struct NODE{
    int val;
    struct NODE *prev;
    struct NODE *next;
}node;

typedef struct list_struct{
    node * front;
    node *back;
    int n;
}list;

typedef struct service_queue{
    list * qu;
    list * bu;
    node ** pointers;
    int buzzer;
    int indsize;
}sq;

list *lst_create() {
list *l = malloc(sizeof(list));

  l->front = NULL;
  l->back = NULL;
  l->n = 0;
  return l;
}
sq * sq_create(){
  sq * s = malloc(sizeof(sq));
  s->qu = lst_create();
  s->bu = lst_create();
  s->pointers = (node**)malloc(sizeof(node*)*2);
  s->indsize = 2;
  s->buzzer=0;
  return s;
}
void lst_free(list *l) {
node *p = l->front;
node *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}
int lst_is_empty(list *l) {
  return l->front == NULL;
}
int lst_length(list *l) {
  return l->n;
}
void lst_print(list *l) {
node *p = l->front;

  printf("[");
  while(p != NULL) {
    printf("%i ", p->val);
    p = p->next;
  }
  printf("]\n");
}
int lst_pop_front(list *l){
int ret;
node *p;
  if(lst_is_empty(l))
	return 0;
  ret = l->front->val;
  
  if(l->front == l->back) {  // one element
        free(l->front);
        l->front = NULL;
        l->back = NULL;
  }
  else {
        p = l->front;  // don't lose node being deleted
        l->front = l->front->next;  // hop over
        l->front->prev= NULL;
	free(p);
  }
  (l->n)--;
  return ret;
}

void lst_push_front(list *l, int val) {
node *p = malloc(sizeof(node));

  p->val = val;
  p->next = l->front;
  p->prev = NULL;
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;

  (l->n)++;
}
void lst_push_back(list *l, int val) {
node *p;

  if(l->back == NULL)   // list empty - same as push_front
        lst_push_front(l, val);
  else {  // at least one element before push
        p = malloc(sizeof(node));
        p->val = val;
        p->next = NULL;
        l->back->next = p;
        p->prev = l->back;
        l->back = p;
        (l->n)++;
  }
}
int lst_remove_first(list *l, int x) {
node *p, *tmp;

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
void pntr_free(node ** n, int size){
  int i;
  for(i=0;i<size;i++){
   free(n[i]);
  }
  free(n);
}
void sq_free(sq *q){
  lst_free(q->qu);
  lst_free(q->bu);
  pntr_free(q->pointers, q->indsize);
  free(q);
}
void sq_display(sq *q){
   printf("Current-queue contents:\n  ");
   lst_print(q->qu);
   printf("\n");
}
int sq_length(sq *q){
   return lst_length(q->qu);
}
int sq_give_buzzer(sq *q){
  int buzzer;
  if(!lst_is_empty(q->bu)) {
	buzzer = lst_pop_front(q->bu);
	lst_push_back(q->qu, buzzer);
	q->buzzer++;
	return buzzer;
  }
  else{
	buzzer = sq_length(q);
	lst_push_back(q->qu, buzzer);
        q->buzzer++;
	return buzzer;
  }
}
int sq_seat(sq *q) {
int buzzer;

	if(lst_is_empty(q->qu))
	  return -1;
	else{
	  buzzer = lst_pop_front(q->qu);
	  lst_push_front(q->bu, buzzer);
	  return buzzer;
	}
} 
int sq_kick_out(sq *q, int buzzer) {

  if(lst_remove_first(q->qu, buzzer)) {
	lst_push_front(q->bu, buzzer);
	return 1;
  }
  else
	return 0;
}

int sq_take_bribe(sq *q, int buzzer) {

  if(lst_remove_first(q->qu, buzzer)) {
	lst_push_front(q->qu, buzzer);
	return 1;
  }
  else {
	return 0;
  }
}

