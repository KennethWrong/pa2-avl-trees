#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"

//if balanced return 1, else 0
int check_balanced(Tnode *node){
    if (node == NULL){
        return 1;
    }
    int balance;
    balance = getBalance(node);
    printf("node height is is %d\n",node->height);
    printf("balance is %d\n",balance);
    if (balance > 1 || balance < -1 ){
        return 0;
    }
    int left;
    int right;
    left = check_balanced(node->left);
    right = check_balanced(node->right);

    if(left == 0 || right == 0){
        return 0;
    }else {
        return 1;
    }
}

//return 1 if binary else return 0
int check_if_bst(Tnode *node){
    if(node == NULL){
        return 1;
    }

    if(node->left != NULL && node->left->key > node->key ){
        return 0;
    }
    if(node->right != NULL && node->right->key <= node->key){
        return 0;
    }

    int left = check_if_bst(node->left);
    int right = check_if_bst(node->right);
    //printf("%d %d %d\n", left,right, node->key);
    if(left==0 || right==0){
        return 0;
    }
    return 1;
}