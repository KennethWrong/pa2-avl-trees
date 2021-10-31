#include <stdio.h>
#include <stdlib.h>
#include <

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        return EXIT_FAILURE;
    }

    char flag = argv[1][1]

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

}
