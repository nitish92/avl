#ifndef TREE_H
#define TREE_H

class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};

int height(Node *N);
int max(int a, int b);
int min(int a, int b);
Node* newNode(int key);
Node* rightRotate(Node *y);
Node* leftRotate(Node *x);
int getBalance(Node *N);
Node* insert(Node* node, int key, int *rotations, int *visits);
void preOrder(Node *root);
int lookup(Node* root, int find, int *visits);

void printTree(Node* root, int *c);


#endif