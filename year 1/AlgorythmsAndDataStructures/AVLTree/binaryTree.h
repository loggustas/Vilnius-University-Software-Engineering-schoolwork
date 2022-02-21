//AUTHOR:   Gustas Logvinovas
//ID:       590

#ifndef AVL_TREE_H
#define AVL_TREE_H

//needs two libraries, stdio for printing, and stdlib for allocating memory
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{        //structure of the node
    int data;
    int height;
    struct Node *left;
    struct Node *right;

}Node;

/*
@function insert
@return Node*
@param node - a pointer to a root or a node of a binary search tree
@param data - the key of data to insert
*/
Node* insert(Node* node, int data);         //inserting node

/*
@function deleteNode
@return Node*
@param node - a pointer to a root of a binary search tree
@param data - the key of data to delete
*/
Node* deleteNode(Node* root, int data);     //deleting node

/*
@function findMin
@return int
@param node - a pointer to a root of a binary search tree
*/
int findMin(Node* node);    //recursive, no loop,find min in the subtree

/*
@function findMax
@return int
@param node - a pointer to a root of a binary search tree
*/
int findMax(Node* node);    //recursive, no loop,find max in the subtree

//printing list
/*
@function inOrder
@return void
@param node - a pointer to a root of a binary search tree
*/
void inOrder(Node* node); 

/*
@function preOrder
@return void
@param node - a pointer to a root of a binary search tree
*/
void preOrder(Node* node);

/*
@function postOrder
@return void
@param node - a pointer to a root of a binary search tree
*/
void postOrder(Node* node);


/*
@function search
@return Node*
@param node - a pointer to a root of a binary search tree
@param data - the key of data to search
*/
Node* search(Node* root, int data);     //search for number





//iternal functions for functionality of a library. SHOULD NOT USE!
int getHeightBalance(Node* node);  
Node *minValueNode(struct Node* node);

Node* rightRotate(Node* y);
Node* leftRotate(Node* x);

Node* newNode(int data);

int height(Node *node);
int max(int x, int y);
int isEmpty(Node* root);

#endif