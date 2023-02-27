#include "treeADT.h"
#include "linkedlist.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

TREELIST createNewTree(){
    TREELIST temp = (TREELIST) malloc(sizeof(tree_list));
    temp->head = NULL;
    return temp;
}

TREENODE createNewTreeNode(TREENODE parent){
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
    TREENODE* treePointerArray = (TREENODE*) malloc(numberOfRHSElements*sizeof(TREENODE));
    int idx=0;
    temp = temp->next;
    //temp is at first node of RHS
    int count = 0;
    
    TREENODE treenode = createNewTreeNode(parent);
    treePointerArray[idx]=treenode;
    idx++;
    while(temp!=NULL){

        int type = getTypeOfData(temp->data);
        if(type==0){
            //epsilon
            treenode->name = "eps";
        }else{
            //non-terminal or terminal
            treenode->name = temp->data;
            // printf("Inside insertRuleToTree, temp->data = %s\n",temp->data);
        }

        if(count==0) parent->child = treenode;

        TREENODE next_of_treenode = createNewTreeNode(parent);
        treenode->next = next_of_treenode;
        treenode = next_of_treenode;

        treePointerArray[idx]=treenode;
        idx++;

        temp = temp->next;
        count++;
    }
    return treePointerArray;
}

void printTree(TREELIST tree){
    TREENODE head = tree->head;


}
