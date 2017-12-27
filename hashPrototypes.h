/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Prototypes for the Hash Table functions
*/

//#include "BSTStructs.h"
//#include "BSTPrototypes.h"

phTable fileToHash(char *fileName, int tableSize, pnode root);
int hashFunction(char *s, int T);
phNode createHashNode(char symbol[11], int lc);
phTable createHashTable(int tableSize);
phEntry findHashEntry(phTable table, char symbol[11], int tableSize);
phNode findHashNode(phEntry entry, char symbol[11]);
unsigned int findLCValue(phTable table, char symbol[11], int tableSize);
phTable insertHashNode(phTable table, char symbol[11], int lc, int tableSize);
void freeHashTable(phTable table, int tableSize);
void freeHashEntry(phEntry entry);
void freeHashNode(phNode node);
void printHashTable(phTable table, int tableSize);


