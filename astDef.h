#ifndef ASTDEF_H
#define ASTDEF_H
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "treeADT.h"

// typedef struct ast_node_moduleDeclarations{
void appendAtEndNextNotNULL(TREENODE head, TREENODE node, int step);
void appendAtEnd(TREENODE head, TREENODE node);
TREENODE generate_ast(TREENODE node);
void printAst(TREENODE head);
void setASTParent(TREENODE head);
// } AST_NODE_MODULEDECLARATIONS;

// typedef struct ast_node_otherModules{

// } AST_NODE_OTHERMODULES;

// typedef struct ast_node_driverModule{

// } AST_NODE_DRIVERMODULE;

// typedef struct ast_node_statements{

// } AST_NODE_STATEMENTS;

// typedef struct ast_node_declareStmt{

// } AST_NODE_DECLARESTMT;

// typedef struct ast_node_idList{

// } AST_NODE_IDLIST;

// typedef struct ast_node_program{

// } AST_NODE_PROGRAM;

// struct ast_node{
//     enum{
//         ast_node_program,
//     } tag;
//     union
//     {
//         AST_NODE_PROGRAM ast_node_program;
//     };
// };

#endif