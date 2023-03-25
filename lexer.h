/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "lexerDef.h"
// #define MAX_LEXEME_LENGTH 20
// #define BUFFER_SIZE 40


FILE *getStream(FILE *fp);

// removes comments from the testcase file and creates a new file without comments
void removeComments(FILE *input_file_pointer, FILE *output_file_pointer);

// returns the next valid token from the file
Token get_next_token(FILE *input_file_pointer);

// returns the next character from the file
char get_next_char(FILE *input_file_pointer);

void retract(int n);
// initializes the lexer
void initialize_lexer_variables(FILE *input_file_pointer);

void update_buffer(FILE *input_file_pointer);
#endif