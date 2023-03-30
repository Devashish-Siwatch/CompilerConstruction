#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treeADT.h"

populate_tables(TREENODE root){
    if (root == NULL)
    {
        // printf("Currently at %s",head->name);
        return;
    }else{
        if(strcmp(root->name,"DRIVER_MODULE_STMTS")==0){
            
        }
    }
    populate_tables(root->child);
    populate_tables(root->next);
}
