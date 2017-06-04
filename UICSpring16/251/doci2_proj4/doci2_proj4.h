/*Denis Doci
 *
 *Doci2
 *
 *Library for all the c files
 *
 *includes all necessary libraries
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


//enum definition for boolean
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

//node being used
typedef struct NODE {
    int size;
    char *name;
    boolean inres; 
    struct NODE *next;
} node;

//list struct being used
typedef struct list_struct{
    node *front;
}list;

//all functions used
extern list * lst_create();

extern int getPosInt();

extern char *getName();

extern void clearToEoln();

extern void doAdd(list *l, int dbug);

extern void doCallAhead(list *l, int dbug);

extern void doRetrieve(list *l, int dbug);

extern void doWaiting(list *l, int dbug);

extern void doList(list *l, int dbug );

extern void doDisplay(list *l, int dbug);

extern void addToList(list *l, int size, char * name, boolean inres, int dbug);

extern int doesNameExist(list *l, char * name, int dbug);

extern boolean updateStatus(list *l, char *name, int dbug);

extern char * retrieveAndRemove(list *l, int size, int dbug);

extern int countGroupsAhead(list *l, char *name, int dbug);

extern void displayGroupSizeAhead(list *l, char *name, int dbug);

extern void displayListInformation(list *l, int dbug);

extern void lst_free(list *l, int dbug);
