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
    int index = func_hash(temp);
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
void printChildren(TREENODE head){
    if(head==NULL){
        return;
    }
    if(head->child!=NULL){
        printChildren(head->child);
    }
    printf("%s \n",head->lexeme);
}

FUNCTION_TABLE_VALUE create_function_value(){
    FUNCTION_TABLE_VALUE value = (FUNCTION_TABLE_VALUE)malloc(sizeof(function_table_value));
    value->input_list=NULL;
    value->output_list=NULL;
    value->symbol_table_wrapper=NULL;
    value->isDeclared = false;
    value->needsChecking = false;
    return value;
}

void print_function_table(){
    for(int i=0 ; i<FUNC_HASHMAP_SIZE ; i++){
        if(function_table[i].is_used==true){
            printf("FUNCTION at i=%d : %s\n",i,function_table[i].function_name);
            if(function_table[i].function_table_value->input_list!=NULL){
                printf("INPUT LIST : \n");
                printChildren(function_table[i].function_table_value->input_list->child);
            }
            if(function_table[i].function_table_value->output_list!=NULL){
                printf("OUTPUT LIST : \n");
                printChildren(function_table[i].function_table_value->output_list->child);
            }
            printf("isDeclared : %s\n",function_table[i].function_table_value->isDeclared?"YES":"NO");
            printf("needsChecking : %s\n",function_table[i].function_table_value->needsChecking?"YES":"NO");
        }
    }
}