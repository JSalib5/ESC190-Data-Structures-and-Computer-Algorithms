#include <stdio.h>
#include <stdlib.h>
#include "min_pq.h"

/******************************************************************************
 *  Constants, macros, and types.                                             *
 ******************************************************************************/

#define MIN_CAPACITY 4 

#define PARENT(node)      ((node) / 2)    
#define LEFT_CHILD(node)  ((node) * 2)     
#define RIGHT_CHILD(node) ((node) * 2 + 1) 

//Priority Queue Implementation Using Heap Data Structure 
typedef struct heap_item {
    const void *element;
    priority_t priority; 
} item_t;

struct min_pq {
    size_t size;
    size_t capacity;
    item_t *heap;  
};

typedef size_t node_t;

static void update_capacity(min_pq_t *q);

static void percolate_up(item_t *heap, node_t node);

static void percolate_down(item_t *heap, size_t size);

static node_t min_child(const item_t *heap, node_t node, size_t size);

static void heap_swap(item_t *heap, node_t i, node_t j);

min_pq_t *min_pq_create(void){
    min_pq_t *q = malloc(sizeof(struct min_pq));
    if (q) {
        q->size = 0;
        q->capacity = MIN_CAPACITY;
        q->heap = malloc(q->capacity * sizeof(item_t));
        if (! q->heap) { free(q); q = NULL; }
    }
    return q;
}

void min_pq_destroy(min_pq_t *q){
    free(q->heap);
    free(q);
}

size_t min_pq_size(const min_pq_t *q){
    return q->size;
}

void min_pq_insert(min_pq_t *q, const void *e, priority_t p){
    update_capacity(q);
    q->size++;
    q->heap[q->size].element = e;
    q->heap[q->size].priority = p;
    percolate_up(q->heap, q->size);
}

const void *min_pq_get_min(const min_pq_t *q){
    if (min_pq_size(q) == 0)  return NULL;
    return q->heap[1].element;
}

const void *min_pq_remove_min(min_pq_t *q){
    if (min_pq_size(q) == 0)  return NULL;
    update_capacity(q);
    heap_swap(q->heap, 1, q->size--);
    percolate_down(q->heap, q->size);
    return q->heap[q->size + 1].element;
}

/******************************************************************************
 *  Definitions for helper functions -- see above for documentation.          *
 ******************************************************************************/

void update_capacity(min_pq_t *q){
    size_t old_cap = q->capacity;
    if (q->size + 1 == q->capacity)
        q->capacity *= 2;
    else if (q->size + 1 == q->capacity / 4 && q->capacity >= 2 * MIN_CAPACITY)
        q->capacity /= 2;
    if (q->capacity != old_cap) {
        q->heap = realloc(q->heap, q->capacity * sizeof(item_t));
        if (q->heap == NULL) {
            perror("ERROR: memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
}

void percolate_up(item_t *heap, node_t node){
    node_t parent = PARENT(node);
    while (parent >= 1 && heap[parent].priority > heap[node].priority) {
        heap_swap(heap, node, parent);
        node = parent;
        parent = PARENT(node);
    }
}

void percolate_down(item_t *heap, size_t size){
    node_t node = 1;
    node_t child = min_child(heap, node, size);
    while (child <= size && heap[child].priority < heap[node].priority) {
        heap_swap(heap, node, child);
        node = child;
        child = min_child(heap, node, size);
    }
}

node_t min_child(const item_t *heap, node_t node, size_t size){
    node_t left_child = LEFT_CHILD(node);
    node_t right_child = RIGHT_CHILD(node);
    if (right_child > size
             || heap[left_child].priority <= heap[right_child].priority)
        return left_child;
    else
        return right_child;
}

void heap_swap(item_t *heap, node_t i, node_t j){
    item_t temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}