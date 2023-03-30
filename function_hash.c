#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "treeADTDef.h"
#include "function_hash.h"

int func_hash(char *str)
{
    int hash = 0;
    int c;
    while (c = *str++)
        hash = (hash * 97 + c) % 100;
    return hash;
}

void init_functionhashmap(function_table_hash_map map)
{
    for (int i = 0; i < 100; i++)
    {
        map[i].is_used = false;
    }
}

void function_table_insert(function_table_hash_map map, char *key, FUNCTION_TABLE_VALUE function_table_value)
{
    int index = func_hash(key);
    while (map[index].is_used)
    {
        index = (index + 1) % 100;
    }
    map[index].is_used = true;
    strcpy(map[index].function_name,key);
    map[index].function_table_value=function_table_value;
}

FUNCTION_TABLE_VALUE function_table_get(function_table_hash_map map, char *key, int size)
{
    char temp[size];
    temp[size] = '\0';
    for (int i = 0; i < size; i++)
    {
        temp[i] = key[i];
    }
    int index = hash(temp);
    while (map[index].is_used)
    {
        if (strcmp(map[index].function_name, temp) == 0)
        {
            return map[index].function_table_value;
        }
        index = (index + 1) % 100;
    }
    return NULL;
}