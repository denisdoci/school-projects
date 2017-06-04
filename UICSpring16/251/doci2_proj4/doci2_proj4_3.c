//include the proj4 library
#include "doci2_proj4.h"

//linked list create function
list * lst_create(){
list *l = malloc(sizeof(list));
  l->front = NULL;
  return l;
}

//freeing every element of the linked list
void lst_free(list *l, int dbug) {
node *p = l->front;
node *pnext;

  while(p != NULL) {
    if(dbug==1){//debug print out
      printf("Name: %s  ", p->name);
      printf("Size: %i  ", p->size);
      printf("In Restaurant:");
      if(p->inres == 1) printf(" Yes");
      else printf(" No");
      printf("\n");
    }    
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}


//add a node to the list
void addToList(list *l, int size, char * name, boolean status, int dbug){
//allocating memory for necessary elements of node
  node * temp = l->front;
  node * n = malloc(sizeof(node));
  n->name = malloc(30*sizeof(char));

  n->name = name;
  n->size = size;
  n->inres = status;

  if (l->front == NULL){
	l->front = n;
	return;
  }

  else{
	while(temp->next != NULL){ //adding to the end of a list
	temp = temp->next;
            if(dbug==1){//debug mode on
      	      printf("Name: %s  ", temp->name);
      	      printf("Size: %i  ", temp->size);
      	      printf("In Restaurant:");
              if(temp->inres == 1) printf(" Yes");
              else printf(" No");
              printf("\n");
            }	
	}
  }
  temp->next = n;

  return;
}

//check if given name is already in the list, returns 1 or 0
int doesNameExist(list *l, char * name, int dbug){
	
  if (l->front == NULL){
  //-Queue Empty-
  return 0;
  }

  node  *temp = l->front;
  while (temp!=NULL) {
    if(dbug==1){ //debug mode on
      printf("Name: %s  ", temp->name);
      printf("Size: %i  ", temp->size);
      printf("In Restaurant:");
      if(temp->inres == 1) printf(" Yes");
      else printf(" No");
      printf("\n");
    }    
    if (!strcmp(temp->name,name)) { // found name
    return 1;	
    }
  else 
  temp=temp->next;			
  }	
	return 0;
}

//function to change status of called in person to in restaurant
boolean updateStatus(list *l, char *name, int dbug){

  node * temp = l->front;

  while(temp != NULL){
    if(dbug==1){// debug mode activated
      printf("Name: %s  ", temp->name);
      printf("Size: %i  ", temp->size);
      printf("In Restaurant:");
      if(temp->inres == 1) printf(" Yes");
      else printf(" No");
      printf("\n");
    }
    if(strcmp(temp->name, name)==0) // found name
	break;
    temp = temp->next;
  }

  if(temp->inres==1){ //status in restaurant
    return 1;
  }
  else{
    temp->inres=1; //not in restaurant. then change status to in restaurant
    return 0;
  }
}


//new table open... pop first viable group form the list
char * retrieveAndRemove(list *l, int size, int dbug){

  node * p;
  node * tmp;
  char * ret; 

  if(size >= l->front->size && l->front->inres == 1){
   ret = l->front->name;
   if(l->front->next == NULL) {  // one element
        free(l->front);
        l->front = NULL;
   }
  else {
        p = l->front;  // don't lose node being deleted
        l->front = l->front->next;  // hop over
        free(p);
  }    
    return ret;
  }

  p = l->front;

  while(p->next != NULL){
    if(dbug==1){ //debug mode on
      printf("Name: %s  ", p->name);
      printf("Size: %i  ", p->size);
      printf("In Restaurant:");
      if(p->inres == 1) printf(" Yes");
      else printf(" No");
      printf("\n");
    }
    if(size >= p->next->size && p->next->inres == 1){ //if in restaurant and viable amount of ppl
      ret = p->next->name;
      tmp = p->next;
      p->next = tmp->next;
      free(tmp); //free node
      return ret;
    }
   p = p->next;
  }
  return NULL;
}

//function to count the amount of groups
int countGroupsAhead(list *l, char * name, int dbug){
  int count = 0;
  node * tmp = l->front;
 
  while(strcmp(tmp->name, name)){//continue until name found
    if(dbug==1){//debug mode activated
      printf("Name: %s  ", tmp->name);
      printf("Size: %i  ", tmp->size);
      printf("In Restaurant:");
      if(tmp->inres == 1) printf(" Yes");
      else printf(" No");
      printf("\n");
    }
    tmp = tmp->next;
    count++; //increment count
  } 
  return count;
}

//display data for groups ahead of one provided
void displayGroupSizeAhead(list *l, char *name, int dbug){

  node * tmp = l->front;

  while(strcmp(tmp->name,name)){//continue until name is found
  if(dbug==1){ //debug mode active
    printf("Name: %s  ", tmp->name);
    printf("Size: %i  ", tmp->size);
    printf("In Restaurant:");
    if(tmp->inres == 1) printf(" Yes");
    else printf(" No");
    printf("\n");
  }
  printf("\nGroup: %s Size of Group: %d \n", tmp->name, tmp->size); //print group data
  tmp=tmp->next;
  }
}


//display list
void displayListInformation(list *l, int dbug){
node *p = l->front;

  printf("\n");
  while(p != NULL) {
    printf("Name: %s  ", p->name);
    printf("Size: %i  ", p->size);
    printf("In Restaurant:");
    if(p->inres == 1) printf(" Yes");
    else printf(" No");
    printf("\n");
    if(dbug==1){//debugmode active
      printf("Name: %s  ", p->name);
      printf("Size: %i  ", p->size);
      printf("In Restaurant:");
      if(p->inres == 1) printf(" Yes");
      else printf(" No");
      printf("\n");    
   }
    p = p->next;
  }
}
