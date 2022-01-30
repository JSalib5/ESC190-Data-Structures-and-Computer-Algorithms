#include <stdio.h>

//Question 1
void change_value(int* p_b){
    *p_b = 10;
}



int main(void){
    //Question 1
    /*
    int b = 5;
    printf("Original Value: %d", b);
    change_value(&b);
    printf("\nNew Value: %d", b);
    //return 0;
    */
    //Question 2
    //initializing list to be sorted
    int a[5] = {4, 2, 1, 7, 6};
    //initializing sorting variables
    int i = 0;
    int length = sizeof(a)/sizeof(a[0]);
    int hold = 0;
    //Sorting
    for(i = 0; i < length; i++){
        int j = i; 
        while(a[j-1] > a[j]){
            hold = a[j - 1];
            a[j - 1] = a[j];
            a[j] = hold;
            j--;
        }
    }
    //Printing
    for(i = 0; i < length; i++){
       printf("%d ", a[i]);
   }
}


/*
Lab 1
=====

1. In your main function, define the variable int a and initialize it to 5.
   Now, write a function which does not return anything, but can set the value of 
   an integer to 10.
   
   Use this function to set the value of a to 10.
   
   Use printf to demonstrate that the value of a changed.
   
   Now, put a breakpoint at int a = 5, and trace the code.

2. Implement a function that performs Insertion Sort https://en.wikipedia.org/wiki/Insertion_sort#Algorithm
   The function should take in an array of integers, and modify the array so that it's 
   sorted in increasing order.
  
   Here is code to print out an array of integers using a for-loop and a while-loop in C.

   int i = 0;
   int a[5] = {2, 3, 4, 5, 6};
   // initialize i to 0, run the loop while i < 5, and increase i by 1 every time;
   // Here, i++ is the same as i = i + 1
   for(i = 0; i < 5; i++){
       printf("%d\n", a[i]);
   }

   i = 0;
   while(i < 5){
       printf("%d\n", a[i]);
       i++; // same as i = i + 1
   }
   */