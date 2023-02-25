#include<stdio.h>
#include "linkedlist.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "parser.h"
#include<string.h>

int set_contains(char** arr,int arr_len, char* str){
    for(int i=0 ; i<arr_len ; i++){
        if(strcmp(str,arr[i])==0) return 1;
    }
    return 0;
}

int getTypeOfData(char* str){
    if(strcmp(str,"eps")==0) return 0;                  // 0 for epsilon
    else if((str[0]>='A' && str[1]<='Z')) return 1;       // 1 for non-terminal
    else return 2;                                      // 2 for terminal
}

//This function is used to get the number of unique non-terminals present in our grammar. It populates the array of non-terminals
//which is defined in the parser.h file. It also returns the number of unique non-terminals which is stored in the variable 
//NUMBER_OF_UNIQUE_NONTERMINALS present in the parser.h file.
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

//This function is used to get the number of unique terminals present in our grammar. It populates the array of terminals
//which is defined in the parser.h file. It also returns the number of unique terminals which is stored in the variable 
//NUMBER_OF_UNIQUE_TERMINALS present in the parser.h file.
int getNumberOfTerminals(){
    int maxlen = 0;




    for(int i=0 ; i<NUMBER_OF_RULES ; i++){
        NODE temp = grammar[i]->head;
        while(temp->next!=NULL){
            temp = temp->next;
            char* terminal = temp->data;
            int found = 0;
            // if(terminal[0]>='A' && terminal[0]<='Z'){
            if(getTypeOfData(terminal)==2){
                //iterating for lhs over the set of unique nt
                for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS ; j++){
                    if(arrayOfTerminals[j][0]!='-'){
                        if(strcmp(terminal,arrayOfTerminals[j])==0){
                            found = 1;
                            // printf("For terminal : %s, it was found at index %d",lhs,j);
                            break;
                        }
                    }else{
                        if(found==0){
                            strcpy(arrayOfTerminals[j],terminal);
                            // printf("For nonterminal : %s, it was added at index %d",lhs,j);
                            maxlen++;
                            break;
                        }
                    }
                }
            }
        }
    }
    number_of_unique_terminals = maxlen;
    return maxlen;
}


int contains_epsilon(char ** set){
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
        if(strcmp(set[i],"eps")==0){
            return 1;
        }
    }
    return 0;
}

char ** get_first_set(char* nonterminal){
    char **first = (char**)malloc(MAX_NUMBER_OF_UNIQUE_TERMINALS*sizeof(char*));
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
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
                    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
                        if(strcmp(first_of_temp[i],"-1")==0) break;
                        if(strcmp(first_of_temp[i],"eps")!=0){
                            if(set_contains(first,MAX_NUMBER_OF_UNIQUE_TERMINALS,first_of_temp[i])==0){
                                first[index] = first_of_temp[i];
                                // printf("copied %s into index : %d of first of %s\n",first_of_temp[i],index,nonterminal);
                                index++;
                            }
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
    return first;
}

char ** get_follow_set(char* nonterminal){
    char **follow = (char**)malloc(MAX_NUMBER_OF_UNIQUE_TERMINALS*sizeof(char*));
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
        follow[i] = (char*) malloc(sizeof(char)*MAX_LENGTH_OF_NONTERMINAL);
    }
    int index = 0;
    //iterating to all the rules
    for(int i=0 ; i<NUMBER_OF_RULES ; i++){
        //traversing the entire rule to find the non-terminal in the RHS
        int found = 0;
        NODE lhs = grammar[i]->head;
        NODE temp = grammar[i]->head;
        while(temp->next!=NULL){
            temp = temp->next;
            if(strcmp(temp->data,nonterminal)==0) found = 1;
            if(found==1){
                // printf("%s is found\n",temp->data);
                if(temp->next!=NULL){
                    //get first of the next element
                    if(getTypeOfData(temp->next->data)==2){
                            if(set_contains(follow,MAX_NUMBER_OF_UNIQUE_TERMINALS,temp->next->data)==0){
                                follow[index] = temp->next->data;
                                index++;
                            }   
                            break;                    
                    }else{
                        char ** first_of_next = get_first_set(temp->next->data);
                        //copy non-epsilon elements from first of next to follow
                        for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
                            if(strcmp(first_of_next[i],"-1")==0) break;
                            if(strcmp(first_of_next[i],"eps")!=0){

                                if(set_contains(follow,MAX_NUMBER_OF_UNIQUE_TERMINALS,first_of_next[i])==0){
                                    follow[index] = first_of_next[i];
                                    // printf("copied %s into index : %d of first of %s\n",first_of_temp[i],index,nonterminal);
                                    index++;
                                }
                            }
                        }
                        //copying done
                        //if first of next has epsilon, go forward
                        if(contains_epsilon(first_of_next)){
                            continue;
                        }else{
                            break;
                        }
                    }
                }else{
                    if(strcmp(temp->data,lhs->data)==0) break;
                    //get follow of LHS and copy to follow
                    char** follow_of_lhs = get_follow_set(lhs->data);
                    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
                        if(strcmp(follow_of_lhs[i],"-1")==0) break;

                        if(set_contains(follow,MAX_NUMBER_OF_UNIQUE_TERMINALS,follow_of_lhs[i])==0){
                            follow[index] = follow_of_lhs[i];
                            // printf("copied %s into index : %d of first of %s\n",first_of_temp[i],index,nonterminal);
                            index++;
                        }
                    }
                    //copying done
                }
            }
        }
    }
    follow[index] = "-1";
    return follow;
}

char *** all_first_sets(){

    char ***first_of_all = (char***)malloc(number_of_unique_nonterminals*sizeof(char**));
    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        first_of_all[i] = (char**) malloc(sizeof(char*)*MAX_NUMBER_OF_UNIQUE_TERMINALS);
        for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS; j++){
            first_of_all[i][j] = (char*) malloc(sizeof(char)*MAX_LENGTH_OF_NONTERMINAL);
        }
    }

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


char *** all_follow_sets(){

    char ***follow_of_all = (char***)malloc(number_of_unique_nonterminals*sizeof(char**));
    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        follow_of_all[i] = (char**) malloc(sizeof(char*)*MAX_NUMBER_OF_UNIQUE_TERMINALS);
        for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS; j++){
            follow_of_all[i][j] = (char*) malloc(sizeof(char)*MAX_LENGTH_OF_NONTERMINAL);
        }
    }

    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        //length of arrayOfNonTerminals is more but we stop at the correct length
        follow_of_all[i] = get_follow_set(arrayOfNonTerminals[i]);
        // printf("PRINTING FIRST OF %s\n",arrayOfNonTerminals[i]);
        // for(int j=0 ; j<NUMBER_OF_UNIQUE_NONTERMINALS; j++){
            // printf("%s\n",first_of_all[i][j]);
        //     if(strcmp(first_of_all[i][j],"-1")==0) break;
        // }
    }

    return follow_of_all;
}



void init_nt_array(){
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
        arrayOfNonTerminals[i][0]='-';
    }
    getNumberOfNonTerminals();
}

void init_t_array(){
    for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
        arrayOfTerminals[i][0]='-';
    }
    getNumberOfTerminals();
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
    init_t_array();
    complete_first_sets = all_first_sets(); //populating first set
    complete_follow_sets = all_follow_sets(); //populating follow set
    printf("NUMBER OF UNIQUE TERMINALS : %d\n",number_of_unique_terminals);
    printf("NUMBER OF UNIQUE NON-TERMINALS : %d\n",number_of_unique_nonterminals);


    // printf("NO OF UNIQUE NT : %d\n",x);

    // char ** first = get_first_set("MODULEDECLARATIONS");
    // printf("FINAL PRINT\n");
    // for(int i=0 ; i<NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
    //     printf("%s\n",first[i]);
    //     if(strcmp(first[i],"-1")==0) break;
    // }

    // Printing follow sets
    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        printf("PRINTING FOLLOW OF %s:-\n",arrayOfNonTerminals[i]);
        for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS ; j++){
            // printf("here\n");
            if(strcmp(complete_follow_sets[i][j],"-1")==0) break;
            printf("%s\n",complete_follow_sets[i][j]);
        }
    }

    //  Printing first sets
    // for(int i=0 ; i<number_of_unique_nonterminals ; i++){
    //     printf("PRINTING FIRST OF %s:-\n",arrayOfNonTerminals[i]);
    //     for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS ; j++){
    //         // printf("here\n");
    //         if(strcmp(complete_first_sets[i][j],"-1")==0) break;
    //         printf("%s\n",complete_first_sets[i][j]);
    //     }
    // }

    char** follow = get_follow_set("STATEMENTS");
    for(int i=0 ; i<number_of_unique_terminals ; i++){
        printf("%s\n",follow[i]);
        if(strcmp(follow[i],"-1")==0) break;
    }

}