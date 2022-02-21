#include "binaryTree.h"
#include <stdlib.h>
#include <stdio.h>


Node* insert(Node* node, int data){   //recursive function, node starts from the r
    
    if (node == NULL){
        return newNode(data);
    }
    if (data < node->data){
        node->left  = insert(node->left, data);
    }
    else if (data > node->data){
        node->right = insert(node->right, data);
    }
    else{
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;  //new acestor height
    int balance = getHeightBalance(node);
////////////////////////////////////////////////////////////
    //next, checking if node becomes unbalanced
    // LL
    if (balance > 1 && data < node->left->data){
        return rightRotate(node);
    }

     // LR
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // RR
    if (balance < -1 && data > node->right->data){
        return leftRotate(node);
    }

    // RL
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}


Node* deleteNode(Node* root, int data){    ///function is recursive


    //deletion

    if (root == NULL){     //if the tree is empty
        return root;
    }  

    if ( data < root->data ){            //if left side
        root->left = deleteNode(root->left, data);
    }
    else if( data > root->data ){         //if rigth side
        root->right = deleteNode(root->right, data);
    } 
    else            //if it is the root is the key
    {
        
        if((root->left == NULL) || (root->right == NULL))   // node with one child or no child
        {
            Node *temp;
            //  root->left ? root->left : root->right;
            if(root->left){
                temp = root->left;
            }
            else{
                temp = root->right;
            }

            if (temp == NULL)            //if no children
            {
                temp = root;
                root = NULL;
            }
            else //one child
             *root = *temp;         //copying the child
            free(temp);             
        }
        else            //if two children
        {

            struct Node* temp = minValueNode(root->right);            //smallest in the right side of the tree

            root->data = temp->data;                                  //copying that node instead of the old one, becasuse the leftmost value on the right side, will be the closest to the former value and 
                                                                      //won't mix up the tree
            root->right = deleteNode(root->right, temp->data);        //deleting that leftmost value
        }
    }
 
    if (root == NULL){    // If the tree had one node?
      return root;
    }

 
   
    root->height = max(height(root->left), height(root->right)) + 1;    //updating height
 
    //checking balance
    int balance = getHeightBalance(root);
 
    // LL
    if (balance > 1 && getHeightBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }

    // LR
    if (balance > 1 && getHeightBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // RR
    if (balance < -1 && getHeightBalance(root->right) <= 0){
        return leftRotate(root);
    }

    // RL
    if (balance < -1 && getHeightBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

int findMin(Node* node){   //recursive, no loop,find min in the subtree

    Node* temp = NULL;
    temp = node;
    if(temp == NULL){
        return 0;
    }
    if(temp->left == NULL){
        return temp->data;
    }
    else{
        return findMin(temp->left);
    }

}
int findMax(Node* node){   //recursive, no loop,find max in the subtree

    Node* temp = NULL;
    temp = node;
    if(temp == NULL){
        return 0;
    }
    if(temp->right == NULL){
        return temp->data;
    }
    else{
        return findMax(temp->right);
    }
    
}

void inOrder(Node* node){
    Node* temp = node;
    if(temp != NULL) {
        inOrder(temp->left);
        printf("%d  ", temp->data);
        inOrder(temp->right);
    }
}
void preOrder(Node* node){
    Node* temp = node;
    if(temp != NULL){
        printf("%d  ", temp->data);
        inOrder(temp->left);
        inOrder(temp->right);
    }
}
void postOrder(Node* node){
    Node* temp = node;
    if(temp != NULL){
        inOrder(temp->left);
        inOrder(temp->right);
        printf("%d  ", temp->data);
    } 
}

Node* search(Node* root, int data)
{

    if (root == NULL || root->data == data){
       return root;         //root is null or key is root
    }

    if (root->data < data){
       return search(root->right, data);      //num is bigger than root's key
    }
 
    return search(root->left, data);       //num is smaller than root's key
}









///////////////////////////////////////////////////////////////////////////
//iternal functions, for functionality of a library
int getHeightBalance(Node* node){
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node *minValueNode(struct Node* node){
    struct Node* temp = node;
 
    while (temp->left != NULL) {   //searching for the leftmost value
        temp = temp->left;
    }
 
    return temp;
}


Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;    // rotation
    y->left = temp;
 
    y->height = max(height(y->left), height(y->right))+1;    // Updating height
    x->height = max(height(x->left), height(x->right))+1;
 
    return x; //root
}

Node* leftRotate(Node* x){
    Node *y = x->right;
    Node *temp = y->left;
 

    y->left = x;
    x->right = temp;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
 
    return y;
}

Node* newNode(int data){           /// creates newNode with the datat value
    Node* node = (Node*)malloc(sizeof(Node*));

    node->data = data;
    node->height = 1;  // node is firtly a leaf, therefore height is only 1
    node->left   = NULL;
    node->right  = NULL;

    return node;
}

int height(Node *node){
    if(node == NULL){
        return 0;
    } else {
        return node->height;
    }
}

int max(int x, int y){
    if(x > y){
        return x;
    } else {
        return y;
    }
}

int isEmpty(Node* root) {
    if(root == NULL){
        return 1;
    } else {
        return 0;
    }
}