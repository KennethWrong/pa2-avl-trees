#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"
#include "validate.h"

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
            return 0;
        }
        c = fgetc(read_ptr);
    }
    preOrder(root, write_ptr);
    fclose(read_ptr);
    fclose(write_ptr);
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
        fprintf(stdout,"-1,X,X");
        return 1;
    }
    Tnode *root = NULL;
    //wrong format???

    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    if (size_of_file % (sizeof(int) + sizeof(char)) != 0){
        fprintf(stdout,"0,X,X");
        return 1;
    }

    int total_nodes = size_of_file / (sizeof(int) + sizeof(char));

    int c = fgetc(read_ptr);

    int *curr_int = malloc(sizeof(int));
    char *curr_char = malloc(sizeof(char));
    long int size;
    while (c != EOF)
    {
        ungetc(c,read_ptr);
        fread(curr_int,sizeof(int) ,1,read_ptr);
        fread(curr_char,sizeof(char) ,1,read_ptr);
        printf("%d %d\n",*curr_int, *curr_char);

        c = fgetc(read_ptr);
        root = insert(root, *curr_int);
    }
    fclose(read_ptr);

    file_validity = 1;
    int height_balanced;
    height_balanced = check_balanced(root);
    int is_bst = check_if_bst(root);
    printf("%d,%d,%d",file_validity, is_bst, height_balanced);

    deallocate(root);
    return 0;
}