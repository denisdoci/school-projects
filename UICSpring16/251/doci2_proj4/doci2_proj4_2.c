//include the the project4 library

#include "doci2_proj4.h"


/*
 *Function to complete the do command
 *with error check
 *slightly modified from given
*/

void doAdd (list *l, int dbug)
{
 /* get group size from input */
 int size = getPosInt();
 boolean status = 1;
 if (size < 1)
   {
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 printf ("Adding group \"%s\" of size %d\n", name, size);

//checking to see if if the name is in in the queue
 if ( doesNameExist(l,name, dbug) == 0){
   //if not add name
   addToList(l, size, name, status, dbug);
  }
  else{
    printf ("\nName already exists in list. Please use unique entry.\n");
  }
}


/*
 *Function to complete the call ahead commmand
 *Slightly modified form the given one
 */
void doCallAhead (list * l, int dbug)
{
 /* get group size from input */
  boolean status = 0;
  int size = getPosInt();
  if (size < 1)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }
  char *name = getName();
  if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

  printf ("Call-ahead group \"%s\" of size %d\n", name, size);

 // Check to see if name is on the list
  if(doesNameExist(l, name, dbug)==0)
    addToList(l,size,name,status, dbug);   //if not add name to the list as a not in restaurant entry
  else{
    printf ("\nName already exists in list. Please use unique entry.\n");
  }
}


/*
 *Function to complete the waiting command
 *Slightly modified form the given one
 */
void doWaiting (list *l, int dbug)
{
 boolean called;
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

    
 //check to see if name is in the queue
  if ( doesNameExist(l,name,dbug) == 1){
    called=updateStatus (l,name,dbug); // if it is do update status function
  }
  else{
    printf ("\nError: Group Name not on list\n");
  }
  if(called == 1){
    printf("\nThe group is already in the restaurant\n ");
  }
  else{
    printf ("Waiting group \"%s\" is now in the restaurant\n", name);
  }
}


/*
 *Function to complete the retrieve commmand
 *Slightly modified form the given one
 */
void doRetrieve (list *l, int dbug)
{
 /* get table size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
   }
 clearToEoln();
 
// check to see if list is empty
 char* name=NULL;
 if(l->front == NULL){
   printf("\nList is empty, cannot seat\n");
   return;
 }
 name = retrieveAndRemove(l, size, dbug);
 printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);
 if(name == NULL)
   printf("\nTable not big enough to seat anybody\n");
 else
   printf("\n%s has been seated\n", name);
}


/*
 *Function to complete the list commmand
 *Slightly modified form the given one
 */
void doList (list *l, int dbug)
{
 // get group name from input
 char *name = getName();
 int  numGr;

 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
   }

  if (doesNameExist(l,name,dbug) == 0){ //check to see if name is on the list
    printf ("\nError: Group Name not on list\n");  
  }
  else{
    numGr = countGroupsAhead(l, name, dbug); //count groups ahead of the group
    printf("\nThere are %d groups ahead of %s\n", numGr, name);
    printf ("Group \"%s\" is behind the following groups\n", name);
    displayGroupSizeAhead(l, name, dbug); //list groups ahead and their information
 }
}

/*
 *Function to complete the display commmand
 *Slightly modified form the given one
 */
void doDisplay (list * l, int dbug)
{
 clearToEoln();
 printf ("Display information about all groups\n");
 displayListInformation(l, dbug);
}
