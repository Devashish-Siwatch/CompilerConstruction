#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "lexer.h"
#define MAX_SIZE_TOKEN_NAME 100
#define NUMBER_OF_RULES 127
#define MAX_NUMBER_OF_UNIQUE_NONTERMINALS 100
#define MAX_LENGTH_OF_NONTERMINAL 50

char arrayOfNonTerminals[MAX_NUMBER_OF_UNIQUE_NONTERMINALS][MAX_LENGTH_OF_NONTERMINAL];
int number_of_unique_nonterminals;

// typedef struct token_node
// {
//     char* element_name;
//     struct token_node* next;
// } Element;

// typedef struct grammar_rule
// {
//     Element* lhs;
//     Element* tail;
//     Element* head;
// } Grammar_Rule;


// Element** grammar;

// void init_parser();
// void populate_grammar();
#endif