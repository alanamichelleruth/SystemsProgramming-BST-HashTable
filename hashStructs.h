/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Structure definitions for the Hash Table
*/

//Structure for each node in the hash table
typedef struct hashNode{
  char symbol[11];
  unsigned int lc;
  struct hashNode *next;
} hNode, *phNode;

//Structure for each entry of the hash table
typedef struct hashEntry{
  int key;
  phNode hNodeList;
}hEntry, *phEntry;

//Structure for the hash table
typedef struct hashTable{
  phEntry *hEntries;
}hTable, *phTable;



