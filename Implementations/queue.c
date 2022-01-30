#include <stdio.h>
#include <stdlib.h>

//Queue Implementation in C using traditional Linked Lists
typedef struct Queue{
    int data;
    struct Queue * next;
} q;

q* init_q(int value){
    q* qnode = (q*)malloc(sizeof(q));
    qnode->data = value;
    qnode->next = NULL;
    return qnode;
}

void enqueue(q* head, int value){
    q* cur = head;
    while (cur->next != NULL){
        cur = cur->next;
    }
    q* newnode = (q*)malloc(sizeof(q));
    cur->next = newnode;
    newnode->next = NULL;
    newnode->data = value;
}

int dequeue(q** head){
    int value = (*head)->data;
    q* temp = *head;
    *head = (*head)->next; 
    free(temp);
    return value;
}

int peek(q* head){
    int value = head->data;
    return value;
}

void display(q* head){
    q* cur = head;
    while (cur != NULL){
        printf("%d \n", cur->data);
        cur = cur->next;
    }
}

int main(){
    q* queue = init_q(3);
    enqueue(queue, 1);
    enqueue(queue, 4);
    enqueue(queue, 7);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    display(queue);
}