/*
1. The function strcat in <string.h> appends a source string to a destination
   string. It returns the destination string. Write a version of the function
   char *my_strcat(char *dest, char *src)

2. Write a recursive version of strcmp. The signature must be
   int my_strcmp_rec(char *str1, char *str2).
   The function should return 0 if the contents of str1 and str2
   are the same.
   If the contents of str1 and str2 are not the same, and the first
   character that doesn't match is at location i, the function
   should return str1[i]-str2[i].
   Each character corresponds to an integer value. For example,
   'A' corresponds to 65, 'B' corresponds to 66, ..., 'Z' 
   corresponds to 90, 'a' corresponds to 97, 'b' corresponds to
   98, ... 
   https://simple.wikipedia.org/wiki/ASCII#/media/File:ASCII-Table-wide.svg
   Returning the difference between the first pair of unmatched characters
   makes it so that strcmp returns a negative value if str1 comes before
   str2 in a lexicographic order.

3. The C library function atoi converts a string to an integer. Write
   your own version of the function, with the signature
   int atoi(char *str)
   Hints:
   * The function isdigit (defined in <ctype.h>) can be used to tell if 
   a character is a digit
   * You can convert a digit c to an integer value using c-'0'

4. Implement Floyd's cycle-finding algorithm for a linked list in C
   https://en.wikipedia.org/wiki/Cycle_detection#Floyd's_tortoise_and_hare
   Your function should return 1 if there is a cycle in the linked list,
   and 0 otherwise. (Note that the linked code does more than that).

   Test your algorithm.
   */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data; 
    struct node *next; 
};

//Question 1
char *my_strcat(char *dest, char *src){
    char* p = dest+strlen(dest);
    while (*src !=  '\0'){
       *p++ = *src++;
    }
    *p = '\0';
    return dest;
}


//Question 2
int my_strcmp_rec(char *str1, char *str2) {
    if (*str1 == *str2) {
      if (*str1 == '\0' && *str2 == '\0'){
          return 0;
      }  
      str1++;
      str2++;
      my_strcmp_rec(str1, str2);
    }
    else {
       return(*str1-*str2);
    }
}


//Question 3
int my_atoi(char *str) {
   int c = 0;
   while (isdigit(*str)) {
      c = c*10 + *str-'0';
      str++;
    }
    return c;
}


//Question 4
int floyd(struct node* head){
    struct node* tortoise = head;
    struct node* hare = head;
    while (hare->next != NULL && tortoise->next != NULL && (hare->next)->next != NULL){
        tortoise = tortoise->next;
        hare = (hare->next)->next;
        if (tortoise == hare){
            return 1;
        }
    }
    return 0;
}



int main(void){

   //Question 1
    char s1[10] = "johnathon";
    char s2[5] = "inho";
    printf("%s\n",my_strcat(s1,s2));

    //Question 2
    char str1[6] = "johb";
    char str2[5] = "joha";
    printf("%d\n",my_strcmp_rec(str1,str2));

    //Question 3
    char str3[6] = "3";
    printf("%d\n",my_atoi(str3));

    //Question 4
    struct node* node0 = (struct node*)malloc(sizeof(struct node));
    node0->data = 2;

    struct node* node1 = (struct node*)malloc(sizeof(struct node));
    node0->next = node1;
    node1->data = 0;

    struct node* node2 = (struct node*)malloc(sizeof(struct node));
    node1->next = node2;
    node2->data = 6;

    struct node* node3 = (struct node*)malloc(sizeof(struct node));
    node2->next = node3;
    node3->data = 3;

    struct node* node4 = (struct node*)malloc(sizeof(struct node));
    node3->next = node4;
    node4->data = 1;

    struct node* node5 = (struct node*)malloc(sizeof(struct node));
    node4->next = node5;
    node5->data = 6;

    struct node* node6 = (struct node*)malloc(sizeof(struct node));
    node5->next = node6;
    node6->data = 3;

    struct node* node7 = (struct node*)malloc(sizeof(struct node));
    node6->next = node3;
    node7->data = 1;

    struct node* node8 = (struct node*)malloc(sizeof(struct node));
    node7->next = node8;
    node8->data = 0;
    node8->next = NULL;
 
    printf("%d\n",floyd(node0));
}

