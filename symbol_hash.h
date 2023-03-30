#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"
#include "treeADTDef.h"
#include "symbol_hash_def.h"

int symbol_hash(char *str);
void init_symbolhashmap(symbol_table_hash_map map);
void symbol_insert(symbol_table_hash_map map, char *key, SYMBOL_TABLE_VALUE type);
SYMBOL_TABLE_VALUE symbol_table_get(symbol_table_hash_map map, char *key, int size);
void print_symbol_table(SYMBOL_TABLE_WRAPPER wrapper);
void print_symbol_table_value(SYMBOL_TABLE_VALUE value);

