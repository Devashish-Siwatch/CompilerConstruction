#ifndef TREEADT_H
#define TREEADT_H
#include "lexer.h"
#include "linkedlist.h"

typedef struct tree_node tree_node;
typedef tree_node * TREENODE;
struct tree_node
{
    char* name;
    char* lexeme;
    int line_number;
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
TREENODE* insertRuleToTree(LIST grammar_rule, TREENODE parent);
TREENODE createNewTreeNode(TREENODE parent);
TREELIST createNewTree();
void printParseTree(TREENODE node);




#endif