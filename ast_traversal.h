/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "function_hash.h"

void ast_pass2(TREENODE root);
void populate_function_and_symbol_tables(TREENODE root);
bool check_if_declared_before(char *var);
bool check_if_redeclared(char *var);
void check_expression_if_declared_before(TREENODE root);
void go_back_to_parent_symbol_table();
void populateSymboltabeValue(TREENODE datatype, SYMBOL_TABLE_VALUE value);
void insert_symbol_table_at_end(SYMBOL_TABLE_WRAPPER wrapper, SYMBOL_TABLE_WRAPPER temp);
void populateSymboltableValue(TREENODE current_node, TREENODE datatype, SYMBOL_TABLE_VALUE value, char *module_name, int nesting_level, int start_line_number, bool isInputParameter, bool isLoopVariable, bool isOutputParameter, bool outputParameterNeedsChecking);
void addListtoSymbolTable(TREENODE root, int nesting_level, bool isInputParam, bool isOutputParam, bool outputParamNeedsChecking);
int get_width(SYMBOL_TABLE_WRAPPER wrapper);
void get_total_width();
int get_nesting_level(SYMBOL_TABLE_WRAPPER wrapper);
SYMBOL_TABLE_VALUE get_symbol_table_value_in_above_table(SYMBOL_TABLE_WRAPPER cc,char *var);
SYMBOL_TABLE_VALUE get_type_of_expression(TREENODE root);
int get_type_of_variable(char *lexeme);
bool check_if_function_declared(char *var);
void appendWhileVariables(TREENODE root, LIST list);
void check_array_index_bounds(TREENODE indexRoot, char *arrayLexeme, int line_number);
SYMBOL_TABLE_WRAPPER search_below_by_line_number(int line_no);
void populate_function_and_symbol_tables_without_error(TREENODE root);
void print_array_info(SYMBOL_TABLE_WRAPPER wrapper);
void print_all_array_info();
void init_ast_traversal();
