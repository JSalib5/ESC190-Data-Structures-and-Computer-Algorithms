#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void insert(struct node *head, int value){
    struct node *cur = head;
    while(cur->next != NULL) {
        cur = cur->next;
    }
    struct node *node_new = (struct node *)malloc(sizeof(struct node));
    node_new->data = value;
    node_new->next = NULL;
    cur->next = node_new;
}

void delete_list(struct node *head, int value){
    struct node *cur = head;
    while((cur->next)->data != value) {
        cur = cur->next;
    }
    struct node* temp = cur->next;
    cur->next = (cur->next)->next;
    free(temp);
}

void free_list(struct node *head){
    struct node *next = NULL;
    while(head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}


void print_list(struct node* head){
    struct node* cur = head;  
    while(cur != NULL){
        printf("%d\n", cur->data);
        cur = cur->next;
    }  
    
}
