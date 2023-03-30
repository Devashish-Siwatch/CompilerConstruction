#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "treeADTDef.h"
#include "symbol_hash.h"

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
    int index = symbol_hash(key);
    while (map[index].is_used)
    {
        index = (index + 1) % 100;
    }
    map[index].is_used = true;
    strcpy(map[index].variable_name,key);
    map[index].symbol_table_value = type;
}

SYMBOL_TABLE_VALUE symbol_table_get(symbol_table_hash_map map, char *key, int size)
{
    char temp[size];
    temp[size] = '\0';
    for (int i = 0; i < size; i++)
    {
        temp[i] = key[i];
    }
    // printf("\n***%s***", temp);
    int index = symbol_hash(temp);
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

