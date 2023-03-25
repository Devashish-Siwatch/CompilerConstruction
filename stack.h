/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef STACK_H
#define STACK_H
#include "treeADT.h"
#include "stack_linked_list.h"
#include "stackDef.h"

Stack *newStack(); 
// Returns a pointer to a new stack. Returns NULL if memory allocation fails

int push(Stack *stack, char* name, TREENODE treepointer); 
// Pushes element onto stack. Returns false if memory allocation fails

STACKNODE top(Stack *stack); 
// Returns a pointer to the top element. Returns NULL if stack is empty

int pop(Stack *stack); 
// Pops the top element and returns true. Returns false if stack is empty

int isEmpty(Stack *stack);
// Returns true if stack is empty. Returns false otherwise

void freeStack(Stack *stack); 
// Frees all memory associated with stack
int isTopTerminal(STACK stack);
void pushRuleToStackandTree(STACK stack,LIST grammarRule,TREENODE parent);

STACK init_stack();
#endif