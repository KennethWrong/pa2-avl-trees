#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"
#include "validate.h"

void treeTraversal(Tnode *node);

int build_tree_binary(char* infile, char * outfile)
{
    FILE *read_ptr;
    FILE *write_ptr;
    write_ptr = fopen(outfile, "wb");
    read_ptr = fopen(infile, "rb");
    

    if(read_ptr == NULL)
    {
        return -1;
    }

    Tnode *root = NULL;

    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    if(size_of_file%(sizeof(int)+sizeof(char)) != 0){
        return -1;
    }

    if(size_of_file == 0){
        return -1;
    }

    int c = fgetc(read_ptr);
    int *curr_int = malloc(sizeof(int));
    char *curr_char = malloc(sizeof(char));
    long int size = ftell(read_ptr);
    
    while (c != EOF)
    {
        ungetc(c,read_ptr);
        size = ftell(read_ptr);
        fread(curr_int,sizeof(int) ,1,read_ptr);
        fread(curr_char,sizeof(char) ,1,read_ptr);
        long int size2 = ftell(read_ptr);
        if (size2 - size < 3){
            deallocate(root);
            free(curr_char);
            free(curr_int);
            return 0;
        }
        else{
            size = size2;
        }

        if(*curr_char == 'i'){
            root = insert(root, *curr_int);
        }
        else if(*curr_char == 'd'){
            root = deleteNode(root, *curr_int);
        }
        else{
            deallocate(root);
            free(curr_char);
            free(curr_int);
            return 0;
        }
        c = fgetc(read_ptr);
    }
    preOrder(root, write_ptr);
    free(curr_int);
    free(curr_char);
    deallocate(root);

    return 1;
}

int build_tree_e(char* infile, char *outfile)
{
    FILE *read_ptr;
    read_ptr = fopen(infile, "rb");
    int file_validity;

    if(read_ptr == NULL)
    {
        fprintf(stdout,"-1,X,X\n");
        return 1;
    }
    Tnode *root = NULL;

    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    if (size_of_file % (sizeof(int) + sizeof(char)) != 0){
        fprintf(stdout,"0,X,X\n");
        return 1;
    }
    if(size_of_file <= 0 || size_of_file <= sizeof(int) || size_of_file <= sizeof(char)){
        fprintf(stdout, "0,X,X\n");
        return 1;
    }

    int total_nodes = size_of_file / (sizeof(int) + sizeof(char));
    int *pre_order_array = malloc(total_nodes * sizeof(int));
    char *number_of_child_array = malloc(total_nodes * sizeof(char));

    int *curr_int = malloc(sizeof(int));
    char *curr_char = malloc(sizeof(char));
    long int size;
    int i = 0;
    while (fread(curr_int,sizeof(int) ,1,read_ptr))
    {
        fread(curr_char,sizeof(char) ,1,read_ptr);
        pre_order_array[i] = *curr_int;
        number_of_child_array[i] = *curr_char;
        i++;
    }
    fclose(read_ptr);

    int *index = malloc(sizeof(int));
    *index = 0;
    root = preorder_rebuild_BST(pre_order_array,number_of_child_array,index);


    if(root == NULL && total_nodes > 0){
        fprintf(stdout,"0,X,X\n");
        free(index);
        free(curr_int);
        free(curr_char);
        return 1;
    }

    if(*index == total_nodes)
    {
        file_validity = 1;
    }
    else{
        file_validity = 0;
    }

    int height_balanced;
    height_balanced = check_balanced(root);
    int is_bst = check_if_bst(root);
    fprintf(stdout,"%d,%d,%d\n",file_validity,is_bst,height_balanced);
    deallocate(root);
    free(index);
    free(curr_int);
    free(curr_char);
    free(pre_order_array);
    free(number_of_child_array);
    return 0;
}

void treeTraversal(Tnode *node){
    if(node == NULL || sizeof(node) != sizeof(Tnode *))
    {
        return;
    }
    treeTraversal(node->left);
    treeTraversal(node->right);
}