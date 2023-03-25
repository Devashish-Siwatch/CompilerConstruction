/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef LINKEDLISTDEF_H
#define LINKEDLISTDEF_H


#include "stdbool.h"

struct node
{
    char* data;
    struct node *next;
};
typedef struct node node;
typedef node * NODE;

struct linked_list
{
    int count;
    NODE head;
    // NODE tail; // Not required for stack. Required for Queue
};
typedef struct linked_list linked_list;
typedef linked_list * LIST;

linked_list** grammar;


#endif