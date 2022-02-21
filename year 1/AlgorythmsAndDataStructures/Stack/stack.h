//Gustas Logvinovas

#ifndef STACK_H
#define STACK_H

#include <stdlib.h>             //needs stdlib for memory allocation

struct node {                   //structure of the node
    int data;
    struct node* link;
};


void push(int data);   //pushes data to the stack
int pop();             //pops data to the stack

int stackIsEmpty();    //checks if the stack is empty, returns 1 if yes, 0 if no
void printStack();     //prints the entire stack

int peek();            //returns the top element, without deleting it


#endif