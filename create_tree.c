#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

Tnode *create_new_node(int key);
Tnode *leftRotate(Tnode *a);
Tnode *create_tree(char *filename);
Tnode *insert(Tnode *node, int key);
int getBalance(Tnode *N);
Tnode *leftRotate(Tnode *a);
Tnode *rightRotate(Tnode *a);
void preOrder(Tnode *root);
int max(int a, int b);
int height(Tnode *N);

Tnode *create_tree(char *filename)
{
    //create tree
}

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


int main()
{
  Tnode *root = NULL;

  /* Constructing tree given in the above figure */
  root = insert(root, 10);
  insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);

  /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */

  printf("Preorder traversal of the constructed AVL"
         " tree is \n");
  preOrder(root);

  return 0;
}




