#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avlbag.h"
#include "bstbag.h"

/*
Lab 8
=====

In this lab, you will be working with code from avl_bag.c, to understand it more deeply
*/

// comparator for our new bag
static
int float_cmp(bag_elem_t a, bag_elem_t b)
{
    return *(float *) a < *(float *) b ? -1
         : *(float *) a > *(float *) b;
}

int main(void){
    size_t i;
    // tree elements
    float elts[] = {4, 2, 5, 7, 6, 3, 8, 9, 10};
    float new = 11; 
    bag_t *b1 = avlbag_create(float_cmp);
    // making the new tree
    for (i = 0; i < sizeof(elts) / sizeof(elts[0]); ++i){
            avlbag_insert(b1, &elts[i]);
    }
    //testing the bst insert if it is an avl tree
    printf("%d \n",avlbag_insert_norot(b1, &new));
    //testing avl remove
    printf("%d \n",avlbag_remove(b1, &new));
}
