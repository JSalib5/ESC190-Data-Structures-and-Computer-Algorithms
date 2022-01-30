#if !defined(LINKEDLIST_H)
#define LINKEDLIST_H
struct node {
    int data; 
    struct node *next; 
};

void insert(struct node *head, int value);

void delete_list(struct node *head, int value);

void free_list(struct node *head);

void print_list(struct node *head);

#endif