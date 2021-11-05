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
    read_text(argv[2]);
    return 0;
}

/**
int main()
{
  Tnode *root = NULL;

  //Constructing tree given in the above figure
  root = insert(root, 10);
  insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);



  printf("Preorder traversal of the constructed AVL"
         " tree is \n");
  preOrder(root);

  return 0;
}
**/
