#include <stdio.h>
#include "lexer.h"

Token get_next_token(FILE *input_file_pointer)
{
    Token t;
    t.token_name = ID;
    return t;
    while(True) {
        char ch;
        switch (state)
        {
        case 1:;
        ch = get_next_char(input_file_pointer);
        if (ch == '<') {
            state = 2;
        }
        else if (ch == '>') {
            state = 8;
        }
        //TODO: ALPHABETS
        else if (ch == '!') {
            state = 16;
        }
        else if (ch == '*') {
            state = 19;
        }
        else if (ch == ':') {
            state = 24;
        }
        else if (ch == '+') {
            state = 27;
        }
        else if (ch == 'EOF') {
            state = 28;
        }
        else if  (ch == '-')
        {
            state = 29;
        }
        //TODO: WHITESPACE
        else if (ch == '/')
        {
            state = 32;
        }
        else if (ch == '=')
        {
            state = 34;
        }
        else if (ch == '.')
        {
            state = 36;
        }
        //TODO: NUMERICS
        else if (ch == ']')
        {
            state = 39;
        }
        else if (ch == '[')
        {
            state = 40;
        }
        else if (ch == ')')
        {
            state = 41;
        }
        else if (ch == ',')
        {
            state = 42;
        }
        else if (ch == '(')
        {
            state = 43;
        }
        else if (ch == ';')
        {
            state = 44;
        }
    }
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
