#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"

int read_binary_to_txt(char* infile, char * outfile)
{
    FILE *read_ptr;
    read_ptr = fopen(infile, "rb");

    FILE *write_ptr;
    write_ptr = fopen(outfile,"w+");

    if(read_ptr == NULL)
    {
        return 1;
    }
    fseek(read_ptr,0,SEEK_END);
    int size_of_file = ftell(read_ptr);
    fseek(read_ptr,0,SEEK_SET);

    int c = fgetc(read_ptr);
    int *curr_int = malloc(sizeof(int));
    char *curr_char = malloc(sizeof(char));
    while (c != EOF)
    {
        long int pos1 = ftell(read_ptr);
        fread(curr_int, sizeof(int),1, read_ptr);
        printf("%d",*curr_int);
        long int pos2 = ftell(read_ptr);
        fread(curr_char, sizeof(char),1, read_ptr);
        // printf("%d",*curr_int);
        // printf("%c",*curr_char);
        fprintf(write_ptr, "%d%c",*curr_int,*curr_char);
        c = fgetc(read_ptr);
    }
    fclose(read_ptr);
    fclose(write_ptr);

    return 0;
}

int read_text(char* infile)
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
        fscanf(read_ptr,"%d %c",curr_int,curr_char);

        long int size2 = ftell(read_ptr);
        printf("%ld %ld\n",size,size2);

        if (size2 - size < 3)
        {
            break;
        }else{
            size = size2;
        }

        // printf("cint: %d\n",*curr_int);
        // printf("c char: %c\n",*curr_char);
        c = fgetc(read_ptr);

        if(*curr_char == 'i')
        {
            root = insert(root, *curr_int);
        }
        // else if(*curr_char == 'd')
        // {
        //     root = deleteNode(root, *curr_int);
        // }
        //printf("%d\n",c);
    }
    preOrder(root);
    fclose(read_ptr);

    return 0;
}