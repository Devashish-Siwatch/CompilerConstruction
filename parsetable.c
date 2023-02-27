#include <stdlib.h>
#include <stdio.h>
#include "parsetable.h"
#include <string.h>
#include "parser.h"

void init_parse_table()
{
    row_size = number_of_unique_nonterminals;
    column_size = number_of_unique_terminals;
    createParseTable(row_size, column_size);
}

void createParseTable(int row, int col)
{
    parse_table = (int **)malloc(sizeof(int) * (row));
    for (int i = 0; i < row; i++)
    {
        parse_table[i] = (int **)malloc(sizeof(int) * (col));
    }
}

int searchForRowIndex(char *data)
{
    for (int i = 0; i < MAX_NUMBER_OF_UNIQUE_NONTERMINALS; i++)
    {
        if (strcmp(data, arrayOfNonTerminals[i]) == 0)
        {
            return i;
        }
    }
}

int searchForColIndex(char *data)
{
    for (int i = 0; i < MAX_NUMBER_OF_UNIQUE_TERMINALS; i++)
    {
        if (strcmp(data, arrayOfTerminals[i]) == 0)
        {
            return i;
        }
    }
}
void fillParseTable()
{
    for (int i = 0; i < NUMBER_OF_RULES; i++)
    {
        NODE lhs = grammar[i]->head;
        int row = searchForRowIndex(lhs->data);
        NODE temp = lhs;
        char **first_set;
        int index = 0;

        while (temp->next != NULL)
        {
            temp = temp->next;
            if (strcmp(temp->data, "eps") == 0)
            {
                first_set = get_follow_set(lhs->data);
            }
            else if ((int)(temp->data[0]) >= 65 && (int)(temp->data[0]) <= 90)
            {

                char **first_of_temp = get_first_set(temp->data);
                // copy all non-eps from this first_of_temp into our first_set
                // check if first_of_temp has eps
                // if yes, then temp = temp->next
                // if no then break;
            }
            else
            {
                strcpy(first_set[index], temp->data); // check if this is not already present
                index++;
            }
        }

        for (int i = 0; i < MAX_NUMBER_OF_UNIQUE_NONTERMINALS; i++)
        {
            int temp = searchForColIndex(first_set[i]);
        }
    }
}

// int main()
// {

// }