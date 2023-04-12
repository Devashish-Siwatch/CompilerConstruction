/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#include "treeADT.h"
#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include <string.h>
#include "stack.h"
#include "treeADT.h"
#include "treeADTDef.h"
#include "stack.h"
#include <ctype.h>
#include "astDef.h"

// void insertNullAtEnd(TREENODE head){
//     TREENODE temp = head;
//     while(temp.next!=NULL){

//     }
// }
void appendAtLast(TREENODE head, TREENODE node)
{

    if (node != NULL)
    {
        printf("trying to append at last %s\n", node->name);
        node->next = NULL;
    }
    if (head == NULL)
        head = node;
    else
    {
        TREENODE temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void appendAtEnd(TREENODE head, TREENODE node)
{
    if (node != NULL)
        node->next = NULL;
    if (head == NULL)
        head = node;
    else
    {
        TREENODE temp = head;
        while (temp->child != NULL)
        {
            temp = temp->child;
        }
        temp->child = node;
    }
}

void appendAtEndNextNotNULL(TREENODE head, TREENODE node, int step)
{
    if (step == 2 && node != NULL && node->next != NULL)
    {
        node->next->next = NULL;
    }
    else if (step == 3 && node != NULL && node->next != NULL && node->next != NULL)
    {
        node->next->next->next = NULL;
    }

    if (head == NULL)
        head = node;
    else
    {
        TREENODE temp = head;
        while (temp->child != NULL)
        {
            temp = temp->child;
        }
        temp->child = node;
    }
}

void printAst(TREENODE head)
{
    if (head == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }
    printAst(head->child);
    if (head->parent != NULL)
        printf("Currently at node : %-20s, lexeme : %-20s and parent : %-20s, plexeme : %-20s \n", head->name, head->lexeme, head->parent->name, head->parent->lexeme);
    else
        printf("Currently at node : %-20s and parent : %-20s\n", head->name, "NULL");
    printAst(head->next);
}
void setASTParent(TREENODE root)
{
    if (root == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }
    TREENODE temp = root->child;
    while (temp != NULL)
    {
        temp->parent = root;
        setASTParent(temp);
        temp = temp->next;
    }
    // printf("Currently at node : %-20s parent: %-20s\n", head->name, head->parent->name);
    // setASTParent(head->next);
}

TREENODE generate_ast(TREENODE node)
{
    if (getTypeOfData(node->name) == 1)
    {
        int rule_number = node->rule_number;
        if (rule_number == -1)
            printf("KUCH TO DIKKAT HAI\n");
        printf("%d ************\n", rule_number);
        switch (rule_number)
        {
        case 0:
        {
            // free(node->child->next);
            node->child->next = NULL;
            node->child = generate_ast(node->child);
            return node;
        }
        case 29:
        case 36:
        case 37:
        case 49:
        case 30:
        case 17:
        case 78:
        case 89:
        case 91:
        case 92:
        case 93:
        case 94:
        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
        case 103:
        case 52:
        case 53:
        case 131:
        case 132:
        case 133:
        case 130:
        case 128:
        case 45:
        case 46:
        case 18:
        case 19:
        case 22:
        case 23:
        case 24:
        case 118:
        case 109:
        case 110:
        case 111:
        case 41:
        case 42:
        case 38:
        case 39:
        case 31:
        case 32:
        case 28:
        case 50:
        case 67:
        case 68:
        // case 57:
        // case 58:
        case 60:
        case 61:
        {
            TREENODE temp = node->child;
            temp->line_number = node->line_number;
            // //free(node);
            return generate_ast(temp);
        }
        case 57:
        {
            TREENODE temp = node->child;
            // free(node);
            TREENODE result = generate_ast(temp);
            result->name = "PLUS";
            return result;
        }
        case 58:
        {
            TREENODE temp = node->child;
            // free(node);
            TREENODE result = generate_ast(temp);
            result->name = "MINUS";
            return result;
        }
        case 43:
        case 47:
        {
            TREENODE temp_second = node->child->next;
            // free(node->child);
            // free(temp_second->next);
            return generate_ast(temp_second);
        }
        case 1:
        {
            TREENODE temp_mds = node->child;
            TREENODE temp_oms = node->child->next;
            TREENODE temp_dm = node->child->next->next;
            TREENODE temp_oms2 = node->child->next->next->next;

            // free(node);

            TREENODE moduleDeclarations = createNewTreeNode2();
            moduleDeclarations->name = "MDS";
            TREENODE otherModules = createNewTreeNode2();
            otherModules->name = "OMS";

            TREENODE moduleDeclarationsHead = createNewTreeNode2();
            moduleDeclarationsHead->name = "MDSHead";
            TREENODE otherModulesHead = createNewTreeNode2();
            otherModulesHead->name = "OMSHead";

            temp_mds->inh = moduleDeclarationsHead;
            temp_oms->inh = otherModulesHead;

            moduleDeclarations->child = moduleDeclarationsHead;
            otherModules->child = otherModulesHead;

            generate_ast(temp_mds);
            generate_ast(temp_oms);

            moduleDeclarations->next = otherModules;

            TREENODE driverModule = createNewTreeNode2();
            driverModule->name = "DriverModule";
            driverModule->child = generate_ast(temp_dm);
            otherModules->next = driverModule;

            TREENODE otherModules2 = createNewTreeNode2();
            otherModules2->name = "OMS2";
            TREENODE otherModules2Head = createNewTreeNode2();
            otherModules2Head->name = "OMS2Head";
            otherModules2->child = otherModules2Head;
            temp_oms2->inh = otherModules2Head;
            generate_ast(temp_oms2);

            driverModule->next = otherModules2;
            otherModules2->next = NULL;

            return moduleDeclarations;
        }
        case 3:

        case 13:
        case 16:
        case 65:
        case 73:
        {
            appendAtEnd(node->inh, NULL);
            // free(node->child);
            //  node->child = NULL;
            // free(node);
            return NULL;
        }
        case 7:
        {
            int line_number = node->child->line_number;
            for (int i = 0; i < 4; i++)
            {
                TREENODE temp = node->child->next;
                // free(node->child);
                node->child = temp;
            }
            TREENODE driver_module = createNewTreeNode2();
            driver_module->name = "DRIVER_MODULE_STMTS";
            driver_module->line_number = line_number;
            driver_module->child = generate_ast(node->child)->next;
            return driver_module;
        }
        case 25:
        {

            TREENODE temp = node->child->next;
            int end_line_number = temp->next->line_number;
            // free(node->child);
            // free(temp->next);
            node->child = temp;
            TREENODE statementsHead = createNewTreeNode2();
            statementsHead->name = "STMTSHead";
            temp->inh = statementsHead;
            temp->line_number = end_line_number;
            generate_ast(temp);
            // free(node);
            return statementsHead;
        }
        case 26:
        {
            node->child->next->line_number = node->line_number;
            node->child->line_number = node->line_number; // Changed
            appendAtLast(node->inh, generate_ast(node->child));
            node->child->next->inh = node->inh;
            generate_ast(node->child->next);
            // free(node);
            return NULL;
        }
        case 6:
        case 108:
        {
            appendAtLast(node->inh, NULL);
            // free(node->child);
            return NULL;
        }
        case 27:
        {
            TREENODE stmts_end = createNewTreeNode2();
            stmts_end->name = "STMTS_END";
            stmts_end->line_number = node->line_number;
            appendAtLast(node->inh, stmts_end);
            appendAtLast(node->inh, NULL);
            ////free(node->child);
            return NULL;
        }
        case 104:
        {
            TREENODE declare_stmt = createNewTreeNode2();
            declare_stmt->name = "DECLARESTMT";
            TREENODE idList = node->child->next;
            TREENODE dType = idList->next->next;
            // free(node->child);  // //free declare
            // free(idList->next); // //free :
            // free(dType->next);  // //free ;
            declare_stmt->child = generate_ast(idList);
            declare_stmt->child->next = generate_ast(dType);
            declare_stmt->child->next->next = NULL;
            // free(idList);
            return declare_stmt;
        }
        case 71:
        {
            TREENODE idListHead = createNewTreeNode2();
            idListHead->name = "IDLHead";
            TREENODE temp_N3 = node->child->next;
            appendAtEnd(idListHead, node->child);
            temp_N3->inh = idListHead;
            generate_ast(temp_N3);
            // free(node);
            return idListHead;
        }
        case 72:
        {
            TREENODE temp = node->child->next;
            // free(node->child);
            node->child = temp;
            TREENODE temp_N3 = node->child->next;
            appendAtEnd(node->inh, node->child);
            temp_N3->inh = node->inh;
            generate_ast(temp_N3);
            node = NULL;
            // free(node);
            return NULL;
        }
        case 62: // MODULEREUSESTMT
        {
            TREENODE opt, id, aplist;
            opt = node->child;
            id = opt->next->next->next;
            aplist = id->next->next->next;
            // free(opt->next->next);
            // free(opt->next);
            // free(id->next->next);
            // free(id->next);
            // free(aplist->next);
            TREENODE module_reuse = createNewTreeNode2();
            module_reuse->name = "MODULE_REUSE_STMT";
            TREENODE temp_opt = generate_ast(opt);
            TREENODE temp_id = generate_ast(id);
            TREENODE temp_aplist = generate_ast(aplist);
            if (temp_opt == NULL)
            {
                module_reuse->child = temp_id;
                module_reuse->child->next = temp_aplist;
                module_reuse->child->next->next = NULL;
            }
            else
            {
                module_reuse->child = temp_opt;
                module_reuse->child->next = temp_id;
                module_reuse->child->next->next = temp_aplist;
                module_reuse->child->next->next->next = NULL;
            }
            return module_reuse;
        }
        case 69:
        {
            TREENODE temp_idlist = node->child->next;
            // free(node->child);
            // free(temp_idlist->next->next);
            // free(temp_idlist->next);
            node->child = generate_ast(temp_idlist);
            // free(temp_idlist);
            return node->child;
        }
        case 10:
        case 44:
        case 48:
        case 59:
        case 70:
        {
            // free(node->child);
            return NULL;
        }
        case 63:
        {
            TREENODE apl2head = createNewTreeNode2();
            apl2head->name = "APL2Head";
            TREENODE temp_sign = generate_ast(node->child);
            if (temp_sign != NULL)
            {
                TREENODE temp_apl2 = generate_ast(node->child->next);
                if (temp_apl2->next == NULL)
                {
                    // case where only id is present so total length = sign + id = 2
                    temp_sign->next = temp_apl2;
                    appendAtEndNextNotNULL(apl2head, temp_sign, 2);
                    node->child->next->next->inh = apl2head;
                    generate_ast(node->child->next->next);
                    return apl2head;
                }
                else
                {
                    // case where array element is present so total length = 3
                    temp_sign->next = temp_apl2;
                    appendAtEndNextNotNULL(apl2head, temp_sign, 3);
                    node->child->next->next->inh = apl2head;
                    generate_ast(node->child->next->next);
                    return apl2head;
                }
            }
            else
            {
                TREENODE temp_apl2 = generate_ast(node->child->next);
                if (temp_apl2->next == NULL)
                {
                    // case where only id is present so total length 1
                    appendAtEnd(apl2head, temp_apl2);
                    node->child->next->next->inh = apl2head;
                    generate_ast(node->child->next->next);
                    return apl2head;
                }
                else
                {
                    // case where array element is present so total length = 2
                    appendAtEndNextNotNULL(apl2head, temp_apl2, 2);
                    node->child->next->next->inh = apl2head;
                    generate_ast(node->child->next->next);
                    return apl2head;
                }
            }
        }
        case 64:
        {
            TREENODE temp_comma = node->child;
            node->child = node->child->next;
            // free(temp_comma);
            TREENODE temp_sign = generate_ast(node->child);
            if (temp_sign != NULL)
            {
                // case where we have sign
                TREENODE temp_apl2 = generate_ast(node->child->next);
                if (temp_apl2->next == NULL)
                {
                    // case where only id is present so total length = sign + id = 2
                    temp_sign->next = temp_apl2;
                    appendAtEndNextNotNULL(node->inh, temp_sign, 2);
                    node->child->next->next->inh = node->inh;
                    generate_ast(node->child->next->next);
                    // free(node);
                    return NULL;
                }
                else
                {
                    // case where array element is present so total length = 3
                    temp_sign->next = temp_apl2;
                    appendAtEndNextNotNULL(node->inh, temp_sign, 3);
                    node->child->next->next->inh = node->inh;
                    generate_ast(node->child->next->next);
                    // free(node);
                    return NULL;
                }
            }
            else
            {
                TREENODE temp_apl2 = generate_ast(node->child->next);
                if (temp_apl2->next == NULL)
                {
                    // case where only id is present so total length 1
                    appendAtEnd(node->inh, temp_apl2);
                    node->child->next->next->inh = node->inh;
                    generate_ast(node->child->next->next);
                    // free(node);
                    return NULL;
                }
                else
                {
                    // case where array element is present so total length = 2
                    appendAtEndNextNotNULL(node->inh, temp_apl2, 2);
                    node->child->next->next->inh = node->inh;
                    generate_ast(node->child->next->next);
                    // free(node);
                    return NULL;
                }
            }
        }
        case 66:
        {
            TREENODE temp = generate_ast(node->child->next);
            if (temp == NULL)
            {
                printf("reached the case where whichId is null\n");
                TREENODE result = generate_ast(node->child);
                result->next = NULL;
                return result;
            }
            else
            {
                printf("reached the case where whichId is NOT null\n");

                TREENODE id = generate_ast(node->child);
                id->next = temp;
                id->next->next = NULL;
                // free(node);
                return id;
            }
        }
        case 74:
        case 81:
        case 84:
        case 119:
        case 123:
        {
            // node->child->next->inh = generate_ast(node->child);
            TREENODE temp = node->child->next;
            temp->inh = generate_ast(node->child);
            // free(node->child);
            // free(node);
            return generate_ast(temp);
        }
        case 75:
        {
            TREENODE logical_op = generate_ast(node->child);
            logical_op->child = node->inh;
            node->inh->parent = logical_op;
            TREENODE newChild = generate_ast(node->child->next);
            logical_op->child->next = newChild;
            newChild->parent = logical_op;
            node->child->next->next->inh = logical_op;
            TREENODE be2 = node->child->next->next;
            // //free(node->child->next);
            // //free(node->child);
            // //free(node);
            return generate_ast(be2);
        }
        case 82:
        case 85:
        case 121:
        case 124:
        {
            TREENODE logical_op = generate_ast(node->child);
            logical_op->child = node->inh;
            node->child->next->next->inh = generate_ast(node->child->next);
            logical_op->child->next = generate_ast(node->child->next->next);
            // free(node->child->next);
            // free(node->child);
            // free(node);
            return logical_op;
        }
        case 76:
        case 83:
        case 86:
        case 122:
        case 125:
        case 113:
        {
            return node->inh;
        }
        case 77:
        {
            node->child->next->inh = generate_ast(node->child);
            TREENODE temp = node->child->next;
            // free(node);
            return generate_ast(temp);
        }
        case 79:
        {
            TREENODE relational_op = generate_ast(node->child);
            relational_op->child = node->inh;
            relational_op->child->next = generate_ast(node->child->next);
            // free(node->child->next);
            // free(node->child);
            // free(node);
            return relational_op;
        }
        case 80:
        {
            TREENODE temp = node->inh;
            // free(node);
            return temp;
        }
        // case 87:
        case 88:
        // case 126:
        case 127:
        {
            TREENODE factor2 = node->child->next;
            TREENODE sign = generate_ast(node->child);
            sign->child = generate_ast(factor2);
            sign->name = "MINUS";
            // free(factor2);
            // free(node);
            return sign;
        }
        case 126:
        case 87:
        {
            TREENODE factor2 = node->child->next;
            TREENODE sign = generate_ast(node->child);
            sign->child = generate_ast(factor2);
            sign->name = "PLUS";
            // free(factor2);
            // free(node);
            return sign;
        }

        case 90:
        case 129:
        {
            TREENODE expr = node->child->next;
            // free(node->child); // //free (
            node->child = expr;
            // free(node->child->next); // //free )
            TREENODE temp = node->child;
            // free(node);
            return generate_ast(temp);
        }
        case 51:
        {
            TREENODE id = node->child;
            TREENODE whichstmt = node->child->next;
            TREENODE ass = createNewTreeNode2();
            ass->name = "ASSIGNMENTSTMT";
            ass->child = generate_ast(id);
            whichstmt->line_number = id->line_number;
            ass->child->next = generate_ast(whichstmt);
            // free(whichstmt);
            // free(node);
            return ass;
        }
        case 54:
        {
            TREENODE expr = node->child->next;
            // free(node->child); // //free :=
            // free(expr->next);  // //free ;
            return generate_ast(expr);
            // free(expr);
        }
        case 55:
        {
            // TREENODE aexplt= node->child->next;
            // //free(node->child); // //free [
            // generate_ast(aexplt);
            // TREENODE expr=aexplt->next->next->next;
            // //free(aexplt->next->next);
            // //free(aexplt->next);
            TREENODE aexplt = node->child->next;
            TREENODE expr = aexplt->next->next->next;
            TREENODE arrstmt = createNewTreeNode2();
            arrstmt->name = "LVALUEARRSTMT";
            arrstmt->line_number = node->line_number;
            TREENODE index = createNewTreeNode2();
            index->name = "INDEX";
            index->child = generate_ast(aexplt);
            TREENODE expression = createNewTreeNode2();
            expression->name = "EXPRESSION";
            expression->child = generate_ast(expr);
            arrstmt->child = index;
            arrstmt->child->next = expression;
            // free(node->child);        // //free [
            // free(aexplt->next->next); // //free ]
            // free(aexplt->next);       // //free:=
            // free(expr->next);         // //free ;
            // free(aexplt);
            // free(expr);
            return arrstmt;
        }
        // TODO : VERIFY AND UNCOMMENT
        case 105:
        {
            TREENODE id = node->child->next->next;
            // free(node->child);       // //free switch
            // free(node->child->next); // //free (
            TREENODE cstmts = id->next->next->next;
            // free(id->next);       // //free )
            // free(id->next->next); // //free start
            TREENODE deflt = cstmts->next;
            // free(deflt->next);
            TREENODE conditionalstmt = createNewTreeNode2();
            conditionalstmt->name = "CONDITIONALSTMT";
            conditionalstmt->child = generate_ast(id);
            conditionalstmt->child->next = generate_ast(cstmts);
            conditionalstmt->child->next->next = generate_ast(deflt);
            // free(cstmts);
            // free(deflt);
            // free(node);
            return conditionalstmt;
        }
        case 106:
        {
            TREENODE caseStmtsHead = createNewTreeNode2();
            caseStmtsHead->name = "CASE_STMTS_HEAD";
            TREENODE caseStmtsHead2 = createNewTreeNode2();
            caseStmtsHead2->name = "CASE_STMTS_HEAD2";
            TREENODE caseStmt = createNewTreeNode2();
            caseStmtsHead->child = caseStmtsHead2;
            caseStmt->name = "CASE_STMT";
            caseStmt->line_number = node->child->line_number;
            TREENODE value = node->child->next;
            TREENODE stmts = value->next->next;
            TREENODE n7 = stmts->next->next->next;
            // free(node->child);
            // free(value->next);
            // free(stmts->next);
            // free(stmts->next->next);
            n7->inh = caseStmtsHead2;
            caseStmt->child = generate_ast(value);

            TREENODE stmts_head = createNewTreeNode2();
            stmts_head->name = "STATEMENTS_HEAD_OF_THIS_CASE";
            stmts->inh = stmts_head;
            stmts->line_number = stmts->next->line_number;
            generate_ast(stmts);
            caseStmt->child->next = stmts_head;
            appendAtLast(caseStmtsHead2, caseStmt);
            generate_ast(n7);
            return caseStmtsHead;
        }
        case 107:
        {
            TREENODE caseStmt = createNewTreeNode2();
            caseStmt->name = "CASE_STMT";
            caseStmt->line_number = node->child->line_number;
            TREENODE value = node->child->next;
            TREENODE stmts = value->next->next;
            stmts->line_number = stmts->next->line_number;
            TREENODE n7 = stmts->next->next->next;
            // free(node->child);
            // free(value->next);
            // free(stmts->next);
            // free(stmts->next->next);
            n7->inh = node->inh;
            caseStmt->child = generate_ast(value);
            TREENODE statements_head = createNewTreeNode2();
            statements_head->name = "STATEMENTS_HEAD_OF_THIS_CASE";
            stmts->inh = statements_head;
            generate_ast(stmts);
            caseStmt->child->next = statements_head;
            appendAtLast(node->inh, caseStmt);
            generate_ast(n7);
            return NULL;
        }
        case 112:
        {
            TREENODE temp = node->child->next->next;
            // free(node);
            // free(node->child);
            // free(node->child->next);
            // free(temp->next);
            // free(temp->next->next);
            TREENODE default_stmts = createNewTreeNode2();
            default_stmts->name = "DEFAULT";
            default_stmts->line_number = node->child->line_number;
            TREENODE default_stmts_head = createNewTreeNode2();
            default_stmts_head->name = "DEFAULT_STATEMENTS_HEAD";
            default_stmts->child = default_stmts_head;
            temp->inh = default_stmts_head;
            temp->line_number = temp->next->line_number;
            generate_ast(temp);
            return default_stmts;
        }

        case 33: // IOSTMT
        {
            TREENODE IO_INPUT = createNewTreeNode2();
            IO_INPUT->name = "IO_INPUT";
            TREENODE temp = node->child->next->next;
            // free(node->child->next->next->next->next);
            // free(node->child->next->next->next);
            // free(node->child->next);
            // free(node->child);
            temp->next = NULL;
            IO_INPUT->child = generate_ast(temp);
            return IO_INPUT;
        }

        case 34:
        {
            TREENODE IO_OUTPUT = createNewTreeNode2();
            IO_OUTPUT->name = "IO_OUTPUT";
            TREENODE temp_var_bool = node->child->next->next;
            // free(node->child->next->next->next->next);
            // free(node->child->next->next->next);
            // free(node->child->next);
            // free(node->child);
            temp_var_bool->next = NULL;
            IO_OUTPUT->child = generate_ast(temp_var_bool);
            return IO_OUTPUT;
        }
        case 114:
        {
            TREENODE ITERATIVESTMT_WHILE = createNewTreeNode2();
            ITERATIVESTMT_WHILE->name = "ITERATIVESTMT_WHILE";
            ITERATIVESTMT_WHILE->line_number = node->child->line_number;
            TREENODE tempExpr = node->child->next->next;
            TREENODE tempStmt = node->child->next->next->next->next->next;
            int end_line_number = tempStmt->next->line_number;
            // free(node->child->next->next->next->next->next->next);
            // free(node->child->next->next->next->next);
            // free(node->child->next->next->next);
            // free(node->child->next);
            // free(node->child);
            ITERATIVESTMT_WHILE->child = generate_ast(tempExpr);
            TREENODE while_stmts_head = createNewTreeNode2();
            while_stmts_head->name = "WHILE_STMTS_HEAD";
            tempStmt->inh = while_stmts_head;
            tempStmt->line_number = end_line_number;
            generate_ast(tempStmt);
            ITERATIVESTMT_WHILE->child->next = while_stmts_head;
            return ITERATIVESTMT_WHILE;
        }
        case 120:
        {
            int start_line_number = node->child->line_number;
            TREENODE ITERATIVESTMT_FOR = createNewTreeNode2();
            ITERATIVESTMT_FOR->name = "ITERATIVESTMT_FOR";
            ITERATIVESTMT_FOR->line_number = start_line_number;
            TREENODE tempId = node->child->next->next;
            TREENODE tempRange = node->child->next->next->next->next;
            TREENODE tempStmt = node->child->next->next->next->next->next->next->next;
            int end_line_number = tempStmt->next->line_number;
            // free(node->child->next->next->next->next->next->next->next->next);
            // free(node->child->next->next->next->next->next->next);
            // free(node->child->next->next->next->next->next);
            // free(node->child->next->next->next);
            // free(node->child->next);
            // free(node->child);
            ITERATIVESTMT_FOR->child = generate_ast(tempId);
            ITERATIVESTMT_FOR->child->next = generate_ast(tempRange);
            TREENODE for_stmts_head = createNewTreeNode2();
            for_stmts_head->name = "FOR_STMTS_HEAD";
            for_stmts_head->line_number = start_line_number;
            tempStmt->inh = for_stmts_head;
            tempStmt->line_number = end_line_number;
            generate_ast(tempStmt);
            ITERATIVESTMT_FOR->child->next->next = for_stmts_head;
            return ITERATIVESTMT_FOR;
        }
        case 116:
        case 117:
        {
            return node->child;
        }
        case 115:
        {
            TREENODE temp = node->child->next->next;
            // free(node->child->next);
            node->child->next = temp;
            return node;
        }
        case 8:
        {
            TREENODE id = node->child->next->next;
            // free(node->child->next);
            // free(node->child);
            // free(node);
            TREENODE iplist = id->next->next->next->next->next;
            // free(id->next->next->next->next);
            // free(id->next->next->next);
            // free(id->next->next);
            // free(id->next);
            TREENODE ret = iplist->next->next->next;
            // free(iplist->next->next);
            // free(iplist->next);
            TREENODE mdef = ret->next;
            TREENODE MODULE1 = createNewTreeNode2();
            MODULE1->name = "Module1";
            MODULE1->line_number = node->child->line_number;
            MODULE1->child = generate_ast(id);
            MODULE1->child->next = generate_ast(iplist);
            TREENODE temp_ret = generate_ast(ret);
            if (temp_ret == NULL)
            {
                MODULE1->child->next->next = generate_ast(mdef);
            }
            else
            {
                MODULE1->child->next->next = temp_ret;
                MODULE1->child->next->next->next = generate_ast(mdef);
            }
            return MODULE1;
        }
        case 9:
        {
            TREENODE opl = node->child->next->next;
            // free(node->child->next);
            // free(node->child);
            // free(opl->next->next);
            // free(opl->next);
            // free(node);
            return generate_ast(opl);
        }

        case 11:
        {
            TREENODE inputPlistHead = createNewTreeNode2();
            inputPlistHead->name = "InputPlistHead";

            TREENODE temp_id = node->child;
            TREENODE temp_N1 = node->child->next->next->next;
            TREENODE temp_datatype = node->child->next->next;
            // free(temp_id->next);

            TREENODE inputPlistElement = generate_ast(temp_id);
            inputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(inputPlistHead, inputPlistElement, 2);

            temp_N1->inh = inputPlistHead;
            generate_ast(temp_N1);
            // free(node);
            return inputPlistHead;
        }
        case 14:
        {
            TREENODE outputPlistHead = createNewTreeNode2();
            outputPlistHead->name = "OutputPlistHead";

            TREENODE temp_id = node->child;
            TREENODE temp_N1 = node->child->next->next->next;
            TREENODE temp_datatype = node->child->next->next;
            // free(temp_id->next);

            TREENODE outputPlistElement = generate_ast(temp_id);
            outputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(outputPlistHead, outputPlistElement, 2);

            temp_N1->inh = outputPlistHead;
            generate_ast(temp_N1);
            // free(node);
            return outputPlistHead;
        }
        case 12:
        {
            TREENODE temp_id = node->child->next;
            TREENODE temp_datatype = temp_id->next->next;
            TREENODE temp_N1 = temp_datatype->next;
            // free(temp_id->next);

            TREENODE inputPlistElement = generate_ast(temp_id);
            inputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(node->inh, inputPlistElement, 2);
            temp_N1->inh = node->inh;

            generate_ast(temp_N1);
            // free(node);
            // free(temp_datatype);
            return NULL;
        }
        case 15:
        {
            TREENODE temp_id = node->child->next;
            TREENODE temp_datatype = temp_id->next->next;
            TREENODE temp_N1 = temp_datatype->next;
            // free(temp_id->next);

            TREENODE outputPlistElement = generate_ast(temp_id);
            outputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(node->inh, outputPlistElement, 2);
            temp_N1->inh = node->inh;

            generate_ast(temp_N1);
            // free(node);
            // free(temp_datatype);
            return NULL;
        }
        case 5:
        {
            appendAtLast(node->inh, generate_ast(node->child));
            node->child->next->inh = node->inh;
            generate_ast(node->child->next);
            // free(node->child);
            // free(node);
            return NULL;
        }
        case 20:
        {
            TREENODE tempRange2 = node->child->next->next;
            TREENODE tempType = node->child->next->next->next->next->next;
            // free(node->child->next->next->next->next);
            // free(node->child->next->next->next);
            // free(node->child->next);
            // free(node->child);
            // free(node);
            TREENODE range2 = generate_ast(tempRange2);
            range2->child->next->next = generate_ast(tempType);
            return range2;
        }
        case 21:
        {
            TREENODE tempIndex2 = node->child->next->next;
            // free(node->child->next);
            node->child = generate_ast(node->child);
            node->child->next = generate_ast(tempIndex2);
            return node;
        }
        case 56:
        {
            TREENODE temp_index = generate_ast(node->child->next);
            TREENODE temp_sign = generate_ast(node->child);
            if (temp_sign == NULL)
            {
                // free(node);
                return temp_index;
                temp_index->child = NULL;
            }
            else
            {
                temp_sign->child = temp_index;
                temp_index->child = NULL;
                // free(node);
                return temp_sign;
            }
        }
        case 40:
        case 35:
        {
            TREENODE temp = node->child;
            TREENODE temp1 = node->child->next;
            temp = generate_ast(node->child);
            temp->child = generate_ast(temp1);
            // free(node);
            return temp;
        }
        case 4:
        {
            TREENODE temp = node->child->next->next;
            // free(node->child->next->next->next);
            // free(node->child->next);
            // free(node->child);
            // free(node);
            return generate_ast(temp);
        }
        case 2:
        {
            appendAtEnd(node->inh, generate_ast(node->child));
            node->child->next->inh = node->inh;
            generate_ast(node->child->next);
            return NULL;
        }
        }
    }
    else
    {
        node->next = NULL;
        return node;
    }
}