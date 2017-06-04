/*
 *Denis Doci
 *doci2
 *radix sort
 *project3 part 1
 *
 *************************
 *IMPORTANT NOTE!!!
 *************************
 *I'm not sure if its my computer but the program works better with a file 
 *redirection. If theres no file redirection please do not attatch a character
 *to the any value of the input. And run the program
 *AT LEAST TWO TIMES. Also make sure there is a space or new line following the input.
 * 
 *Example: please do not input: 21 123 1 231 3d
 * 
 *  	  rather input: 21 123 1 231 3 d 
 *************************
 *IMPORTANT NOTE (exception)
 *************************
 *
 * This might just be my computer, as on bertvm it works perfectly fine.
 * I dont know the exact issue but it seems to only be a problem on my personal laptop. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "llist.c"

/*
 *Radix sort function 
 *Establishes a largest to smallest sort with radix base 
 *being integer input
 */
LIST * rsort(LIST *list,  const int radix, int passes){
    
    int n = 1;
    int i,j;
    NODE ** bucket, *next, *temp;
    NODE * head = list->front; 
   
 
    // bucket array
    bucket = malloc(sizeof(NODE)*radix);
 
 
    for(j = 0; j < passes ;j++)
    {
        
        //Place numbers in the linked list into proper bucket.  
        while(head != NULL)
        {    
                next                         = head->next;
                head->next                   = bucket[(head->val/n)%radix];
                bucket[(head->val/n)%radix]  = head;
                head                         = head->next;
                head 			             = next;

 	    }
        //this is to rebuild the list with proper order of nodes
        for(i = 0; i < radix; i++)
        {        
            while(bucket[i]!=NULL)
            { 

                temp            = bucket[i]->next;
                bucket[i]->next = head;
                head            = bucket[i];
                bucket[i]       = bucket[i]->next;
                bucket[i]       = temp;
            }
        }
        n *= radix;
    }
  for(i=0; i<radix; i++)
    free(bucket[i]); //free bucket array
  list->front = head; //set return list to the ordered list
  return list;
}

int main()
{
  int i;
  int input=0; //userinput
  int valid = 1; //check to see if input is valid
  LIST *l = lst_create(); //linked list to store values 

  printf("\nEnter values of linked list enter nondigit to stop\n");
  while(valid == 1) {
  valid = scanf("%d", &input); //keep reading in values until invalid input or EOF
  if(valid == 0) break; //if invalid dont push
  lst_push_back(l, input);
  }
  printf("\nValues of list before sorting\n");

  lst_print(l);
  printf("\nValues of list after sorting\n");
  if(lst_length(l) <= 1){
    lst_print(l);
  }
  else{
    int radix = l->n;  //set radix value
    int passes = radix+radix; //set value of passes
  //printf("\nPasses: %d\n", passes);
  //printf("\nworking\n");
    l=rsort(l, radix, passes); 
    lst_print_rev(l);  //print list smallest to largest
  }
  lst_free(l); //free list
  return 1;
}
