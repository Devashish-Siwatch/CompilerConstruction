#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "function_hash.h"

void populate_function_and_symbol_tables(TREENODE root);
void insert_symbol_table_at_end(SYMBOL_TABLE_WRAPPER wrapper, SYMBOL_TABLE_WRAPPER temp);
void populateSymboltableValue(TREENODE datatype,SYMBOL_TABLE_VALUE value, char* module_name, int nesting_level,int start_line_number);
void addListtoSymbolTable(TREENODE root, int nesting_level);