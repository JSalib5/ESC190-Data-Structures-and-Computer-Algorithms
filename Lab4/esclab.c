/*
1. Write a header file for operating on linked lists (include at least inserting a value, deleting a node with a specified value (if there is more than one, delete the first one), and freeing the entire linked list). Write a file linkedlist.c that implements the functions declared in the h file. Now write a main file with a main function that uses the functions declared in the h file. Make sure that everything compiles and runs correctly.

2. In Python, write a function find(L, e) that takes in a sorted list L and an element e, and returns the lowest index in L such that L[i] == e. (-1 if there is no such index)
   Write a function that takes in a sorted linst L and an element e, and returns the index of the highest index in L such that L[i] == e. (-1 if there is no such index).
   The function should run in O(log(n)) time.
   This should help you with Project 1.
*/
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

int main(void){
    struct node* node0 = (struct node*)malloc(sizeof(struct node));
    node0->data = 3;
    node0->next = NULL;
    
    
    //initialize: 5
    //insert(node0, 5);
    printf("Insert Node\n");
    print_list(node0);
    //insert nodes: 5, 4, 3
    insert(node0, 4);
    insert(node0, 3);
    printf("Insert Nodes\n");
    print_list(node0);
    //delete  node 4: 5, 3
    delete_list(node0, 4);
    printf("Delete Node\n");
    print_list(node0);
    //free list
    free_list(node0);
    printf("Free List\n");
    
    return 0;
}

