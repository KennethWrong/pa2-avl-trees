#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"
#include "tree_helper.h"

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        return EXIT_FAILURE;
    }
    int res;
    char flag = argv[1][1];

    /**
    if (flag == 'b')
    {
        //build bst with instructions from input file
    }
    else if (flag == 'e')
    {
        //evaluate bst to see if its valid
    }
    else
    {
        //input flag is wrong
        return EXIT_FAILURE;
    }
    **/
    //read_binary_to_txt(argv[2], argv[3]);
    
    //-1 is error
    if (flag == 'b')
    {
        res = build_tree_text(argv[2], argv[3]);
        if (res == -1)
        {
            fprintf(stdout,"%d",res);
            return EXIT_FAILURE;
        }
        else if (res == 1)
        {
            fprintf(stdout,"%d",res);
            return EXIT_SUCCESS;
        }
    }
    else if(flag == 'e')
    {
        build_tree_text_e(argv[2]);
    }


    return 0;
}
