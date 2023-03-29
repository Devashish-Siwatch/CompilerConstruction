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
} symbol_table_wrapper;

typedef symbol_table_wrapper * SYMBOL_TABLE_WRAPPER;

int symbol_hash(char *str)
{
    int hash = 0;
    int c;
    while (c = *str++)
        hash = (hash * 97 + c) % 100;
    return hash;
}

void init_symbolhashmap(symbol_table_hash_map map)
{
    for (int i = 0; i < 100; i++)
    {
        map[i].is_used = false;
    }
}

void symbol_insert(symbol_table_hash_map map, char *key, SYMBOL_TABLE_VALUE type)
{
    int index = func_hash(key);
    while (map[index].is_used)
    {
        index = (index + 1) % 100;
    }
    map[index].is_used = true;
    strcpy(map[index].variable_name,key);
    map[index].symbol_table_value = type;
}

SYMBOL_TABLE_VALUE get(symbol_table_hash_map map, char *key, int size)
{
    char temp[size];
    temp[size] = '\0';
    for (int i = 0; i < size; i++)
    {
        temp[i] = key[i];
    }
    // printf("\n***%s***", temp);
    int index = hash(temp);
    while (map[index].is_used)
    {
        if (strcmp(map[index].variable_name, temp) == 0)
        {
            // printf("\nSTRING BEING SEARCHED : %s, SEARCH RESULT : %d", temp, index);
            return map[index].symbol_table_value;
        }
        index = (index + 1) % 100;
    }
    return NULL;
}

