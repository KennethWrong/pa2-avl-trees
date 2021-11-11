#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "create_tree.h"
#include "tree_helper.h"

int main(int argc, char *argv[])
{
    int res;
    char flag = argv[1][1];

    if (flag == 'b')
    {
        if(argc != 4){
            return EXIT_FAILURE;
        }

        res = build_tree_binary(argv[2], argv[3]);
        if (res == 1)
        {
            fprintf(stdout,"%d",res);
            return EXIT_SUCCESS;
        }
        else
        {
            fprintf(stdout,"%d",res);
            return EXIT_FAILURE;
        }
    }
    else if(flag == 'e')
    {
        if(argc != 3)
        {
            return EXIT_FAILURE;
        }
        int res;
        res = build_tree_e(argv[2], argv[3]);

        if (res == 1){
            return EXIT_FAILURE;
        }else{
            return EXIT_SUCCESS;
        }
    }
    else
    {
        return EXIT_FAILURE;
    }

    return 0;
}
