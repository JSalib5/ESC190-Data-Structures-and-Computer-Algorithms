#include <stdio.h>
#include <stdlib.h>
#define MAX 50
//Stack Structure Implementation Using C Arrays
typedef struct Stack{
    int items[MAX];
    int top; 
}s;

s* init_s(int value){
    s * stack = (s*)malloc(sizeof(s));
    stack->items[0] = value;
    stack->top = 0;
    return stack;
}

void push(s* stack, int value){
    stack->top++;
    stack->items[stack->top] = value;
}

int pop(s* stack){
    printf("%d \n", stack->items[stack->top]);
    stack->top--;
}

void display(s* stack){
    for (int i = 0; i <= stack->top; i++){
        printf("%d \n", stack->items[i]);
    }
}

int main(){
    s* s = init_s(5);
    push(s, 3);
    push(s, 7);
    push(s, 5);
    pop(s);
    display(s);
    return 0;
}