/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef TREEADT_H
#define TREEADT_H
#include "lexer.h"
#include "linkedlist.h"
#include "treeADTDef.h"

TREENODE* insertRuleToTree(LIST grammar_rule, TREENODE parent, int grammar_rule_number);
TREENODE createNewTreeNode(TREENODE parent);
TREENODE createNewTreeNode2();
TREELIST createNewTree();
void printTree(TREELIST tree);
void printParseTree(TREENODE node);




#endif