#include<stdio.h>
#include "linkedlist.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "parser.h"

void populate_grammer()
{
    FILE *grammar_input_file;
    grammar_input_file = fopen("grammar.txt", "r");
    char *str=(char*)(malloc(sizeof(char)*30));
    int index=0;
    char ch;
    int line_number = 0;
    while((ch = fgetc(grammar_input_file)) != EOF)
    {
        if(ch!=' ' && ch!='\n')
        {
            str[index] = ch;
            index++;
        }
        else if(ch ==' ')
        {
            char* a = (char*)malloc(sizeof(char) * (index + 1));
            for(int i=0 ; i<index ; i++)
            {
                a[i] = str[i];
            }
            a[index] = '\0';
            NODE element = createNewNode(a);
            insertNodeIntoList(element,grammar[line_number]);
            index = 0;
        }
        else
        {
            char* a = (char*)malloc(sizeof(char) * (index + 1));
            for(int i=0 ; i<index ; i++)
            {
                a[i] = str[i];
            }
            a[index] = '\0';
            NODE element = createNewNode(a);
            insertNodeIntoList(element,grammar[line_number]);
            index = 0;
            line_number++;
        }
    }
}
void display_rules()
{
    for(int i = 0; i < NUMBER_OF_RULES; ++i)
        display(grammar[i]);

}
int main()
{
    grammar = (linked_list**) malloc(sizeof(linked_list *) * NUMBER_OF_RULES);
    for(int i = 0; i < NUMBER_OF_RULES; ++i )
        grammar[i] = createNewList();
    populate_grammer();
    display_rules();
}