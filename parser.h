#ifndef PARSER_H
#define PARSER_H
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

int getTypeOfData(char* str);
int searchForRowIndex(char* data);
int searchForColIndex(char* data);

int parser_complete_functionality(FILE* input_file, FILE* output_file);
void parser(FILE *input_file_pointer);
void fillParseTable();
void printParseTable();
void createParseTable(int row, int col);
void init_parse_table();
void display_rules();
void populate_grammer();
void init_t_array();
void init_nt_array();
char ***all_follow_sets();
char ***all_first_sets();
char ***all_synch_sets();
char** get_synch_set(char* nonterminal);
char **get_follow_set(char *nonterminal);
char **get_first_set(char *nonterminal);
int contains_epsilon(char **set);
void printParseTable();
int getNumberOfTerminals();
int getNumberOfNonTerminals();
int getTypeOfData(char *str);
int set_contains(char **arr, int arr_len, char *str);
void init_parser();
char *convertToLowercase(char *str);


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