/* FILE avl_bag.c
 *    Implementation of the bag ADT using an AVL tree.
 * Author: Francois Pitt, March 2012.
 */

/******************************************************************************
 *  Types and Constants.                                                      *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "avlbag.h"

/* MACRO HEIGHT
 *    An expression for one more than the height of a node in an AVL tree
 *    (evaluates to 0 if node is NULL).
 * Side-effects:  evaluates its argument more than once
 */
#define HEIGHT(node) ((node) ? (node)->height : 0)
////////////////////////////////////////////////////////////////////////////////
//  Example of macros and side-effects interfering with one another:          //
//      #define MAX(x,y)  ((x) >= (y) ? (x) : (y))                            //
//  Consider this code:                                                       //
//      printf("%d", MAX(a++,b - 5));                                         //
//  This is replaced textually before compilation:                            //
//      printf("%d", ((a++) >= (b - 5) ? (a++) : (b - 5)));                   //
//  If a++ >= b - 5, then a++ is evaluated TWICE!                             //
////////////////////////////////////////////////////////////////////////////////

/* TYPE avl_note_t -- A node in an AVL tree. */
typedef struct avl_node {
    bag_elem_t elem;        /* the element stored in this node       */
    size_t height;          /* one more than the height of this node */
    struct avl_node *left;  /* pointer to this node's left child     */
    struct avl_node *right; /* pointer to this node's right child    */
} avl_node_t;

/* TYPE struct bag -- Definition of struct bag from the header. */
struct bag {
    avl_node_t *root; /* root of the AVL tree storing the elements */
    size_t size;      /* number of elements in this bag            */
    int (*cmp)(bag_elem_t, bag_elem_t); /* function to compare elements */
};

/******************************************************************************
 *  Declarations of helper functions -- including full documentation.         *
 ******************************************************************************/

/* FUNCTION avl_destroy
 *    Free the memory allocated for the binary tree rooted at a given node.
 * Parameters and preconditions:
 *    root: the root of the tree to free
 * Return value:  none
 * Side-effects:
 *    all the memory allocated for nodes in the subtree rooted at root has been
 *    freed
 */
static
void avl_destroy(avl_node_t *root);

/* FUNCTION avl_elems
 *    Fill an array with the elements in a BST, given its root.  Place the
 *    elements in sorted order, starting at the given index, and return the
 *    number of elements copied.
 * Parameters and preconditions:
 *    root: the root of the BST containing the values to be copied
 *    array: the array into which to copy the values
 *    index: the index of array where to copy the first value
 * Return value:
 *    the number of elements copies into array
 * Side-effects:
 *    elements are copied from the BST rooted at root into array
 */
static
size_t avl_elems(const avl_node_t *root, bag_elem_t *array, size_t index);

/* FUNCTION avl_traverse
 *    Call a function on every element in a BST, given its root.
 * Parameters and preconditions:
 *    root: the root of the BST to traverse
 *    fun != NULL: a pointer to a function to apply to each element in the tree
 * Return value:  none
 * Side-effect:
 *    function fun has been called on each element in the tree rooted at root,
 *    in order
 */
static
void avl_traverse(const avl_node_t *root, void (*fun)(bag_elem_t));

/* FUNCTION avl_contains
 *    Return whether or not a BST contains a certain element, given the root.
 * Parameters and preconditions:
 *    root: the root of the BST to search
 *    elem: the element to search for
 *    cmp != NULL: the comparison function to use for the search
 * Return value:
 *    true if the BST rooted at 'root' contains elem; false otherwise
 * Side-effects:  none
 */
static
bool avl_contains(const avl_node_t *root, bag_elem_t elem,
                  int (*cmp)(bag_elem_t, bag_elem_t));

/* FUNCTION avl_insert
 *    Add an element to a BST, given a pointer to its root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST into which to insert
 *    elem: the element to insert
 *    cmp != NULL: the comparison function to use to find the insertion point
 * Return value:
 *    true if elem was inserted; false in case of error
 * Side-effects:
 *    memory has been allocated for the new element, and the tree structure has
 *    been adjusted accordingly
 */
static
bool avl_insert(avl_node_t **root, bag_elem_t elem,
                int (*cmp)(bag_elem_t, bag_elem_t));

/* FUNCTION avl_remove
 *    Remove an element from a BST, given a pointer to its root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST into which to remove
 *    elem: the element to remove
 *    cmp != NULL: the comparison function to use to find the removal point
 * Return value:
 *    true if elem was removed; false if the element was not there
 * Side-effects:
 *    memory has been freed for the element removed, and the tree structure has
 *    been adjusted accordingly
 */
static
bool avl_remove(avl_node_t **root, bag_elem_t elem,
                int (*cmp)(bag_elem_t, bag_elem_t));

/* FUNCTION avl_remove_min
 *    Remove and return the smallest element in a BST, given a pointer to its
 *    root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST
 * Return value:
 *    the smallest element in the BST rooted at 'root'
 * Side-effects:
 *    memory has been freed for the node containing the smallest element, and
 *    the tree structure has been adjusted accordingly
 */
static
bag_elem_t avl_remove_min(avl_node_t **root);

/* FUNCTION avl_remove_max
 *    Remove and return the largest element in a BST, given a pointer to its
 *    root.
 * Parameters and preconditions:
 *    root: a pointer to the root of the BST
 * Return value:
 *    the largest element in the BST rooted at 'root'
 * Side-effects:
 *    memory has been freed for the node containing the largest element, and
 *    the tree structure has been adjusted accordingly
 */
static
bag_elem_t avl_remove_max(avl_node_t **root);

/* FUNCTION avl_rebalance_to_the_left
 *    Rebalance the subtree rooted at *root, given that its right subtree is too
 *    tall -- this involves performing either a single or a double rotation.
 * Parameters and preconditions:
 *    root != NULL: a pointer to the root of the tree to rebalance
 *                  (*root != NULL and (*root)->right != NULL)
 * Return value:  none
 * Side-effects:
 *    the subtree rooted at *root has been rebalanced, and the heights of each
 *    node involved have been updated appropriately
 */
static
void avl_rebalance_to_the_left(avl_node_t **root);

/* FUNCTION avl_rebalance_to_the_right
 *    Rebalance the subtree rooted at *root, given that its left subtree is too
 *    tall -- this involves performing either a single or a double rotation.
 * Parameters and preconditions:
 *    root != NULL: a pointer to the root of the tree to rebalance
 *                  (*root != NULL and (*root)->left != NULL)
 * Return value:  none
 * Side-effects:
 *    the subtree rooted at *root has been rebalanced, and the heights of each
 *    node involved have been updated appropriately
 */
static
void avl_rebalance_to_the_right(avl_node_t **root);

/* FUNCTION avl_rotate_to_the_left
 *    Perform a single rotation of *parent to the left -- the tree structure
 *    goes from    *parent         to          child
 *                  /   \                      /   \
 *                 A     child           *parent    C
 *                       /   \            /   \
 *                      B     C          A     B
 * Parameters and precondition:
 *    parent != NULL: a pointer to the root of the tree to rotate
 *                    (*parent != NULL and (*parent)->right != NULL)
 * Return value:  none
 * Side-effects:
 *    the subtree rooted at *parent has been modified by rotating *parent with
 *    its right child
 */
static
void avl_rotate_to_the_left(avl_node_t **parent);

/* avl_rotate_to_the_right
 *    Perform a single rotation of *parent to the right -- the tree structure
 *    goes from         *parent    to     child
 *                       /   \            /   \
 *                  child     C          A    *parent
 *                  /   \                      /   \
 *                 A     B                    B     C
 * Parameters and precondition:
 *    parent != NULL: a pointer to the root of the tree to rotate
 *                    (*parent != NULL and (*parent)->left != NULL)
 * Return value:  none
 * Side-effects:
 *    the subtree rooted at *parent has been modified by rotating *parent with
 *    its left child
 */
static
void avl_rotate_to_the_right(avl_node_t **parent);

/* FUNCTION avl_update_height
 *    Update the height of a node (based on the heights of its children).
 * Parameters and preconditions:
 *    node != NULL: the node to update
 * Return value:  none
 * Side-effects:
 *    the height of node is updated
 */
static
void avl_update_height(avl_node_t *node);

/* FUNCTION avl_node_create
 *    Create a new avl_node.
 * Parameters and preconditions:
 *    elem: the element to store in the new node
 * Return value:
 *    pointer to a new node that stores elem and whose children are both NULL;
 *    NULL in case of error with memory allocation
 * Side-effects:
 *    memory has been allocated for the new node
 */
static
avl_node_t *avl_node_create(bag_elem_t elem);
/*
   The function takes in a pointer to a BST, and returns True if the BST is an AVL tree.
*/

static
bool is_avl_tree_rec(avl_node_t *root);

static
void bag_insert_norot_recursive(avl_node_t *node, bag_elem_t elem, int (*cmp)(bag_elem_t, bag_elem_t));

/******************************************************************************
 *  Definitions of "public" functions -- see header file for documentation.   *
 ******************************************************************************/

bag_t *avlbag_create(int (*cmp)(bag_elem_t, bag_elem_t))
{
    bag_t *bag = malloc(sizeof(bag_t));
    if (bag) {
        bag->size = 0;
        bag->root = NULL;
        bag->cmp = cmp;
    }
    return bag;
}

void avlbag_destroy(bag_t *bag)
{
    avl_destroy(bag->root);
    free(bag);
}

size_t avlbag_size(const bag_t *bag)
{
    return bag->size;
}

size_t avlbag_elems(const bag_t *bag, bag_elem_t *array)
{
    return avl_elems(bag->root, array, 0);
}

void avlbag_traverse(const bag_t *bag, void (*fun)(bag_elem_t))
{
    avl_traverse(bag->root, fun);
}

bool avlbag_contains(const bag_t *bag, bag_elem_t elem)
{
    return avl_contains(bag->root, elem, bag->cmp);
}

bool avlbag_insert(bag_t *bag, bag_elem_t elem)
{
    if (avl_insert(&bag->root, elem, bag->cmp)) {
        bag->size++;
        return true;
    } else {
        return false;
    }
}

bool avlbag_remove(bag_t *bag, bag_elem_t elem)
{
    if (avl_remove(&bag->root, elem, bag->cmp)) {
        bag->size--;
        return true;
    } else {
        return false;
    }
}

/******************************************************************************
 *  Definitions of helper functions -- see above for documentation.           *
 ******************************************************************************/

void avl_destroy(avl_node_t *root)
{
    if (root) {
        avl_destroy(root->left);
        avl_destroy(root->right);
        free(root);
    }
}

size_t avl_elems(const avl_node_t *root, bag_elem_t *array, size_t index)
{
    size_t count = 0; /* number of elements copied so far */
    if (root) {
        count += avl_elems(root->left, array, index + count);
        array[index + count++] = root->elem;
        count += avl_elems(root->right, array, index + count);
    }
    return count;
}

void avl_traverse(const avl_node_t *root, void (*fun)(bag_elem_t))
{
    if (root) {
        avl_traverse(root->left, fun);
        (*fun)(root->elem);
        avl_traverse(root->right, fun);
    }
}

bool avl_contains(const avl_node_t *root, bag_elem_t elem,
                  int (*cmp)(bag_elem_t, bag_elem_t))
{
    if (! root)
        return false;
    else if ((*cmp)(elem, root->elem) < 0)
        return avl_contains(root->left, elem, cmp);
    else if ((*cmp)(elem, root->elem) > 0)
        return avl_contains(root->right, elem, cmp);
    else /* ((*cmp)(elem, root->elem) == 0) */
        return true;
}

bool avl_insert(avl_node_t **root, bag_elem_t elem,
                int (*cmp)(bag_elem_t, bag_elem_t))
{
    bool inserted;

    if (! *root) {
        inserted = (*root = avl_node_create(elem));
    } else if ((*cmp)(elem, (*root)->elem) < 0) {
        if ((inserted = avl_insert(&(*root)->left, elem, cmp))) {
            /* Check if the subtree needs rebalancing; update its height. */
            if (HEIGHT((*root)->left) > HEIGHT((*root)->right) + 1)
                avl_rebalance_to_the_right(root);
            else
                avl_update_height(*root);
        }
    } else if ((*cmp)(elem, (*root)->elem) > 0) {
        if ((inserted = avl_insert(&(*root)->right, elem, cmp))) {
            /* Check if the subtree needs rebalancing; update its height. */
            if (HEIGHT((*root)->right) > HEIGHT((*root)->left) + 1)
                avl_rebalance_to_the_left(root);
            else
                avl_update_height(*root);
        }
    } else { /* ((*cmp)(elem, (*root)->elem) == 0) */
        /* Insert into the subtree with smaller height. */
        if (HEIGHT((*root)->left) < HEIGHT((*root)->right))
            inserted = avl_insert(&(*root)->left, elem, cmp);
        else
            inserted = avl_insert(&(*root)->right, elem, cmp);
        /* No rebalancing necessary, but update height. */
        if (inserted)  avl_update_height(*root);
    }

    return inserted;
}

//Question 3
bool avl_remove(avl_node_t **root, bag_elem_t elem, int (*cmp)(bag_elem_t, bag_elem_t)){
    if (*root == NULL){ //check if root exists to remove the element
        return false; //returns false when there is no root meaning the element is not found to remove
    }
    
    if ((*cmp)(elem, (*root)->elem) < 0) { //element we are removing is smaller than the root, hence we need to look to the left of the root
        if (avl_remove(&(*root)->left, elem, cmp)){ // if remove function recall to the left of the root sends true means it has removed the element, thus we must check for rebalancing
            if (HEIGHT((*root)->left) + 1 < HEIGHT((*root)->right)) { //checks if height of the left tree is atleast 2 levels lower than the right after the element to the left
                avl_rebalance_to_the_left(root); //if true this means that there is more than 2 level discrepency between both sub-trees so it will require the rebalancing to the left to balance out the tree
            }
            else {
                avl_update_height(*root); //if this is called the tree is still balanced and thus we must only update the height
            }
        }
    }
    
    if ((*cmp)(elem, (*root)->elem) > 0) { //element we are removing is bigger than the root, hence we need to look to the right of the root
        if (avl_remove(&(*root)->right, elem, cmp)){ // if remove function recall to the right of the root sends true means it has removed the element, thus we must check for rebalancing
            if (HEIGHT((*root)->right) + 1 < HEIGHT((*root)->left)) { //checks if height of the right tree is atleast 2 levels lower than the left after the element to the right
                avl_rebalance_to_the_right(root); //if true this means that there is more than 2 level discrepency between both sub-trees so it will require the rebalancing to the right to balance out the tree
            }
            else {
                avl_update_height(*root); //if this is called the tree is still balanced and thus we must only update the height
            }
        }
    } 
    
    else { //which means (*cmp)(elem, (*root)->elem) > 0) = 0, thus both elements are the same, the element to be removed is the root
        if ((*root)->left && (*root)->right) { //check if both left and right childs exist
            if (HEIGHT((*root)->left) > HEIGHT((*root)->right)) { //if the left sub-tree is bigger, if this is true we must keep the balance by removing the element from the left subtree
                (*root)->elem = avl_remove_max(&(*root)->left); //remove the max of the left (top), which is the root as to the left it is in decreasing order (root is largest)
            }
            else {
                (*root)->elem = avl_remove_min(&(*root)->right); //if the right sub-tree is bigger, remove the min of the right (top) which is the root as the right sub-tree is in increasing order
            }
            avl_update_height(*root); //update root height as in both cases the subtrees are balanced
        }
        else { // if one of the children do not exist we simply move the single child in place of the root and remove the root
            avl_node_t *old = *root;
            if ((*root)->left != NULL){ //replaces the root with the left child if they exist
                *root = (*root)->left;
            } 
            else { //replaces the root with the right child if they exist
                *root = (*root)->right;
            }
            free(old); //removes the old root
        }    
    }
    return true; //returns true when the removing of the element is done
}

bag_elem_t avl_remove_min(avl_node_t **root)
{
    bag_elem_t min;

    if ((*root)->left) {
        /* *root is not the minimum, keep going and rebalance if necessary. */
        min = avl_remove_min(&(*root)->left);
        if (HEIGHT((*root)->left) + 1 < HEIGHT((*root)->right))
            avl_rebalance_to_the_left(root);
        else
            avl_update_height(*root);
    } else {
        /* Remove *root. */
        avl_node_t *old = *root;
        min = (*root)->elem;
        *root = (*root)->right;
        free(old);
    }

    return min;
}

bag_elem_t avl_remove_max(avl_node_t **root)
{
    bag_elem_t max;

    if ((*root)->right) {
        /* *root is not the maximum, keep going and rebalance if necessary. */
        max = avl_remove_max(&(*root)->right);
        if (HEIGHT((*root)->right) + 1 < HEIGHT((*root)->left))
            avl_rebalance_to_the_right(root);
        else
            avl_update_height(*root);
    } else {
        /* Remove *root. */
        avl_node_t *old = *root;
        max = (*root)->elem;
        *root = (*root)->left;
        free(old);
    }

    return max;
}

void avl_rebalance_to_the_left(avl_node_t **root)
{
    if (HEIGHT((*root)->right->left) > HEIGHT((*root)->right->right))
        avl_rotate_to_the_right(&(*root)->right);
    avl_rotate_to_the_left(root);
}

void avl_rebalance_to_the_right(avl_node_t **root)
{
    if (HEIGHT((*root)->left->right) > HEIGHT((*root)->left->left))
        avl_rotate_to_the_left(&(*root)->left);
    avl_rotate_to_the_right(root);
}

void avl_rotate_to_the_left(avl_node_t **parent)
{
    /* Rearrange pointers. */
    avl_node_t *child = (*parent)->right;
    (*parent)->right = child->left;
    child->left = *parent;
    *parent = child;

    /* Update heights. */
    avl_update_height(child->left);
    avl_update_height(child);
}

void avl_rotate_to_the_right(avl_node_t **parent)
{
    /* Rearrange pointers. */
    avl_node_t *child = (*parent)->left;
    (*parent)->left = child->right;
    child->right = *parent;
    *parent = child;

    /* Update heights. */
    avl_update_height(child->right);
    avl_update_height(child);
}

void avl_update_height(avl_node_t *node)
{
    node->height = 1 + ( HEIGHT(node->left) > HEIGHT(node->right) ?
                         HEIGHT(node->left) : HEIGHT(node->right) );
}

avl_node_t *avl_node_create(bag_elem_t elem)
{
    avl_node_t *node = malloc(sizeof(avl_node_t));
    if (node) {
        node->elem = elem;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}


//QUESTION 1
bool is_avl_tree_rec(avl_node_t *root){
    if (!root) {
        return true;
    }
    if (!root->right||!root->left){
        if (root->height<3){
            return true;
        }
        return false;
    }
    if (abs(root->left->height - root->right->height)<2 && is_avl_tree_rec(root->left) && is_avl_tree_rec(root->right)) {
        return true;
    }
    return false;
}

bool is_avl_tree(bag_t *bag){
    if (bag->root == NULL) {
        return false;
    }
    return is_avl_tree_rec(bag->root);
}

//QUESTION 2
void bag_insert_norot_recursive(avl_node_t *node, bag_elem_t elem, int (*cmp)(bag_elem_t, bag_elem_t)) {
    if((*cmp)(elem, node->elem) == -1) { //line 40
        if (node->left == NULL) {
            node->left = avl_node_create(elem); //line 54
            avl_update_height(node); //line 68
        }
        else { 
            bag_insert_norot_recursive(node->left, elem, cmp);
            avl_update_height(node);
        }
    }
    else { //if 0 or 1, which means "*(float *) a > *(float *) b;"
        if (node->right == NULL) {
            node->right = avl_node_create(elem); //line 54
            avl_update_height(node); //line 68
        }
        else {
            bag_insert_norot_recursive(node->right, elem, cmp);
            avl_update_height(node);
        }
    }
}

bool bag_insert_norot(bag_t *bag, bag_elem_t elem, int (*cmp)(bag_elem_t, bag_elem_t)){
    if (bag-> root == NULL) {
        bag->root = avl_node_create(elem); //line 54
        bag->size++;
    }
    else {
        bag_insert_norot_recursive(bag->root, elem, cmp);
        bag->size++;
    }
    return is_avl_tree(bag);
}

/******************************************************************************
 *  Additional "hidden" functions, for debugging purposes.                    *
 ******************************************************************************/

bool avlbag_is_avl(bag_t *bag){
    return is_avl_tree(bag);
}

bool avlbag_insert_norot(bag_t *bag, bag_elem_t elem){
    return bag_insert_norot(bag, elem, bag->cmp);
}