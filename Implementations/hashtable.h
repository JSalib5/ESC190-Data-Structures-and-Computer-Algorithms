#if !defined(HASHTABLE_H)
#define HASHTABLE_H


#include <stdlib.h>
#include <stdbool.h>

struct table_elem{
    int key;
    int value;
    bool full;
    bool deleted;
};


struct hashtable{
    size_t table_size;
    size_t n_elems;
    struct table_elem *table;   
    int (*probe_fn)(int i, int key);
    int (*hash_fn)(int key, int table_size);
    double max_load;
};

void ht_create(struct hashtable **ht, double max_load, int (*hash_fn)(int key, int table_size), int (*probe_fn)(int i, int key));
void ht_destroy(struct hashtable *ht);
bool ht_set(struct hashtable *ht, int key, int value);
bool ht_delete(struct hashtable *ht, int key);
void ht_print(struct hashtable *ht);
bool ht_in(struct hashtable *ht, int key);
int ht_get(struct hashtable *ht, int key);

#endif