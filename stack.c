#include "stack.h"
#include "parser.h"
#include"treeADT.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>
#include "stack_linked_list.h"
#define STACK_SIZE 10000

struct Stack
{
    STACKLIST list;
};



Stack *newStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if(s != NULL)
        s -> list = createNewStackList();
    return s;
}

int push(Stack *s, char* name, TREENODE treepointer)
{
    if((s -> list) -> count == STACK_SIZE)
        return 0;
    STACKNODE new_node = createNewStackNode(name, treepointer);
    if(new_node == NULL)
        return 0;
    insertStackNodeIntoList(new_node, s -> list);
    return 1;
}

STACKNODE top(Stack *s)
{
    if((s -> list) -> count == 0)
        return NULL;
    else
        return s->list->head;
}

int pop(Stack *s)
{
    if((s -> list) -> count == 0)
        return 0;
    removeFirstStackNode(s -> list);
    return 1;
}

int isEmpty(Stack *s)
{
    if((s -> list) -> count == 0)
        return 1;
    else
        return 0;
}

void freeStack(Stack *s)
{
    destroyStackList(s -> list);
    free(s);
}

int isTopTerminal(STACK stack){
    STACKNODE top_of_stack = top(stack);
    if(getTypeOfData(top_of_stack->name)==2) return 1;  //returns 1 for terminal
    else return 0;                                      //returns 0 for non-terminal
}

void pushRuleToStackandTree(STACK stack,LIST grammarRule,TREENODE parent){
    //temp is at first element of rhs of the rule
    NODE temp = grammarRule->head->next;
    TREENODE* arrayOfTreeNodePointers = insertRuleToTree(grammarRule,parent);
    int rhsLength = grammarRule->count-1;

    pop(stack);
    if(strcmp("eps",arrayOfTreeNodePointers[0]->name)==0) return;

    // printf("PUSHING INTO STACK\n");
    for(int i=rhsLength-1 ; i>=0 ; i--){
        push(stack,arrayOfTreeNodePointers[i]->name,arrayOfTreeNodePointers[i]);
        // printf("______________________________________Pushed %s\n",arrayOfTreeNodePointers[i]->name);
    }

}

STACK init_stack(){
    return newStack();
}
