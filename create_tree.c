#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"

//Helper function to find height of subtree without segfault
int height(Tnode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

//Inserting tree nodes into the AVL tree
Tnode *insert(Tnode *node, int key)
{
   if(node == NULL)
   {
    Tnode *new_node = create_new_node(key);
    return new_node;
   }

   if(key <= node->key)
   {
        node->left = insert(node->left, key);
   }
   else if(key > node->key)
   {
        node->right = insert(node->right, key);
   }


   node->height = max(height(node->left), height(node->right)) + 1;

   int balance = getBalance(node);

   //LL case
   if (balance > 1 && key <= node->left->key)
   {
        return rightRotate(node);
   }

   //RR case
   if (balance < -1 && key > node->right->key)
   {
        return leftRotate(node);
   }

   //LR case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

   //RL case
    if (balance < -1 && key <= node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;

}

//get balance of node to see if it is imbalanced
int getBalance(Tnode *N)
{
    if (N == NULL)
        return 0;

    return height(N->left) - height(N->right);
}

//create a new tree node
Tnode *create_new_node(int key)
{
    Tnode *new_node = (Tnode *)malloc(sizeof(Tnode));
    new_node->height = 1;
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

//
int max(int a, int b)
{
    return (a > b)? a : b;
}

//Left Rotate
Tnode *leftRotate(Tnode *a)
{
    Tnode *b = a -> right;
    Tnode *bl = b -> left;

    b->left = a;
    a->right = bl;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;

    return b;

}

//Right rotate
Tnode *rightRotate(Tnode *a)
{
    Tnode *b = a->left;
    Tnode *br = b->right;

    b->right = a;
    a->left = br;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(a->left), height(a->right)) + 1;

    return b;
}

//Prints tree in preoreder
void preOrder(Tnode *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}


Tnode *deleteNode(Tnode *root, int key)
{
    //case 1: node to delete is head
    //case 2: node to delete has two children
    //case 3: node to delete one or no children

    //case 1: node to delete is head
    if (root == NULL)
    {
        return root;
    }

    if (key < root->key)
    {
        root->left = deleteNode(root->left,key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right,key);
    }
    else{
        if((root->left == NULL) || (root->right == NULL))
        {
            Tnode *temp = root->left ? root->left: root->right;

            if (temp == NULL)
            {
                temp = root;
                free(root);
            }
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            Tnode *temp = get_predecesor(root->left);
            root->key = temp->key;
            root->right = deleteNode(root->right,temp->key);
        }
    }
    if (root == NULL)
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

Tnode* get_predecesor(Tnode* node)
{
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}