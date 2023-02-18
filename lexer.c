#include <stdio.h>
#include "lexer.h"

Token get_next_token()
{
    Token t;
    t.token_name = ID;
    return t;
}
char get_next_char()
{
    return 'a';
}
