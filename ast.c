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
        case 57:
        case 58:
        case 60:
        case 61:
        {
            TREENODE temp = node->child;
            free(node);
            return generate_ast(temp);
        }
        case 43:
        case 47:
        {
            TREENODE temp_second = node->child->next;
            free(node->child);
            free(temp_second->next);
            return generate_ast(temp_second);
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
        case 13:
        case 16:
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
        case 10:
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
                array_element->child->next->next = NULL;
                free(node);
                return array_element;
            }
        }
        case 74:
        case 81:
        case 84:
        case 119:
        case 123:
        {
            //node->child->next->inh = generate_ast(node->child);
            TREENODE temp = node->child->next;
            temp->inh = generate_ast(node->child);
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
        case 114:
        {
            TREENODE ITERATIVESTMT_WHILE = (TREENODE)malloc(sizeof(tree_node));
            ITERATIVESTMT_WHILE->name = "ITERATIVESTMT_WHILE";
            TREENODE tempExpr = node->child->next->next;
            TREENODE tempStmt = node->child->next->next->next->next->next;
            free(node->child->next->next->next->next->next->next);
            free(node->child->next->next->next->next);
            free(node->child->next->next->next);
            free(node->child->next);
            free(node->child);
            ITERATIVESTMT_WHILE->child = generate_ast(tempExpr);
            TREENODE while_stmts_head = (TREENODE)malloc(sizeof(tree_node));
            while_stmts_head->name = "WHILE_STMTS_HEAD";
            tempStmt->inh = while_stmts_head;
            generate_ast(tempStmt);
            ITERATIVESTMT_WHILE->child->next = while_stmts_head;
            return ITERATIVESTMT_WHILE;
        }
        case 120:
        {
            TREENODE ITERATIVESTMT_FOR = (TREENODE)malloc(sizeof(tree_node));
            ITERATIVESTMT_FOR->name = "ITERATIVESTMT_FOR";
            TREENODE tempId = node->child->next->next;
            TREENODE tempRange = node->child->next->next->next->next;
            TREENODE tempStmt = node->child->next->next->next->next->next->next->next;
            free(node->child->next->next->next->next->next->next->next->next);
            free(node->child->next->next->next->next->next->next);
            free(node->child->next->next->next->next->next);
            free(node->child->next->next->next);
            free(node->child->next);
            free(node->child);
            ITERATIVESTMT_FOR->child = generate_ast(tempId);
            ITERATIVESTMT_FOR->child->next = generate_ast(tempRange);
            TREENODE for_stmts_head = (TREENODE)malloc(sizeof(tree_node));
            for_stmts_head->name = "FOR_STMTS_HEAD";
            tempStmt->inh = for_stmts_head;
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
            free(node->child->next);
            node->child->next = temp;
            return node;
        }
        case 8:
        {
            TREENODE id=node->child->next->next;
            free(node->child->next);
            free(node->child);
            free(node);
            TREENODE iplist = id->next->next->next->next->next;
            free(id->next->next->next->next);
            free(id->next->next->next);
            free(id->next->next);
            free(id->next);
            TREENODE ret = iplist->next->next->next;
            free(iplist->next->next);
            free(iplist->next);
            TREENODE mdef = ret->next;
            TREENODE MODULE1 = (TREENODE)malloc(sizeof(tree_node));
            MODULE1->name="Module1";
            MODULE1->child=generate_ast(id);
            MODULE1->child->next=generate_ast(iplist);
            TREENODE temp_ret=generate_ast(ret);
            if(temp_ret==NULL){
                MODULE1->child->next->next=generate_ast(mdef);
            }
            else{
                MODULE1->child->next->next=temp_ret;
                MODULE1->child->next->next->next=generate_ast(mdef);

            }
            return MODULE1;
            
        }
        case 9:{
            TREENODE opl=node->child->next->next;
            free(node->child->next);
            free(node->child);
            free(opl->next->next);
            free(opl->next);
            free(node);
            return generate_ast(opl);
        }

        case 11:
        {
            TREENODE inputPlistHead = (TREENODE)malloc(sizeof(tree_node));
            inputPlistHead->name = "InputPlistHead";

            TREENODE temp_id = node->child;
            TREENODE temp_N1 = node->child->next->next->next;
            TREENODE temp_datatype = node->child->next->next;
            free(temp_id->next);

            TREENODE inputPlistElement = generate_ast(temp_id);
            inputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(inputPlistHead, inputPlistElement,2);

            temp_N1->inh = inputPlistHead;
            generate_ast(temp_N1);
            free(node);
            return inputPlistHead;
        }
        case 14:
        {
            TREENODE outputPlistHead = (TREENODE)malloc(sizeof(tree_node));
            outputPlistHead->name = "OutputPlistHead";

            TREENODE temp_id = node->child;
            TREENODE temp_N1 = node->child->next->next->next;
            TREENODE temp_datatype = node->child->next->next;
            free(temp_id->next);

            TREENODE outputPlistElement = generate_ast(temp_id);
            outputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(outputPlistHead, outputPlistElement,2);

            temp_N1->inh = outputPlistHead;
            generate_ast(temp_N1);
            free(node);
            return outputPlistHead;
        }
        case 12:
        {
            TREENODE temp_id = node->child->next;
            TREENODE temp_datatype = temp_id->next->next;
            TREENODE temp_N1 = temp_datatype->next;
            free(temp_id->next);

            TREENODE inputPlistElement = generate_ast(temp_id);
            inputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(node->inh, inputPlistElement, 2);
            temp_N1->inh = node->inh;

            generate_ast(temp_N1);
            free(node);
            free(temp_datatype);
            return NULL;
        }
        case 15:
        {
            TREENODE temp_id = node->child->next;
            TREENODE temp_datatype = temp_id->next->next;
            TREENODE temp_N1 = temp_datatype->next;
            free(temp_id->next);

            TREENODE outputPlistElement = generate_ast(temp_id);
            outputPlistElement->next = generate_ast(temp_datatype);
            appendAtEndNextNotNULL(node->inh, outputPlistElement, 2);
            temp_N1->inh = node->inh;

            generate_ast(temp_N1);
            free(node);
            free(temp_datatype);
            return NULL;
        }
        case 5:
        {
            appendAtEnd(node->inh,generate_ast(node->child));
            node->child->next->inh=node->inh;
            generate_ast(node->child->next);
            free(node->child);
            free(node);
            return NULL;
        }
        case 20:
        {
            TREENODE tempRange2 = node->child->next->next;
            TREENODE tempType = node->child->next->next->next->next->next;
            free(node->child->next->next->next->next);
            free(node->child->next->next->next);
            free(node->child->next);
            free(node->child);
            free(node);
            TREENODE range2 = generate_ast(tempRange2);
            range2->next = generate_ast(tempType);
            return range2;
        }
        case 21:
        {
            TREENODE tempIndex2 = node->child->next->next;
            free(node->child->next);
            node->child = generate_ast(node->child);
            node->child->next = generate_ast(tempIndex2);
            return node;
        }
        case 56:
        {
            TREENODE temp1 = generate_ast(node->child->next);
            TREENODE temp = generate_ast(node->child);
            temp->next = temp1;
            free(node);
            return temp;
        }
        case 40:
        case 35:
        {
            TREENODE temp = node->child;
            TREENODE temp1 = node->child->next;
            temp = generate_ast(node->child);
            temp->next = generate_ast(temp1);
            free(node);
            return temp;
        }
        case 4:
        {
            TREENODE temp = node->child->next->next;
            free(node->child->next->next->next);
            free(node->child->next);
            free(node->child);
            free(node);
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