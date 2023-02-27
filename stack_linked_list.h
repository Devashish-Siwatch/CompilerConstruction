#ifndef STACKLINKEDLIST_H
#define STACKLINKEDLIST_H

#include "stdbool.h"

struct stack_node
{
    char* name;
    TREENODE treepointer;
    struct stack_node *next;
};
typedef struct stack_node stack_node;
typedef stack_node * STACKNODE;

struct stack_linked_list
{
    int count;
    STACKNODE head;
    // NODE tail; // Not required for stack. Required for Queue
};
typedef struct stack_linked_list stack_linked_list;
typedef stack_linked_list * STACKLIST;

STACKLIST createNewStackList();
// This function allocates memory for a new list and returns a pointer to it.
// The list is empty and the count is set to 0.

STACKNODE createNewStackNode(char* name, TREENODE pointer);
// This function allocates memory for a new node and returns a pointer to it.
// The next pointer is set to NULL and the data is set to the value passed in.

void insertStackNodeIntoList(STACKNODE node, STACKLIST list);
// This function inserts a node at the beginning of the list.

void removeFirstStackNode(STACKLIST list);
// This function removes the first node from the list.

// void insertNodeAtEnd(NODE node, LIST list); // Not required for stack. Required for Queue
// This function inserts a node at the end of the list.

void destroyStackList(STACKLIST list);
#endif