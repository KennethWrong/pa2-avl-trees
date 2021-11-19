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

Tnode *deleteNode(Tnode *root, int key)
{


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
    //this is when our node equals the key to delete
    else{
        //If this node has one or no children
        if((root->left == NULL) || (root->right == NULL))
        {
            //temp to be the side that is not null
            Tnode *temp = root->left ? root->left: root->right;

            //When both children are NULL
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                //copy content of non-empty child
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            Tnode *temp = get_predecesor(root->left);
            root->key = temp->key;
            root->left = deleteNode(root->left,temp->key);
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
    Tnode * curr = node;
    while (curr->right != NULL)
    {
        curr = curr->right;
    }
    return curr;
}

//Prints tree in preoreder
void preOrder(Tnode *root, FILE *fptr)
{
    if(root != NULL)
    {
        char childs;
        if((root->left != NULL) && (root->right != NULL))
        {
            childs = '3';
        }
        else if((root->left == NULL) && (root->right == NULL))
        {
            childs = '0';
        }
        else{
            childs = root->left != NULL ? '2':'1';
        }
        fprintf(fptr, "%d %c\n", root->key, childs);
        preOrder(root->left, fptr);
        preOrder(root->right, fptr);
    }
}

void deallocate (Tnode * node)
{
    if(node==NULL)
        return;

    deallocate(node->right);
    deallocate(node->left);

    free(node);
}

Tnode *preorder_rebuild_BST(int *a, char *b, int *ptr)
{
    char *child_info = malloc(sizeof(char));
    *child_info = b[*ptr];

    printf("key value: %d\n",a[*ptr]);

    Tnode *root = (Tnode *)malloc(sizeof(Tnode));

    if(root != NULL){
        root->key = a[*ptr];
        (*ptr)++;

        if(*child_info == 3)
        {
            root->left = preorder_rebuild_BST(a,b, ptr);
            root->right = preorder_rebuild_BST(a,b, ptr); 
        }
        else if(*child_info == 2)
        {
            root->left = preorder_rebuild_BST(a,b, ptr);
        }
        else if(*child_info == 1){
            root->right = preorder_rebuild_BST(a,b,ptr); 
        }
    }
    return root;
}