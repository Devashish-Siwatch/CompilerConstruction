#ifndef TREEADT_H
#define TREEADT_H
#include "lexer.h"

struct tree_node
{
    Token token;
    struct tree_node *next;
    struct tree_node *parent;
    struct tree_list *child;
};
typedef struct tree_node tree_node;
typedef tree_node * TREENODE;

struct tree_list
{
    TREENODE head;
};
typedef struct tree_list tree_list;
typedef tree_list * TREELIST;

#endif