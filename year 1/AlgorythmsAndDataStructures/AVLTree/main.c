#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

int main(){
    Node* root = NULL;

    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 15);
    root = insert(root, 14);
    root = insert(root, 13);
    root = insert(root, 12);
    root = insert(root, 11);
    root = insert(root, 10);

    inOrder(root);
    printf("\n");

    preOrder(root);
    printf("\n");

    postOrder(root);
    printf("\n");
    
    Node* test1 = search(root, 14);
    Node* test2 = search(root, 40);

    if(test1 != NULL){
        printf("test1: %d\n", test1->data);
    }
    if(test2 != NULL){
        printf("test2: %d\n", test2->data);
    }
    else{
        printf("test2: not found\n");
    }

    deleteNode(root, 12);
    deleteNode(root, 11);

    inOrder(root);
    printf("\n");

    preOrder(root);
    printf("\n");

    postOrder(root);
    printf("\n");


    return 0;
}