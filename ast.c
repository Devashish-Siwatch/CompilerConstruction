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
    printf("Currently at %s\n", head->name);
    printAst(head->next);
}

TREENODE generate_ast(TREENODE node)
{
    if (getTypeOfData(node->name) == 1)
    {
        int rule_number = node->rule_number;
        if (rule_number == -1)
            printf("KUCH TO DIKKAT HAI\n");
        printf("%d ************\n ", rule_number);

        // switch(rule_number){
        //     case 0:
        //     case 30:
        //     case 17:
        //         return generate_ast(node->child);
        //         break;
        //     case 1:
        //         node->child->inh = node->child;
        //         node->child->next->inh = node->child->next;
        //         node->child->next->next->inh = node->child->next->next;
        //         TREENODE temp = node->child;
        //         while(temp!=NULL){
        //             generate_ast(temp);
        //             temp = temp->next;
        //         }
        //         return node;
        //         break;
        //     case 3:
        //     case 6:
        //     case 27:

        //         free(node->child);
        //         free(node);
        //         // insertNullAtEnd(node->inh);
        //         return NULL;
        //         break;
        //     case 7:
        //         for(int i=0 ; i<4 ; i++){
        //             TREENODE temp = node->child->next;
        //             free(node->child);
        //             node->child = temp;
        //         }
        //         return generate_ast(node->child);
        //         break;
        //     case 25:
        //         for(int i=0 ; i<1 ; i++){
        //             TREENODE temp = node->child->next;
        //             free(node->child);
        //             node->child = temp;
        //         }
        //         free(node->child->next);
        //         node->child->next = NULL;
        //         node->child->inh = node;
        //         return generate_ast(node->child);
        //     case 26:
        //         //TREENODE stmt = generate_ast(node->child);
        //         appendAtEnd(node->inh, generate_ast(node->child));

        //         node->child->next->inh = node->inh;
        //         generate_ast(node->child->next);
        //         break;
        //     case 104:

        //         TREENODE temp = node->child->next;
        //         free(node->child);
        //         node->child = temp;

        //         TREENODE temp1=node->child;
        //         TREENODE temp2=node->child->next->next;
        //         free(temp1->next);
        //         free(temp2->next);
        //         node->child=NULL;
        //         TREENODE temp3=generate_ast(temp1);
        //         TREENODE temp4=generate_ast(temp2);
        //         temp3->next=temp4;
        //         node->child=temp3;

        //         // node->child=generate_ast(node->child);

        //         // temp = node->child->next->next;
        //         // free(node->child->next);
        //         // node->child->next = temp;
        //         // free(node->child->next->next);
        //         // node->child->next->next = NULL;
        //         // generate_ast(node->child->next);
        //         break;
        //     case 71:
        //         node->inh=node->child;
        //         node->child->next->inh=node->inh;

        //         return generate_ast(node->child->next);

        //         break;
        //     case 72:
        //         appendAtEnd(node->inh, node->child->next);
        //         node->child->next->next->inh = node->inh;
        //         return node;
        //         break;
        //     case 73:
        //         node->parent->child=NULL;
        //         free(node);
        //         break;
        //     default: printf("%d L lg gye\n", rule_number);
        // }
        switch (rule_number)
        {
        case 0:
        {
            free(node->child->next);
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
        case 57: // SIGN plus
        case 58: // SIGN minus
        {
            TREENODE temp = node->child;
            free(node);
            return generate_ast(temp);
        }
        case 1:
        {
            TREENODE moduleDeclarationsHead = (TREENODE)malloc(sizeof(tree_node));
            moduleDeclarationsHead->name = "MDSHead";
            TREENODE otherModulesHead = (TREENODE)malloc(sizeof(tree_node));
            otherModulesHead->name = "OMSHead";
            TREENODE otherModules2Head = (TREENODE)malloc(sizeof(tree_node));
            otherModules2Head->name = "OMS2Head";
            node->child->inh = moduleDeclarationsHead;
            node->child->next->inh = otherModulesHead;
            node->child->next->next->next->inh = otherModules2Head;
            generate_ast(node->child);
            generate_ast(node->child->next);
            TREENODE temp_driver_module = node->child->next->next;
            TREENODE temp_other_modules_2 = node->child->next->next->next;
            node->child = moduleDeclarationsHead;
            node->child->next = otherModulesHead;
            node->child->next->next = generate_ast(temp_driver_module);
            generate_ast(temp_other_modules_2);
            node->child->next->next->next = otherModules2Head;
            return node->child;
        }
        case 3:
        case 6:
        case 27:
        case 65:
        case 73:
        case 108:
        {
            appendAtEnd(node->inh, NULL);
            free(node->child);
            // node->child = NULL;
            free(node);
            return NULL;
        }
        case 7:
        {
            for (int i = 0; i < 4; i++)
            {
                TREENODE temp = node->child->next;
                free(node->child);
                node->child = temp;
            }
            return generate_ast(node->child);
        }
        case 25:
        {
            TREENODE temp = node->child->next;
            free(node->child);
            free(temp->next);
            node->child = temp;
            TREENODE statementsHead = (TREENODE)malloc(sizeof(tree_node));
            statementsHead->name = "STMTSHead";
            temp->inh = statementsHead;
            generate_ast(temp);
            free(node);
            return statementsHead;
        }
        case 26:
        {
            appendAtEnd(node->inh, generate_ast(node->child));
            node->child->next->inh = node->inh;
            generate_ast(node->child->next);
            free(node);
            return NULL;
        }
        case 104:
        {
            TREENODE idList = node->child->next;
            TREENODE dType = idList->next->next;
            free(node->child);  // free declare
            free(idList->next); // free :
            free(dType->next);  // free ;
            node->child = generate_ast(idList);
            node->child->next = generate_ast(dType);
            node->child->next->next = NULL;
            free(idList);
            return node;
        }
        case 71:
        {
            TREENODE idListHead = (TREENODE)malloc(sizeof(tree_node));
            idListHead->name = "IDLHead";
            TREENODE temp_N3 = node->child->next;
            appendAtEnd(idListHead, node->child);
            temp_N3->inh = idListHead;
            generate_ast(temp_N3);
            free(node);
            return idListHead;
        }
        case 72:
        {
            TREENODE temp = node->child->next;
            free(node->child);
            node->child = temp;
            TREENODE temp_N3 = node->child->next;
            appendAtEnd(node->inh, node->child);
            temp_N3->inh = node->inh;
            generate_ast(temp_N3);
            node = NULL;
            free(node);
            return NULL;
        }
        case 62: // MODULEREUSESTMT
        {
            TREENODE tempiter = node->child;
            TREENODE opt, id, aplist;
            for (int i = 0; i < 8; i++)
            { // removing all unnecessary nodes
                TREENODE temp = tempiter->next;
                if (i == 0)
                { // optional saved
                    opt = tempiter;
                }
                else if (i == 3)
                { // id saved
                    id = tempiter;
                }
                else if (i == 6)
                { // ACTUALPARALIST saved
                    aplist = tempiter;
                }
                else
                    free(tempiter);
                tempiter = temp;
            }
            TREENODE module_reuse = (TREENODE)malloc(sizeof(tree_node));
            module_reuse->name = "MODULE_REUSE_STMT";
            node->child = generate_ast(opt);
            if (node->child == NULL)
                node->child = generate_ast(id);
            else
            {
                node->child->next = generate_ast(id);
            }
            id->next = generate_ast(aplist);
            free(opt);
            module_reuse->child = node->child;
            return module_reuse;
        }
        case 69:
        {
            TREENODE temp_idlist = node->child->next;
            free(node->child);
            free(temp_idlist->next->next);
            free(temp_idlist->next);
            node->child = generate_ast(temp_idlist);
            free(temp_idlist);
            return node->child;
        }
        case 44:
        case 48:
        case 59:
        case 70:
        {
            free(node->child);
            return NULL;
        }
        case 63:
        {
            TREENODE apl2head = (TREENODE)malloc(sizeof(tree_node));
            apl2head->name = "APL2Head";
            TREENODE temp_sign = generate_ast(node->child);
            if (temp_sign != NULL)
            {
                temp_sign->next = generate_ast(node->child->next);
                apl2head->child = temp_sign;
                node->child->next->next->inh = apl2head;
                generate_ast(node->child->next->next);
                return apl2head;
            }
            else
            {
                apl2head->child = generate_ast(node->child->next);
                node->child->next->next->inh = apl2head;
                generate_ast(node->child->next->next);
                return apl2head;
            }
        }
        case 64:
        {
            TREENODE temp_comma = node->child;
            node->child = node->child->next;
            free(temp_comma);
            TREENODE temp_sign = generate_ast(node->child);
            if (temp_sign != NULL)
            {
                // inserting sign->apl2 in list
                temp_sign->next = generate_ast(node->child->next);
                appendAtEndNextNotNULL(node->inh, temp_sign, 2);
                node->child->next->next->inh = node->inh;
                generate_ast(node->child->next->next);
                return NULL;
            }
            else
            {
                // inserting apl2 in list

                appendAtEnd(node->inh, generate_ast(node->child->next));

                node->child->next->next->inh = node->inh;
                generate_ast(node->child->next->next);
                return NULL;
            }
        }
        case 66:
        {
            TREENODE temp = generate_ast(node->child->next);
            if (temp == NULL)
            {
                return generate_ast(node->child);
            }
            else
            {
                TREENODE array_element = (TREENODE)malloc(sizeof(tree_node));
                array_element->name = "ARRAY_ELEMENT";
                array_element->child = generate_ast(node->child);
                array_element->child->next = generate_ast(node->child->next);
                free(node);
                return array_element;
            }
        case 74:
        case 81:
        case 84:
        case 119:
        case 123:
        {
            node->child->next->inh = generate_ast(node->child);
            TREENODE temp = node->child->next;
            free(node->child);
            free(node);
            return generate_ast(temp);
        }
        case 75:
        case 82:
        case 85:
        case 121:
        case 124:
        {
            TREENODE logical_op = generate_ast(node->child);
            logical_op->child = node->inh;
            node->child->next->next->inh = generate_ast(node->child->next);
            logical_op->child->next = generate_ast(node->child->next->next);
            free(node->child->next);
            free(node->child);
            free(node);
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
            free(node);
            return generate_ast(temp);
        }
        case 79:
        {
            TREENODE relational_op = generate_ast(node->child);
            relational_op->child = node->inh;
            relational_op->child->next = generate_ast(node->child->next);
            free(node->child->next);
            free(node->child);
            free(node);
            return relational_op;
        }
        case 80:
        {
            TREENODE temp = node->inh;
            free(node);
            return temp;
        }
        case 87:
        case 88:
        case 126:
        case 127:
        {
            TREENODE factor2 = node->child->next;
            TREENODE sign = generate_ast(node->child);
            sign->next = generate_ast(factor2);
            free(factor2);
            free(node);
            return sign;
        }
        case 90:
        case 129:
        {
            TREENODE expr = node->child->next;
            free(node->child); // free (
            node->child = expr;
            free(node->child->next); // free )
            TREENODE temp = node->child;
            free(node);
            return generate_ast(temp);
        }
        case 51:
        {
            TREENODE id = node->child;
            TREENODE whichstmt = node->child->next;
            TREENODE ass = (TREENODE)malloc(sizeof(tree_node));
            ass->name = "ASSIGNMENTSTMT";
            ass->child = generate_ast(id);
            ass->child->next = generate_ast(whichstmt);
            free(whichstmt);
            free(node);
            return ass;
        }
        case 54:
        {
            TREENODE expr = node->child->next;
            free(node->child); // free :=
            free(expr->next);  // free ;
            return generate_ast(expr);
            free(expr);
        }
        case 55:
        {
            // TREENODE aexplt= node->child->next;
            // free(node->child); // free [
            // generate_ast(aexplt);
            // TREENODE expr=aexplt->next->next->next;
            // free(aexplt->next->next);
            // free(aexplt->next);
            TREENODE aexplt = node->child->next;
            TREENODE expr = aexplt->next->next->next;
            TREENODE arrstmt = (TREENODE)malloc(sizeof(tree_node));
            arrstmt->name = "LVALUEARRSTMT";
            arrstmt->child = generate_ast(aexplt);
            arrstmt->child->next = generate_ast(expr);
            free(node->child);        // free [
            free(aexplt->next->next); // free ]
            free(aexplt->next);       // free:=
            free(expr->next);         // free ;
            free(aexplt);
            free(expr);
            return arrstmt;
        }
            // TODO : VERIFY AND UNCOMMENT
            case 105:
            {
                TREENODE id = node->child->next->next;
                free(node->child); //free switch
                free(node->child->next); //free (
                TREENODE cstmts = id->next->next->next;
                free(id->next); // free )
                free(id->next->next); //free start
                TREENODE deflt = cstmts->next;
                free(deflt->next); //free end
                TREENODE conditionalstmt = (TREENODE) malloc(sizeof(tree_node));
                conditionalstmt->name = "CONDITIONALSTMT";
                conditionalstmt->child = generate_ast(id);
                conditionalstmt->child->next = generate_ast(cstmts);
                conditionalstmt->child->next->next = generate_ast(deflt);
                free(cstmts);
                free(deflt);
                free(node);
                return conditionalstmt;
            }
            case 106:
            {
                TREENODE caseStmtsHead = (TREENODE) malloc(sizeof(tree_node));
                caseStmtsHead->name = "CASE_STMTS_HEAD";
                TREENODE caseStmt = (TREENODE) malloc(sizeof(tree_node));
                caseStmt->name = "CASE_STMT";
                TREENODE value = node->child->next;
                TREENODE stmts = value->next->next;
                TREENODE n7 = stmts->next->next->next;
                free(node->child);
                free(value->next);
                free(stmts->next);
                free(stmts->next->next);
                n7->inh = caseStmtsHead;
                caseStmt->child = generate_ast(value);

                TREENODE stmts_head = (TREENODE) malloc(sizeof(tree_node));
                stmts_head->name = "STATEMENTS_HEAD_OF_THIS_CASE";
                stmts->inh = stmts_head;
                generate_ast(stmts);
                caseStmt->child->next = stmts_head;
                appendAtEnd(caseStmtsHead, caseStmt);
                generate_ast(n7);
                return caseStmtsHead;
            }
            case 107:
            {
                TREENODE caseStmt = (TREENODE) malloc(sizeof(tree_node));
                caseStmt->name = "CASE_STMT";
                TREENODE value = node->child->next;
                TREENODE stmts = value->next->next;
                TREENODE n7 = stmts->next->next->next;
                free(node->child);
                free(value->next);
                free(stmts->next);
                free(stmts->next->next);
                n7->inh = node->inh;
                caseStmt->child = generate_ast(value);
                TREENODE statements_head = (TREENODE) malloc(sizeof(tree_node));
                statements_head->name = "STATEMENTS_HEAD_OF_THIS_CASE";
                stmts->inh = statements_head;
                generate_ast(stmts);
                caseStmt->child->next = statements_head;
                appendAtEnd(node->inh, caseStmt);
                generate_ast(n7);
                return NULL;
            }
            case 112:
            {
                TREENODE temp = node->child->next->next;
                free(node);
                free(node->child);
                free(node->child->next);
                free(temp->next);
                free(temp->next->next);
                TREENODE default_stmts_head = (TREENODE) malloc(sizeof(tree_node));
                default_stmts_head->name = "DEFAULT_STATEMENTS_HEAD";
                temp->inh = default_stmts_head;
                generate_ast(temp);
                return default_stmts_head;
            }

        case 33: // IOSTMT
        {
            TREENODE IO_INPUT = (TREENODE)malloc(sizeof(tree_node));
            IO_INPUT->name = "IO_INPUT";
            TREENODE temp = node->child->next->next;
            free(node->child->next->next->next->next);
            free(node->child->next->next->next);
            free(node->child->next);
            free(node->child);
            temp->next = NULL;
            IO_INPUT->child = generate_ast(temp);
            return IO_INPUT;
        }

        case 34:
        {
            TREENODE IO_OUTPUT = (TREENODE)malloc(sizeof(tree_node));
            IO_OUTPUT->name = "IO_OUTPUT";
            TREENODE temp_var_bool = node->child->next->next;
            free(node->child->next->next->next->next);
            free(node->child->next->next->next);
            free(node->child->next);
            free(node->child);
            temp_var_bool->next = NULL;
            IO_OUTPUT->child = generate_ast(temp_var_bool);
            return IO_OUTPUT;
        }
        }
        case 43:
        case 47:
        {
            TREENODE temp_second = node->child->next;
            free(node->child);
            free(temp_second->next);
            return generate_ast(temp_second);
        }
        }
    }
    else
    {
        if (node != NULL)
            node->next = NULL;
        return node;
    };
}