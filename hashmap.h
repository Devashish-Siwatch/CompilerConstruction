/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdio.h>
#include "lexer.h"
#include <stdbool.h>
#include "hashmapDef.h"



int hash(char *str);
void init_hashmap(hashmap map);
void insert(hashmap map, char *lexeme, valid_token_names value);
valid_token_names get(hashmap map, char *key, int size);
void populate_hashmap();

#endif