#include <assert.h>
#include "bst.h"
#include <stdio.h>

int main(){
    int i;

    /* PART 1 */

    int a[] = {8, 2, 6, 9, 11, 3, 7};
    int * l;

    BST_PTR t = bst_create();

    for(i=0; i<7; i++)
        bst_insert(t, a[i]);

    printf("\n\nThe size of the array is: %d\n", bst_size(t));

    bst_remove(t, 7);

    printf("\n\nThe size of the array is: %d\n", bst_size(t));

    assert(bst_size(t) == 6);

    /* PART 2 */
    
    bst_inorder(t);

    bst_preorder(t);

    bst_postorder(t);
    
    printf("\n\nArray contains: ");

    l = bst_to_array(t);

    for(i=0; i<6; i++){
 	printf(" %d ", l[i]);
    }
    int d = 4;
    printf("\n\nThe %dth smallest values is: ", d);
    printf("%d\n", bst_get_ith(t,d));
    printf("\n\nThe number of elements geq to 4 is: ");
    printf("%d\n", bst_num_geq(t,4));
    printf("\n\nThe number of elements leq to 4 is: ");
    printf("%d\n", bst_num_leq(t,4));
    printf("\n\nThe number nearest to 11 is: ");
    printf("%d\n", bst_get_nearest(t,11));
    bst_free(t);
    /* PART 3 (extra) */
    
    int sorted_a[] = {2, 3, 6, 7, 8, 9, 11};
    
    t = bst_from_sorted_arr(sorted_a, 7);
    
    
    bst_inorder(t);

    /*
    bst_preorder(t);

    bst_postorder(t);

    bst_free(t);
    */
}
