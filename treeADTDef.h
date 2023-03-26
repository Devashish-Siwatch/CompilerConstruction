/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef TREEADTDEF_H
#define TREEADTDEF_H
#include "lexer.h"
#include "linkedlist.h"

typedef struct tree_node tree_node;
typedef tree_node * TREENODE;
struct tree_node
{
    char* name;
    char* lexeme;
    int line_number;
    int rule_number;
    int valueIfNum;
    float valueIfRNum;
    TREENODE next;
    TREENODE parent;
    TREENODE child;
};


struct tree_list
{
    TREENODE head;
};
typedef struct tree_list tree_list;
typedef tree_list * TREELIST;





#endif