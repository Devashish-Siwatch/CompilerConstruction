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

void print_symbol_table_value(SYMBOL_TABLE_VALUE value){
    printf("#################################################################\n");
    if(value->isarray){
        //it is an array
        printf("<<<<<<<<ARRAY DEFN STARTS>>>>>>>>>>\n");
        if(value->symbol_table_value_union.array.is_bottom_dynamic){
            printf("bottom range is %s and sign is %s\n",value->symbol_table_value_union.array.bottom_range.bottom_var, value->symbol_table_value_union.array.is_bottom_sign_plus?"+":"-");
        }else{
            printf("bottom range is %d and sign is %s\n",value->symbol_table_value_union.array.bottom_range.bottom, value->symbol_table_value_union.array.is_bottom_sign_plus?"+":"-");
        }

        if(value->symbol_table_value_union.array.is_top_dynamic){
            printf("top range is %s and sign is %s\n",value->symbol_table_value_union.array.top_range.top_var, value->symbol_table_value_union.array.is_top_sign_plus?"+":"-");
        }else{
            printf("top range is %d and sign is %s\n",value->symbol_table_value_union.array.top_range.top, value->symbol_table_value_union.array.is_top_sign_plus?"+":"-");
        }

        printf("element type is %d\n",value->symbol_table_value_union.array.element_type);
        printf("<<<<<<<<ARRAY DEFN ENDS>>>>>>>>>>\n");
    }else{
        //not an array
        printf("Not array, its type is %d\n",value->symbol_table_value_union.not_array.type);
    }
    printf("The function it belongs to is %s.\n",value->module_name);
    printf("Its nesting level is %d.\n",value->nesting_level);
    printf("Its width is %d.\n",value->width);
    printf("Its offset is %d.\n",value->offset);
    printf("Its start line is %d.\n",value->line_number_start);
    printf("Its end line is %d.\n",value->line_number_end);

    printf("#################################################################\n");
}

void printSymboltableDFS(SYMBOL_TABLE_WRAPPER wrapper){
    if(wrapper==NULL){
        return;
    }
    printSymboltableDFS(wrapper->child);
    SYMBOL_TABLE_WRAPPER symboliter=wrapper;
    while(symboliter!=NULL){
        print_symbol_table(symboliter);
        init_symbolhashmap(symboliter->symbol_table);
        symboliter=symboliter->next;
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

SYMBOL_TABLE_VALUE create_new_symbol_node(char* name)
{
    SYMBOL_TABLE_VALUE value = (SYMBOL_TABLE_VALUE)malloc(sizeof(symbol_table_value));
    if(strcmp(name,"array")==0)
    {
        value->isarray = true;
        value->symbol_table_value_union.array.is_bottom_dynamic=false;
        value->symbol_table_value_union.array.is_bottom_sign_plus=false;
        value->symbol_table_value_union.array.is_top_dynamic=false;
        value->symbol_table_value_union.array.is_top_sign_plus=false;
        value->symbol_table_value_union.array.top_range.top=0;
        value->symbol_table_value_union.array.top_range.top_var="";
        value->symbol_table_value_union.array.bottom_range.bottom=0;
        value->symbol_table_value_union.array.bottom_range.bottom_var="";
        value->symbol_table_value_union.array.element_type=integer;
    }
    else
    {
        value->isarray=true;
        value->symbol_table_value_union.not_array.type=integer;
    }
    return value;
}

SYMBOL_TABLE_WRAPPER create_symbol_table_wrapper(){
    SYMBOL_TABLE_WRAPPER wrapper = (SYMBOL_TABLE_WRAPPER)malloc(sizeof(symbol_table_wrapper));
    init_symbolhashmap(wrapper->symbol_table);
    wrapper->next=NULL;
    wrapper->child=NULL;
    wrapper->parent=NULL;
    return wrapper;
}

void print_symbol_table(SYMBOL_TABLE_WRAPPER wrapper){
    printf("-----------------------------------\n");
    printf("AT symbol table : %s\n",wrapper->name);
    for(int i=0 ; i<SYMBOL_HASHMAP_SIZE ; i++){
        if(wrapper->symbol_table[i].is_used==true){
            printf("SYMBOL at i=%d : %s\n",i,wrapper->symbol_table[i].variable_name);
            print_symbol_table_value(wrapper->symbol_table[i].symbol_table_value);
        }
    }
    printf("-----------------------------------\n");
}

