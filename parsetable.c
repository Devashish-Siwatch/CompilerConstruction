#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "parsetable.h"
#include<string.h>

void init_parse_table(){
    row_size = 0;
    column_size =0;
    createParseTable(row_size,column_size);
}
void createParseTable(int row,int col)
{
    parse_table=(int**)malloc(sizeof(int)*(row));
    for(int i=0;i<row;i++){
        parse_table[i] = (int**)malloc(sizeof(int)*(col));
    }
}

int main()
{

}