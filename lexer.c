#include <stdio.h>
#include "lexer.h"

Token get_next_token(FILE *input_file_pointer)
{
    Token t;
    t.token_name = ID;
    return t;
}
char get_next_char(FILE *input_file_pointer)
{
    char ch;
    // check if the file has reached EOF
    if ((ch = fgetc(input_file_pointer)) != EOF)
    {
        return ch;
    }
    else
    {
        return EOF;
    }
}
