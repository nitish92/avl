#include <fstream>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "Tree.h"
using namespace std;
  
// A utility function to get the  
// height of the tree  
int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  
  
// A utility function to get maximum 
// of two integers  
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}

int min(int a, int b)  
{  
    return (a < b)? a : b;  
}  

/* Helper function that allocates a  
   new node with the given key and  
   NULL left and right pointers. */
Node* newNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; // new node is initially 
                      // added at leaf  
    return(node);  
}  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
Node *rightRotate(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;  
  
    // Perform rotation  
    x->right = y;  
    y->left = T2;  
  
    // Update heights  
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;  
  
    // Return new root  
    return x;  
}  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
Node *leftRotate(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
  
// Get Balance factor of node N  
int getBalance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
  
// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree.  
Node* insert(Node* node, int key, int *rotationsPointer, int *visits)  
{  
    /* 1. Perform the normal BST insertion */
    if (node == NULL)  
        return(newNode(key));  
  
    if (key < node->key)
    {
        *visits += 1;  
        node->left = insert(node->left, key, rotationsPointer, visits);  
    }
    else if (key > node->key)
    {
        *visits += 1;  
        node->right = insert(node->right, key, rotationsPointer, visits); 
    } 
    else // Equal keys are not allowed in BST  
    {
        *visits += 1;
        return node;
    }  
  
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    /* 3. Get the balance factor of this ancestor  
        node to check whether this node became  
        unbalanced */
    int balance = getBalance(node);  
  
    // If this node becomes unbalanced, then  
    // there are 4 cases  
  
    // Left Left Case  
    if (balance > 1 && key < node->left->key)
    {
        *rotationsPointer+=1;
        return rightRotate(node);
    }  
          
    // Right Right Case  
    if (balance < -1 && key > node->right->key)
    {
        *rotationsPointer+=1;
        return leftRotate(node);
    }  
          
  
    // Left Right Case  
    if (balance > 1 && key > node->left->key)  
    {  
        *rotationsPointer+=2;
        node->left = leftRotate(node->left);  
        return rightRotate(node);  
    }  
  
    // Right Left Case  
    if (balance < -1 && key < node->right->key)  
    {  
        *rotationsPointer+=2;
        node->right = rightRotate(node->right);  
        return leftRotate(node);  
    }  
  
    /* return the (unchanged) node pointer */
    return node;  
}

int lookup(Node* root, int find, int *visits)
{
    if(root != NULL)
    {
        if(find == root->key)
        {
            *visits +=1;
            return find;
        }
        else if(find < root->key)
        {
            *visits +=1;
            return lookup(root->left, find, visits);
        }
        else if(find > root->key)
        {
            *visits +=1;
            return lookup(root->right, find, visits);
        }
        else
            return -1;
    }
    else
        return -1;
}

void print_the_tree(Node* root, int *count)
{
    if(root != NULL)
    {
        if (root->left != NULL || root->right != NULL)
        {
            cout << string(*count, ' ' ) << string(*count, ' ' );
            cout << "Node(" << root->key << ", h=" << root->height -1 << "):" << endl;
            int s= *count+1;
            print_the_tree(root->left, &s);
            print_the_tree(root->right, &s);
        }
        if (root->left == NULL && root->right == NULL)
        {
            cout << string(*count, ' ' ) << string(*count, ' ' );
            cout << "Leaf(" << root->key << ")" << endl;
        }
    }
    else
    {
        cout << string(*count, ' ' ) << string(*count, ' ' );
        cout << "Null" << endl;
    }
}

void delete_everything(Node* root)
{
  if (root != NULL)
  {
    delete_everything(root->right);
    delete_everything(root->left);
    delete root;
  }
}
  
// A utility function to print preorder  
// traversal of the tree.  
// The function also prints height  
// of every node  
void preOrder(Node *root)  
{  
    if(root != NULL)  
    {  
        cout << root->key << " ";  
        preOrder(root->left);  
        preOrder(root->right);  
    }  
}