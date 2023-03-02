/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef HASHMAPDEF_H
#define HASHMAPDEF_H
#include <stdio.h>
#include "lexer.h"
#include <stdbool.h>
#define HASHMAP_SIZE 100

typedef struct hashmap_node
{
    char lexeme[20];
    valid_token_names value;
    bool is_used;
} hashmap_node;

typedef hashmap_node hashmap[HASHMAP_SIZE];
hashmap lookup_table;


#endif