#include<stdio.h>
#include "linkedlist.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "parser.h"
#include<string.h>

int getNumberOfNonTerminals(){
    int maxlen = 0;
    for(int i=0 ; i<NUMBER_OF_RULES ; i++){
        int found = 0;
        char* lhs = grammar[i]->head->data;
        // printf("LHS : %s\n",lhs);
        //iterating for lhs over the set of unique nt
        for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; j++){
            if(arrayOfNonTerminals[j][0]!='-'){
                if(strcmp(lhs,arrayOfNonTerminals[j])==0){
                    found = 1;
                    // printf("For nonterminal : %s, it was found at index %d",lhs,j);
                    break;
                }
            }else{
                if(found==0){
                    strcpy(arrayOfNonTerminals[j],lhs);
                    // printf("For nonterminal : %s, it was added at index %d",lhs,j);
                    maxlen++;
                    break;
                }
            }
        }
    }
    number_of_unique_nonterminals = maxlen;
    return maxlen;
}

int contains_epsilon(char ** set){
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
        if(strcmp(set[i],"eps")==0){
            return 1;
        }
    }
    return 0;
}

char ** get_first_set(char* nonterminal){
    char **first = (char**)malloc(MAX_NUMBER_OF_UNIQUE_NONTERMINALS*sizeof(char*));
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
        first[i] = (char*) malloc(sizeof(char)*MAX_LENGTH_OF_NONTERMINAL);
    }
    int index = 0;
    for(int i=0 ; i<NUMBER_OF_RULES ; i++){
        // printf("here for %s\n",nonterminal);
        if(strcmp(nonterminal,grammar[i]->head->data)==0){
            NODE temp = grammar[i]->head->next;
            if(strcmp(temp->data,"eps")==0){
                // printf("Case 1\n");
                first[index] = "eps";
                index++;
            }else if(temp->data[0]>='a' && temp->data[0]<='z'){
                // printf("Case 2\n");
                first[index] = temp->data;
                index++;
            }else{
                // printf("Case 3\n");
                while(true){
                    char** first_of_temp = get_first_set(temp->data);
                    //copy all non-eps from fot to first
                    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
                        if(strcmp(first_of_temp[i],"-1")==0) break;
                        if(strcmp(first_of_temp[i],"eps")!=0){
                            first[index] = first_of_temp[i];
                            // printf("copied %s into index : %d of first of %s\n",first_of_temp[i],index,nonterminal);
                            index++;
                        }
                    }
                    //copying done
                    if(contains_epsilon(first_of_temp)==1){
                        if(temp->next==NULL){
                            //add eps to first
                            first[index] = "eps";
                            index++;
                            break;
                        }else{
                            temp = temp->next;
                        }
                    }else{
                        break;
                    }
                }
            }            
        }
    }
    first[index] = "-1";
    // printf("returned for %s\n",nonterminal);
    // for(int i=0 ; i<50 ; i++){
    //     printf("%s\n",first[i]);
    //     if(strcmp(first[i],"-1")==0) break;
    // }
    return first;
}

char *** all_first_sets(){

    char ***first_of_all = (char***)malloc(number_of_unique_nonterminals*sizeof(char**));
    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        first_of_all[i] = (char**) malloc(sizeof(char*)*MAX_NUMBER_OF_UNIQUE_NONTERMINALS);
        for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_NONTERMINALS; j++){
            first_of_all[i][j] = (char*) malloc(sizeof(char)*MAX_LENGTH_OF_NONTERMINAL);
        }
    }

    printf("malloc done\n");

    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        //length of arrayOfNonTerminals is more but we stop at the correct length
        first_of_all[i] = get_first_set(arrayOfNonTerminals[i]);
        // printf("PRINTING FIRST OF %s\n",arrayOfNonTerminals[i]);
        // for(int j=0 ; j<NUMBER_OF_UNIQUE_NONTERMINALS; j++){
            // printf("%s\n",first_of_all[i][j]);
        //     if(strcmp(first_of_all[i][j],"-1")==0) break;
        // }
    }

    return first_of_all;
}

void init_nt_array(){
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
        arrayOfNonTerminals[i][0]='-';
    }
    getNumberOfNonTerminals();
}

void populate_grammer()
{
    FILE *grammar_input_file;
    grammar_input_file = fopen("grammar.txt", "r");
    char *str=(char*)(malloc(sizeof(char)*30));
    int index=0;
    char ch;
    int line_number = 0;
    while((ch = fgetc(grammar_input_file)) != EOF)
    {
        if(ch!=' ' && ch!='\n')
        {
            str[index] = ch;
            index++;
        }
        else if(ch ==' ')
        {
            char* a = (char*)malloc(sizeof(char) * (index + 1));
            for(int i=0 ; i<index ; i++)
            {
                a[i] = str[i];
            }
            a[index] = '\0';
            NODE element = createNewNode(a);
            insertNodeIntoList(element,grammar[line_number]);
            index = 0;
        }
        else
        {
            char* a = (char*)malloc(sizeof(char) * (index + 1));
            for(int i=0 ; i<index ; i++)
            {
                a[i] = str[i];
            }
            a[index] = '\0';
            NODE element = createNewNode(a);
            insertNodeIntoList(element,grammar[line_number]);
            index = 0;
            line_number++;
        }
    }
}
void display_rules()
{
    for(int i = 0; i < NUMBER_OF_RULES; ++i)
        display(grammar[i]);

}
int main()
{
    grammar = (linked_list**) malloc(sizeof(linked_list *) * NUMBER_OF_RULES);
    for(int i = 0; i < NUMBER_OF_RULES; ++i )
        grammar[i] = createNewList();
    populate_grammer();
    // display_rules();

    init_nt_array();
    // printf("NO OF UNIQUE NT : %d\n",x);

    // char ** first = get_first_set("MODULEDECLARATIONS");
    // printf("FINAL PRINT\n");
    // for(int i=0 ; i<NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
    //     printf("%s\n",first[i]);
    //     if(strcmp(first[i],"-1")==0) break;
    // }

    char*** complete_first_sets = all_first_sets();
    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        printf("PRINTING FIRST OF %s:-\n",arrayOfNonTerminals[i]);
        for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; j++){
            // printf("here\n");
            if(strcmp(complete_first_sets[i][j],"-1")==0) break;
            printf("%s\n",complete_first_sets[i][j]);
        }
    }

}