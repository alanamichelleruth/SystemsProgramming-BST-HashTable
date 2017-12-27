/*
Daniel Hug dhug@albany.edu: Monitor
Alana Ruth Aruth@albany.edu : Recorder
Jessica Kanczura jKanczura@albany.edu : Leader

Functions for the Hash Table
*/

#include "BSTStructs.h"
#include "BSTPrototypes.h"
#include "hashStructs.h"
#include "hashPrototypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function to make a hash table for the given program file, returns the hash table
phTable fileToHash(char *fileName, int tableSize, pnode root){

  FILE *fp;

  //If given file cannot be opened, print error message and stop
  if((fp = fopen(fileName, "r"))== NULL){
    fprintf(stderr, "Error: File %s cannot be opened.\n", fileName);
    return NULL;
  }

  //Delcare local variables
  char line[100]; //Each line of the file
  char symbol[11]; //Each symbol
  char instruction[6]; //Each instruction
  char *token; //For strtok function
  unsigned int lc = 0; //Each lc value (beginning at 0)

  //Create an empty hash table of the given size
  phTable table = createHashTable(tableSize);

  //Iterate through file, line by line
  while(fgets(line, sizeof(line), fp) != NULL){

    //If a line has a symbol in the label field
    if(line[0] != '\t' && line[0] != ' '){
      //Get first token
      token = strtok(line, " ");
      //Initialize symbol
      strcpy(symbol, token);
      symbol[11] = '\0';

      //Get the next token (the instruction)
      token = strtok(NULL, " ");
      //Initialize instruction
      strcpy(instruction, token);
      instruction[6] = '\0';

      //Increment LC value by the directive (if search doesn't equal null)
      if(search(root, instruction) != NULL)
        lc += search(root, instruction)->opFormat;

      //Insert the hash node into the hash table and set the table
      table = insertHashNode(table, symbol, lc, tableSize);
    }
    //Otherwise, still increment the lc value
    else{
      //Get token
      token = strtok(line, "\t ");
      //Initialize instruction
      strcpy(instruction, token);
      instruction[6] = '\0';

      //Increment LC value by the instruction
      if(search(root, instruction) != NULL)
        lc += search(root, instruction)->opFormat;
    }
  }

  //Close the file
  fclose(fp);

  //Return the hash table
  return table;
}

/*Hash Function provided by Charalampos Chelmis, November 2017*/
int hashFunction(char *s, int T){

  /* The parameter s represents the symbol to be hashed and  */
  /* the parameter T represents the size of the hash table.  */
  /* The function returns the hash value for the symbol s.   */

  /* String s is assumed to be terminated with '\0'.         */
  /* It is also assumed that T is at least 2. The returned   */
  /* hash value is an integer in the range 0 to T-1.         */

  /* The function computes the hash value using arithmetic   */
  /* based on powers of the BASE value defined below.        */

   #define BASE 127

  int h = 0;     /* Will hold the hash value at the end. */
  int temp;      /* Temporary.                           */

  /* The hash value is computed in the for loop below. */
  for (;  *s != 0;  s++) {
    temp = (BASE * h + *s);
    if (temp < 0) temp = -temp;
    h = temp % T;
  }

  /* The hash value computation is complete. So, */
  return h;

} /* End of hash function */

//Function to create a new hash node, returns the new hash node
phNode createHashNode(char symbol[11], int lc){

  //Allocate memory for the new node
  phNode newNode = (phNode)malloc(sizeof(hNode));

  //If memory allocation fails, print error and stop
  if(newNode == NULL){
    fprintf(stderr, "Error: Memory allocation error.\n");
    return NULL;
  }

  //Copy all the respective values to the new node
  memcpy(newNode->symbol, symbol, 11);
  newNode->lc = lc;
  newNode->next = NULL;

  //Return the new hash node
  return newNode;
}

//Function to create a new hash table, returns the new hash table
phTable createHashTable(int tableSize){

  //Allocate memory for the new hash table
  phTable table = (phTable)malloc(sizeof(hTable));

  //If memory allocation fails, print error and stop
  if(table == NULL){
    fprintf(stderr, "Error: Memory allocation error.\n");
    return NULL;
  }

  table->hEntries = (phEntry*)malloc(sizeof(phEntry)*tableSize);

  //Create a new empty hash table with keys equal to the indices
  unsigned int i;
  for(i = 0; i < tableSize; i++){
    //Allocate memory for the entry
    table->hEntries[i] = (phEntry)malloc(sizeof(hEntry));

    //Set key to be index
    table->hEntries[i]->key = i;

    //Make empty node list
    table->hEntries[i]->hNodeList = NULL;
  }

  //Return the new empty hash table of given size
  return table;
}

//Function to find a hash entry in a given hash table, returns the hash entry
phEntry findHashEntry(phTable table, char symbol[11], int tableSize){

  //Find the hash value for the given symbol using the hashFunction
  int key = hashFunction(symbol, tableSize);

  //Return the entry for that key
  return table->hEntries[key];
}

//Function to find a hash node in a given hash entry, returns the hash node
phNode findHashNode(phEntry entry, char symbol[11]){

  //If the entry isn't null
  if(entry != NULL){
    //Set temp to be the node list
    phNode temp = entry->hNodeList;

    //Iterate through the list
    while (temp != NULL){
      //If the symbol is found, return that node
      if (strcmp(temp->symbol, symbol) == 0)
        return temp;
      temp = temp->next;
    }
  }

  //If the node wasn't found with that symbol, return null
  return NULL;
}

//Function to retrieve the LC value for a given symbol, returns unsigned int lc
unsigned int findLCValue(phTable table, char symbol[11], int tableSize){

  //Find the hash entry and node for the given symbol
  phEntry e = findHashEntry(table, symbol, tableSize);
  phNode n = findHashNode(e, symbol);

  //Return the lc value of the hash node
  return n->lc;
}

//Function to insert a new node into the hash table, returns the hash table
phTable insertHashNode(phTable table, char symbol[11], int lc, int tableSize){

  //Create a new node
  phNode node = createHashNode(symbol, lc);

  //Find the hash entry for the appropriate key
  phEntry entry = findHashEntry(table, symbol, tableSize);

  //If the entry's node list is empty, set it to be the new node
  if(entry->hNodeList == NULL)
    entry->hNodeList = node;

  //Otherwise, iterate through the node list until the end
  else{
    //Allocate memory for temp
    phNode temp = (phNode)malloc(sizeof(hNode));
    //If memory allocation fails, print error message and stop
    if(temp == NULL){
      fprintf(stderr, "Error: Memory allocation error.\n");
      return NULL;
    }

    //Go to the end of the list
    temp = entry->hNodeList;
    while(temp->next != NULL){
      temp = temp->next;
    }

    //Add the new node to the next pointer of the end of the node list
    temp->next = node;
  }

  //Return the hash table with the new node inserted
  return table;
}

//Function to free the hash table
void freeHashTable(phTable table, int tableSize){

  //Loop through the hash table and free all entries
  unsigned int i;
  for (i = 0; i < tableSize; i++){
    freeHashEntry(table->hEntries[i]);
  }
  //Free the hash table
  free(table);
}

//Function to free the hash entry
void freeHashEntry(phEntry entry){

  //Loop through the entry and free all nodes
  if (entry != NULL){
    if (entry->hNodeList != NULL)
      freeHashNode(entry->hNodeList);
    free(entry);
  }
}

//Function to free the hash node
void freeHashNode(phNode node){

  //Loop through the node list and free each
  if(node != NULL){
   //Free arguments
    if(node->next != NULL)
      freeHashNode(node->next);
    free(node);
  }
}

//Function to print the contents of the hash table, one hash node per line
void printHashTable(phTable table, int tableSize){

  //Loop through the hash table
  unsigned int i;
  for (i = 0; i < tableSize; i++){
    phEntry entry = table->hEntries[i];

    //If the entry isn't null
    if(entry != NULL){
      //Print the entry key
      printf("%d: ", entry->key);

      //Loop through its nodes
     phNode node = entry->hNodeList;
      while(node != NULL){
        //Print the symbol and the lc value
        printf("%s(%d)->", node->symbol, node->lc);
        node = node->next;
      }
      printf("NULL.\n");
    }
  }
}



