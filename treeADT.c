/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#include "treeADT.h"
#include "linkedlist.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>

void printParseTree(TREENODE  node, FILE* output_file) {

    if (node == NULL) return;

    if(node->child != NULL){
        printParseTree(node->child,output_file);
    }
    printf("%s and rule number : %d\n",node->name, node->rule_number+1);
    /*
    printf("Name : %-20s, lexeme : %-20s, line number : %-5d, valueIfNum : %-15d, valueIfRNum : %-15f \n", node->name, node->lexeme, node->line_number, node->valueIfNum, node->valueIfRNum);
    printf("%-20s ",node->lexeme);
    if(node->line_number<0)
        printf("%-11d ",node->line_number);
    else
        printf("%-10d ",node->line_number);
    if(strcmp(node->lexeme,"----"))
        printf("%-20s ",node->name);
    else
        printf("%-20s","");

    if(strcmp(node->name,"num")==0){
        printf("%-10d ",node->valueIfNum); 
    }
    else if(strcmp(node->name,"rnum")==0){
        printf("%-10f ",node->valueIfRNum);
    }
    else
    {
        printf("%-11s","");
    }
    if(strcmp(node->name,"S")==0)
        printf("ROOT%-17s","");
    else
        printf("%-20s ",node->parent->name);
    if(node->child!=NULL)
        printf("no%-10s","");
    else    
        printf("yes%-9s","");
    if(node->child!=NULL)
        printf("%-20s ",node->name);
    else
        printf("%-20s","");
    // printf("%-5f ",node->valueIfRNum);
    printf("%-10d ",node->line_number);
    printf("\n");*/

    //Writing to output file
    fprintf(output_file,"%-20s ",node->lexeme);
    if(node->line_number<0)
        fprintf(output_file,"%-11d ",node->line_number);
    else
        fprintf(output_file,"%-10d ",node->line_number);
    if(strcmp(node->lexeme,"----"))
        fprintf(output_file,"%-20s ",node->name);
    else
        fprintf(output_file,"%-20s","");

    if(strcmp(node->name,"num")==0){
        fprintf(output_file,"%-10d ",node->valueIfNum); 
    }
    else if(strcmp(node->name,"rnum")==0){
        fprintf(output_file,"%-10f ",node->valueIfRNum);
    }
    else
    {
        fprintf(output_file,"%-11s","");
    }
    if(strcmp(node->name,"S")==0)
        fprintf(output_file,"ROOT%-17s","");
    else
        fprintf(output_file,"%-20s ",node->parent->name);
    if(node->child!=NULL)
        fprintf(output_file,"no%-10s","");
    else    
        fprintf(output_file,"yes%-9s","");
    if(node->child!=NULL)
        fprintf(output_file,"%-20s ",node->name);
    else
        fprintf(output_file,"%-20s","");
    fprintf(output_file,"%-10d ",node->line_number);
    // printf("%-5f ",node->valueIfRNum);

    fprintf(output_file,"\n");

    if (node->child != NULL){
        TREENODE temp = node->child->next;
        while (temp != NULL){
            printParseTree(temp, output_file);
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
    temp->rule_number = -1;
    temp->valueIfRNum = 0.0;
    temp->child = NULL;
    temp->parent = parent;
    temp->next = NULL;
    return temp;
}

TREENODE createNewTreeNode2(){\
    TREENODE temp = (TREENODE)malloc(sizeof(tree_node));
    char* name = (char*)malloc(50*sizeof(char));
    char* lexeme = (char*)malloc(50*sizeof(char));
    temp->name = name;
    temp->lexeme = lexeme;
    strcpy(temp->name, "----");
    strcpy(temp->lexeme, "----");
    temp->line_number = -1;
    temp->valueIfNum = 0;
    temp->rule_number = -1;
    temp->valueIfRNum = 0.0;
    temp->child = NULL;
    temp->parent = NULL;
    temp->next = NULL;
    return temp;
}

TREENODE* insertRuleToTree(LIST grammar_rule, TREENODE parent, int grammar_rule_number){
    NODE temp = grammar_rule->head;
    int numberOfRHSElements=grammar_rule->count-1;
    parent->rule_number = grammar_rule_number;
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
        // printf("INSERTED INTO ============= %s\n",treenode->name);
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

void printTree(TREELIST tree, FILE *output_file){
    TREENODE head = tree->head;
    printParseTree(head, output_file);
}
