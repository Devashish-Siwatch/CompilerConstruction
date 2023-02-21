#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

int hash(char *str)
{
    int hash = 0;
    int c;
    while (c = *str++)
        hash = (hash*97 + c)%100;
    return hash;
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
        index = (index + 1) % 100;
    }
    map[index].is_used = true;
    strcpy(map[index].lexeme, key);
    map[index].value = value;
    printf("String : %s, hash value : %d\n",key,index);
}

valid_token_names get(hashmap map, char *key, int size)
{   
    printf("\ninside get, size is %d",size);
    char temp[size];
    // strncpy(temp,key,sizeof(temp));
    temp[size] = '\0';
    for(int i=0 ; i<size ; i++){
        temp[i] = key[i];
    }
    printf("\n***%s***", temp);
    int index = hash(temp);
    while (map[index].is_used)
    {
        if (strcmp(map[index].lexeme, temp) == 0){
            printf("\nSTRING BEING SEARCHED : %s, SEARCH RESULT : %d",temp,index);
            return map[index].value;
        }
        index = (index + 1) % 100;
    }
    return -1;
}

void populate_hashmap(hashmap map)
{
    insert(map, "AND", AND);
    insert(map, "OR", OR);
    insert(map, "true", TRUE);
    insert(map, "false", FALSE);
    insert(map, "integer", INTEGER);
    insert(map, "real", REAL);
    insert(map, "boolean", BOOLEAN);
    insert(map, "of", OF);
    insert(map, "array", ARRAY);
    insert(map, "start", START);
    insert(map, "end", END);
    insert(map, "declare", DECLARE);
    insert(map, "module", MODULE);
    insert(map, "driver", DRIVER);
    insert(map, "program", PROGRAM);
    insert(map, "get_value", GET_VALUE);
    insert(map, "print", PRINT);
    insert(map, "use", USE);
    insert(map, "with", WITH);
    insert(map, "parameters", PARAMETERS);
    insert(map, "takes", TAKES);
    insert(map, "input", INPUT);
    insert(map, "returns", RETURNS);
    insert(map, "for", FOR);
    insert(map, "in", IN);
    insert(map, "switch", SWITCH);
    insert(map, "case", CASE);
    insert(map, "break", BREAK);
    insert(map, "default", DEFAULT);
    insert(map, "while", WHILE);
}
// int main()
// {
//     hashmap map;
//     init_hashmap(map);
//     insert(map, "ID", ID);
//     insert(map, "NUM", NUM);
//     insert(map, "RNUM", RNUM);
//     insert(map, "AND", AND);
//     insert(map, "OR", OR);
//     insert(map, "TRUE", TRUE);
//     insert(map, "FALSE", FALSE);
//     valid_token_names tok = get(map, "ID");
//     if (tok == -1)
//         printf("Not found\n");
//     else if (tok == ID)
//         printf("Found\n");
//     else
//         printf("error\n");

//     tok = get(map, "TRUE");
//     if (tok == -1)
//         printf("Not found\n");
//     else if (tok == FALSE)
//         printf("Found\n");
//     else
//         printf("error\n");
//     return 0;
// }