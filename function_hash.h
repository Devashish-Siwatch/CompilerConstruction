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
#include "treeADTDef.h"
#include "symbol_hash.h"
#include "function_hash_def.h"


int func_hash(char *str);
void init_functionhashmap(function_table_hash_map map);
void function_table_insert(function_table_hash_map map, char *key, FUNCTION_TABLE_VALUE function_table_value);
FUNCTION_TABLE_VALUE function_table_get(function_table_hash_map map, char *key, int size);
void printChildren(TREENODE head);
FUNCTION_TABLE_VALUE create_function_value();
void print_function_table();