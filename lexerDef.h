/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef LEXERDEF_H
#define LEXERDEF_H

#include <stdio.h>
// #define MAX_LEXEME_LENGTH 20
// #define BUFFER_SIZE 40

int BUFFER_SIZE;
int MAX_LEXEME_LENGTH;
int state;
int line_no;
int begin, forward;
int eof_reached;
char* buffer;
char* lexeme;
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
    WHILE,EOFILE
    // COMMENTMARK
} valid_token_names;

// Defining token and its structure
typedef struct token
{
    valid_token_names token_name;
    struct
        {
            char *str; // For accomodating '\0'
        } id;
    int numeric_value;
    double real_numeric_value;
    int line_no;
} Token;



#endif