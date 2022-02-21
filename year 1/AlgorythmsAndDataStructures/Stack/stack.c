#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct node *top = NULL;

void push(int data) {
    struct node *newNode;
    newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        printf("Stack Overflow.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->link = top;
    top = newNode;
}

int pop(){
    if(stackIsEmpty()){
        printf("Can't pop element, because stack is empty");
        exit(1);
    }
    struct node *temp;
    temp = top;
    int value = temp->data;
    top = top->link;

    free(temp);
    return value;

}

int stackIsEmpty(){
    if(top == NULL){
        return 1;
    } 
    else{
        return 0;
    }
}

void printStack(){
    struct node* temp;
    temp = top;
    if(stackIsEmpty()){
        printf("Stack is empty.\n");
        exit(1);
    }
    printf("The elements starting from the top: \n");
    while(temp) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int peek(){
    if(stackIsEmpty()){
        printf("Stack is empty.\n");
        exit(1);
    }
    return top->data;
}