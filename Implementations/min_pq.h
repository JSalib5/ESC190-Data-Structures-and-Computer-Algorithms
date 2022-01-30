////////////////////////////////////////////////////////////////////////////////
//  As usual, I will use // for comments that explain what I am doing but     //
//  that would not normally belong in well-written code, and I will use the   //
//  more "traditional" delimited comments /*...*/ for "regular" comments.     //
////////////////////////////////////////////////////////////////////////////////

/* FILE min_pq.h
 *    Public constants, types, and function declarations for a generic Minimum
 *    Priority Queue ADT.
 * DESIGN DECISIONS:
 *  - Elements are stored as type (const void *), to be generic.
 *  - Priorities are separate from elements, and paired together in the queue.
 *  - Smaller priority values are more important.
 * Author: Francois Pitt, March 2012.
 */
#ifndef MIN_PQ_H
#define MIN_PQ_H

/******************************************************************************
 *  Preprocessor directives, constants, and types.                            *
 ******************************************************************************/

#include <stdlib.h> // for size_t

/* TYPE priority_t -- The type of priorities. */
typedef long priority_t;
// 'long' is the largest standard integer type, so the most general.

/* TYPE min_pq_t -- The type of a min priority queue. */
typedef struct min_pq min_pq_t;
// Information hiding: definition of struct min_pq will go in the .c file.

/******************************************************************************
 *  Functions.                                                                *
 ******************************************************************************/

/* FUNCTION min_pq_create
 *    Create and return a new min priority queue.
 * Parameters and preconditions:  none
 * Return value:
 *    a new min priority queue; NULL in case of error
 * Side-effects:
 *    memory has been allocated for a new min priority queue
 */
min_pq_t *min_pq_create(void);

/* FUNCTION min_pq_destroy
 *    Free the memory used for a min priority queue.
 * Parameters and preconditions:
 *    q != NULL: a min priority queue
 * Return value:  none
 * Side-effects:
 *    all memory allocated for q has been freed
 */
void min_pq_destroy(min_pq_t *q);

/* FUNCTION min_pq_size
 *    Return the size of a min priority queue.
 * Parameters and preconditions:
 *    q != NULL: a min priority queue
 * Return value:
 *    the number of element in q
 * Side-effects:  none
 */
size_t min_pq_size(const min_pq_t *q);

/* FUNCTION min_pq_insert
 *    Add an element with a given priority to a min priority queue.
 * Parameters and preconditions:
 *    q != NULL: a min priority queue
 *    e: the element to insert
 *    p: the priority for e
 * Return value:  none
 * Side-effects:
 *    contents of the queue have been changed to add e;
 *    will terminate the program in case of errors with memory allocation
 */
void min_pq_insert(min_pq_t *q, const void *e, priority_t p);

/* FUNCTION min_pq_get_min
 *    Return an element with smallest priority in a min priority queue.
 * Parameters and preconditions:
 *    q != NULL: a min priority queue
 * Return value:
 *    the element with smallest priority that was inserted first into the queue;
 *    NULL if the queue is empty
 * Side-effects:  none
 */
const void *min_pq_get_min(const min_pq_t *q);

/* FUNCTION min_pq_remove_min
 *    Remove and return an element with smallest priority in a min priority
 *    queue.
 * Parameters and preconditions:
 *    q != NULL: a min priority queue
 * Return value:
 *    the element with smallest priority that was inserted first into the queue;
 *    NULL if the queue is empty
 * Side-effects:
 *    contents of the queue have been changed to remove the element returned;
 *    will terminate the program in case of errors with memory allocation
 */
const void *min_pq_remove_min(min_pq_t *q);

#endif/*MIN_PQ_H*/