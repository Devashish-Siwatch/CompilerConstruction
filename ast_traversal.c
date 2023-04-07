#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "function_hash.h"
#include "symbol_hash.h"
#include "ast_traversal.h"

SYMBOL_TABLE_WRAPPER current_symbol_table_wrapper;

bool check_if_declared_before(char* var){
    SYMBOL_TABLE_WRAPPER temp_wrapper = current_symbol_table_wrapper;
    while(true){
        SYMBOL_TABLE_VALUE value = symbol_table_get(temp_wrapper->symbol_table,var,strlen(var));
        if(value!=NULL) return true;
        else{
            if(temp_wrapper->parent==NULL) return false;
            else temp_wrapper = temp_wrapper->parent;
        }
    }
    
}

void check_expression_if_declared_before(TREENODE root)
{
    // printf("CHECKING FOR %s------------------\n",root->name);
    if(strcmp(root->name,"and")==0 || strcmp(root->name,"or")==0 || strcmp(root->name,"lt")==0  || 
    strcmp(root->name,"gt")==0 || strcmp(root->name,"le")==0 || strcmp(root->name,"ge")==0 || 
    strcmp(root->name,"ne")==0 || strcmp(root->name,"eq")==0 || strcmp(root->name,"plus")==0 || 
    strcmp(root->name,"minus")==0 || strcmp(root->name,"mul")==0 || strcmp(root->name,"div")==0 )
    {
        check_expression_if_declared_before(root->child);
        check_expression_if_declared_before(root->child->next);
    }
    else if(strcmp(root->name,"PLUS")==0 ||strcmp(root->name,"MINUS")==0 ){
        check_expression_if_declared_before(root->child);
    }
    else if(strcmp(root->name,"id")==0 ){
        bool is_present = check_if_declared_before(root->lexeme);
        if(!is_present){
            printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m",root->lexeme);
        }
    }
}

void go_back_to_parent_symbol_table(){
    //going back to parent symbol table if statements have ended
    if(current_symbol_table_wrapper->parent==NULL){
        // no need to do anything as module has ended here and new module creates a new symbol table itself
    }else{
        current_symbol_table_wrapper = current_symbol_table_wrapper->parent;
    }
}

void populateSymboltabeValue(TREENODE datatype,SYMBOL_TABLE_VALUE value){
    if (strcmp(datatype->name, "integer") == 0)
        {
            value->isarray = false;
            value->symbol_table_value_union.not_array.type = integer;
        }
        else if (strcmp(datatype->name, "real") == 0)
        {
            value->isarray = false;
            value->symbol_table_value_union.not_array.type = real;
        }
        else if (strcmp(datatype->name, "boolean") == 0)
        {
            value->isarray = false;
            value->symbol_table_value_union.not_array.type = boolean;
        }
        else
        {
            value->isarray = true;
            TREENODE range1 = datatype->child;
            TREENODE range2 = datatype->child->next;
            TREENODE elementType = datatype->child->next->next;

            // bottom range
            if (strcmp(range1->name, "plus") == 0)
            {
                range1 = range1->child;
                value->symbol_table_value_union.array.is_bottom_sign_plus = true;
            }
            else if (strcmp(range1->name, "minus") == 0)
            {
                range1 = range1->child;
                value->symbol_table_value_union.array.is_bottom_sign_plus = false;
            }
            else
            {
                value->symbol_table_value_union.array.is_bottom_sign_plus = true;
            }
            if (strcmp(range1->name, "num") == 0)
            {
                value->symbol_table_value_union.array.bottom_range.bottom = atoi(range1->lexeme);
                value->symbol_table_value_union.array.is_bottom_dynamic = false;
            }
            else
            {
                value->symbol_table_value_union.array.bottom_range.bottom_var = range1->lexeme;
                value->symbol_table_value_union.array.is_bottom_dynamic = true;
            }

            // top range
            if (strcmp(range2->name, "plus") == 0)
            {
                range2 = range2->child;
                value->symbol_table_value_union.array.is_top_sign_plus = true;
            }
            else if (strcmp(range2->name, "minus") == 0)
            {
                range2 = range2->child;
                value->symbol_table_value_union.array.is_top_sign_plus = false;
            }
            else
            {
                value->symbol_table_value_union.array.is_top_sign_plus = true;
            }
            if (strcmp(range2->name, "num") == 0)
            {
                value->symbol_table_value_union.array.top_range.top = atoi(range2->lexeme);
                value->symbol_table_value_union.array.is_top_dynamic = false;
            }
            else
            {
                value->symbol_table_value_union.array.top_range.top_var = range2->lexeme;
                value->symbol_table_value_union.array.is_top_dynamic = true;
            }

            // element type
            if (strcmp(elementType->lexeme, "integer") == 0)
            {
                value->symbol_table_value_union.array.element_type = integer;
            }
            else if (strcmp(elementType->lexeme, "real") == 0)
            {
                value->symbol_table_value_union.array.element_type = real;
            }
            else
            {
                value->symbol_table_value_union.array.element_type = boolean;
            }
        }
}
void addListtoSymbolTable(TREENODE root)
{
    // used when root->child is id and root->child->next is datatype
    TREENODE ListHead = root;
    TREENODE temp = ListHead->child; // points to first child in Listhead
    while (temp != NULL)
    {

        TREENODE datatype = temp->next;
        SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
        populateSymboltabeValue(datatype,value);
        symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
        temp = temp->child;
    }
}

void insert_symbol_table_at_end(SYMBOL_TABLE_WRAPPER wrapper, SYMBOL_TABLE_WRAPPER temp)
{
    if (wrapper->child == NULL)
    {
        wrapper->child = temp;
        temp->parent = wrapper;
    }
    else
    {
        SYMBOL_TABLE_WRAPPER iter = wrapper->child;
        while (iter->next != NULL)
        {
            iter = iter->next;
        }
        iter->next = temp;
        temp->next = NULL;
        temp->parent = wrapper;
    }
}

void populate_function_and_symbol_tables(TREENODE root)
{
    if (root == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }
    else
    {
        if (strcmp(root->name, "Module1") == 0)
        {
            printf("REACHED MODULE1 NODE\n");
            FUNCTION_TABLE_VALUE value = create_function_value();
            value->input_list = root->child->next;
            if (strcmp(root->child->next->next->name, "OutputPlistHead") == 0)
                value->output_list = root->child->next->next;
            else
                value->output_list = NULL;
            value->symbol_table_wrapper = create_symbol_table_wrapper();
            value->symbol_table_wrapper->name = root->child->name;
            strcat(value->symbol_table_wrapper->name,"_symbol_table");
            value->symbol_table_wrapper->parent = NULL;
            value->symbol_table_wrapper->child = NULL;
            value->symbol_table_wrapper->next = NULL;
            function_table_insert(function_table, root->child->lexeme, value);
            current_symbol_table_wrapper = value->symbol_table_wrapper;
        }
        else if (strcmp(root->name, "InputPlistHead") == 0)
        {
            addListtoSymbolTable(root);
        }
        else if (strcmp(root->name, "ASSIGNMENTSTMT") ==0){
            TREENODE lhs = root->child;
            TREENODE rhs = lhs->next;
            bool lhs_exists = check_if_declared_before(lhs->lexeme);
            if(!lhs_exists){
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m",lhs->lexeme);
            }
            check_expression_if_declared_before(rhs);
        }
        else if (strcmp(root->name, "DRIVER_MODULE_STMTS") == 0)
        {
            FUNCTION_TABLE_VALUE value = create_function_value();
            value->input_list = NULL;
            value->output_list = NULL;
            value->symbol_table_wrapper = create_symbol_table_wrapper();
            value->symbol_table_wrapper->name = "driver_symbol_table";
            value->symbol_table_wrapper->parent = NULL;
            value->symbol_table_wrapper->child = NULL;
            value->symbol_table_wrapper->next = NULL;
            function_table_insert(function_table, "driver", value);
            current_symbol_table_wrapper = value->symbol_table_wrapper;
        }
        else if(strcmp(root->name,"STMTS_END")==0){
            go_back_to_parent_symbol_table();
        }
        else if (strcmp(root->name, "DECLARESTMT") == 0)
        {
            TREENODE datatype = root->child->next;
            TREENODE idListHead = root->child;
            TREENODE temp = idListHead->child; // points to first child in idList
            while (temp != NULL)
            {
                SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
                populateSymboltabeValue(datatype,value);
                symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
                temp = temp->child;
            }
        }
        else if (strcmp(root->name, "ITERATIVESTMT_WHILE") == 0)
        {
            //checking if condition has expr has been declared before
            check_expression_if_declared_before(root->child);
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "WHILE_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
            
        }
        else if(strcmp(root->name,"CONDITIONALSTMT")==0){
             //checking if condition has expr has been declared before
             bool is_declared = check_if_declared_before(root->child->lexeme);
            if(!is_declared){
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m",root->child->lexeme);
            }
            // check_if_declared_before(root->child->lexeme);
        }
        else if(strcmp(root->name,"CASE_STMT")==0)
        {
            
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "CASE_STMT_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if(strcmp(root->name,"DEFAULT")==0)
        {
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "DEFAULT_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if (strcmp(root->name, "ITERATIVESTMT_FOR") == 0)
        {
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "FOR_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
            SYMBOL_TABLE_VALUE value = create_new_symbol_node("integer");
            value->isarray = false;
            value->symbol_table_value_union.not_array.type = integer;
            symbol_insert(current_symbol_table_wrapper->symbol_table, root->child->lexeme, value);
        }
        else if(strcmp(root->name,"IO_INPUT")==0)
        {
            TREENODE var = root->child;
            bool var_exists = check_if_declared_before(var->lexeme);
            if(!var_exists){
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m",var->lexeme);
            }
        }
        else if(strcmp(root->name,"IO_OUTPUT")==0)
        {
            TREENODE var = root->child;
            bool var_exists=true;
            if(strcmp(var->name,"id")==0)
                var_exists = check_if_declared_before(var->lexeme);
            if(!var_exists){
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m",var->lexeme);
            }
            if(var->next!=NULL)
            {
                var=var->next;
                if((strcmp(var->name,"id")==0) && (!check_if_declared_before(var->lexeme)))
                {
                    printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m",var->lexeme);
                }
            }
        }
    }
    populate_function_and_symbol_tables(root->child);
    populate_function_and_symbol_tables(root->next);
}
