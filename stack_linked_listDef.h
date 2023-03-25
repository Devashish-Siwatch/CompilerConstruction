/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef STACKLINKEDLISTDEF_H
#define STACKLINKEDLISTDEF_H

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


#endif