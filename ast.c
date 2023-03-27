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
    if(head==NULL)
        head=node;
    else
    {
        TREENODE temp=head;
        while(temp->child!=NULL)
        {
            temp=temp->child;
        }
        temp->child=node;
    }
}

TREENODE generate_ast(TREENODE node){
    if(getTypeOfData(node->name)==1){
        int rule_number = node->rule_number;
        if(rule_number==-1) printf("KUCH TO DIKKAT HAI\n");
                printf("%d ************\n ",rule_number);

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
        switch(rule_number){
            case 0:
                free(node->child->next);
                node->child->next = NULL;
                node->child = generate_ast(node->child);
                break;
            case 30:
            case 17:
                TREENODE temp = node->child;
                free(node);
                return generate_ast(temp);
            case 1:
                TREENODE moduleDeclarationsHead = (TREENODE) malloc(sizeof(tree_node));
                TREENODE otherModulesHead = (TREENODE) malloc(sizeof(tree_node));
                TREENODE otherModules2Head = (TREENODE) malloc(sizeof(tree_node));
                node->child->inh = moduleDeclarationsHead;
                node->child->next->inh = otherModulesHead;
                node->child->next->next->next->inh = otherModules2Head;
                generate_ast(node->child);
                generate_ast(node->child->next);

                node->child = moduleDeclarationsHead;
                node->child->next = otherModulesHead;
                node->child->next->next = generate_ast(node->child->next->next);
                generate_ast(node->child->next->next->next);
                node->child->next->next->next = otherModules2Head;
                return node->child;
            case 3:
            case 6:
            case 27:
                appendAtEnd(node->inh, NULL);
                free(node->child);
                // node->child = NULL;
                free(node);
                return NULL;
            case 8:
                for(int i=0 ; i<4 ; i++){
                    TREENODE temp = node->child->next;
                    free(node->child);
                    node->child = temp;
                }
                return generate_ast(node->child);
            case 25:
                TREENODE temp = node->child->next;
                free(node->child);
                free(temp->next);
                node->child = temp;
                TREENODE statementsHead = (TREENODE)malloc(sizeof(tree_node));
                temp->inh = statementsHead;
                generate_ast(temp);
                free(node);
                return statementsHead;
            case 26:
                appendAtEnd(node->inh, generate_ast(node->child));
                node->child->next->inh = node->inh;
                generate_ast(node->child->next);
                free(node);
                return NULL;
            case 104:
                TREENODE idList = node->child->next;
                TREENODE dType = idList->next->next;
                
        }
    }
}