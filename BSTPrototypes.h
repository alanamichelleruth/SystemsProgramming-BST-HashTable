/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Function prototypes for the Binary Search Tree
*/

pnode fileToBST(char *fileName);
pnode createnode(char instruction[6], unsigned int opcode, unsigned int opformat);
pnode insertNode(pnode root, char instruction[6], unsigned int opcode, unsigned int opformat);
pnode search(pnode root, char instruction[6]);
void printTree(pnode root);
void freeTree(pnode root);
int getBSTHeight(pnode root);

