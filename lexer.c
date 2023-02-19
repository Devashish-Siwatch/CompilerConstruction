#include <stdio.h>
#include "lexer.h"

Token get_next_token(FILE *input_file_pointer)
{
    Token t;
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
                else if (isalpha(ch)) {
                    state = 14;
                }
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
                else if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
                {
                    if (ch == '\n')
                    {
                        line_no++;
                    }
                    state = 30;
                }
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
                else if (isdigit(c))
                {
                    state = 45;
                }
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
            case 2:;
                ch = get_next_char(input_file_pointer);
                if (ch == '<') {
                    state = 3;
                }
                else if (ch == '=') {
                    state = 6;
                }
                else {
                    state = 7;
                }
            case 3:;
                ch = get_next_char(input_file_pointer);
                if (ch == '<') {
                    state = 4;
                }
                else {
                    state = 5;
                }
            case 4:;
                t.token_name = DRIVERDEF;
                t.line_no = line_no;
                state = 0;
                return t;
            case 5:;
                retract(input_file_pointer, 1);
                t.token_name = DEF;
                t.line_no = line_no;
                state = 0;
                return t;
            case 6:;
                t.token_name = LE;
                t.line_no = line_no;
                state = 0;
                return t;
            case 7:; 
                retract(input_file_pointer, 1);
                t.token_name = LT;
                t.line_no = line_no;
                state = 0;
                return t;
            case 8:;
                ch = get_next_char(input_file_pointer);
                if (ch == '>') {
                    state = 9;
                }
                else if (ch == '=') {
                    state = 12;
                }
                else {
                    state = 13;
                }
            case 9:;
                ch = get_next_char(input_file_pointer);
                if (ch == '>') {
                    state = 10;
                }
                else {
                    state = 11;
                }
            case 10:;
                t.token_name = DRIVERENDDEF;
                t.line_no = line_no;
                state = 0;
                return t;
            case 11:;
                retract(input_file_pointer, 1);
                t.token_name = ENDDEF;
                t.line_no = line_no;
                state = 0;
                return t;
            case 12:;
                t.token_name = GE;
                t.line_no = line_no;
                state = 0;
                return t;
            case 13:;
                retract(input_file_pointer, 1);
                t.token_name = GT;
                t.line_no = line_no;
                state = 0;
                return t;
            case 14:;
                ch = get_next_char(input_file_pointer);
                if (isalpha(ch) || isdigit(ch)) {
                    state = 14;
                }
                else {
                    state = 15;
                }
            case 15:;
                // TODO: ALPHABET HANDLING?
                continue;
            case 16:;
                ch = get_next_char(input_file_pointer);
                if (ch == '=') {
                    state = 17;
                }
                else {
                    state = 18;
                }
            case 17:;
                t.token_name = NE;
                t.line_no = line_no;
                state = 0;
                return t;
            case 18:;
            // TODO: error
            case 19:;
                ch = get_next_char(input_file_pointer);
                if (ch == '*') {
                    state = 20;
                }
                else {
                    state = 23;
                }
            case 20:;
                ch = get_next_char(input_file_pointer);
                if (ch == '*') {
                    state = 21;
                }
                else {
                    state = 20;
                }
            case 21:;
                ch = get_next_char(input_file_pointer);
                if (ch == '*') {
                    state = 22;
                }
                else {
                    state = 20;
                }
            case 22:;
            //TODO: Comments?
            case 23:;
                retract(input_file_pointer, 1);
                t.token_name = MUL;
                t.line_no = line_no;
                state = 0;
                return t;
            case 24:;
                ch = get_next_char(input_file_pointer);
                if (ch == '=') {
                    state = 26;
                }
                else {
                    state = 25;
                }
            case 25:;
                retract(input_file_pointer, 1);
                t.token_name = COLON;
                t.line_no = line_no;
                state = 0;
                return t;
            case 26:;
                t.token_name = ASSIGNOP;
                t.line_no = line_no;
                state = 0;
                return t;
            case 27:;
                t.token_name = PLUS;
                t.line_no = line_no;
                state = 0;
                return t;
            case 28:;
                t.token_name = EOF;
                t.line_no = line_no;
                state = 0;
                return t;
            case 29:;
                t.token_name = MINUS;
                t.line_no = line_no;
                state = 0;
                return t;
            case 30:;
                ch = get_next_char(input_file_pointer);
                if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
                    if (ch == '\n') {
                        line_no++;
                    }
                    state = 30;
                }
                else {
                    state = 31;
                }
            case 31:;
                retract(input_file_pointer, 1);
                state = 0;
            case 32:;
                t.token_name = DIV;
                t.line_no = line_no;
                state = 0;
                return t;
            case 34:;
                ch = get_next_char(input_file_pointer);
                if (ch == '=') {
                    state = 35;
                }
                else {
                    state = 33;
                }
            case 33:;
                //TODO: error
            case 35:;
                t.token_name = EQ;
                t.line_no = line_no;
                state = 0;
                return t;
            case 36:;
                ch = get_next_char(input_file_pointer);
                if (ch == '.') {
                    state = 38;
                }
                else {
                    state = 37;
                }
            case 37:;
                //TODO: error
            case 38:;
                t.token_name = RANGEOP;
                t.line_no = line_no;
                state = 0;
                return t;
            case 39:;
                t.token_name = SQBC;
                t.line_no = line_no;
                state = 0;
                return t;
            case 40:;
                t.token_name = SQBO;
                t.line_no = line_no;
                state = 0;
                return t;
            case 41:;
                t.token_name = BC;
                t.line_no = line_no;
                state = 0;
                return t;
            case 42:;
                t.token_name = COMMA;
                t.line_no = line_no;
                state = 0;
                return t;
            case 43:;
                t.token_name = BO;
                t.line_no = line_no;
                state = 0;
                return t;
            case 44:;
                t.token_name = SEMICOL;
                t.line_no = line_no;
                state = 0;
                return t;
            case 45:;
                ch = get_next_char(input_file_pointer);
                if (isdigit(ch)) {
                    state = 45;
                }
                else if (ch == '.') {
                    state = 48;
                }
                else {
                    state = 46;
                }
            case 46:;
                retract(input_file_pointer, 1);
                t.token_name = NUM;
                t.line_no = line_no;
                t.numeric_value = atoi(buffer);
                state = 0;
                return t;
            case 48:;
                ch = get_next_char(input_file_pointer);
                if (isdigit(ch)) {
                    state = 50;
                }
                else if (ch == '.') {
                    state = 47;
                }
                else {
                    state = 49;
                }
            case 47:;
                retract(input_file_pointer, 2);
                t.token_name = NUM;
                t.line_no = line_no;
                t.numeric_value = atoi(buffer);
                state = 0;
                return t;
            case 49:;
                //TODO: error
            case 50:;
                ch = get_next_char(input_file_pointer);
                if (isdigit(ch)) {
                    state = 50;
                }
                else if (ch == 'e' || ch == 'E') {
                    state = 52;
                }
                else {
                    state = 51;
                }
            case 51:;
                retract(input_file_pointer, 1);
                t.token_name = RNUM;
                t.line_no = line_no;
                t.real_value = atof(buffer);
                state = 0;
                return t;
            case 52:;
                ch = get_next_char(input_file_pointer);
                if (ch == '+' || ch == '-') {
                    state = 54;
                }
                else if (isdigit(ch)) {
                    state = 56;
                }
                else {
                    state = 53;
                }
            case 53:;
                //TODO: error
            case 54:;
                ch = get_next_char(input_file_pointer);
                if (isdigit(ch)) {
                    state = 56;
                }
                else {
                    state = 55;
                }
            case 55:;
                //TODO: error
            case 56:;
                ch = get_next_char(input_file_pointer);
                if (isdigit(ch)) {
                    state = 56;
                }
                else {
                    state = 57;
                }
            case 57:;
                retract(input_file_pointer, 1);
                t.token_name = RNUM;
                t.line_no = line_no;
                t.real_value = atof(buffer);
                state = 0;
                return t;
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

FILE *retract(FILE *input_file_pointer, int n) {
    fseek(input_file_pointer, n, SEEK_CUR);
    return input_file_pointer;
}