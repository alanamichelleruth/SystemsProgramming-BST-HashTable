/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Data structure for the Binary Search Tree
*/

typedef struct BSTNode {
  //instruction will be used as the key
  char instruction[6];
  unsigned int opcode;
  unsigned int opFormat;
  struct BSTNode* leftNode;
  struct BSTNode* rightNode;
} node, *pnode;

