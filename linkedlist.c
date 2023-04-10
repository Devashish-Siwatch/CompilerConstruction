/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#include "stdbool.h"
#include <string.h>
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
bool data_exists(char* data, LIST list){
    NODE temp = list->head;
    while(temp!=NULL){
        if(strcmp(data,temp->data)==0){
            return true;
        }
        temp = temp->next;
    }
    return false;
}