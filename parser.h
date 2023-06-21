/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/
#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "lexer.h"
#include "parserDef.h"
#include "treeADTDef.h"
int getTypeOfData(char* str);
int searchForRowIndex(char* data);
int searchForColIndex(char* data);

int parser_complete_functionality(FILE* input_file, FILE* output_file);
int parse_tree_func(FILE *input_file);
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
void parse_tree_formation_ast_printing(FILE *input_file);
void parse_tree_formation_ast_formation(FILE *input_file);
void ast_formation_print_ast(FILE *input_file);
int total_tree_nodes(TREENODE head);
int get_memory_of_tree(TREENODE head);
void ast_formation_print_activation_records(FILE *input_file);
void ast_formation_print_all_errors(FILE* input_file);
void ast_formation_array_info_print(FILE *input_file);
#endif