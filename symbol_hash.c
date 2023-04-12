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

void print_symbol_table_value(SYMBOL_TABLE_VALUE value)
{
    // printf("#################################################################\n");
    printf("%-15s", value->module_name);
    printf("%5s [%d","", value->line_number_start);
    printf("-%d]  %-5s", value->line_number_end,"");
    if(value->isarray){
        if(value->symbol_table_value_union.array.element_type == integer){
            printf("integer%-6s", "");
        }
        else if(value->symbol_table_value_union.array.element_type == real){
            printf("real%-9s", "");
        }
        else if(value->symbol_table_value_union.array.element_type == boolean){
            printf("boolean%-6s", "");
        } 
        printf("yes%-8s", ""); 
        if(!value->symbol_table_value_union.array.is_top_dynamic && !value->symbol_table_value_union.array.is_bottom_dynamic){
            printf("static%-2s", "");
            printf("%3s [%d-","", value->symbol_table_value_union.array.bottom_range.bottom);
            printf("%d] %-6s", value->symbol_table_value_union.array.top_range.top,"");
        }
        else{
            printf("dynamic%-2s", "");
            if(value->symbol_table_value_union.array.is_top_dynamic && !value->symbol_table_value_union.array.is_bottom_dynamic){
                printf("%3s [%d-","", value->symbol_table_value_union.array.bottom_range.bottom);
                printf("%s] %-6s", value->symbol_table_value_union.array.top_range.top_var,"");
                
            }
            else if(!value->symbol_table_value_union.array.is_top_dynamic && value->symbol_table_value_union.array.is_bottom_dynamic){
                printf("%3s [%s-","", value->symbol_table_value_union.array.bottom_range.bottom_var);
                printf("%d] %-6s", value->symbol_table_value_union.array.top_range.top ,"");
            }
            else{
                printf("%3s [%s-","", value->symbol_table_value_union.array.bottom_range.bottom_var);
                printf("%s] %-6s", value->symbol_table_value_union.array.top_range.top_var,"");
            }
        }

    }
    else{
        if(value->symbol_table_value_union.not_array.type == integer){
            printf("integer%-6s", "");
        }
        else if(value->symbol_table_value_union.not_array.type == real){
            printf("real%-9s", "");
        }
        else if(value->symbol_table_value_union.not_array.type == boolean){
            printf("boolean%-6s", "");
        }
        printf("no%-10s", "");
        printf("**%-10s", "");
        printf("**%-10s", "");
    }
    printf("%-10d", value->width);
    printf("%-10d", value->offset);
    printf("%-10d\n", value->nesting_level);

    // if (value->isarray)
    // {
    //     // it is an array
    //     printf("<<<<<<<<ARRAY DEFN STARTS>>>>>>>>>>\n");
    //     if (value->symbol_table_value_union.array.is_bottom_dynamic)
    //     {
    //         printf("bottom range is %s and sign is %s\n", value->symbol_table_value_union.array.bottom_range.bottom_var, value->symbol_table_value_union.array.is_bottom_sign_plus ? "+" : "-");
    //     }
    //     else
    //     {
    //         printf("bottom range is %d and sign is %s\n", value->symbol_table_value_union.array.bottom_range.bottom, value->symbol_table_value_union.array.is_bottom_sign_plus ? "+" : "-");
    //     }

    //     if (value->symbol_table_value_union.array.is_top_dynamic)
    //     {
    //         printf("top range is %s and sign is %s\n", value->symbol_table_value_union.array.top_range.top_var, value->symbol_table_value_union.array.is_top_sign_plus ? "+" : "-");
    //     }
    //     else
    //     {
    //         printf("top range is %d and sign is %s\n", value->symbol_table_value_union.array.top_range.top, value->symbol_table_value_union.array.is_top_sign_plus ? "+" : "-");
    //     }

    //     printf("element type is %d\n", value->symbol_table_value_union.array.element_type);
    //     printf("<<<<<<<<ARRAY DEFN ENDS>>>>>>>>>>\n");
    // }
    // else
    // {
    //     // not an array
    //     printf("Not array, its type is %d\n", value->symbol_table_value_union.not_array.type);
    // }
    
    
}

void printSymboltableDFS(SYMBOL_TABLE_WRAPPER wrapper)
{
    if (wrapper == NULL)
    {
        return;
    }
    printSymboltableDFS(wrapper->child);
    SYMBOL_TABLE_WRAPPER symboliter = wrapper;
    while (symboliter != NULL)
    {
        print_symbol_table(symboliter);
        init_symbolhashmap(symboliter->symbol_table);
        symboliter = symboliter->next;
    }
}

void init_all_symbol_tables(SYMBOL_TABLE_WRAPPER wrapper){
    if (wrapper == NULL)
    {
        return;
    }
    init_all_symbol_tables(wrapper->child);
    SYMBOL_TABLE_WRAPPER symboliter = wrapper;
    while (symboliter != NULL)
    {
       
        init_symbolhashmap(symboliter->symbol_table);
        symboliter = symboliter->next;
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
    strcpy(map[index].variable_name, key);
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

SYMBOL_TABLE_VALUE create_new_symbol_node(char *name)
{
    SYMBOL_TABLE_VALUE value = (SYMBOL_TABLE_VALUE)malloc(sizeof(symbol_table_value));
    if (strcmp(name, "array") == 0)
    {
        value->isarray = true;
        value->symbol_table_value_union.array.is_bottom_dynamic = false;
        value->symbol_table_value_union.array.is_bottom_sign_plus = false;
        value->symbol_table_value_union.array.is_top_dynamic = false;
        value->symbol_table_value_union.array.is_top_sign_plus = false;
        value->symbol_table_value_union.array.top_range.top = 0;
        value->symbol_table_value_union.array.top_range.top_var = "";
        value->symbol_table_value_union.array.bottom_range.bottom = 0;
        value->symbol_table_value_union.array.bottom_range.bottom_var = "";
        value->symbol_table_value_union.array.element_type = integer;
    }
    else
    {
        value->isarray = false;
        value->symbol_table_value_union.not_array.type = integer;
    }
    value->module_name = "----";
    value->isInputParameter = false;
    value->isOutputParameter = false;
    value->outputParameterNeedsChecking = false;
    value->line_number_end = 0;
    value->line_number_start = 0;
    value->nesting_level = 0;
    value->offset = 0;
    value->width = 0;
    value->isLoopVariable = false;
    return value;
}

SYMBOL_TABLE_WRAPPER create_symbol_table_wrapper()
{
    SYMBOL_TABLE_WRAPPER wrapper = (SYMBOL_TABLE_WRAPPER)malloc(sizeof(symbol_table_wrapper));
    init_symbolhashmap(wrapper->symbol_table);
    wrapper->next = NULL;
    wrapper->child = NULL;
    wrapper->parent = NULL;
    wrapper->while_variables = NULL;
    wrapper->while_condition_fulfilled = false;
    wrapper->starting_line_number = 0;
    wrapper->shadowed = NULL;
    return wrapper;
}

void print_symbol_table(SYMBOL_TABLE_WRAPPER wrapper)
{
    // printf("-----------------------------------\n");
    // printf("AT symbol table : %s\n", wrapper->name);
    // printf("starting line number : %d\n", wrapper->starting_line_number);

    if(wrapper->shadowed!=NULL){
        for (int i = 0; i < SYMBOL_HASHMAP_SIZE; i++)
        {
            if (wrapper->shadowed->symbol_table[i].is_used == true)
            {
                printf("%-15s", wrapper->shadowed->symbol_table[i].variable_name);
                print_symbol_table_value(wrapper->shadowed->symbol_table[i].symbol_table_value);
            }
        }
    }

    for (int i = 0; i < SYMBOL_HASHMAP_SIZE; i++)
    {
        if (wrapper->symbol_table[i].is_used == true)
        {
            printf("%-15s", wrapper->symbol_table[i].variable_name);
            print_symbol_table_value(wrapper->symbol_table[i].symbol_table_value);
        }
    }
    // printf("-----------------------------------\n");
}
