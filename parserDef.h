/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/
#ifndef PARSERDEF_H
#define PARSERDEF_H
#include <stdio.h>
#include "lexer.h"
#define MAX_SIZE_TOKEN_NAME 100
#define NUMBER_OF_RULES 134
#define MAX_NUMBER_OF_UNIQUE_NONTERMINALS 100
#define MAX_LENGTH_OF_NONTERMINAL 50
#define MAX_NUMBER_OF_UNIQUE_TERMINALS 100
#define MAX_LENGTH_OF_TERMINAL 50
#define MAX_EXTRA_TERMINALS 10

char arrayOfNonTerminals[MAX_NUMBER_OF_UNIQUE_NONTERMINALS][MAX_LENGTH_OF_NONTERMINAL];
char arrayOfTerminals[MAX_NUMBER_OF_UNIQUE_TERMINALS][MAX_LENGTH_OF_TERMINAL];
int number_of_unique_nonterminals;
int number_of_unique_terminals;
char*** complete_first_sets;
char*** complete_follow_sets;
char*** complete_synch_sets;
int ** parse_table;
int row_size;
int column_size;




#endif