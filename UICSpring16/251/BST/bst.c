/*
 *Denis Doci
 *doci2
 *bst.c final version
 */


#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int val;
    struct bst_node *left;
    struct bst_node *right;

};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
    int size;
    int height;
};

BST_PTR bst_create(){
  BST_PTR t = malloc(sizeof(struct bst));
  t->root = NULL;
  t->size = 0;
  return t;
}


static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST_PTR t){
    free_r(t->root);
    free(t);
}

static NODE * insert(NODE *r, int x){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      return leaf;
    }

    if(r->val == x)
        return r;
    if(x < r->val){
        r->left = insert(r->left, x);
        return r;
    }
    else {
        r->right = insert(r->right, x);
        return r;
    }
}

// how about an iterative version?
static NODE *insert_i(NODE *r, int x){

  return NULL;

}


void bst_insert(BST_PTR t, int x){
    t->root = insert(t->root, x);
    t->size++;
}

int bst_contains(BST_PTR t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;  
}

static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;
    return NULL;
  }
  if(r->val == x){
    *success = 1;

    if(r->left == NULL){
        tmp = r->right;
        free(r);
        return tmp;
    }
    if(r->right == NULL){
        tmp = r->left;
        free(r);
        return tmp;
    }
    // if we get here, r has two children
    r->val = min_h(r->right);
    r->right = remove_r(r->right, r->val, &sanity);
    if(!sanity)
        printf("ERROR:  remove() failed to delete promoted value?\n");
    return r;
  }
  if(x < r->val){
    r->left = remove_r(r->left, x, success);
  }
  else {
    r->right = remove_r(r->right, x, success);
  }
  return r;

}


int bst_remove(BST_PTR t, int x){
    int success;
    t->root = remove_r(t->root, x, &success);
    t->size--;
    return success;
}

int bst_size(BST_PTR t){
    return t->size;
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST_PTR t){
    return height(t->root);
}

int bst_min(BST_PTR t){
    return min_h(t->root);
}

int bst_max(BST_PTR t){
    return max_h(t->root);
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d]\n", r->val);
  inorder(r->right);

}
void bst_inorder(BST_PTR t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d\n", r->val);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST_PTR t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

/* 
 * Not a graded exercise, but good practice!
 *
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
    /* FILL IN FUNCTION */
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST_PTR t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

/* 
 * Recursive helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
int m;
NODE *root;

    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->val = a[m];
    root->left = from_arr(a, m);
    root->right = from_arr(&(a[m+1]), n-(m+1));
    return root;

}

BST_PTR bst_from_sorted_arr(int *a, int n){

  BST_PTR t = bst_create();

  t->root = from_arr(a, n);

  return t;
}


/******    TODO      *********/

//recursive helper function for the bst_to_array
void to_array(NODE * r, int * arr, int * i){
    //base case
    if(r == NULL ) return;

    to_array(r->left, arr, i); //go left
    arr[*i] = r->val;  //store val in array
    arr[*i] = r->val;  //store val in array
    (*i)++;  //increment index
    to_array(r->right, arr, i); //go right
}

//bst_to_array uses a helper function
int * bst_to_array(BST_PTR t) {

  int * arr =  malloc(sizeof(int)*t->size); //allocate enough memory for array
  NODE * r = t->root;
  int i = 0;

  if(t->root == NULL) //empty BST
  return NULL;

  to_array(r, arr, &i);
  
  return arr;
}

//get_ith recursive helper function
NODE * get_ith(NODE * r, int * i){
    
 if(!r || i < 0) return NULL; // base case
    
  get_ith(r->left, i); //go left
  --(*i);  //decrement

  if(*i == 0){ //found ith
    return r;
  }
  get_ith(r->right, i); //go right
}
int bst_get_ith(BST_PTR t, int i) {
  if(i<0 || i>t->size){
	fprintf(stderr, "\n\nError ith out of range\n");
	return -9999;
  }
  NODE * r = t ->root;
  NODE * ret =  get_ith(r, &i);
  return ret->val;
}

int bst_get_nearest(BST_PTR t, int x) {
  int nearest=0;    //actual value of the nearest number
  int min = 1000;  //minimum |x-y| .... this 1000 is arbitrary, it honestly just needs to be > 1
  NODE * r = t->root;
  if(t == NULL){
      fprintf(stderr, "\n\nERROR: Your BST seems to be empty.\n");
      return -9999;
  }
  while(r != NULL){
     if(x <= r->val){  //x is less
	if((r->val-x) < min){ //check if its min
	 min = r->val-x;
	 nearest = r->val; 
	}
     r=r->left; //only increment left
     }
    else{   //x is greater
	if((x-r->val)<min){ //check if its a min
	min = x-r->val;
	nearest=r->val;  
	}
     r=r->right; //only increment right
     }
  }
  return nearest;
}


//recursive helper function for greater than or equal to
void num_geq(NODE * r, int * numel, int x){
   if(r==NULL){return;} // base case
   if(r->val >= x){ // if it is geq increment number of elements
	(*numel)++;
   num_geq(r->left, numel, x); //go left (if greater then lesser value could be > x)
   }
   num_geq(r->right, numel,x);  // go right ... to find > number
}

int bst_num_geq(BST_PTR t, int x) {
  int numel = 0; //incremented return value
  NODE * r = t->root;
  num_geq(r, &numel, x);
  return numel;
}

//recursive helper function for less than or equal to
void num_leq(NODE * r, int * numel, int x){
   if(r==NULL){return;} //base case
   if(r->val <= x){ //if it is a leq, increment number of elements
        (*numel)++;
   num_leq(r->right, numel, x); //go left (if leq then greater value could be < x)
   }
   num_leq(r->left, numel, x);  //find a < number
}

int bst_num_leq(BST_PTR t, int x) {
  int numel = 0; //incremented return
  NODE * r = t->root;
  num_leq(r, &numel, x);
  return numel;
}
