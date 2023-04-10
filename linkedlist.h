/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include "stdbool.h"
#include "linkedlistDef.h"



LIST createNewList();
// This function allocates memory for a new list and returns a pointer to it.
// The list is empty and the count is set to 0.

NODE createNewNode(char* data);
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertNodeIntoList(NODE node, LIST list);
// This function inserts a node at the beginning of the list.

void removeFirstNode(LIST list);
// This function removes the first node from the list.

// void insertNodeAtEnd(NODE node, LIST list); // Not required for stack. Required for Queue
// This function inserts a node at the end of the list.
void display(LIST list);
void destroyList(LIST list);
bool data_exists(char* data, LIST list);
#endif