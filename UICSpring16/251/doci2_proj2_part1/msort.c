#include <stdio.h>
#include "llist.c"

void mergeSort2(LIST * n){
  int k = lst_length(n);
  if(k<=1){
    return;
  }
  else{
  LIST * left;
  left = lst_prefix(n, k/2);
  mergeSort2(left);
  mergeSort2(n);
  lst_merge_sorted(n,left);
  }
}
int main()
{
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
  mergeSort2(l);
  lst_print(l);  
  }
  lst_free(l);
  return 1;
}
