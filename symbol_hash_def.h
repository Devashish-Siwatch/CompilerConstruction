#ifndef SYMBOLHASHDEF_H
#define SYMBOLHASHDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "treeADTDef.h"

#define SYMBOL_HASHMAP_SIZE 100

typedef enum valid_types {
    integer,
    real,
    boolean,
}valid_types;

typedef struct symbol_table_value {
    union  
    {  
        struct
        {  
            bool isarray;
            valid_types type;
        } not_array;  
        struct 
        {  
            bool isarray;
            union {
                int bottom;
                char* bottom_var;
            } bottom_range;
            union {
                int top;
                char* top_var;
            } top_range;
            bool is_top_sign_plus;
            bool is_bottom_sign_plus;
            bool is_top_dynamic;
            bool is_bottom_dynamic;
            valid_types element_type;
        } array;  
    }symbol_table_value_union;
} symbol_table_value;

typedef symbol_table_value * SYMBOL_TABLE_VALUE;

typedef struct symbol_table_hash_node
{
    char variable_name[100];
    bool is_used;
    SYMBOL_TABLE_VALUE symbol_table_value;
} symbol_table_hash_node;

typedef symbol_table_hash_node symbol_table_hash_map[SYMBOL_HASHMAP_SIZE];

typedef struct symbol_table_wrapper{
    symbol_table_hash_map symbol_table;
    SYMBOL_TABLE_WRAPPER child;
    SYMBOL_TABLE_WRAPPER parent;
    SYMBOL_TABLE_WRAPPER next;
} symbol_table_wrapper;

typedef symbol_table_wrapper * SYMBOL_TABLE_WRAPPER;

#endif