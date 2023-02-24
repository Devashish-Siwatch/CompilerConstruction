#include "stdbool.h"
#include <stdlib.h>
#include<stdio.h>
#include "linkedlist.h"

LIST createNewList()
{
    LIST new_list = malloc(sizeof(linked_list));
    new_list -> count = 0;
    new_list -> head = NULL;
    return new_list;
}
NODE createNewNode(char* data)
{
    NODE new_node = malloc(sizeof(node));
    new_node -> data = data;
    new_node -> next = NULL;
    return new_node;
}
void insertNodeIntoList(NODE node, LIST list)
{
    if(list -> count == 0 )
    {
        list -> head = node;
    }
    else
    {
        NODE temp = list -> head;
        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = node;
    }
    list -> count += 1;
    
}
void removeFirstNode(LIST list)
{
    if(list -> count !=0)
    {
        NODE temp = list -> head;
        list -> head = temp -> next;
        (list -> count)--;
        free(temp); 
    }
}
void display(LIST list)
{
    NODE temp = list -> head;
    while(temp != NULL)
    {
        printf("%s ", temp ->data);
        temp=temp->next;
    }
    printf("\n");
}
void destroyList(LIST list)
{
    NODE temp = list -> head;
    while(temp -> next != NULL)
    {
        NODE todelete =  temp;
        temp = temp -> next;
        free(todelete);
    }
    free(temp);
    free(list);
}