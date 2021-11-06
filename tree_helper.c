#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"

int build_tree_binary(char* infile, char * outfile)
{
    FILE *read_ptr;
    read_ptr = fopen(infile, "r");

    if(read_ptr == NULL)
    {
        return -1;
    }

    Tnode *root = NULL;

    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    int c = fgetc(read_ptr);
    long int *curr_int = malloc(sizeof(int));
    char *curr_char = malloc(sizeof(char));
    long int size = ftell(read_ptr);
    
    while (c != EOF)
    {
        ungetc(c,read_ptr);
        size = ftell(read_ptr);
        fread(curr_int,sizeof(long) ,1,read_ptr);
        fread(curr_char,sizeof(char) ,1,read_ptr);
        printf("%ld %c\n",*curr_int, *curr_char);
        long int size2 = ftell(read_ptr);
        if (size2 - size < 3)
        {
            break;
        }
        else
        {
            size = size2;
        }
        c = fgetc(read_ptr);

        if(*curr_char == 'i')
        {
            root = insert(root, *curr_int);
        }
        else if(*curr_char == 'd')
        {
            root = deleteNode(root, *curr_int);
        }
    }
    preOrder(root);
    fclose(read_ptr);

    return 1;
}

int build_tree_text(char* infile, char * outfile)
{
    FILE *read_ptr;
    read_ptr = fopen(infile, "r");

    if(read_ptr == NULL)
    {
        return 1;
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
        fscanf(read_ptr,"%d %c",curr_int,curr_char);
        printf("%d %c\n",*curr_int, *curr_char);
        long int size2 = ftell(read_ptr);
        if (size2 - size < 3)
        {
            break;
        }else{
            size = size2;
        }
        c = fgetc(read_ptr);

        if(*curr_char == 'i')
        {
            root = insert(root, *curr_int);
        }
        else if(*curr_char == 'd')
        {
            root = deleteNode(root, *curr_int);
        }
    }
    preOrder(root);
    fclose(read_ptr);

    return 0;
}

Tnode* build_tree_text_e(char* infile)
{
    FILE *read_ptr;
    read_ptr = fopen(infile, "r");

    if(read_ptr == NULL)
    {
        printf("-1,0,0");
        return -1;
    }

    Tnode *root = NULL;

    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    int c = fgetc(read_ptr);

    int *curr_int = malloc(sizeof(int));
    int *int2 = malloc(sizeof(int));
    long int size = ftell(read_ptr);
    while (c != EOF)
    {
        ungetc(c,read_ptr);
        size = ftell(read_ptr);
        fscanf(read_ptr,"%d %d",curr_int,int2);
        printf("%d %c\n",*curr_int, *int2);
        long int size2 = ftell(read_ptr);
        if (size2 - size < 3)
        {
            break;
        }else{
            size = size2;
        }
        c = fgetc(read_ptr);

        root = insert(root, *curr_int);
    }
    fclose(read_ptr);

    return root;
}