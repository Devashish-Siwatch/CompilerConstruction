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
#define MAX_LEXEME_LENGTH 20
#define BUFFER_SIZE 40

int state;
int line_no;
int begin, forward;
int eof_reached;
char buffer[BUFFER_SIZE];
char lexeme[MAX_LEXEME_LENGTH];
int lastUpdatedHalf;
int lexemeSize;
int sizeErrorDetected;
// List of valid token names in the language
typedef enum valid_token_names
{
    ID,
    NUM,
    RNUM,
    AND,
    OR,
    TRUE,
    FALSE,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    DEF,
    ENDDEF,
    DRIVERDEF,
    DRIVERENDDEF,
    COLON,
    RANGEOP,
    SEMICOL,
    COMMA,
    ASSIGNOP,
    SQBO,
    SQBC,
    BO,
    BC,
    INTEGER,
    REAL,
    BOOLEAN,
    OF,
    ARRAY,
    START,
    END,
    DECLARE,
    MODULE,
    DRIVER,
    PROGRAM,
    GET_VALUE,
    PRINT,
    USE,
    WITH,
    PARAMETERS,
    TAKES,
    INPUT,
    RETURNS,
    FOR,
    IN,
    SWITCH,
    CASE,
    BREAK,
    DEFAULT,
    WHILE,
    // COMMENTMARK
} valid_token_names;

// Defining token and its structure
typedef struct token
{
    valid_token_names token_name;
    union
    {
        struct
        {
            char str[MAX_LEXEME_LENGTH + 1]; // For accomodating '\0'
        } id;
        int numeric_value;
        double real_numeric_value;
    };
    int line_no;
} Token;
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