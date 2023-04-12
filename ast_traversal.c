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
#include "function_hash.h"
#include "symbol_hash.h"
#include "ast_traversal.h"

SYMBOL_TABLE_WRAPPER current_symbol_table_wrapper;
char *current_module_name;
int current_offset_value = 0;
SYMBOL_TABLE_WRAPPER current_symbol_table_wrapper_pass_2;

void init_ast_traversal(){
    current_module_name="";
    current_offset_value=0;
    current_symbol_table_wrapper=NULL;
    current_symbol_table_wrapper_pass_2=NULL;
    return;
}

void copy_symbol_table_value(SYMBOL_TABLE_VALUE newValue, SYMBOL_TABLE_VALUE oldValue){
    if (oldValue->isarray)
    {
        newValue->isarray = true;
        newValue->symbol_table_value_union.array.is_bottom_dynamic = oldValue->symbol_table_value_union.array.is_bottom_dynamic;
        newValue->symbol_table_value_union.array.is_bottom_sign_plus = oldValue->symbol_table_value_union.array.is_bottom_sign_plus;
        newValue->symbol_table_value_union.array.is_top_dynamic = oldValue->symbol_table_value_union.array.is_top_dynamic;
        newValue->symbol_table_value_union.array.is_top_sign_plus = oldValue->symbol_table_value_union.array.is_top_sign_plus;
        newValue->symbol_table_value_union.array.top_range.top = oldValue->symbol_table_value_union.array.top_range.top;
        newValue->symbol_table_value_union.array.top_range.top_var = oldValue->symbol_table_value_union.array.top_range.top_var;
        newValue->symbol_table_value_union.array.bottom_range.bottom = oldValue->symbol_table_value_union.array.bottom_range.bottom;
        newValue->symbol_table_value_union.array.bottom_range.bottom_var = oldValue->symbol_table_value_union.array.bottom_range.bottom_var;
        newValue->symbol_table_value_union.array.element_type = oldValue->symbol_table_value_union.array.element_type;
    }
    else
    {
        newValue->isarray = false;
        newValue->symbol_table_value_union.not_array.type = oldValue->symbol_table_value_union.not_array.type;
    }
    newValue->module_name = oldValue->module_name;
    newValue->isInputParameter = oldValue->isInputParameter;
    newValue->isOutputParameter = oldValue->isOutputParameter;
    newValue->outputParameterNeedsChecking = oldValue->outputParameterNeedsChecking;
    newValue->line_number_end = oldValue->line_number_end;
    newValue->line_number_start = oldValue->line_number_start;
    newValue->nesting_level = oldValue->nesting_level;
    newValue->offset = oldValue->offset;
    newValue->width = oldValue->width;
    newValue->isLoopVariable = oldValue->isLoopVariable;
    return;
}

int get_width(SYMBOL_TABLE_WRAPPER wrapper)
{
    int total = 0;
    for (int i = 0; i < SYMBOL_HASHMAP_SIZE; i++)
    {
        if (wrapper->symbol_table[i].is_used)
        {
            SYMBOL_TABLE_VALUE value = wrapper->symbol_table[i].symbol_table_value;
            total += value->width;
        }
    }
    if (wrapper->child != NULL)
        total += get_width(wrapper->child);
    if (wrapper->next != NULL)
        total += get_width(wrapper->next);
    return total;
}

void get_total_width()
{
    for (int i = 0; i < FUNC_HASHMAP_SIZE; i++)
    {   
        int total = 0;

        if (function_table[i].is_used)
        {
            FUNCTION_TABLE_VALUE value = function_table[i].function_table_value;
            SYMBOL_TABLE_WRAPPER temp = value->symbol_table_wrapper;
            total += get_width(temp);
            printf("%s %d\n",function_table[i].function_name,total);
        }
        
        
    }
    return;
}

void print_array_info(SYMBOL_TABLE_WRAPPER wrapper){
    for (int i = 0; i < SYMBOL_HASHMAP_SIZE; i++)
    {
        if (wrapper->symbol_table[i].is_used)
        {
            SYMBOL_TABLE_VALUE value = wrapper->symbol_table[i].symbol_table_value;
            if(value!=NULL && value->isarray){
                char* s_or_d = (!value->symbol_table_value_union.array.is_top_dynamic && !value->symbol_table_value_union.array.is_bottom_dynamic)?"Static":"Dynamic";
                char* top, bottom;
                char* type;
                if(value->symbol_table_value_union.array.element_type==integer){
                    type = "integer";
                }else if(value->symbol_table_value_union.array.element_type==real){
                    type = "real";
                }else if(value->symbol_table_value_union.array.element_type==boolean){
                    type = "boolean";
                }


                if(!value->symbol_table_value_union.array.is_top_dynamic && !value->symbol_table_value_union.array.is_bottom_dynamic){
                    printf("%-20s %4d-%-4d %-20s %-8s array           [%4d,%-4d] \t%-20s\n",value->module_name, value->line_number_start, value->line_number_end, wrapper->symbol_table[i].variable_name, s_or_d,value->symbol_table_value_union.array.bottom_range.bottom,value->symbol_table_value_union.array.top_range.top,type);
                }else if(value->symbol_table_value_union.array.is_top_dynamic && value->symbol_table_value_union.array.is_bottom_dynamic){
                    printf("%-20s %4d-%-4d %-20s %-8s array           [%4s,%-4s] \t%-20s\n",value->module_name, value->line_number_start, value->line_number_end, wrapper->symbol_table[i].variable_name, s_or_d,value->symbol_table_value_union.array.bottom_range.bottom_var,value->symbol_table_value_union.array.top_range.top_var,type);
                }else if(!value->symbol_table_value_union.array.is_top_dynamic && value->symbol_table_value_union.array.is_bottom_dynamic){
                    printf("%-20s %4d-%-4d %-20s %-8s array           [%4s,%-4d] \t%-20s\n",value->module_name, value->line_number_start, value->line_number_end, wrapper->symbol_table[i].variable_name, s_or_d,value->symbol_table_value_union.array.bottom_range.bottom_var,value->symbol_table_value_union.array.top_range.top,type);
                }else if(value->symbol_table_value_union.array.is_top_dynamic && !value->symbol_table_value_union.array.is_bottom_dynamic){
                    printf("%-20s %4d-%-4d %-20s %-8s array           [%4d,%-4s] \t%-20s\n",value->module_name, value->line_number_start, value->line_number_end, wrapper->symbol_table[i].variable_name, s_or_d,value->symbol_table_value_union.array.bottom_range.bottom,value->symbol_table_value_union.array.top_range.top_var,type);
                }
            }
        }    
    }
    if (wrapper->child != NULL)
        print_array_info(wrapper->child);
    if (wrapper->next != NULL)
        print_array_info(wrapper->next);
    return;
}

void print_all_array_info(){
    for (int i = 0; i < FUNC_HASHMAP_SIZE; i++)
    {   
        if (function_table[i].is_used)
        {
            FUNCTION_TABLE_VALUE value = function_table[i].function_table_value;
            SYMBOL_TABLE_WRAPPER temp = value->symbol_table_wrapper;
            // printf("calling for %s\n",value->symbol_table_wrapper->name);
            print_array_info(temp);
        }
    }
    return;
}

int get_nesting_level(SYMBOL_TABLE_WRAPPER wrapper)
{
    SYMBOL_TABLE_WRAPPER temp = wrapper;
    int count = 0;
    while (temp->parent != NULL)
    {
        temp = temp->parent;
        count++;
    }
    return count;
}

SYMBOL_TABLE_WRAPPER get_while_symbol_table_having_declaration_of(char *var)
{
    SYMBOL_TABLE_WRAPPER temp_wrapper = current_symbol_table_wrapper;
    while (true)
    {
        if (temp_wrapper == NULL)
            return NULL;
        if (temp_wrapper->while_variables != NULL && data_exists(var, temp_wrapper->while_variables))
        {
            return temp_wrapper;
        }
        else
        {
            temp_wrapper = temp_wrapper->parent;
        }
    }
}

SYMBOL_TABLE_VALUE get_symbol_table_value_in_above_table(SYMBOL_TABLE_WRAPPER cc, char *var)
{
    SYMBOL_TABLE_WRAPPER temp_wrapper = cc;
    while (true)
    {
        if (temp_wrapper == NULL)
            return NULL;
        SYMBOL_TABLE_VALUE value = symbol_table_get(temp_wrapper->symbol_table, var, strlen(var));
        if (value != NULL)
            return value;
        else
        {
            temp_wrapper = temp_wrapper->parent;
        }
    }
}

SYMBOL_TABLE_VALUE get_type_of_expression(TREENODE root)
{
    SYMBOL_TABLE_VALUE type = create_new_symbol_node("type");
    type->isarray = false;
    if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0 || strcmp(root->name, "lt") == 0 ||
        strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
        strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0 || strcmp(root->name, "plus") == 0 ||
        strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0 || strcmp(root->name, "div") == 0)
    {
        SYMBOL_TABLE_VALUE a = get_type_of_expression(root->child);
        SYMBOL_TABLE_VALUE b = get_type_of_expression(root->child->next);
        // printf("a->isarray = %s\n", root->child->lexeme);
        // printf("b->isarray = %s\n", root->child->next->lexeme);
        // printf("a->isarray = %d\n", a->isarray);
        // printf("b->isarray = %d\n", b->isarray);
        if (!a->isarray && !b->isarray)
        {
            int type_a = a->symbol_table_value_union.not_array.type;
            int type_b = b->symbol_table_value_union.not_array.type;

            if (strcmp(root->name, "plus") == 0 ||
                strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0)
            {

                if (type_a == 0 && type_b == 0)
                {
                    type->symbol_table_value_union.not_array.type = 0;
                }
                else if (type_a == 1 && type_b == 1)
                    type->symbol_table_value_union.not_array.type = 1;
                else if (type_a == -2 || type_b == -2)
                {
                    type->symbol_table_value_union.not_array.type = -2;
                }
                else
                {
                    type->symbol_table_value_union.not_array.type = -1;
                    // printf("\033[31m\nERROR : Types of %s and %s are different\n\033[0m", root->child->lexeme,root->child->next->lexeme);
                }
            }
            else if (strcmp(root->name, "div") == 0)
            {
                if (type_a == 0 && type_b == 0)
                {
                    type->symbol_table_value_union.not_array.type = 1; // real in all cases
                }
                else if (type_a == 0 && type_b == 1 || type_a == 1 && type_b == 0)
                {
                    type->symbol_table_value_union.not_array.type = 1;
                }
                else if (type_a == 1 && type_b == 1)
                {
                    type->symbol_table_value_union.not_array.type = 1;
                }
                else if (type_a == -2 || type_b == -2)
                {
                    type->symbol_table_value_union.not_array.type = -2;
                }
                else
                {
                    type->symbol_table_value_union.not_array.type = -1;
                    // printf("TYPE MISMATCH IN EXPRESSION");
                }
            }
            else if (strcmp(root->name, "lt") == 0 ||
                     strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
                     strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0)
            {
                if (type_a == 0 && type_b == 0)
                {
                    type->symbol_table_value_union.not_array.type = 2; // relational on int
                }
                else if (type_a == 1 && type_b == 1)
                {
                    type->symbol_table_value_union.not_array.type = 2; // relational on real
                }
                else if (type_a == -2 || type_b == -2)
                {
                    type->symbol_table_value_union.not_array.type = -2;
                }
                else
                {
                    type->symbol_table_value_union.not_array.type = -1;
                    // printf("TYPE MISMATCH IN EXPRESSION");
                }
            }
            else if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0)
            {
                if (type_a == 2 && type_b == 2)
                {
                    type->symbol_table_value_union.not_array.type = 2; // logical on bool
                }
                else if (type_a == -2 || type_b == -2)
                {
                    type->symbol_table_value_union.not_array.type = -2;
                }
                else
                {
                    type->symbol_table_value_union.not_array.type = -1;
                    // printf("TYPE MISMATCH IN EXPRESSION");
                }
            }
            return type;
        }
        else if (a->isarray && b->isarray)
        {
            int type_a = a->symbol_table_value_union.array.element_type;
            int type_b = b->symbol_table_value_union.array.element_type;
            if (type_a == -2 || type_b == -2)
            {
                type->symbol_table_value_union.not_array.type = -2;
                return type;
            }
            else if (root->child->child == NULL || root->child->next->child == NULL)
            {
                // printf("a->null = %s\n", root->child->lexeme);
                // printf("\033[31m\nERROR : TYPE MISMATCH in both arrays.\n\033[0m");
                type->symbol_table_value_union.not_array.type = -1;
                return type;
            }

            else
            {
                if (a->symbol_table_value_union.array.element_type == b->symbol_table_value_union.array.element_type)
                {
                    if (strcmp(root->name, "plus") == 0 ||
                        strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0)
                    {

                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 0 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 0;
                        }
                        else if (type_a == 1 && type_b == 1)
                            type->symbol_table_value_union.not_array.type = 1;

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("\033[31m\nERROR : Types of %s and %s are different\n\033[0m", root->child->lexeme,root->child->next->lexeme);
                        }
                    }
                    else if (strcmp(root->name, "div") == 0)
                    {
                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 0 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 1; // real in all cases
                        }
                        else if (type_a == 0 && type_b == 1 || type_a == 1 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 1;
                        }
                        else if (type_a == 1 && type_b == 1)
                        {
                            type->symbol_table_value_union.not_array.type = 1;
                        }

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("TYPE MISMATCH IN EXPRESSION");
                        }
                    }
                    else if (strcmp(root->name, "lt") == 0 ||
                             strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
                             strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0)
                    {
                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 0 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 2; // relational on int
                        }
                        else if (type_a == 1 && type_b == 1)
                        {
                            type->symbol_table_value_union.not_array.type = 2; // relational on real
                        }

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("TYPE MISMATCH IN EXPRESSION");
                        }
                    }
                    else if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0)
                    {
                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 2 && type_b == 2)
                        {
                            type->symbol_table_value_union.not_array.type = 2; // logical on bool
                        }

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("TYPE MISMATCH IN EXPRESSION");
                        }
                    }
                    return type;
                }
            }
        }
        else if (a->isarray && !b->isarray)
        {
            int type_a = a->symbol_table_value_union.array.element_type;
            int type_b = b->symbol_table_value_union.not_array.type;

            if (type_a == -2 || type_b == -2)
            {
                type->symbol_table_value_union.not_array.type = -2;
                return type;
            }
            else if (root->child->child == NULL)
            {

                type->symbol_table_value_union.not_array.type = -1;
                return type;
            }
            else if (b->symbol_table_value_union.not_array.type != a->symbol_table_value_union.array.element_type)
            {
                type->symbol_table_value_union.not_array.type = -1;
                return type;
            }

            else
            {
                if (strcmp(root->name, "plus") == 0 ||
                    strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0)
                {

                    if (type_a == -2 || type_b == -2)
                    {
                        type->symbol_table_value_union.not_array.type = -2;
                    }
                    else if (type_a == 0 && type_b == 0)
                    {
                        type->symbol_table_value_union.not_array.type = 0;
                    }
                    else if (type_a == 1 && type_b == 1)
                        type->symbol_table_value_union.not_array.type = 1;

                    else
                    {
                        type->symbol_table_value_union.not_array.type = -1;
                        // printf("\033[31m\nERROR : Types of %s and %s are different\n\033[0m", root->child->lexeme,root->child->next->lexeme);
                    }
                }
                else if (strcmp(root->name, "div") == 0)
                {
                    if (type_a == -2 || type_b == -2)
                    {
                        type->symbol_table_value_union.not_array.type = -2;
                    }
                    else if (type_a == 0 && type_b == 0)
                    {
                        type->symbol_table_value_union.not_array.type = 1; // real in all cases
                    }
                    else if (type_a == 0 && type_b == 1 || type_a == 1 && type_b == 0)
                    {
                        type->symbol_table_value_union.not_array.type = 1;
                    }
                    else if (type_a == 1 && type_b == 1)
                    {
                        type->symbol_table_value_union.not_array.type = 1;
                    }

                    else
                    {
                        type->symbol_table_value_union.not_array.type = -1;
                        // printf("TYPE MISMATCH IN EXPRESSION");
                    }
                }
                else if (strcmp(root->name, "lt") == 0 ||
                         strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
                         strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0)
                {
                    if (type_a == -2 || type_b == -2)
                    {
                        type->symbol_table_value_union.not_array.type = -2;
                    }
                    else if (type_a == 0 && type_b == 0)
                    {
                        type->symbol_table_value_union.not_array.type = 2; // relational on int
                    }
                    else if (type_a == 1 && type_b == 1)
                    {
                        type->symbol_table_value_union.not_array.type = 2; // relational on real
                    }

                    else
                    {
                        type->symbol_table_value_union.not_array.type = -1;
                        // printf("TYPE MISMATCH IN EXPRESSION");
                    }
                }
                else if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0)
                {
                    if (type_a == -2 || type_b == -2)
                    {
                        type->symbol_table_value_union.not_array.type = -2;
                    }
                    else if (type_a == 2 && type_b == 2)
                    {
                        type->symbol_table_value_union.not_array.type = 2; // logical on bool
                    }

                    else
                    {
                        type->symbol_table_value_union.not_array.type = -1;
                        // printf("TYPE MISMATCH IN EXPRESSION");
                    }
                }
                return type;
            }
            // }
            // else
            // {
            //     if (a->symbol_table_value_union.array.element_type == b->symbol_table_value_union.not_array.type)
            //     {
            //         return a;
            //     }
            // }
        }
        else if (!a->isarray && b->isarray)
        {
            int type_a = a->symbol_table_value_union.not_array.type;
            int type_b = b->symbol_table_value_union.array.element_type;
            if (type_a == -2 || type_b == -2)
            {
                type->symbol_table_value_union.not_array.type = -2;
                return type;
            }
            else if (root->child->next->child == NULL)
            {
                if (a->symbol_table_value_union.not_array.type != b->symbol_table_value_union.array.element_type)
                {
                    type->symbol_table_value_union.not_array.type = -1;
                    return type;
                }
                else
                {
                    return a;
                }
            }

            else
            {
                if (a->symbol_table_value_union.not_array.type == b->symbol_table_value_union.array.element_type)
                {
                    if (strcmp(root->name, "plus") == 0 ||
                        strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0)
                    {

                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 0 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 0;
                        }
                        else if (type_a == 1 && type_b == 1)
                            type->symbol_table_value_union.not_array.type = 1;

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("\033[31m\nERROR : Types of %s and %s are different\n\033[0m", root->child->lexeme,root->child->next->lexeme);
                        }
                    }
                    else if (strcmp(root->name, "div") == 0)
                    {
                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 0 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 1; // real in all cases
                        }
                        else if (type_a == 0 && type_b == 1 || type_a == 1 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 1;
                        }
                        else if (type_a == 1 && type_b == 1)
                        {
                            type->symbol_table_value_union.not_array.type = 1;
                        }

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("TYPE MISMATCH IN EXPRESSION");
                        }
                    }
                    else if (strcmp(root->name, "lt") == 0 ||
                             strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
                             strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0)
                    {
                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 0 && type_b == 0)
                        {
                            type->symbol_table_value_union.not_array.type = 2; // relational on int
                        }
                        else if (type_a == 1 && type_b == 1)
                        {
                            type->symbol_table_value_union.not_array.type = 2; // relational on real
                        }

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("TYPE MISMATCH IN EXPRESSION");
                        }
                    }
                    else if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0)
                    {
                        if (type_a == -2 || type_b == -2)
                        {
                            type->symbol_table_value_union.not_array.type = -2;
                        }
                        else if (type_a == 2 && type_b == 2)
                        {
                            type->symbol_table_value_union.not_array.type = 2; // logical on bool
                        }

                        else
                        {
                            type->symbol_table_value_union.not_array.type = -1;
                            // printf("TYPE MISMATCH IN EXPRESSION");
                        }
                    }
                    return type;
                }
            }
        }
    }
    else if (strcmp(root->name, "PLUS") == 0 || strcmp(root->name, "MINUS") == 0)
    {
        get_type_of_expression(root->child);
    }
    else if (strcmp(root->name, "id") == 0)
    {
        // printf("id: %s\n", root->lexeme);
        bool is_present = check_if_declared_before(root->lexeme);
        SYMBOL_TABLE_VALUE stv = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, root->lexeme);
        if (is_present)
        {
            if (!stv->isarray)
            {
                return stv;
            }

            else
            {
                // printf("array element: %s\n", root->lexeme);
                // printf("ISARRAY:%d\n", stv->isarray);
                //  int x = get_type_of_expression(root->child);
                //  if(x!=0){
                //      printf("Array range expression not integer");
                //  }
                //  printf("array element: %d\n", stv->symbol_table_value_union.array.top_range);
                return stv;
            }
        }
        else
        {
            type->isarray = 0;
            type->symbol_table_value_union.not_array.type = -2;
            return type;
        }

        // bool is_present = check_if_declared_before(root->lexeme);
        // if (!is_present)
        // {
        //     printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", root->lexeme);
        // }
        // if (root->next != NULL)
        //     check_expression_if_declared_before(root->next);
    }
    else if (strcmp(root->name, "num") == 0)
    {
        type->symbol_table_value_union.not_array.type = 0;
        return type;
    }
    else if (strcmp(root->name, "rnum") == 0)
    {
        type->symbol_table_value_union.not_array.type = 1;
        return type;
    }
    else if (strcmp(root->name, "true") == 0 || strcmp(root->name, "false") == 0)
    {
        type->symbol_table_value_union.not_array.type = 2;
        return type;
    }
    else if (strcmp(root->name, "LVALUEARRSTMT") == 0)
    {
        SYMBOL_TABLE_VALUE a = get_type_of_expression(root->child->child);
        SYMBOL_TABLE_VALUE b = get_type_of_expression(root->child->next->child);
        if (!a->isarray)
        {
            if (!a->symbol_table_value_union.not_array.type == 0)
            {
                printf("\033[31m\nLine %d ERROR : Array range expression not integer.\n\033[0m", root->line_number);
            }
        }
        else
        {
            printf("\033[31m\nLine %d ERROR : Array range expression not integer.\n\033[0m", root->line_number);
        }
        return b;
    }
}

int get_type_of_variable(char *lexeme)
{
    SYMBOL_TABLE_VALUE stv = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, lexeme);
    // printf("%s\n", stv->module_name);
    if (stv->symbol_table_value_union.not_array.type == integer)
        return 0;
    else if (stv->symbol_table_value_union.not_array.type == real)
        return 1;
    return 2;
}

bool check_if_declared_before(char *var)
{
    SYMBOL_TABLE_WRAPPER temp_wrapper = current_symbol_table_wrapper;
    while (true)
    {
        SYMBOL_TABLE_VALUE value = symbol_table_get(temp_wrapper->symbol_table, var, strlen(var));
        if (value != NULL)
            return true;
        else
        {
            if (temp_wrapper->parent == NULL)
                return false;
            else
                temp_wrapper = temp_wrapper->parent;
        }
    }
}
bool check_if_function_declared(char *var)
{
    FUNCTION_TABLE_VALUE value = function_table_get(function_table, var, strlen(var));
    if (value != NULL)
        return true;
    else
        return false;
}
bool check_if_redeclared(char *var)
{
    SYMBOL_TABLE_WRAPPER temp_wrapper = current_symbol_table_wrapper;
    SYMBOL_TABLE_VALUE value = symbol_table_get(temp_wrapper->symbol_table, var, strlen(var));
    if (value != NULL)
        return true;
    else
        return false;
}

void appendWhileVariables(TREENODE root, LIST list)
{
    // printf("CHECKING FOR %s------------------\n", root->name);
    if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0 || strcmp(root->name, "lt") == 0 ||
        strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
        strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0 || strcmp(root->name, "plus") == 0 ||
        strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0 || strcmp(root->name, "div") == 0)
    {
        appendWhileVariables(root->child, list);
        appendWhileVariables(root->child->next, list);
    }
    else if (strcmp(root->name, "PLUS") == 0 || strcmp(root->name, "MINUS") == 0)
    {
        appendWhileVariables(root->child, list);
    }
    else if (strcmp(root->name, "id") == 0)
    {
        NODE node = createNewNode(root->lexeme);
        insertNodeIntoList(node, list);
        return;
    }
}

void check_array_index_bounds(TREENODE indexRoot, char *arrayLexeme, int line_number)
{
    if (strcmp(indexRoot->name, "num") == 0)
    {
        int index = atoi(indexRoot->lexeme);
        SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, arrayLexeme);
        if (value != NULL && value->isarray && !value->symbol_table_value_union.array.is_bottom_dynamic && !value->symbol_table_value_union.array.is_top_dynamic)
        {
            int lower = value->symbol_table_value_union.array.bottom_range.bottom * ((value->symbol_table_value_union.array.is_bottom_sign_plus) ? 1 : -1);
            int upper = value->symbol_table_value_union.array.top_range.top * ((value->symbol_table_value_union.array.is_top_sign_plus) ? 1 : -1);
            if (!(index >= lower && index <= upper))
            {
                printf("\033[31m\nLine %d ERROR : Array index out of bounds.\n\033[0m", line_number);
            }
        }
    }
    else if (strcmp(indexRoot->name, "PLUS") == 0 && strcmp(indexRoot->child->name, "num") == 0)
    {
        int index = atoi(indexRoot->child->lexeme);
        SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, arrayLexeme);
        if (value != NULL && value->isarray && !value->symbol_table_value_union.array.is_bottom_dynamic && !value->symbol_table_value_union.array.is_top_dynamic)
        {
            int lower = value->symbol_table_value_union.array.bottom_range.bottom * ((value->symbol_table_value_union.array.is_bottom_sign_plus) ? 1 : -1);
            int upper = value->symbol_table_value_union.array.top_range.top * ((value->symbol_table_value_union.array.is_top_sign_plus) ? 1 : -1);
            if (!(index >= lower && index <= upper))
            {
                printf("\033[31m\nLine %d ERROR : Array index out of bounds.\n\033[0m", line_number);
            }
        }
    }
    else if (strcmp(indexRoot->name, "MINUS") == 0 && strcmp(indexRoot->child->name, "num") == 0)
    {
        int index = -1 * atoi(indexRoot->child->lexeme);
        SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, arrayLexeme);
        if (value != NULL && value->isarray && !value->symbol_table_value_union.array.is_bottom_dynamic && !value->symbol_table_value_union.array.is_top_dynamic)
        {
            int lower = value->symbol_table_value_union.array.bottom_range.bottom * ((value->symbol_table_value_union.array.is_bottom_sign_plus) ? 1 : -1);
            int upper = value->symbol_table_value_union.array.top_range.top * ((value->symbol_table_value_union.array.is_top_sign_plus) ? 1 : -1);
            if (!(index >= lower && index <= upper))
            {
                printf("\033[31m\nLine %d ERROR : Array index out of bounds.\n\033[0m", line_number);
            }
        }
    }
}

void check_expression_if_declared_before(TREENODE root)
{
    // printf("CHECKING FOR %s------------------\n",root->name);
    if (strcmp(root->name, "and") == 0 || strcmp(root->name, "or") == 0 || strcmp(root->name, "lt") == 0 ||
        strcmp(root->name, "gt") == 0 || strcmp(root->name, "le") == 0 || strcmp(root->name, "ge") == 0 ||
        strcmp(root->name, "ne") == 0 || strcmp(root->name, "eq") == 0 || strcmp(root->name, "plus") == 0 ||
        strcmp(root->name, "minus") == 0 || strcmp(root->name, "mul") == 0 || strcmp(root->name, "div") == 0)
    {
        check_expression_if_declared_before(root->child);
        check_expression_if_declared_before(root->child->next);
    }
    else if (strcmp(root->name, "PLUS") == 0 || strcmp(root->name, "MINUS") == 0)
    {
        check_expression_if_declared_before(root->child);
    }
    else if (strcmp(root->name, "id") == 0)
    {
        bool is_present = check_if_declared_before(root->lexeme);
        if (!is_present)
        {
            printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", root->line_number, root->lexeme);
        }
        else
        {
            // checking type bound for a[5] like terms
            if (root->child != NULL)
            {
                SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, root->lexeme);
                if (!value->isarray)
                {
                    printf("\033[31m\nLine %d ERROR : Array type access for non-array element.\n\033[0m", root->line_number);
                }
                else
                {
                    check_array_index_bounds(root->child, root->lexeme, root->line_number);
                }
            }
        }
        if (root->child != NULL)
            check_expression_if_declared_before(root->child);
    }
}

void go_back_to_parent_symbol_table()
{
    // going back to parent symbol table if statements have ended
    if (current_symbol_table_wrapper->parent == NULL)
    {
        // no need to do anything as module has ended here and new module creates a new symbol table itself
    }
    else
    {
        current_symbol_table_wrapper = current_symbol_table_wrapper->parent;
    }
}

void populateSymboltableValue(TREENODE current_node, TREENODE datatype, SYMBOL_TABLE_VALUE value, char *module_name, int nesting_level, int start_line_number, bool isInputParameter, bool isLoopVariable, bool isOutputParameter, bool outputParameterNeedsChecking)
{
    value->isOutputParameter = isOutputParameter;
    value->outputParameterNeedsChecking = outputParameterNeedsChecking;
    value->isLoopVariable = isLoopVariable;
    value->isInputParameter = isInputParameter;
    value->module_name = module_name;
    value->nesting_level = nesting_level;
    value->line_number_start = start_line_number;
    if (strcmp(datatype->name, "integer") == 0)
    {
        value->isarray = false;
        value->symbol_table_value_union.not_array.type = integer;
        value->width = 2;
    }
    else if (strcmp(datatype->name, "real") == 0)
    {
        value->isarray = false;
        value->symbol_table_value_union.not_array.type = real;
        value->width = 4;
    }
    else if (strcmp(datatype->name, "boolean") == 0)
    {
        value->isarray = false;
        value->symbol_table_value_union.not_array.type = boolean;
        value->width = 1;
    }
    else
    {
        value->isarray = true;
        TREENODE range1 = datatype->child;
        TREENODE range2 = datatype->child->next;
        TREENODE elementType = datatype->child->next->next;

        // bottom range
        if (strcmp(range1->name, "PLUS") == 0)
        {
            range1 = range1->child;
            value->symbol_table_value_union.array.is_bottom_sign_plus = true;
        }
        else if (strcmp(range1->name, "MINUS") == 0)
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
        if (strcmp(range2->name, "PLUS") == 0)
        {
            range2 = range2->child;
            value->symbol_table_value_union.array.is_top_sign_plus = true;
        }
        else if (strcmp(range2->name, "MINUS") == 0)
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
        if (!value->symbol_table_value_union.array.is_top_dynamic && !value->symbol_table_value_union.array.is_bottom_dynamic)
        {
            int top_range = value->symbol_table_value_union.array.top_range.top;
            int bottom_range = value->symbol_table_value_union.array.bottom_range.bottom;
            if (!(value->symbol_table_value_union.array.is_top_sign_plus))
                top_range *= -1;
            if (!(value->symbol_table_value_union.array.is_bottom_sign_plus))
                bottom_range *= -1;
            if ((bottom_range) > (top_range))
            {

                printf("\033[31m\nLine %d ERROR : Upper range is less than lower range of the array .\n\033[0m", current_node->line_number);
            }
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

        // width
        if (value->symbol_table_value_union.array.is_bottom_dynamic || value->symbol_table_value_union.array.is_top_dynamic)
        {
            value->width = 1;
        }
        if (!value->symbol_table_value_union.array.is_bottom_dynamic && !value->symbol_table_value_union.array.is_top_dynamic)
        {
            int bottom = (value->symbol_table_value_union.array.bottom_range.bottom) * (value->symbol_table_value_union.array.is_bottom_sign_plus ? 1 : -1);
            int top = (value->symbol_table_value_union.array.top_range.top) * (value->symbol_table_value_union.array.is_top_sign_plus ? 1 : -1);
            value->width = abs(top - bottom) + 1;
            if (strcmp(elementType->lexeme, "integer") == 0)
            {
                value->width = value->width * 2 + 1;
            }
            else if (strcmp(elementType->lexeme, "real") == 0)
            {
                value->width = value->width * 4 + 1;
            }
            else
            { // boolean
                value->width = value->width * 1 + 1;
            }
        }
    }
    value->offset = current_offset_value;
}
void addListtoSymbolTable(TREENODE root, int nesting_level, bool isInputParam, bool isOutputParam, bool outputParamNeedsChecking)
{
    // used when root->child is id and root->child->next is datatype
    TREENODE ListHead = root;
    TREENODE temp = ListHead->child; // points to first child in Listhead
    // Going to stmts_end
    TREENODE module1_node = root->parent;
    TREENODE stmts_end_node = module1_node->child;
    while (stmts_end_node->next != NULL)
        stmts_end_node = stmts_end_node->next;
    int end_line_number = stmts_end_node->line_number;
    while (temp != NULL)
    {

        TREENODE datatype = temp->next;
        SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
        value->line_number_end = end_line_number;
        populateSymboltableValue(temp, datatype, value, current_module_name, nesting_level, current_symbol_table_wrapper->starting_line_number, isInputParam, false, isOutputParam, outputParamNeedsChecking);
        current_offset_value += value->width;
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

SYMBOL_TABLE_WRAPPER search_below_by_line_number(int line_no)
{
    SYMBOL_TABLE_WRAPPER iter = current_symbol_table_wrapper_pass_2->child;
    while (iter != NULL)
    {
        if (iter->starting_line_number == line_no)
        {
            return iter;
        }
        iter = iter->next;
    }
    return NULL;
}

void ast_pass2(TREENODE root)
{
     // printf("%s sigma\n",root->name);
    if (root == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }
    else if (strcmp(root->name, "DRIVER_MODULE_STMTS") == 0)
    {
        FUNCTION_TABLE_VALUE val = function_table_get(function_table, "driver", strlen("driver"));
        if (val != NULL)
        {
            current_symbol_table_wrapper_pass_2 = val->symbol_table_wrapper;
        }
    }

    else if (strcmp(root->name, "Module1") == 0)
    {
        // printf("REACHED Module1 NODE\n");
        FUNCTION_TABLE_VALUE val = function_table_get(function_table, root->child->lexeme, strlen(root->child->lexeme));
        if (val != NULL)
        {
            current_symbol_table_wrapper_pass_2 = val->symbol_table_wrapper;
        }
    }

    else if (strcmp(root->name, "ITERATIVESTMT_WHILE") == 0)
    {
        // printf("REACHED ITERATIVESTMT_WHILE NODE\n");
        int line_number = root->line_number;

        current_symbol_table_wrapper_pass_2 = search_below_by_line_number(line_number);
    }
    else if (strcmp(root->name, "ITERATIVESTMT_FOR") == 0)
    {
        // printf("REACHED ITERATIVESTMT_FOR NODE\n");
        int line_number = root->line_number;

        current_symbol_table_wrapper_pass_2 = search_below_by_line_number(line_number);
    }
    else if (strcmp(root->name, "STMTS_END") == 0)
    {
        // printf("REACHED STMTS_END NODE\n");
        if (current_symbol_table_wrapper_pass_2->parent != NULL)
            current_symbol_table_wrapper_pass_2 = current_symbol_table_wrapper_pass_2->parent;
    }
    else if (strcmp(root->name, "CASE_STMT") == 0)
    {
        // printf("REACHED CASE_STMT NODE\n");
        int line_number = root->line_number;

        current_symbol_table_wrapper_pass_2 = search_below_by_line_number(line_number);
    }

    else if (strcmp(root->name, "MODULE_REUSE_STMT") == 0)
    {
        // printf("REACHED MODULE_REUSE_STMT NODE\n");
        TREENODE module_id_node;
        FUNCTION_TABLE_VALUE value;
        TREENODE optional = NULL;
        if (strcmp(root->child->name, "id") == 0)
        {
            module_id_node = root->child;
            value = function_table_get(function_table, root->child->lexeme, strlen(root->child->lexeme));
        }
        else
        {
            optional = root->child;
            module_id_node = root->child->next;
            value = function_table_get(function_table, module_id_node->lexeme, strlen(module_id_node->lexeme));
        }
        if (value != NULL)
        {
            if (value->input_list != NULL)
            {
                TREENODE input_plist_iterator = value->input_list->child;
                TREENODE apl_iter = module_id_node->next->child;
                while (input_plist_iterator != NULL && apl_iter != NULL)
                {
                    // printf("value->input_list:   %s\n", input_plist_iterator->lexeme);

                    // printf("type of input list parameter is %s\n", input_plist_iterator->next->name);

                    TREENODE apl_id_node;
                    if (strcmp(apl_iter->name, "PLUS") == 0 || strcmp(apl_iter->name, "MINUS") == 0)
                    {
                        apl_id_node = apl_iter->next;
                    }
                    else
                        apl_id_node = apl_iter;
                    // printf("APL ids: %s\n",apl_id_node->lexeme);
                    if (strcmp(apl_id_node->name, "num") == 0)
                    {

                        if (strcmp(input_plist_iterator->next->name, "integer") != 0)
                        {
                            printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                        }
                    }
                    else if (strcmp(apl_id_node->name, "rnum") == 0)
                    {
                        if (strcmp(input_plist_iterator->next->name, "real") != 0)
                        {
                            printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                        }
                    }
                    else
                    {

                        SYMBOL_TABLE_VALUE sym_val = get_symbol_table_value_in_above_table(current_symbol_table_wrapper_pass_2, apl_id_node->lexeme);
                        if (sym_val != NULL)
                        {

                            if (sym_val->isarray == false)
                            {
                                if (strcmp(input_plist_iterator->next->name, "RANGE2") == 0)
                                {
                                    printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s should be an array.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                }
                                else if (sym_val->symbol_table_value_union.not_array.type == integer)
                                {
                                    if (strcmp(input_plist_iterator->next->name, "integer") != 0)
                                    {
                                        printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                    }
                                }
                                else if (sym_val->symbol_table_value_union.not_array.type == real)
                                {
                                    if (strcmp(input_plist_iterator->next->name, "real") != 0)
                                    {
                                        printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                    }
                                }
                                else
                                {
                                    if (strcmp(input_plist_iterator->next->name, "boolean") != 0)
                                    {
                                        printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                    }
                                }
                            }
                            else
                            {
                                if (strcmp(input_plist_iterator->next->name, "RANGE2") != 0)
                                {
                                    printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s should not be an array.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                }
                                else
                                {

                                    if (sym_val->symbol_table_value_union.array.element_type == integer)
                                    {

                                        // printf("HERE is %s\n",input_plist_iterator->next->child->next->next->name);
                                        if (strcmp(input_plist_iterator->next->child->next->next->name, "integer") != 0)
                                        {

                                            printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of uenxpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                        }
                                    }
                                    else if (sym_val->symbol_table_value_union.array.element_type == real)
                                    {

                                        // printf("HERE is %s\n",input_plist_iterator->next->child->next->next->name);
                                        if (strcmp(input_plist_iterator->next->child->next->next->name, "real") != 0)
                                        {
                                            printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                        }
                                    }
                                    else if (sym_val->symbol_table_value_union.array.element_type == boolean)
                                    {

                                        // printf("HERE is %s\n",input_plist_iterator->next->child->next->next->name);
                                        if (strcmp(input_plist_iterator->next->child->next->next->name, "boolean") != 0)
                                        {
                                            printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s is of unexpected type.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                        }
                                    }
                                    // printf("%d here",sym_val->symbol_table_value_union.array.bottom_range.bottom);
                                    if (sym_val->symbol_table_value_union.array.is_bottom_dynamic == false && sym_val->symbol_table_value_union.array.is_top_dynamic == false)
                                    {
                                        int lower_bound_apl = sym_val->symbol_table_value_union.array.bottom_range.bottom;
                                        if (sym_val->symbol_table_value_union.array.is_bottom_sign_plus == false)
                                            lower_bound_apl *= -1;

                                        int upper_bound_apl = sym_val->symbol_table_value_union.array.top_range.top;
                                        if (sym_val->symbol_table_value_union.array.is_top_sign_plus == false)
                                            upper_bound_apl *= -1;

                                        int lower_bound_ipl;
                                        int upper_bound_ipl;
                                        TREENODE lower_bound_ipl_node = input_plist_iterator->next->child;
                                        TREENODE upper_bound_ipl_node = input_plist_iterator->next->child->next;

                                        // bottom range
                                        if (strcmp(lower_bound_ipl_node->name, "PLUS") == 0)
                                        {
                                            lower_bound_ipl_node = lower_bound_ipl_node->child;
                                            lower_bound_ipl = 1;
                                        }
                                        else if (strcmp(lower_bound_ipl_node->name, "MINUS") == 0)
                                        {
                                            lower_bound_ipl = -1;
                                            lower_bound_ipl_node = lower_bound_ipl_node->child;
                                        }
                                        else
                                        {
                                            lower_bound_ipl = 1;
                                        }
                                        lower_bound_ipl *= (atoi(lower_bound_ipl_node->lexeme));

                                        // top range
                                        if (strcmp(upper_bound_ipl_node->name, "PLUS") == 0)
                                        {
                                            upper_bound_ipl_node = upper_bound_ipl_node->child;
                                            upper_bound_ipl = 1;
                                        }
                                        else if (strcmp(upper_bound_ipl_node->name, "MINUS") == 0)
                                        {
                                            upper_bound_ipl = -1;
                                            upper_bound_ipl_node = upper_bound_ipl_node->child;
                                        }
                                        else
                                        {
                                            upper_bound_ipl = 1;
                                        }
                                        upper_bound_ipl *= (atoi(upper_bound_ipl_node->lexeme));

                                        // int upper_bound_apl=sym_val->symbol_table_value_union.array.top_range.top;
                                        // if(strcmp(input_plist_iterator->next->child->name,"PLUS")==0)
                                        // printf("lower bound %d upper bound %d of apl \n",lower_bound_apl,upper_bound_apl);
                                        // printf("lower bound %d upper bound %d of ipl \n",lower_bound_ipl,upper_bound_ipl);
                                        int size_of_array_apl = abs(upper_bound_apl - lower_bound_apl);
                                        int size_of_array_ipl = abs(upper_bound_ipl - lower_bound_ipl);
                                        if (size_of_array_apl != size_of_array_ipl)
                                        {
                                            printf("\033[31m\nLine %d ERROR : Input Parameter Type Mismatch %s array size does not match with input parameter array size.\n\033[0m", apl_id_node->line_number, apl_id_node->lexeme);
                                        }
                                    }
                                }
                            }
                            // if(strcmp(input_plist_iterator->next->name,"integer")==0){

                            //  }
                        }
                    }

                    input_plist_iterator = input_plist_iterator->child;
                    apl_iter = apl_iter->child;
                }

                if (input_plist_iterator == NULL && apl_iter != NULL)
                {
                    printf("\033[31m\nLine %d ERROR : Too many arguments in Input Parameter List while calling module: %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
                }
                if (input_plist_iterator != NULL && apl_iter == NULL)
                {
                    printf("\033[31m\nLine %d ERROR : Too few arguments in Input Parameter List while calling module: %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
                }
            }
            else
            {
                printf("\033[31m\nLine %d ERROR : Module declared but not defined.\n\033[0m", module_id_node->line_number);
                ast_pass2(root->child);
                ast_pass2(root->next);
                return;
            }
            // printf("value->input_list:   %s\n", value->input_list->child->next->name);
            //  SYMBOL_TABLE_VALUE sym_val=symbol_table_get(value->symbol_table_wrapper->symbol_table,value->input_list->child->lexeme,strlen(value->input_list->child->lexeme));
            //  printf("Module Name of input list parameter : %s\n", sym_val->symbol_table_value_union.not_array.type);
            if (optional == NULL && value->output_list != NULL)
            {
                printf("\033[31m\nLine %d ERROR : Expected return parameters while calling module : %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
            }
            if (optional != NULL && value->output_list == NULL)
            {
                printf("\033[31m\nLine %d ERROR : No return parameter expected while calling module: %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
            }
            else if (optional != NULL && value->output_list != NULL && value->output_list->child != NULL)
            {
                TREENODE optional_itr = optional->child;
                TREENODE output_itr = value->output_list->child;
                while (optional_itr != NULL && output_itr != NULL)
                {

                    SYMBOL_TABLE_VALUE sym_val = get_symbol_table_value_in_above_table(current_symbol_table_wrapper_pass_2, optional_itr->lexeme);
                    if (sym_val != NULL)
                    {
                        if (sym_val->isarray == true)
                        {
                            printf("\033[31m\nLine %d ERROR : Array not allowed in output parameter while calling module %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
                        }
                        else
                        {
                            if (sym_val->symbol_table_value_union.not_array.type == integer)
                            {
                                if (strcmp(output_itr->next->name, "integer") != 0)
                                {
                                    printf("\033[31m\nLine %d ERROR : Output Parameter Type Mismatch %s is of unexpected type.\n\033[0m", optional_itr->line_number, optional_itr->lexeme);
                                }
                            }
                            else if (sym_val->symbol_table_value_union.not_array.type == real)
                            {
                                if (strcmp(output_itr->next->name, "real") != 0)
                                {
                                    printf("\033[31m\nLine %d ERROR : Output Parameter Type Mismatch %s is of unexpected type.\n\033[0m", optional_itr->line_number, optional_itr->lexeme);
                                }
                            }
                            else if (sym_val->symbol_table_value_union.not_array.type == boolean)
                            {
                                if (strcmp(output_itr->next->name, "boolean") != 0)
                                {
                                    printf("\033[31m\nLine %d ERROR : Output Parameter Type Mismatch %s is of unexpected type.\n\033[0m", optional_itr->line_number, optional_itr->lexeme);
                                }
                            }
                        }
                    }

                    optional_itr = optional_itr->child;
                    output_itr = output_itr->child;
                }
                if (optional_itr == NULL && output_itr != NULL)
                {
                    printf("\033[31m\nLine %d ERROR : Too many output parameters are returned while calling module: %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
                }
                if (optional_itr != NULL && output_itr == NULL)
                {
                    printf("\033[31m\nLine %d ERROR : Too few output parameters are returned while calling module: %s.\n\033[0m", module_id_node->line_number, module_id_node->lexeme);
                }
            }

            // printf("value->output_list:   %s\n", value->output_list->lexeme);
            //  printf("%dasdasd", get_type_of_variable(root->child->next->child->name));
        }
    }

    ast_pass2(root->child);
    ast_pass2(root->next);
}
void populate_function_and_symbol_tables(TREENODE root)
{
    if (root == NULL)
    {
        // printf("Currently at null");
        return;
    }
    else
    {
        // printf("arrived in %s\n",root->name);

        if (strcmp(root->name, "Module1") == 0)
        {
            // printf("REACHED MODULE1 NODE\n");
            // checking for redeclarations
            bool redeclared = check_if_function_declared(root->child->lexeme);
            FUNCTION_TABLE_VALUE value;
            if (redeclared)
            {
                
                //  printf("value->input_list:   %s", value->input_list);
                value = function_table_get(function_table, root->child->lexeme, strlen(root->child->lexeme));
                if (value->input_list != NULL)
                {
                    printf("\033[31m\nLine %d ERROR : Module %s redeclared.\n\033[0m", root->child->line_number, root->child->lexeme);
                    SYMBOL_TABLE_WRAPPER wraped = create_symbol_table_wrapper();
                    wraped->starting_line_number = root->line_number;
                    wraped->name = root->child->lexeme;
                    current_module_name = root->child->lexeme;
                    wraped->parent = NULL;
                    wraped->child = NULL;
                    wraped->next = NULL;
                    current_symbol_table_wrapper = wraped;
                }
                else
                {
                    value->input_list = root->child->next;
                    if (strcmp(root->child->next->next->name, "OutputPlistHead") == 0)
                        value->output_list = root->child->next->next;
                    else
                        value->output_list = NULL;
                    value->symbol_table_wrapper = create_symbol_table_wrapper();
                    value->symbol_table_wrapper->starting_line_number = root->line_number;
                    value->symbol_table_wrapper->name = root->child->lexeme;
                    current_module_name = root->child->lexeme;
                    value->symbol_table_wrapper->parent = NULL;
                    value->symbol_table_wrapper->child = NULL;
                    value->symbol_table_wrapper->next = NULL;
                    // function_table_insert(function_table, root->child->lexeme, value);
                    current_symbol_table_wrapper = value->symbol_table_wrapper;
                }
            }
            else
            {
                value = create_function_value();
                value->isDeclared = false;
                value->needsChecking = true;
                value->input_list = root->child->next;
                if (strcmp(root->child->next->next->name, "OutputPlistHead") == 0)
                    value->output_list = root->child->next->next;
                else
                    value->output_list = NULL;
                value->symbol_table_wrapper = create_symbol_table_wrapper();
                value->symbol_table_wrapper->starting_line_number = root->line_number;
                value->symbol_table_wrapper->name = root->child->lexeme;
                current_module_name = root->child->lexeme;
                value->symbol_table_wrapper->parent = NULL;
                value->symbol_table_wrapper->child = NULL;
                value->symbol_table_wrapper->next = NULL;
                function_table_insert(function_table, root->child->lexeme, value);
                current_symbol_table_wrapper = value->symbol_table_wrapper;
            }
        }
        // checking for redeclaration of function
        else if (strcmp(root->name, "MDSHead") == 0)
        {
            TREENODE temp = root->child;
            while (temp)
            {
                // printf("%s\n",temp->lexeme);
                bool redeclared = check_if_function_declared(temp->lexeme);
                // printf("xdfsdfs %s\n", root->child->lexeme);
                if (redeclared)
                {
                    // printf("ERROR: Function %s redeclared\n", temp->lexeme);
                    printf("\033[31m\nLine %d ERROR : Module %s redeclared.\n\033[0m", temp->line_number, temp->lexeme);
                }
                else
                {
                    FUNCTION_TABLE_VALUE value = create_function_value();
                    value->isDeclared = true;
                    value->needsChecking = true;
                    value->input_list = NULL;
                    value->output_list = NULL;
                    value->symbol_table_wrapper = create_symbol_table_wrapper();
                    value->symbol_table_wrapper->starting_line_number = temp->line_number;
                    value->symbol_table_wrapper->name = temp->name;
                    // strcat(value->symbol_table_wrapper->name, "_symbol_table");
                    value->symbol_table_wrapper->parent = NULL;
                    value->symbol_table_wrapper->child = NULL;
                    value->symbol_table_wrapper->next = NULL;
                    function_table_insert(function_table, temp->lexeme, value);
                    current_symbol_table_wrapper = value->symbol_table_wrapper;
                }
                temp = temp->child;
            }
        }
        else if (strcmp(root->name, "InputPlistHead") == 0)
        {

            addListtoSymbolTable(root, 0, true, false, false);
        }
        else if (strcmp(root->name, "OutputPlistHead") == 0)
        {

            addListtoSymbolTable(root, 0, false, true, true);
        }
        else if (strcmp(root->name, "ASSIGNMENTSTMT") == 0)
        {

            TREENODE lhs = root->child;
            TREENODE rhs = lhs->next;
            SYMBOL_TABLE_VALUE l_type = get_type_of_expression(lhs);
            SYMBOL_TABLE_VALUE r_type = get_type_of_expression(rhs);
            // printf("l ARRAY: %d\n", l_type->isarray);
            // printf("r ARRAY: %d\n", r_type->isarray);
            // print all values of types for each case of l_type->isarray and r_type->isarray
            if (l_type->isarray && r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.array.element_type, r_type->symbol_table_value_union.array.element_type);
            }
            else if (l_type->isarray && !r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.array.element_type, r_type->symbol_table_value_union.not_array.type);
            }
            else if (!l_type->isarray && r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.not_array.type, r_type->symbol_table_value_union.array.element_type);
            }
            else if (!l_type->isarray && !r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.not_array.type, r_type->symbol_table_value_union.not_array.type);
            }
            bool lhs_exists = check_if_declared_before(lhs->lexeme);
            // printf("Kys hus");
            if (!lhs_exists)
            {
                printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", lhs->line_number, lhs->lexeme);
            }
            else
            {

                // checking if lhs is for loop variable
                SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, lhs->lexeme);
                // printf("Ferefefsdf %s\n", value->module_name);
                if (value != NULL && value->isLoopVariable)
                {
                    printf("\033[31m\nLine %d ERROR : %s cannot be assigned as it is a loop variable.\n\033[0m", lhs->line_number, lhs->lexeme);
                }

              

                //  }
                // printf("r_type->symbol_table_value_union.not_array.type %d", r_type->symbol_table_value_union.not_array.type);
                if (r_type->symbol_table_value_union.not_array.type == -2)
                {
                    // printf("SDSAS");
                }
                else if (!l_type->isarray && !r_type->isarray)
                {

                    if (l_type->symbol_table_value_union.not_array.type != r_type->symbol_table_value_union.not_array.type)
                    { // type checking
                        printf("\033[31m\nLine %d ERROR : Type Mismatch\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                }

                else if (l_type->isarray && r_type->isarray)
                {
                    if ((lhs->child == NULL && rhs->child != NULL) || (lhs->child != NULL && rhs->child == NULL))
                    {
                        printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                    else if (l_type->symbol_table_value_union.array.element_type == r_type->symbol_table_value_union.array.element_type)
                    { // type checking
                        // printf("HELLOE");
                        if ((l_type->symbol_table_value_union.array.top_range.top - l_type->symbol_table_value_union.array.bottom_range.bottom) != (r_type->symbol_table_value_union.array.top_range.top - r_type->symbol_table_value_union.array.bottom_range.bottom))
                        {
                            printf("\033[31m\nLine %d ERROR : Type Mismatch: Array sizes different.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                        }
                        printf("%d\n", l_type->symbol_table_value_union.array.element_type);
                    }
                    else
                    {
                        // int x = 102;
                        //  printf("%d", x);
                        printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number);
                    }
                }
                else if (l_type->isarray && !r_type->isarray)
                {
                    // printf("lhs->next %s\n", lhs->next->name);
                    if (!(strcmp(lhs->next->name, "LVALUEARRSTMT") == 0)) // if lhs is of type A = not array
                    {
                        printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                    else if (r_type->symbol_table_value_union.not_array.type != l_type->symbol_table_value_union.array.element_type)
                        printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                }
                else if (!l_type->isarray && r_type->isarray)
                {
                    if (rhs->child == NULL)
                    {
                        printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                    else if (l_type->symbol_table_value_union.not_array.type != r_type->symbol_table_value_union.array.element_type)
                        printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                }

                // checking if lhs is while loop variable
                SYMBOL_TABLE_WRAPPER wrapper = get_while_symbol_table_having_declaration_of(lhs->lexeme);
                if (wrapper != NULL && wrapper->while_variables != NULL && !wrapper->while_condition_fulfilled)
                {
                    if (data_exists(lhs->lexeme, wrapper->while_variables))
                    {
                        wrapper->while_condition_fulfilled = true;
                    }
                }

                // checking if it is output param
                SYMBOL_TABLE_VALUE value2 = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, lhs->lexeme);
                if (value2 != NULL && value2->isOutputParameter && value2->outputParameterNeedsChecking)
                {
                    value2->outputParameterNeedsChecking = false;
                }
            }
            if (strcmp(rhs->name, "LVALUEARRSTMT") == 0)
            {

                check_expression_if_declared_before(rhs->child->child);
                // checking if this index is a single number and if yes, then checking if it is within bounds
                check_array_index_bounds(rhs->child->child, lhs->lexeme, lhs->line_number);
                check_expression_if_declared_before(rhs->child->next->child);
            }
            else
            {
                check_expression_if_declared_before(rhs);
            }
            
        }
        else if (strcmp(root->name, "DRIVER_MODULE_STMTS") == 0)
        {
            FUNCTION_TABLE_VALUE value = create_function_value();
            value->isDeclared = FALSE;
            value->needsChecking = false;
            value->input_list = NULL;
            value->output_list = NULL;
            value->symbol_table_wrapper = create_symbol_table_wrapper();
            value->symbol_table_wrapper->starting_line_number = root->line_number;
            value->symbol_table_wrapper->name = "driver";
            value->symbol_table_wrapper->parent = NULL;
            value->symbol_table_wrapper->child = NULL;
            value->symbol_table_wrapper->next = NULL;
            function_table_insert(function_table, "driver", value);
            current_module_name = "driver";
            current_symbol_table_wrapper = value->symbol_table_wrapper;
        }
        else if (strcmp(root->name, "STMTS_END") == 0)
        {
            if (current_symbol_table_wrapper->while_variables != NULL && !current_symbol_table_wrapper->while_condition_fulfilled)
            {
                printf("\033[31m\nLine %d ERROR : None of the variables in the while condition have been assigned in the while statements.\n\033[0m", current_symbol_table_wrapper->starting_line_number);
            }
            else if (current_symbol_table_wrapper->parent == NULL)
            {
                FUNCTION_TABLE_VALUE ftv = function_table_get(function_table, current_module_name, strlen(current_module_name));
                TREENODE opl = NULL;
                if(ftv!=NULL) opl = ftv->output_list;
                
                if (opl != NULL)
                {
                    TREENODE temp = opl->child;
                    while (temp != NULL)
                    {
                        char *id = temp->lexeme;
                        SYMBOL_TABLE_VALUE stv = symbol_table_get(current_symbol_table_wrapper->symbol_table, id, strlen(id));
                        if (stv!=NULL && stv->isOutputParameter && stv->outputParameterNeedsChecking)
                        {
                            printf("\033[31m\nLine %d ERROR : Output parameter %s has not been changed in the module.\n\033[0m", current_symbol_table_wrapper->starting_line_number, id);
                        }
                        temp = temp->child;
                    }
                }
            }

            go_back_to_parent_symbol_table();
        }
        else if (strcmp(root->name, "DECLARESTMT") == 0)
        {
            TREENODE datatype = root->child->next;
            TREENODE idListHead = root->child;
            TREENODE temp = idListHead->child; // points to first child in idList
            // GOING TO STMTS_END
            TREENODE stmts_end_node = root;
            while (stmts_end_node->next != NULL)
                stmts_end_node = stmts_end_node->next;
            int end_line_number = stmts_end_node->line_number;
            while (temp != NULL)
            {
                bool id_exists = check_if_redeclared(temp->lexeme);
                if (id_exists)
                {
                    SYMBOL_TABLE_VALUE stv = symbol_table_get(current_symbol_table_wrapper->symbol_table, temp->lexeme, strlen(temp->lexeme));
                    if (stv->isInputParameter)
                    {
                        stv->isInputParameter = false;
                        SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
                        int nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
                        stv->line_number_end = end_line_number;
                        populateSymboltableValue(temp, datatype, stv, current_module_name, nesting_level, current_symbol_table_wrapper->starting_line_number, false, false, false, false);
                        
                        // symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
                    }
                    else
                    {
                        printf("\033[31m\nLine %d ERROR : %s has already been declared before.\n\033[0m", temp->line_number, temp->lexeme);
                    }
                }
                else
                {
                    SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
                    int nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
                    value->line_number_end = end_line_number;
                    populateSymboltableValue(temp, datatype, value, current_module_name, nesting_level, current_symbol_table_wrapper->starting_line_number, false, false, false, false);
                    current_offset_value += value->width;

                    symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
                }
                temp = temp->child;
            }
        }
        else if (strcmp(root->name, "ITERATIVESTMT_WHILE") == 0)
        {
            // checking if condition has expr has been declared before
            check_expression_if_declared_before(root->child);
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            temp->starting_line_number = root->line_number;
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "WHILE_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            LIST while_variables_list = createNewList();

            TREENODE expression = root->child;
            appendWhileVariables(expression, while_variables_list);
            temp->while_variables = while_variables_list;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if (strcmp(root->name, "CONDITIONALSTMT") == 0)
        {
            // checking if condition has expr has been declared before
            bool is_declared = check_if_declared_before(root->child->lexeme);
            if (!is_declared)
            {
                printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", root->child->line_number, root->child->lexeme);
            }
            else
            {
                // printf("Hi");
                if (get_type_of_variable(root->child->lexeme) == 2)
                {
                    if (root->child->next->next != NULL)
                        printf("\033[31m\nLine %d ERROR : Default statement not expected in boolean switch case\n\033[0m", root->child->line_number);
                }
                else if (get_type_of_variable(root->child->lexeme) == 0)
                {

                    if (root->child->next->next == NULL)
                        printf("\033[31m\nLine %d ERROR : Default statement is expected in integer switch case\n\033[0m", root->child->line_number);
                }
                if (get_type_of_variable(root->child->lexeme) == 1)
                {

                    root->child->next = NULL;
                    printf("\033[31m\nLine %d ERROR : %s has type real, expected integer or boolean\n\033[0m", root->child->line_number, root->child->lexeme);
                }
            }
            // check_if_declared_before(root->child->lexeme);
        }
        else if (strcmp(root->name, "CASE_STMT") == 0)
        {
            bool is_declared = check_if_declared_before(root->parent->parent->child->lexeme);
            if (is_declared)
            {
                int type_of_switch_variable = get_type_of_variable(root->parent->parent->child->lexeme);
                if (type_of_switch_variable == 0 && (strcmp(root->child->lexeme, "true") == 0 || strcmp(root->child->lexeme, "false") == 0))
                {
                    printf("\033[31m\nLine %d ERROR : Case value is expected to have type Integer.\n\033[0m", root->line_number);
                }
                if (type_of_switch_variable == 2 && !(strcmp(root->child->lexeme, "true") == 0 || strcmp(root->child->lexeme, "false") == 0))
                {
                    printf("\033[31m\nLine %d ERROR : Case value is expected to have type boolean.\n\033[0m", root->line_number);
                }
            }
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "CASE_STMT_symbol_table";
            temp->starting_line_number = root->line_number;
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if (strcmp(root->name, "DEFAULT") == 0)
        {
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "DEFAULT_symbol_table";
            temp->starting_line_number = root->line_number;
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
            temp->starting_line_number = root->line_number;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
            SYMBOL_TABLE_VALUE value = create_new_symbol_node("integer");
            value->isarray = false;
            value->symbol_table_value_union.not_array.type = integer;
            value->width = 2;
            value->offset = current_offset_value;
            current_offset_value += value->width;
            value->line_number_start = root->child->next->next->line_number;
            // GOING TO STMTS_END
            TREENODE stmts_end_node = root->child;
            while (stmts_end_node->next != NULL)
                stmts_end_node = stmts_end_node->next;

            value->line_number_end = stmts_end_node->line_number;
            value->module_name = current_module_name;
            value->nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
            value->isLoopVariable = true;
            

            symbol_insert(current_symbol_table_wrapper->symbol_table, root->child->lexeme, value);
        }
        else if (strcmp(root->name, "IO_INPUT") == 0)
        {
            TREENODE var = root->child;
            bool var_exists = check_if_declared_before(var->lexeme);
            if (!var_exists)
            {
                printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", var->line_number, var->lexeme);
            }
        }
        else if (strcmp(root->name, "IO_OUTPUT") == 0)
        {
            TREENODE var = root->child;
            bool var_exists = true;
            if (strcmp(var->name, "id") == 0)
                var_exists = check_if_declared_before(var->lexeme);
            if (!var_exists)
            {
                printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", var->line_number, var->lexeme);
            }
            if (var->next != NULL)
            {
                var = var->next;
                if ((strcmp(var->name, "id") == 0) && (!check_if_declared_before(var->lexeme)))
                {
                    printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", var->line_number, var->lexeme);
                }
            }
        }
        else if (strcmp(root->name, "MODULE_REUSE_STMT") == 0)
        {

            TREENODE temp = root->child;
            if (current_module_name != NULL)
            {
                if (strcmp(temp->next->name, "id") != 0)
                {
                    if (strcmp(current_module_name, root->child->lexeme) == 0)
                        printf("\033[31m\nLine %d ERROR : Recursion found in Module %s.\n\033[0m", root->child->line_number, root->child->lexeme);
                }
                else
                {
                    if (strcmp(current_module_name, root->child->next->lexeme) == 0)
                        printf("\033[31m\nLine %d ERROR : Recursion found in Module %s.\n\033[0m", root->child->next->line_number, root->child->next->lexeme);
                }
            }
            if (strcmp(temp->name, "id") != 0)
            {
                TREENODE temp2 = temp->child;
                while (temp2 != NULL)
                {
                    bool dec_before = check_if_declared_before(temp2->lexeme);
                    if (!dec_before)
                    {
                        printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", temp2->line_number, temp2->lexeme);
                    }
                    else
                    {
                        // checking if it is a for loop variable
                        SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, temp2->lexeme);
                        if (value != NULL && value->isLoopVariable)
                        {
                            printf("\033[31m\nLine %d ERROR : %s cannot be assigned as it is a loop variable.\n\033[0m", temp2->line_number, temp2->lexeme);
                        }

                        // checking if lhs is while loop variable
                        if (current_symbol_table_wrapper->while_variables != NULL && !current_symbol_table_wrapper->while_condition_fulfilled)
                        {
                            if (data_exists(temp2->lexeme, current_symbol_table_wrapper->while_variables))
                            {
                                current_symbol_table_wrapper->while_condition_fulfilled = true;
                            }
                        }

                        // checking if it is output param
                        if (value != NULL && value->isOutputParameter && value->outputParameterNeedsChecking)
                        {
                            value->outputParameterNeedsChecking = false;
                        }
                    }
                    temp2 = temp2->child;
                }
                temp = temp->next;
            }
            if ((!check_if_function_declared(temp->lexeme)))
            {
                printf("\033[31m\nLine %d ERROR : Module %s has not been declared before.\n\033[0m", temp->line_number, temp->lexeme);
            }
            else
            {
                FUNCTION_TABLE_VALUE value = function_table_get(function_table, temp->lexeme, strlen(temp->lexeme));
                if (value->needsChecking)
                {
                    value->needsChecking = false;
                    if (value->isDeclared && value->input_list != NULL)
                    {
                        printf("\033[31m\nLine %d ERROR : Module %s has been both declared and defined before the first module reuse statement.\n\033[0m", temp->line_number, temp->lexeme);
                    }
                }
            }
            temp = temp->next;
            TREENODE temp2 = temp->child;
            while (temp2 != NULL)
            {
                if (strcmp(temp2->name, "PLUS") == 0 || strcmp(temp2->name, "MINUS") == 0)
                {
                    TREENODE temp3 = temp2->next;
                    if (strcmp(temp3->name, "id") == 0)
                    {
                        if (!check_if_declared_before(temp3->lexeme))
                        {
                            printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", temp3->line_number, temp3->lexeme);
                        }
                    }
                    if (temp3->next != NULL)
                    {
                        temp3 = temp3->next;
                        check_expression_if_declared_before(temp3);
                    }
                    // check_expression_if_declared_before(temp3);
                    temp2 = temp2->child;
                    continue;
                }
                if (strcmp(temp2->name, "id") == 0)
                {
                    bool dec_before = check_if_declared_before(temp2->lexeme);
                    if (!dec_before)
                    {
                        printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", temp2->line_number, temp2->lexeme);
                    }
                    if (temp2->next != NULL)
                    {
                        check_expression_if_declared_before(temp2->next);
                    }
                    // check_expression_if_declared_before(temp2);
                }
                temp2 = temp2->child;
            }
        }
    }
    populate_function_and_symbol_tables(root->child);
    populate_function_and_symbol_tables(root->next);

}


void populate_function_and_symbol_tables_without_error(TREENODE root)
{
    if (root == NULL)
    {
        // printf("Currently at null");
        return;
    }
    else
    {
        // printf("arrived in %s\n",root->name);

        if (strcmp(root->name, "Module1") == 0)
        {
            // printf("REACHED MODULE1 NODE\n");
            // checking for redeclarations
            bool redeclared = check_if_function_declared(root->child->lexeme);
            FUNCTION_TABLE_VALUE value;
            if (redeclared)
            {
                
                //  printf("value->input_list:   %s", value->input_list);
                value = function_table_get(function_table, root->child->lexeme, strlen(root->child->lexeme));
                if (value->input_list != NULL)
                {
                    //printf("\033[31m\nLine %d ERROR : Module %s redeclared.\n\033[0m", root->child->line_number, root->child->lexeme);
                    SYMBOL_TABLE_WRAPPER wraped = create_symbol_table_wrapper();
                    wraped->starting_line_number = root->line_number;
                    wraped->name = root->child->lexeme;
                    current_module_name = root->child->lexeme;
                    wraped->parent = NULL;
                    wraped->child = NULL;
                    wraped->next = NULL;
                    current_symbol_table_wrapper = wraped;
                }
                else
                {
                    value->input_list = root->child->next;
                    if (strcmp(root->child->next->next->name, "OutputPlistHead") == 0)
                        value->output_list = root->child->next->next;
                    else
                        value->output_list = NULL;
                    value->symbol_table_wrapper = create_symbol_table_wrapper();
                    value->symbol_table_wrapper->starting_line_number = root->line_number;
                    value->symbol_table_wrapper->name = root->child->lexeme;
                    current_module_name = root->child->lexeme;
                    value->symbol_table_wrapper->parent = NULL;
                    value->symbol_table_wrapper->child = NULL;
                    value->symbol_table_wrapper->next = NULL;
                    // function_table_insert(function_table, root->child->lexeme, value);
                    current_symbol_table_wrapper = value->symbol_table_wrapper;
                }
            }
            else
            {
                value = create_function_value();
                value->isDeclared = false;
                value->needsChecking = true;
                value->input_list = root->child->next;
                if (strcmp(root->child->next->next->name, "OutputPlistHead") == 0)
                    value->output_list = root->child->next->next;
                else
                    value->output_list = NULL;
                value->symbol_table_wrapper = create_symbol_table_wrapper();
                value->symbol_table_wrapper->starting_line_number = root->line_number;
                value->symbol_table_wrapper->name = root->child->lexeme;
                current_module_name = root->child->lexeme;
                value->symbol_table_wrapper->parent = NULL;
                value->symbol_table_wrapper->child = NULL;
                value->symbol_table_wrapper->next = NULL;
                function_table_insert(function_table, root->child->lexeme, value);
                current_symbol_table_wrapper = value->symbol_table_wrapper;
            }
        }
        // checking for redeclaration of function
        else if (strcmp(root->name, "MDSHead") == 0)
        {
            TREENODE temp = root->child;
            while (temp)
            {
                // printf("%s\n",temp->lexeme);
                bool redeclared = check_if_function_declared(temp->lexeme);
                // printf("xdfsdfs %s\n", root->child->lexeme);
                if (redeclared)
                {
                    // printf("ERROR: Function %s redeclared\n", temp->lexeme);
                    //printf("\033[31m\nLine %d ERROR : Module %s redeclared.\n\033[0m", temp->line_number, temp->lexeme);
                }
                else
                {
                    FUNCTION_TABLE_VALUE value = create_function_value();
                    value->isDeclared = true;
                    value->needsChecking = true;
                    value->input_list = NULL;
                    value->output_list = NULL;
                    value->symbol_table_wrapper = create_symbol_table_wrapper();
                    value->symbol_table_wrapper->starting_line_number = temp->line_number;
                    value->symbol_table_wrapper->name = temp->name;
                    // strcat(value->symbol_table_wrapper->name, "_symbol_table");
                    value->symbol_table_wrapper->parent = NULL;
                    value->symbol_table_wrapper->child = NULL;
                    value->symbol_table_wrapper->next = NULL;
                    function_table_insert(function_table, temp->lexeme, value);
                    current_symbol_table_wrapper = value->symbol_table_wrapper;
                }
                temp = temp->child;
            }
        }
        else if (strcmp(root->name, "InputPlistHead") == 0)
        {

            addListtoSymbolTable(root, 0, true, false, false);
        }
        else if (strcmp(root->name, "OutputPlistHead") == 0)
        {

            addListtoSymbolTable(root, 0, false, true, true);
        }
        else if (strcmp(root->name, "ASSIGNMENTSTMT") == 0)
        {

            TREENODE lhs = root->child;
            TREENODE rhs = lhs->next;
            SYMBOL_TABLE_VALUE l_type = get_type_of_expression(lhs);
            SYMBOL_TABLE_VALUE r_type = get_type_of_expression(rhs);
            // printf("l ARRAY: %d\n", l_type->isarray);
            // printf("r ARRAY: %d\n", r_type->isarray);
            // print all values of types for each case of l_type->isarray and r_type->isarray
            if (l_type->isarray && r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.array.element_type, r_type->symbol_table_value_union.array.element_type);
            }
            else if (l_type->isarray && !r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.array.element_type, r_type->symbol_table_value_union.not_array.type);
            }
            else if (!l_type->isarray && r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.not_array.type, r_type->symbol_table_value_union.array.element_type);
            }
            else if (!l_type->isarray && !r_type->isarray)
            {
                // printf("lt: %d, rt: %d\n", l_type->symbol_table_value_union.not_array.type, r_type->symbol_table_value_union.not_array.type);
            }
            bool lhs_exists = check_if_declared_before(lhs->lexeme);
            // printf("Kys hus");
            if (!lhs_exists)
            {
                //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", lhs->line_number, lhs->lexeme);
            }
            else
            {

                // checking if lhs is for loop variable
                SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, lhs->lexeme);
                // printf("Ferefefsdf %s\n", value->module_name);
                if (value != NULL && value->isLoopVariable)
                {
                    //printf("\033[31m\nLine %d ERROR : %s cannot be assigned as it is a loop variable.\n\033[0m", lhs->line_number, lhs->lexeme);
                }

              

                //  }
                // printf("r_type->symbol_table_value_union.not_array.type %d", r_type->symbol_table_value_union.not_array.type);
                if (r_type->symbol_table_value_union.not_array.type == -2)
                {
                    // printf("SDSAS");
                }
                else if (!l_type->isarray && !r_type->isarray)
                {

                    if (l_type->symbol_table_value_union.not_array.type != r_type->symbol_table_value_union.not_array.type)
                    { // type checking
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                }

                else if (l_type->isarray && r_type->isarray)
                {
                    if ((lhs->child == NULL && rhs->child != NULL) || (lhs->child != NULL && rhs->child == NULL))
                    {
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                    else if (l_type->symbol_table_value_union.array.element_type == r_type->symbol_table_value_union.array.element_type)
                    { // type checking
                        // printf("HELLOE");
                        if ((l_type->symbol_table_value_union.array.top_range.top - l_type->symbol_table_value_union.array.bottom_range.bottom) != (r_type->symbol_table_value_union.array.top_range.top - r_type->symbol_table_value_union.array.bottom_range.bottom))
                        {
                            //printf("\033[31m\nLine %d ERROR : Type Mismatch: Array sizes different.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                        }
                        printf("%d\n", l_type->symbol_table_value_union.array.element_type);
                    }
                    else
                    {
                        // int x = 102;
                        //  printf("%d", x);
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number);
                    }
                }
                else if (l_type->isarray && !r_type->isarray)
                {
                    // printf("lhs->next %s\n", lhs->next->name);
                    if (!(strcmp(lhs->next->name, "LVALUEARRSTMT") == 0)) // if lhs is of type A = not array
                    {
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                    else if (r_type->symbol_table_value_union.not_array.type != l_type->symbol_table_value_union.array.element_type){}
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                }
                else if (!l_type->isarray && r_type->isarray)
                {
                    if (rhs->child == NULL)
                    {
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                    }
                    else if (l_type->symbol_table_value_union.not_array.type != r_type->symbol_table_value_union.array.element_type){}
                        //printf("\033[31m\nLine %d ERROR : Type Mismatch.\n\033[0m", lhs->line_number, lhs->lexeme, rhs->lexeme);
                }

                // checking if lhs is while loop variable
                SYMBOL_TABLE_WRAPPER wrapper = get_while_symbol_table_having_declaration_of(lhs->lexeme);
                if (wrapper != NULL && wrapper->while_variables != NULL && !wrapper->while_condition_fulfilled)
                {
                    if (data_exists(lhs->lexeme, wrapper->while_variables))
                    {
                        wrapper->while_condition_fulfilled = true;
                    }
                }

                // checking if it is output param
                SYMBOL_TABLE_VALUE value2 = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, lhs->lexeme);
                if (value2 != NULL && value2->isOutputParameter && value2->outputParameterNeedsChecking)
                {
                    value2->outputParameterNeedsChecking = false;
                }
            }
            if (strcmp(rhs->name, "LVALUEARRSTMT") == 0)
            {

                check_expression_if_declared_before(rhs->child->child);
                // checking if this index is a single number and if yes, then checking if it is within bounds
                check_array_index_bounds(rhs->child->child, lhs->lexeme, lhs->line_number);
                check_expression_if_declared_before(rhs->child->next->child);
            }
            else
            {
                check_expression_if_declared_before(rhs);
            }
            
        }
        else if (strcmp(root->name, "DRIVER_MODULE_STMTS") == 0)
        {
            FUNCTION_TABLE_VALUE value = create_function_value();
            value->isDeclared = FALSE;
            value->needsChecking = false;
            value->input_list = NULL;
            value->output_list = NULL;
            value->symbol_table_wrapper = create_symbol_table_wrapper();
            value->symbol_table_wrapper->starting_line_number = root->line_number;
            value->symbol_table_wrapper->name = "driver";
            value->symbol_table_wrapper->parent = NULL;
            value->symbol_table_wrapper->child = NULL;
            value->symbol_table_wrapper->next = NULL;
            function_table_insert(function_table, "driver", value);
            current_module_name = "driver";
            current_symbol_table_wrapper = value->symbol_table_wrapper;
        }
        else if (strcmp(root->name, "STMTS_END") == 0)
        {
            if (current_symbol_table_wrapper->while_variables != NULL && !current_symbol_table_wrapper->while_condition_fulfilled)
            {
                //printf("\033[31m\nLine %d ERROR : None of the variables in the while condition have been assigned in the while statements.\n\033[0m", current_symbol_table_wrapper->starting_line_number);
            }
            else if (current_symbol_table_wrapper->parent == NULL)
            {
                FUNCTION_TABLE_VALUE ftv = function_table_get(function_table, current_module_name, strlen(current_module_name));
                TREENODE opl = NULL;
                if(ftv!=NULL) opl = ftv->output_list;
                
                if (opl != NULL)
                {
                    TREENODE temp = opl->child;
                    while (temp != NULL)
                    {
                        char *id = temp->lexeme;
                        SYMBOL_TABLE_VALUE stv = symbol_table_get(current_symbol_table_wrapper->symbol_table, id, strlen(id));
                        if (stv!=NULL && stv->isOutputParameter && stv->outputParameterNeedsChecking)
                        {
                            //printf("\033[31m\nLine %d ERROR : Output parameter %s has not been changed in the module.\n\033[0m", current_symbol_table_wrapper->starting_line_number, id);
                        }
                        temp = temp->child;
                    }
                }
            }

            go_back_to_parent_symbol_table();
        }
        else if (strcmp(root->name, "DECLARESTMT") == 0)
        {
            TREENODE datatype = root->child->next;
            TREENODE idListHead = root->child;
            TREENODE temp = idListHead->child; // points to first child in idList
            // GOING TO STMTS_END
            TREENODE stmts_end_node = root;
            while (stmts_end_node->next != NULL)
                stmts_end_node = stmts_end_node->next;
            int end_line_number = stmts_end_node->line_number;
            while (temp != NULL)
            {
                bool id_exists = check_if_redeclared(temp->lexeme);
                if (id_exists)
                {
                    SYMBOL_TABLE_VALUE stv = symbol_table_get(current_symbol_table_wrapper->symbol_table, temp->lexeme, strlen(temp->lexeme));
                    if (stv->isInputParameter)
                    {
                        SYMBOL_TABLE_VALUE original = create_new_symbol_node("array");
                        stv->isInputParameter = false;
                        copy_symbol_table_value(original,stv);

                        if(current_symbol_table_wrapper->shadowed==NULL){
                            current_symbol_table_wrapper->shadowed = create_symbol_table_wrapper();
                        }
                        symbol_insert(current_symbol_table_wrapper->shadowed->symbol_table, temp->lexeme, original);

                        SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
                        int nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
                        stv->line_number_end = end_line_number;
                        populateSymboltableValue(temp, datatype, stv, current_module_name, nesting_level, current_symbol_table_wrapper->starting_line_number, false, false, false, false);
                        current_offset_value += stv->width;
                        // symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
                    }
                    else
                    {
                        //printf("\033[31m\nLine %d ERROR : %s has already been declared before.\n\033[0m", temp->line_number, temp->lexeme);
                    }
                }
                else
                {
                    SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
                    int nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
                    value->line_number_end = end_line_number;
                    populateSymboltableValue(temp, datatype, value, current_module_name, nesting_level, current_symbol_table_wrapper->starting_line_number, false, false, false, false);
                    current_offset_value += value->width;

                    symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
                }
                temp = temp->child;
            }
        }
        else if (strcmp(root->name, "ITERATIVESTMT_WHILE") == 0)
        {
            // checking if condition has expr has been declared before
            check_expression_if_declared_before(root->child);
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            temp->starting_line_number = root->line_number;
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "WHILE_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            LIST while_variables_list = createNewList();

            TREENODE expression = root->child;
            appendWhileVariables(expression, while_variables_list);
            temp->while_variables = while_variables_list;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if (strcmp(root->name, "CONDITIONALSTMT") == 0)
        {
            // checking if condition has expr has been declared before
            bool is_declared = check_if_declared_before(root->child->lexeme);
            if (!is_declared)
            {
                //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", root->child->line_number, root->child->lexeme);
            }
            else
            {
                // printf("Hi");
                if (get_type_of_variable(root->child->lexeme) == 2)
                {
                    if (root->child->next->next != NULL){}
                        //printf("\033[31m\nLine %d ERROR : Default statement not expected in boolean switch case\n\033[0m", root->child->line_number);
                }
                else if (get_type_of_variable(root->child->lexeme) == 0)
                {

                    if (root->child->next->next == NULL){}
                        //printf("\033[31m\nLine %d ERROR : Default statement is expected in integer switch case\n\033[0m", root->child->line_number);
                }
                if (get_type_of_variable(root->child->lexeme) == 1)
                {

                    root->child->next = NULL;
                    //printf("\033[31m\nLine %d ERROR : %s has type real, expected integer or boolean\n\033[0m", root->child->line_number, root->child->lexeme);
                }
            }
            // check_if_declared_before(root->child->lexeme);
        }
        else if (strcmp(root->name, "CASE_STMT") == 0)
        {
            bool is_declared = check_if_declared_before(root->parent->parent->child->lexeme);
            if (is_declared)
            {
                int type_of_switch_variable = get_type_of_variable(root->parent->parent->child->lexeme);
                if (type_of_switch_variable == 0 && (strcmp(root->child->lexeme, "true") == 0 || strcmp(root->child->lexeme, "false") == 0))
                {
                    //printf("\033[31m\nLine %d ERROR : Case value is expected to have type Integer.\n\033[0m", root->line_number);
                }
                if (type_of_switch_variable == 2 && !(strcmp(root->child->lexeme, "true") == 0 || strcmp(root->child->lexeme, "false") == 0))
                {
                    //printf("\033[31m\nLine %d ERROR : Case value is expected to have type boolean.\n\033[0m", root->line_number);
                }
            }
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "CASE_STMT_symbol_table";
            temp->starting_line_number = root->line_number;
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if (strcmp(root->name, "DEFAULT") == 0)
        {
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "DEFAULT_symbol_table";
            temp->starting_line_number = root->line_number;
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
            temp->starting_line_number = root->line_number;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
            SYMBOL_TABLE_VALUE value = create_new_symbol_node("integer");
            value->isarray = false;
            value->symbol_table_value_union.not_array.type = integer;
            value->width = 2;
            value->offset = current_offset_value;
            current_offset_value += value->width;
            value->line_number_start = root->child->next->next->line_number;
            // GOING TO STMTS_END
            TREENODE stmts_end_node = root->child;
            while (stmts_end_node->next != NULL)
                stmts_end_node = stmts_end_node->next;

            value->line_number_end = stmts_end_node->line_number;
            value->module_name = current_module_name;
            value->nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
            value->isLoopVariable = true;
            

            symbol_insert(current_symbol_table_wrapper->symbol_table, root->child->lexeme, value);
        }
        else if (strcmp(root->name, "IO_INPUT") == 0)
        {
            TREENODE var = root->child;
            bool var_exists = check_if_declared_before(var->lexeme);
            if (!var_exists)
            {
                //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", var->line_number, var->lexeme);
            }
        }
        else if (strcmp(root->name, "IO_OUTPUT") == 0)
        {
            TREENODE var = root->child;
            bool var_exists = true;
            if (strcmp(var->name, "id") == 0)
                var_exists = check_if_declared_before(var->lexeme);
            if (!var_exists)
            {
                //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", var->line_number, var->lexeme);
            }
            if (var->next != NULL)
            {
                var = var->next;
                if ((strcmp(var->name, "id") == 0) && (!check_if_declared_before(var->lexeme)))
                {
                    //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", var->line_number, var->lexeme);
                }
            }
        }
        else if (strcmp(root->name, "MODULE_REUSE_STMT") == 0)
        {

            TREENODE temp = root->child;
            if (current_module_name != NULL)
            {
                if (strcmp(temp->next->name, "id") != 0)
                {
                    if (strcmp(current_module_name, root->child->lexeme) == 0){}
                        //printf("\033[31m\nLine %d ERROR : Recursion found in Module %s.\n\033[0m", root->child->line_number, root->child->lexeme);
                }
                else
                {
                    if (strcmp(current_module_name, root->child->next->lexeme) == 0){}
                        //printf("\033[31m\nLine %d ERROR : Recursion found in Module %s.\n\033[0m", root->child->next->line_number, root->child->next->lexeme);
                }
            }
            if (strcmp(temp->name, "id") != 0)
            {
                TREENODE temp2 = temp->child;
                while (temp2 != NULL)
                {
                    bool dec_before = check_if_declared_before(temp2->lexeme);
                    if (!dec_before)
                    {
                        //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", temp2->line_number, temp2->lexeme);
                    }
                    else
                    {
                        // checking if it is a for loop variable
                        SYMBOL_TABLE_VALUE value = get_symbol_table_value_in_above_table(current_symbol_table_wrapper, temp2->lexeme);
                        if (value != NULL && value->isLoopVariable)
                        {
                            //printf("\033[31m\nLine %d ERROR : %s cannot be assigned as it is a loop variable.\n\033[0m", temp2->line_number, temp2->lexeme);
                        }

                        // checking if lhs is while loop variable
                        if (current_symbol_table_wrapper->while_variables != NULL && !current_symbol_table_wrapper->while_condition_fulfilled)
                        {
                            if (data_exists(temp2->lexeme, current_symbol_table_wrapper->while_variables))
                            {
                                current_symbol_table_wrapper->while_condition_fulfilled = true;
                            }
                        }

                        // checking if it is output param
                        if (value != NULL && value->isOutputParameter && value->outputParameterNeedsChecking)
                        {
                            value->outputParameterNeedsChecking = false;
                        }
                    }
                    temp2 = temp2->child;
                }
                temp = temp->next;
            }
            if ((!check_if_function_declared(temp->lexeme)))
            {
                //printf("\033[31m\nLine %d ERROR : Module %s has not been declared before.\n\033[0m", temp->line_number, temp->lexeme);
            }
            else
            {
                FUNCTION_TABLE_VALUE value = function_table_get(function_table, temp->lexeme, strlen(temp->lexeme));
                if (value->needsChecking)
                {
                    value->needsChecking = false;
                    if (value->isDeclared && value->input_list != NULL)
                    {
                        //printf("\033[31m\nLine %d ERROR : Module %s has been both declared and defined before the first module reuse statement.\n\033[0m", temp->line_number, temp->lexeme);
                    }
                }
            }
            temp = temp->next;
            TREENODE temp2 = temp->child;
            while (temp2 != NULL)
            {
                if (strcmp(temp2->name, "PLUS") == 0 || strcmp(temp2->name, "MINUS") == 0)
                {
                    TREENODE temp3 = temp2->next;
                    if (strcmp(temp3->name, "id") == 0)
                    {
                        if (!check_if_declared_before(temp3->lexeme))
                        {
                            //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", temp3->line_number, temp3->lexeme);
                        }
                    }
                    if (temp3->next != NULL)
                    {
                        temp3 = temp3->next;
                        check_expression_if_declared_before(temp3);
                    }
                    // check_expression_if_declared_before(temp3);
                    temp2 = temp2->child;
                    continue;
                }
                if (strcmp(temp2->name, "id") == 0)
                {
                    bool dec_before = check_if_declared_before(temp2->lexeme);
                    if (!dec_before)
                    {
                        //printf("\033[31m\nLine %d ERROR : %s has not been declared before.\n\033[0m", temp2->line_number, temp2->lexeme);
                    }
                    if (temp2->next != NULL)
                    {
                        check_expression_if_declared_before(temp2->next);
                    }
                    // check_expression_if_declared_before(temp2);
                }
                temp2 = temp2->child;
            }
        }
    }
    populate_function_and_symbol_tables_without_error(root->child);
    populate_function_and_symbol_tables_without_error(root->next);

}