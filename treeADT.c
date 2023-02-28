#include "treeADT.h"
#include "linkedlist.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

void printParseTree(TREENODE  node) {

    if (node == NULL) return;

    if(node->child != NULL){
        printParseTree(node->child);
    }
    
    printf("Name : %-20s, lexeme : %-20s, line number : %-5d, valueIfNum : %-15d, valueIfRNum : %-15f \n", node->name, node->lexeme, node->line_number, node->valueIfNum, node->valueIfRNum);

    if (node->child != NULL){
        TREENODE temp = node->child->next;
        while (temp != NULL){
            printParseTree(temp);
            temp = temp->next;
        }
    }
}

TREELIST createNewTree(){
    TREELIST temp = (TREELIST) malloc(sizeof(tree_list));
    temp->head = NULL;
    return temp;
}

TREENODE createNewTreeNode(TREENODE parent){\
    TREENODE temp = (TREENODE)malloc(sizeof(tree_node));
    char* name = (char*)malloc(50*sizeof(char));
    char* lexeme = (char*)malloc(50*sizeof(char));
    temp->name = name;
    temp->lexeme = lexeme;
    strcpy(temp->name, "----");
    strcpy(temp->lexeme, "----");
    temp->line_number = -1;
    temp->valueIfNum = 0;
    temp->valueIfRNum = 0.0;
    temp->child = NULL;
    temp->parent = parent;
    temp->next = NULL;
    return temp;
}

TREENODE* insertRuleToTree(LIST grammar_rule, TREENODE parent){
    NODE temp = grammar_rule->head;
    int numberOfRHSElements=grammar_rule->count-1;

    // int lengthOfRHS = 0;
    // NODE temp2 = temp;
    // while(temp!=NULL){
    //     temp = temp->next;
    //     lengthOfRHS++;
    // }
    TREENODE* treePointerArray = (TREENODE*) malloc(numberOfRHSElements*sizeof(TREENODE));
    for(int i=0 ; i<numberOfRHSElements ; i++){
        treePointerArray[i] = (TREENODE) malloc(sizeof(tree_node));
    }
    int idx=0;
    temp = temp->next;
    //temp is at first node of RHS
    int count = 0;
    TREENODE treenode = createNewTreeNode(parent);
    while(temp!=NULL){

        int type = getTypeOfData(temp->data);
        if(type==0){
            //epsilon
            treenode->name = "eps";
            // printf("Inside insertRuleToTree, name entered = eps\n");

        }else{
            //non-terminal or terminal
            treenode->name = temp->data;
            // printf("Inside insertRuleToTree, name entered = %s\n",temp->data);
        }

        if(count==0) parent->child = treenode;

        treePointerArray[idx]=treenode;
        printf("INSERTED INTO ============= %s\n",treenode->name);
        idx++;

        if(count==numberOfRHSElements-1) break;

        TREENODE next_of_treenode = createNewTreeNode(parent);
        treenode->next = next_of_treenode;
        treenode = next_of_treenode;

        temp = temp->next;
        count++;
    }
    return treePointerArray;
}

void printTree(TREELIST tree){
    TREENODE head = tree->head;
    printParseTree(head);
}
