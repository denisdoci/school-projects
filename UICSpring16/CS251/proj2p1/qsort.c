#include <stdio.h>
#include "llist.c"

void quicksort(LIST * l)
{ 
  int len = lst_length(l);
  if(len<=1){
    return;
  }
  ElemType pivVal = lst_pop_front(l);
  LIST *piv = lst_create();
  lst_push_front(piv, pivVal);
  LIST * r  = lst_filter_leq(l, pivVal);
//  lst_print(l);
//  lst_print(r);
//  lst_print(piv);
  lst_concat(l,piv);
  quicksort(l);
  quicksort(r);
  lst_concat(l,r); 
}
int main(){

  int input=0;
  int valid = 1;

  LIST *l = lst_create();
  printf("\nEnter values of linked list enter nondigit to stop\n");
  while(valid == 1 || valid == EOF){
  valid = scanf("%d", &input);
  if(valid == 0 || valid == EOF) break;
  lst_push_front(l, input);
  }
  printf("\nValues of list before sorting\n");

  lst_print(l);
  printf("\nValues of list after sorting\n");
  if(lst_length(l) <= 1){
  lst_print(l);
  }
  else{
  quicksort(l);
  lst_print_rev(l);
  }
  lst_free(l);
  return 1;
}
