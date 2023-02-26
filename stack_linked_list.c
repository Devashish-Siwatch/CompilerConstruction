#include "treeADT.h"
#include "stdbool.h"
#include <stdlib.h>
#include "stack_linked_list.h"
STACKLIST createNewStackList()
{
    STACKLIST new_list = malloc(sizeof(stack_linked_list));
    new_list -> count = 0;
    new_list -> head = NULL;
    return new_list;
}
STACKNODE createNewStackNode(char* name, TREENODE pointer)
{
    STACKNODE new_node = malloc(sizeof(stack_node));
    new_node -> name = name;
    new_node -> treepointer = pointer;
    new_node -> next = NULL;
    return new_node;
}
void insertStackNodeIntoList(STACKNODE node, STACKLIST list)
{
    node -> next = list -> head;
    list -> head = node;
    (list -> count)++; 
}
void removeFirstStackNode(STACKLIST list)
{
    if(list -> count !=0)
    {
        STACKNODE temp = list -> head;
        // printf("______________________________________Popped %s\n",temp->name);
        list -> head = temp -> next;
        (list -> count)--;
        free(temp); 
    }
}
void destroyStackList(STACKLIST list)
{
    STACKNODE temp = list -> head;
    while(temp -> next != NULL)
    {
        STACKNODE todelete =  temp;
        temp = temp -> next;
        free(todelete);
    }
    free(temp);
    free(list);
}