
#include <stdio.h>
#include <stdlib.h>

//Question 1 and 2 struct
struct node {
    int data; 
    struct node *next; 
};

//Question 3 universal 
struct node_universal {
    void *p_data; //a pointer to data (allocated with malloc)
    int type; // 0 if int, 1 if float, 2 if double
    struct node_universal *next;
};

//Question 1
void print_all(struct node* head){
    struct node* cur = head;  
    while(cur != NULL){
        printf("%d\n", cur->data);
        cur = cur->next;
    }     
}

//Question 2
int print_all_recursive(struct node* cur){
    if (cur == NULL){
        return 0;
    }
    printf("%d\n", cur->data);
    print_all_recursive(cur->next);
}

//Question 3 Int
void append_int(struct node_universal *head, int value){
    struct node_universal *cur = head;
    while(cur->next != NULL) {
        cur = cur->next;
    }

    struct node_universal *node_universal = (struct node_universal *)malloc(sizeof(struct node_universal));
    node_universal->type = 0;
    node_universal->p_data = (int*)malloc(sizeof(int));
    *(int *)(node_universal->p_data) = value;
    node_universal->next = NULL;
    cur->next = node_universal;
}

//Question 3 Float
void append_float(struct node_universal *head, float value){
    struct node_universal *cur = head;
    while(cur->next != NULL) {
        cur = cur->next;
    }

    struct node_universal *node_universal = (struct node_universal *)malloc(sizeof(struct node_universal));
    node_universal->type = 1;
    node_universal->p_data = (float*)malloc(sizeof(float));
    *(float *)(node_universal->p_data) = value;
    node_universal->next = NULL;
    cur->next = node_universal;
}

//Question 3 Double
void append_double(struct node_universal *head, double value){
    struct node_universal *cur = head;
    while(cur->next != NULL) {
        cur = cur->next;
    }
    struct node_universal *node_universal = (struct node_universal *)malloc(sizeof(struct node_universal));
    node_universal->type = 2;
    node_universal->p_data = (double*)malloc(sizeof(double));
    *(double *)(node_universal->p_data) = value;
    node_universal->next = NULL;
    cur->next = node_universal;
}

//Question 3 Append All Concept
void append_all(struct node_universal *head, int type, double value){
    if(type == 0){
        value = (int)(value);
        append_int(head, value);
    }
    if(type == 1){
        value = (float)(value);
        append_float(head, value);
    }
    if(type == 2){
        append_double(head, value);
    }
}

//Question 3 Print
void print(struct node_universal *head){
    struct node_universal* cur = head; 
    while(cur != NULL){
        int type = cur->type;
        if(type == 0){
            printf("%d\n", *(int*)(cur->p_data));
        }
        if(type == 1){
            printf("%f\n", *(float*)(cur->p_data));
        }
        if(type == 2){
            printf("%lf\n", *(double*)(cur->p_data));
        }
        cur = cur->next;
    }     
}


//main block
int main(void){

    //Questions 1 and 2: int linked list
    struct node* node0 = (struct node*)malloc(sizeof(struct node));
    node0->data = 3;

    struct node* node1 = (struct node*)malloc(sizeof(struct node));
    node0->next = node1;
    node1->data = 5;

    struct node* node2 = (struct node*)malloc(sizeof(struct node));
    node1->next = node2;
    node2->data = 7;
    
    struct node* node3 = (struct node*)malloc(sizeof(struct node));
    node2->next = node3;
    node3->data = 9;
    node3->next = NULL;

    print_all(node0);
    print_all_recursive(node0);



    //Question 3: universal linked list
    struct node_universal* node_universal0 = (struct node_universal*)malloc(sizeof(struct node_universal));
    node_universal0->type = 0;
    node_universal0->p_data = (int*)malloc(sizeof(int));
    *(int*)(node_universal0->p_data) = 4;

    struct node_universal* node_universal1 = (struct node_universal*)malloc(sizeof(struct node_universal));
    node_universal0->next = node_universal1;
    node_universal1->type = 1;
    node_universal1->p_data = (float*)malloc(sizeof(float));
    *(float*)(node_universal1->p_data) = 4.5;

    struct node_universal* node_universal2 = (struct node_universal*)malloc(sizeof(struct node_universal));
    node_universal1->next = node_universal2;
    node_universal2->type = 2;
    node_universal2->p_data = (double*)malloc(sizeof(double));
    *(double*)(node_universal2->p_data) = 4.9054860;
    node_universal2->next = NULL;

    append_all(node_universal0, 0, 3.0);
    print(node_universal0);
    
    return 0;
}