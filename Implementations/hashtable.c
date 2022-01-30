#include "hashtable.h"
#include <stdio.h>
#include <string.h>

void ht_create(struct hashtable **ht, double max_load, int (*hash_fn)(int key, int table_size), int (*probe_fn)(int i, int value))
{
    *ht = (struct hashtable *)malloc(sizeof(struct hashtable));
    (*ht)->table = (struct table_elem *)calloc(sizeof(struct table_elem) * 10, 1);
    (*ht)->table_size = 10;
    (*ht)->hash_fn = hash_fn;
    (*ht)->n_elems = 0;
    (*ht)->probe_fn = probe_fn;
    (*ht)->hash_fn = hash_fn;
    (*ht)->max_load = max_load;
    
}

void ht_destroy(struct hashtable *ht)
{
    free(ht->table);
    free(ht);
}

bool ht_delete(struct hashtable *ht, int key)
{
    int hash = (ht->hash_fn)(key, ht->table_size);
    int add = 0;
    int i = 0;
    while(ht->table[(hash+add)%ht->table_size].key != key && i < ht->table_size){
        i += 1;
        add = ht->probe_fn(i, key);
    }
    if(ht->table[(hash+add)%ht->table_size].key == key){
        ht->table[(hash+add)%ht->table_size].deleted = true;
        return true;
    }else{
        return false;
    }
    
}

void ht_print(struct hashtable *ht)
{
    printf("i\tkey\tvalue\tfull\tdeleted\t\n");
    for(int i = 0; i < ht->table_size; i++){
        printf("%d\t%d\t%d\t%d\t%d\t\n", i,
                                        ht->table[i].key,
                                        ht->table[i].value,
                                        ht->table[i].full,
                                        ht->table[i].deleted);
    }
    printf("\n\n\n");
}

bool ht_set(struct hashtable *ht, int key, int value)
{
    int hash = (ht->hash_fn)(key, ht->table_size);
    int add = 0;
    int i = 0;
    while(ht->table[(hash+add)%ht->table_size].key != key && ht->table[(hash+add)%ht->table_size].full && !ht->table[(hash+add)%ht->table_size].deleted && i < ht->table_size){
        i += 1;
        add = ht->probe_fn(i, key);
    }

    if(i == ht->table_size){
        return false;
    }

    ht->table[(hash+add)%ht->table_size].key = key;
    ht->table[(hash+add)%ht->table_size].value = value;
    ht->table[(hash+add)%ht->table_size].full = true;
    ht->table[(hash+add)%ht->table_size].deleted = false;
    ht->n_elems += 1;


    
    if( ((double)(ht->n_elems + 1))/ht->table_size >= ht->max_load ){
        struct hashtable *ht1;
        ht_create(&ht1, ht->max_load, ht->hash_fn, ht->probe_fn);
        ht1->table = realloc(ht1->table, sizeof(struct table_elem) * ht->table_size * 2);
        ht1->table_size = ht->table_size * 2;
        memset(ht1->table, 0, sizeof(struct table_elem) * ht1->table_size);
        for(int j = 0; j < ht->table_size; j++){
            if(ht->table[j].full  && !ht->table[j].deleted){
                
                ht_set(ht1, ht->table[j].key, ht->table[j].value);
            }
        }
        free(ht->table);
        ht->table = ht1->table;
        ht->table_size = ht1->table_size;
        free(ht1);
    }
      

    return true;
}

bool ht_in(struct hashtable *ht, int key)
{
    int hash = (ht->hash_fn)(key, ht->table_size);
    int add = 0;
    int i = 0;
    while(ht->table[(hash+add)%ht->table_size].key != key && ht->table[(hash+add)%ht->table_size].full && !ht->table[(hash+add)%ht->table_size].deleted && i < ht->table_size){
        i += 1;
        add = ht->probe_fn(i, key);
    }

    return ht->table[(hash+add)%ht->table_size].key == key && !ht->table[(hash+add)%ht->table_size].deleted;
}

int ht_get(struct hashtable *ht, int key)
{
    int hash = (ht->hash_fn)(key, ht->table_size);
    int add = 0;
    int i = 0;
    while(ht->table[(hash+add)%ht->table_size].key != key && ht->table[(hash+add)%ht->table_size].full && !ht->table[(hash+add)%ht->table_size].deleted && i < ht->table_size){
        i += 1;
        add = ht->probe_fn(i, key);
    }

    return ht->table[(hash+add)%ht->table_size].value;
}