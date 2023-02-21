#ifndef HASHMAP_H
#define HASHMAP_H
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

int hash(char *str);
void init_hashmap(hashmap map);
void insert(hashmap map, char *lexeme, valid_token_names value);
valid_token_names get(hashmap map, char *key);
void populate_hashmap();

#endif