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
int get_type_of_variable(char *lexeme)
{
    SYMBOL_TABLE_VALUE stv = symbol_table_get(current_symbol_table_wrapper->symbol_table, lexeme, strlen(lexeme));
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
            printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", root->lexeme);
        }
        // if (root->next != NULL)
        //     check_expression_if_declared_before(root->next);
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

void populateSymboltableValue(TREENODE datatype, SYMBOL_TABLE_VALUE value, char *module_name, int nesting_level, int start_line_number, bool isInputParameter)
{
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

        // width
        if (!value->symbol_table_value_union.array.is_bottom_dynamic && !value->symbol_table_value_union.array.is_top_dynamic)
        {
            printf("++++++++++++++++++++++++++++++++++\n");
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
    current_offset_value += value->width;
}
void addListtoSymbolTable(TREENODE root, int nesting_level, bool isInputParam)
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
        populateSymboltableValue(datatype, value, current_module_name, nesting_level, temp->line_number, isInputParam);
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
void ast_pass2(TREENODE root)
{
    if (root == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }
    else if (strcmp(root->name, "MODULE_REUSE_STMT") == 0)
    {
        printf("REACHED MODULE_REUSE_STMT NODE\n");
        FUNCTION_TABLE_VALUE value = function_table_get(function_table, root->child->lexeme, strlen(root->child->lexeme));
        if (value == NULL)
        {
            printf("ERROR: Module %s not declared\n", root->child->lexeme);
        }
        printf("value->input_list:   %s\n", value->input_list->child->lexeme);
        printf("value->output_list:   %s\n", value->output_list->lexeme);
        // printf("%dasdasd", get_type_of_variable(root->child->next->child->name));
    }
    ast_pass2(root->child);
    ast_pass2(root->next);
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
            // checking for redeclarations
            bool redeclared = check_if_function_declared(root->child->lexeme);
            FUNCTION_TABLE_VALUE value;
            if (redeclared)
            {
                //  printf("value->input_list:   %s", value->input_list);
                value = function_table_get(function_table, root->child->lexeme, strlen(root->child->lexeme));
                if (value->input_list != NULL)
                    printf("\033[31m\nERROR : Module %s redeclared.\n\033[0m", root->child->lexeme);
            }
            else
            {
                value = create_function_value();
            }
            value->input_list = root->child->next;
            if (strcmp(root->child->next->next->name, "OutputPlistHead") == 0)
                value->output_list = root->child->next->next;
            else
                value->output_list = NULL;
            value->symbol_table_wrapper = create_symbol_table_wrapper();
            value->symbol_table_wrapper->name = root->child->lexeme;
            current_module_name = root->child->lexeme;
            value->symbol_table_wrapper->parent = NULL;
            value->symbol_table_wrapper->child = NULL;
            value->symbol_table_wrapper->next = NULL;
            function_table_insert(function_table, root->child->lexeme, value);
            current_symbol_table_wrapper = value->symbol_table_wrapper;
        }
        // checking for redeclaration of function
        else if (strcmp(root->name, "MDSHead") == 0)
        {
            TREENODE temp = root->child;
            while (temp)
            {
                //printf("%s\n",temp->lexeme);
                bool redeclared = check_if_function_declared(temp->lexeme);
                // printf("xdfsdfs %s\n", root->child->lexeme);
                if (redeclared)
                {
                     //printf("ERROR: Function %s redeclared\n", temp->lexeme);
                    printf("\033[31m\nERROR : Module %s redeclared.\n\033[0m", temp->lexeme);
                }
                else
                {
                    FUNCTION_TABLE_VALUE value = create_function_value();
                    value->input_list = NULL;
                    value->output_list = NULL;
                    value->symbol_table_wrapper = create_symbol_table_wrapper();
                    value->symbol_table_wrapper->name = temp->name;
                    strcat(value->symbol_table_wrapper->name, "_symbol_table");
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

            addListtoSymbolTable(root, 0, true);
        }
        else if (strcmp(root->name, "OutputPlistHead") == 0)
        {

            addListtoSymbolTable(root, 0, false);
        }
        else if (strcmp(root->name, "ASSIGNMENTSTMT") == 0)
        {
            TREENODE lhs = root->child;
            TREENODE rhs = lhs->next;
            bool lhs_exists = check_if_declared_before(lhs->lexeme);
            if (!lhs_exists)
            {
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", lhs->lexeme);
            }
            if (strcmp(rhs->name, "LVALUEARRSTMT") == 0)
            {
                check_expression_if_declared_before(rhs->child);
                check_expression_if_declared_before(rhs->child->next);
            }
            else
            {
                check_expression_if_declared_before(rhs);
            }
        }
        else if (strcmp(root->name, "DRIVER_MODULE_STMTS") == 0)
        {
            FUNCTION_TABLE_VALUE value = create_function_value();
            value->input_list = NULL;
            value->output_list = NULL;
            value->symbol_table_wrapper = create_symbol_table_wrapper();
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
                        populateSymboltableValue(datatype, stv, current_module_name, nesting_level, temp->line_number, false);
                        // symbol_insert(current_symbol_table_wrapper->symbol_table, temp->lexeme, value);
                    }
                    else
                    {
                        printf("\033[31m\nERROR : %s has already been declared before.\n\033[0m", temp->lexeme);
                    }
                }
                else
                {
                    SYMBOL_TABLE_VALUE value = create_new_symbol_node(datatype->name);
                    int nesting_level = get_nesting_level(current_symbol_table_wrapper) + 1;
                    value->line_number_end = end_line_number;
                    populateSymboltableValue(datatype, value, current_module_name, nesting_level, temp->line_number, false);
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
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "WHILE_symbol_table";
            temp->parent = current_symbol_table_wrapper;
            temp->child = NULL;
            temp->next = NULL;
            insert_symbol_table_at_end(current_symbol_table_wrapper, temp);
            current_symbol_table_wrapper = temp;
        }
        else if (strcmp(root->name, "CONDITIONALSTMT") == 0)
        {
            // checking if condition has expr has been declared before
            bool is_declared = check_if_declared_before(root->child->lexeme);
            if (get_type_of_variable(root->child->lexeme) == 2)
            {
                if (root->child->next->next != NULL)
                    printf("\033[31m\nERROR : Default statement not expected in boolean switch case\n\033[0m");
            }
            else if (get_type_of_variable(root->child->lexeme) == 0)
            {

                if (root->child->next->next == NULL)
                    printf("\033[31m\nERROR : Default statement is expected in integer switch case\n\033[0m");
            }
            if (get_type_of_variable(root->child->lexeme) == 1)
            {
                printf("\033[31m\nERROR : %s has type real, expected integer or boolean\n\033[0m", root->child->lexeme);
            }
            if (!is_declared)
            {
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", root->child->lexeme);
            }
            // check_if_declared_before(root->child->lexeme);
        }
        else if (strcmp(root->name, "CASE_STMT") == 0)
        {

            int type_of_switch_variable = get_type_of_variable(root->parent->parent->child->lexeme);
            if (type_of_switch_variable == 0 && (strcmp(root->child->lexeme, "true") == 0 || strcmp(root->child->lexeme, "false") == 0))
            {
                printf("\033[31m\nERROR : Case value is expected to have type Integer.\n\033[0m");
            }
            if (type_of_switch_variable == 2 && !(strcmp(root->child->lexeme, "true") == 0 || strcmp(root->child->lexeme, "false") == 0))
            {
                printf("\033[31m\nERROR : Case value is expected to have type boolean.\n\033[0m");
            }
            SYMBOL_TABLE_WRAPPER temp = create_symbol_table_wrapper();
            // init_symbolhashmap(temp->symbol_table);
            temp->name = "CASE_STMT_symbol_table";
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
            symbol_insert(current_symbol_table_wrapper->symbol_table, root->child->lexeme, value);
        }
        else if (strcmp(root->name, "IO_INPUT") == 0)
        {
            TREENODE var = root->child;
            bool var_exists = check_if_declared_before(var->lexeme);
            if (!var_exists)
            {
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", var->lexeme);
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
                printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", var->lexeme);
            }
            if (var->next != NULL)
            {
                var = var->next;
                if ((strcmp(var->name, "id") == 0) && (!check_if_declared_before(var->lexeme)))
                {
                    printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", var->lexeme);
                }
            }
        }
        else if (strcmp(root->name, "MODULE_REUSE_STMT") == 0)
        {

            TREENODE temp = root->child;
            if (current_module_name != NULL)
            {
                if(strcmp(temp->next->name,"id")!=0)
                {
                    if (strcmp(current_module_name, root->child->lexeme) == 0)
                        printf("\033[31m\nERROR : Recursion found in Module %s.\n\033[0m", root->child->lexeme);
                }
                else
                {
                    if (strcmp(current_module_name, root->child->next->lexeme) == 0)
                        printf("\033[31m\nERROR : Recursion found in Module %s.\n\033[0m", root->child->next->lexeme);
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
                        printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", temp2->lexeme);
                    }
                    temp2 = temp2->child;
                }
                temp = temp->next;
            }
            if ((!check_if_function_declared(temp->lexeme)))
            {
                printf("\033[31m\nERROR : Module %s has not been declared before.\n\033[0m", temp->lexeme);
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
                            printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", temp3->lexeme);
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
                        printf("\033[31m\nERROR : %s has not been declared before.\n\033[0m", temp2->lexeme);
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
