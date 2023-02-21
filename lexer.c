#include <stdio.h>
#include "lexer.h"
#include "hashmap.h"
// initializing the lexer variables
void initialize_lexer_variables(FILE *input_file_pointer)
{
    state = 1;
    eof_reached = 0;
    line_no = 1;
    begin = 0;
    forward = 0;
    init_hashmap(lookup_table);
    populate_hashmap(lookup_table);
    update_buffer(input_file_pointer);
}

// updating the buffer's alternating halves with the contents of the file
void update_buffer(FILE *input_file_pointer)
{
    int num;
    if (forward == BUFFER_SIZE)
    {
        forward = 0;
    }
    num = fread(&buffer[forward], 1, BUFFER_SIZE / 2, input_file_pointer);
    // printf("buffer contents: %s", buffer);
    // printf("num: %d", num);
    if (num != BUFFER_SIZE / 2)
        buffer[num + forward + 1] = EOF;
}
Token get_next_token(FILE *input_file_pointer)
{

    Token t;
    while (eof_reached == 0)
    {
        char ch;
        switch (state)
        {
        case 1:;
            ch = get_next_char(input_file_pointer);
            if (ch == '<')
            {
                state = 2;
            }
            else if (ch == '>')
            {
                state = 8;
            }
            else if (isalpha(ch))
            {
                state = 14;
            }
            else if (ch == '!')
            {
                state = 16;
            }
            else if (ch == '*')
            {
                state = 19;
            }
            else if (ch == ':')
            {
                state = 24;
            }
            else if (ch == '+')
            {
                state = 27;
            }
            else if (ch == EOF)
            {
                // printf("EOF reached");
                state = 28;
            }
            else if (ch == '-')
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
            else if (isdigit(ch))
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
            break;
        case 2:;
            ch = get_next_char(input_file_pointer);
            if (ch == '<')
            {
                state = 3;
            }
            else if (ch == '=')
            {
                state = 6;
            }
            else
            {
                state = 7;
            }
            break;
        case 3:;
            ch = get_next_char(input_file_pointer);
            if (ch == '<')
            {
                state = 4;
            }
            else
            {
                state = 5;
            }
            break;
        case 4:;
            t.token_name = DRIVERDEF;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 5:;
            retract(1);
            t.token_name = DEF;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 6:;
            t.token_name = LE;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 7:;
            retract(1);
            t.token_name = LT;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 8:;
            ch = get_next_char(input_file_pointer);
            if (ch == '>')
            {
                state = 9;
            }
            else if (ch == '=')
            {
                state = 12;
            }
            else
            {
                state = 13;
            }
            break;
        case 9:;
            ch = get_next_char(input_file_pointer);
            if (ch == '>')
            {
                state = 10;
            }
            else
            {
                state = 11;
            }
            break;
        case 10:;
            t.token_name = DRIVERENDDEF;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 11:;
            retract(1);
            t.token_name = ENDDEF;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 12:;
            t.token_name = GE;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 13:;
            retract(1);
            t.token_name = GT;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 14:;
            ch = get_next_char(input_file_pointer);
            if (isalpha(ch) || isdigit(ch))
            {
                state = 14;
            }
            else
            {
                state = 15;
            }
            break;
        case 15:;
            retract(1);
            printf("inside 15: %s", lexeme);
            if ((t.token_name = get(lookup_table, lexeme)) != -1)
            {
                t.line_no = line_no;
                state = 1;
                forward++;
                begin = forward;
                return t;
            }
            else
            {
                t.token_name = ID;
                t.line_no = line_no;
                state = 1;
                forward++;
                begin = forward;
                return t;
            }
            break;
        case 16:;
            ch = get_next_char(input_file_pointer);
            if (ch == '=')
            {
                state = 17;
            }
            else
            {
                state = 18;
            }
            break;
        case 17:;
            t.token_name = NE;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 18:;
            // TODO: error
            break;
        case 19:;
            ch = get_next_char(input_file_pointer);
            if (ch == '*')
            {
                state = 20;
            }
            else
            {
                state = 23;
            }
            break;
        case 20:;
            ch = get_next_char(input_file_pointer);
            if (ch == '*')
            {
                state = 21;
            }
            else
            {
                state = 20;
            }
            break;
        case 21:;
            ch = get_next_char(input_file_pointer);
            if (ch == '*')
            {
                state = 22;
            }
            else
            {
                state = 20;
            }
            break;
        case 22:;
            state = 1;
            break;
        case 23:;
            retract(1);
            t.token_name = MUL;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 24:;
            ch = get_next_char(input_file_pointer);
            if (ch == '=')
            {
                state = 26;
            }
            else
            {
                state = 25;
            }
            break;
        case 25:;
            retract(1);
            t.token_name = COLON;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 26:;
            t.token_name = ASSIGNOP;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 27:;
            t.token_name = PLUS;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 28:;
            t.token_name = EOF;
            t.line_no = line_no;
            eof_reached = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 29:;
            t.token_name = MINUS;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 30:;
            ch = get_next_char(input_file_pointer);
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
            {
                if (ch == '\n')
                {
                    line_no++;
                }
                state = 30;
            }
            else
            {
                state = 31;
            }
            break;
        case 31:;
            retract(1);
            state = 1;
            break;
        case 32:;
            t.token_name = DIV;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 34:;
            ch = get_next_char(input_file_pointer);
            if (ch == '=')
            {
                state = 35;
            }
            else
            {
                state = 33;
            }
            break;
        case 33:;
            // TODO: error
            break;
        case 35:;
            t.token_name = EQ;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 36:;
            ch = get_next_char(input_file_pointer);
            if (ch == '.')
            {
                state = 38;
            }
            else
            {
                state = 37;
            }
            break;
        case 37:;
            // TODO: error
            break;
        case 38:;
            t.token_name = RANGEOP;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 39:;
            t.token_name = SQBC;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 40:;
            t.token_name = SQBO;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 41:;
            t.token_name = BC;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 42:;
            t.token_name = COMMA;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 43:;
            t.token_name = BO;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 44:;
            t.token_name = SEMICOL;
            t.line_no = line_no;
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 45:;
            ch = get_next_char(input_file_pointer);
            if (isdigit(ch))
            {
                state = 45;
            }
            else if (ch == '.')
            {
                state = 48;
            }
            else
            {
                state = 46;
            }
            break;
        case 46:;
            retract(1);
            t.token_name = NUM;
            t.line_no = line_no;
            t.numeric_value = atoi(buffer);
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 48:;
            ch = get_next_char(input_file_pointer);
            if (isdigit(ch))
            {
                state = 50;
            }
            else if (ch == '.')
            {
                state = 47;
            }
            else
            {
                state = 49;
            }
            break;
        case 47:;
            retract(2);
            t.token_name = NUM;
            t.line_no = line_no;
            t.numeric_value = atoi(buffer);
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 49:;
            // TODO: error
            break;
        case 50:;
            ch = get_next_char(input_file_pointer);
            if (isdigit(ch))
            {
                state = 50;
            }
            else if (ch == 'e' || ch == 'E')
            {
                state = 52;
            }
            else
            {
                state = 51;
            }
            break;
        case 51:;
            retract(1);
            t.token_name = RNUM;
            t.line_no = line_no;
            t.real_numeric_value = atof(buffer);
            state = 1;
            forward++;
            begin = forward;
            return t;
            break;
        case 52:;
            ch = get_next_char(input_file_pointer);
            if (ch == '+' || ch == '-')
            {
                state = 54;
            }
            else if (isdigit(ch))
            {
                state = 56;
            }
            else
            {
                state = 53;
            }
            break;
        case 53:;
            // TODO: error
            break;
        case 54:;
            ch = get_next_char(input_file_pointer);
            if (isdigit(ch))
            {
                state = 56;
            }
            else
            {
                state = 55;
            }
            break;
        case 55:;
            // TODO: error
            break;
        case 56:;
            ch = get_next_char(input_file_pointer);
            if (isdigit(ch))
            {
                state = 56;
            }
            else
            {
                state = 57;
            }
            break;
        case 57:;
            retract(1);
            t.token_name = RNUM;
            t.line_no = line_no;
            t.real_numeric_value = atof(buffer);
            state = 1;
            forward++;
            begin = forward;
            return t;
        }
    }
}

// getting the next character from the buffer and updating the buffer if necessary
char get_next_char(FILE *input_file_pointer)
{
    // if updating the buffer in case we reach the either end of our twin buffer
    if ((forward == BUFFER_SIZE || forward == BUFFER_SIZE / 2))
    {
        update_buffer(input_file_pointer);
    }
    char c = buffer[forward];
    int lex_index = forward - begin;
    // in case the forward pointer has reached the end of the buffer and is in the first half of the buffer
    if (lex_index < 0)
    {
        lex_index += BUFFER_SIZE;
    }
    if (lex_index < MAX_LEXEME_LENGTH)
        lexeme[lex_index] = c;
    forward++;
    return c;
}

void retract(int n)
{
    forward -= n;
    if (forward < 0)
        forward += BUFFER_SIZE;
}