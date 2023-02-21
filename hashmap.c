#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

int hash(char *str)
{
    int hash = 0;
    int c;
    while (c = *str++)
        hash = hash*97 + c;
    return hash%100;
}

void init_hashmap(hashmap map)
{
    for (int i = 0; i < 100; i++)
    {
        map[i].is_used = false;
        map[i].value = ID;
    }
}

void insert(hashmap map, char *key, valid_token_names value)
{
    int index = hash(key);
    while (map[index].is_used)
    {
        index = (index + 1)%100;
    }
    map[index].is_used = true;
    strcpy(map[index].lexeme, key);
    map[index].value = value;
}

valid_token_names get(hashmap map, char *key)
{
    int index = hash(key);
    while (map[index].is_used)
    {
        if (strcmp(map[index].lexeme, key) == 0)
            return map[index].value;
        index = (index + 1)%100;
    }
    return -1;
}


int main()
{
    hashmap map;
    init_hashmap(map);
    insert(map, "ID", ID);
    insert(map, "NUM", NUM);
    insert(map, "RNUM", RNUM);
    insert(map, "AND", AND);
    insert(map, "OR", OR);
    insert(map, "TRUE", TRUE);
    insert(map, "FALSE", FALSE);
    valid_token_names tok = get(map, "ID");
    if (tok == -1)
        printf("Not found\n");
    else if (tok == ID)
        printf("Found\n");
    else 
        printf("error\n");

    tok = get(map, "TRUE");
    if (tok == -1)
        printf("Not found\n");
    else if (tok == FALSE)
        printf("Found\n");
    else 
        printf("error\n");
    return 0;
}