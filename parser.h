#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "lexer.h"
#define MAX_SIZE_TOKEN_NAME 100
#define NUMBER_OF_RULES 127

typedef struct token_node
{
    char* element_name;
    struct token_node* next;
} Element;

typedef struct grammar_rule
{
    Element* lhs;
    Element* tail;
    Element* head;
} Grammar_Rule;
Grammar_Rule grammar[NUMBER_OF_RULES];

void init_parser();
void populate_grammar();
#endif