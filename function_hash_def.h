/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef FUNCTIONHASHDEF_H
#define FUNCTIONHASHDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "treeADTDef.h"
#include "symbol_hash.h"

#define FUNC_HASHMAP_SIZE 100

typedef struct function_table_value
{
    SYMBOL_TABLE_WRAPPER symbol_table_wrapper;
    TREENODE input_list;
    TREENODE output_list;
    bool isDeclared;
    bool needsChecking;
} function_table_value;

typedef function_table_value * FUNCTION_TABLE_VALUE;

typedef struct function_table_hash_node
{
    char function_name[100];
    FUNCTION_TABLE_VALUE function_table_value;
    bool is_used;
} function_table_hash_node;

typedef function_table_hash_node function_table_hash_map[FUNC_HASHMAP_SIZE];
function_table_hash_map function_table;

#endif