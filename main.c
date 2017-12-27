/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Main worker function
*/

#include <stdio.h>
#include <stdlib.h>
#include "BSTStructs.h"
#include "BSTPrototypes.h"
#include "hashStructs.h"
#include "hashPrototypes.h"

int main(int argc, char *argv[]){

  //If not 4 command line args, print error message and stop
  if (argc != 4){
    fprintf(stderr, "Error: Invalid number of command line arguments.\n");
    return 0;
  }

  //Convert the instruction set opcode file to a binary search tree
  pnode root = fileToBST(argv[1]);
  //Print an inorder traversal of the BST
  printf("\nIn order traversal of BST:\n");
  printTree(root);
  //Print the height of the BST
  printf("\nHeight of the BST: %d\n", getBSTHeight(root));

  //Convert the program file to a hash table
  phTable table = fileToHash(argv[2], atoi(argv[3]), root);
  //Print the hash table
  printf("\nHash table:\n");
  printHashTable(table, atoi(argv[3]));

  return 0;
}

