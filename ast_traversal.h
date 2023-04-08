#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "function_hash.h"

void populate_function_and_symbol_tables(TREENODE root);
bool check_if_declared_before(char* var);
bool check_if_redeclared(char* var);
void check_expression_if_declared_before(TREENODE root);
void go_back_to_parent_symbol_table();
void populateSymboltabeValue(TREENODE datatype,SYMBOL_TABLE_VALUE value);
void insert_symbol_table_at_end(SYMBOL_TABLE_WRAPPER wrapper, SYMBOL_TABLE_WRAPPER temp);
void populateSymboltableValue(TREENODE datatype,SYMBOL_TABLE_VALUE value, char* module_name, int nesting_level,int start_line_number);
void addListtoSymbolTable(TREENODE root, int nesting_level);