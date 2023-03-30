#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "function_hash.h"
#include "symbol_hash.h"
#include "ast_traversal.h"

SYMBOL_TABLE_WRAPPER current_symbol_table_wrapper;

void populate_function_and_symbol_tables(TREENODE root){
    if (root == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }else{
        if(strcmp(root->name,"DRIVER_MODULE_STMTS")==0){
            FUNCTION_TABLE_VALUE value = (FUNCTION_TABLE_VALUE) malloc(sizeof(function_table_value));
            value->input_list = NULL;
            value->output_list = NULL;
            value->symbol_table_wrapper = (SYMBOL_TABLE_WRAPPER) malloc(sizeof(symbol_table_wrapper));
            function_table_insert(function_table, "driver", value);
            current_symbol_table_wrapper = value->symbol_table_wrapper;
        }else if(strcmp(root->name,"DECLARESTMT")==0){
            TREENODE datatype = root->child->next;
            TREENODE idListHead = root->child;
            TREENODE temp = idListHead->next; //points to first child in idList
            while(temp!=NULL){
                SYMBOL_TABLE_VALUE value = (SYMBOL_TABLE_VALUE)malloc(sizeof(symbol_table_value));
                if(strcmp(datatype->name,"integer")==0){
                    value->symbol_table_value_union.not_array.isarray = false;
                    value->symbol_table_value_union.not_array.type = integer;
                }else if(strcmp(datatype->name,"real")==0){
                    value->symbol_table_value_union.not_array.isarray = false;
                    value->symbol_table_value_union.not_array.type = real;
                }else if(strcmp(datatype->name,"boolean")==0){
                    value->symbol_table_value_union.not_array.isarray = false;
                    value->symbol_table_value_union.not_array.type = boolean;
                }else{
                    value->symbol_table_value_union.array.isarray = true;
                    TREENODE range1 = datatype->child;
                    TREENODE range2 = datatype->child->next;
                    if(strcmp(range1->name,"plus")){
                        range1 = range1->child;
                        value->symbol_table_value_union.array.is_bottom_sign_plus = true;
                    }else if(strcmp(range1->name,"minus")){
                        range1 = range1->child;
                        value->symbol_table_value_union.array.is_bottom_sign_plus = false;
                    }else{
                        value->symbol_table_value_union.array.is_bottom_sign_plus = true;
                    }
                    if(strcmp(range1->name,"num")){
                        value->symbol_table_value_union.array.bottom_range.bottom = atoi(range1->lexeme);
                        value->symbol_table_value_union.array.is_bottom_dynamic = false;
                    }else{
                        value->symbol_table_value_union.array.bottom_range.bottom_var = range1->lexeme;
                        value->symbol_table_value_union.array.is_bottom_dynamic = true;
                    }
                }
            }
        }
    }
    populate_function_and_symbol_tables(root->child);
    populate_function_and_symbol_tables(root->next);
}
