#include <stdio.h>
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include <string.h>
#include "parsetable.h"
#include "stack.h"
#include "treeADT.h"
#include "lexer.h"
#include "driver.c"
#include "stack.h"
#include <ctype.h>

STACK stack;

char* convertToLowercase(char* str){
    //printf("CONVert LC\n");
    int len = 0;
    for(int i=0 ; str[i]!='\0' ; i++){
        len++;
    }
    char* temp = (char*)malloc((len+1)*sizeof(char));

    for(int i=0; i<len; i++){
        temp[i] = tolower(str[i]);
        // printf("%c\n",temp[i]);
    }
    temp[len] = '\0';
    return temp;

}

void init_parser(){
    //init stack and tree, added S to bottom of stack and S as root of our tree.
    stack = init_stack();
    TREELIST parse_tree = createNewTree();
    TREENODE head = createNewTreeNode(NULL);
    head->name = "S";
    parse_tree->head = head;
    push(stack,"S",head);
    pop(stack);
    pushRuleToStackandTree(stack,grammar[0],head);
}

void parser(FILE *input_file_pointer){
    initialize_lexer_variables(input_file_pointer);
    init_parser();
    
    Token current = get_next_token(input_file_pointer);
    
    while(current.token_name!=EOF){
        char *currentTk= enum_to_token_name_string[current.token_name];
        char *currentTkLower = convertToLowercase(currentTk);

        STACKNODE top_of_stack = top(stack);
        if(strcmp("dollar",top_of_stack->name)==0){
            //stack is over
            printf("STACK KHATAM\n");
            return;
        }else if(getTypeOfData(top_of_stack->name)==2){
            //stack's top is a terminal
            if(strcmp(currentTkLower,top_of_stack->name)==0){
                printf(">>>>>>>>>>Equality achieved for %s\n",currentTkLower);
                pop(stack);
                TREENODE treenode = top_of_stack->treepointer;
                strcpy(current.id.str,"abcd");
                strcpy(treenode->lexeme,"abc");
                treenode->line_number = current.line_no;
                treenode->valueIfNum = current.numeric_value;
                treenode->valueIfRNum = current.real_numeric_value;
                treenode->child = NULL;
                current = get_next_token(input_file_pointer);
            }else{
                printf("top of stack :%s  and token we got from lexer : %s\n",top_of_stack->name, currentTkLower);
                printf("ERROR : The terminal at top of stack is not equal to the result of lexer.\n");
                return;
            }
        }else{
            //stack's top is a non-terminal
            int col=searchForColIndex(currentTkLower);
            int row=searchForRowIndex(top_of_stack->name);
            // printf("row %d for %s col %d for %s\n",row,top_of_stack->name,col,currentTkLower);
            if(parse_table[row][col]==-1){
                printf("Parse Table Khaali hai i.e. Error row : %s, col : %s\n",top_of_stack->name,currentTkLower);
                return;//TODO: return hoga ya error handling???
            }else{
                int rule_no=parse_table[row][col];
                // printf("RULE number : %d\n",rule_no);
                LIST grammar_rule= grammar[rule_no];
                pushRuleToStackandTree(stack,grammar_rule,top(stack)->treepointer);
            }
        }
    }
}

int set_contains(char** arr,int arr_len, char* str){
    for(int i=0 ; i<arr_len ; i++){
        if(strcmp(str,arr[i])==0) return 1;
    }
    return 0;
}

int getTypeOfData(char* str){
    if(strcmp(str,"eps")==0) return 0;                      // 0 for epsilon
    else if((str[0]>='A' && str[0]<='Z')) return 1;         // 1 for non-terminal
    else return 2;                                          // 2 for terminal
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

void printParseTable(){
    for(int i=0 ; i<number_of_unique_nonterminals ; i++){
        printf("ROW OF %s : ",arrayOfNonTerminals[i]);
        for(int j=0 ; j<number_of_unique_terminals ; j++){
            if(parse_table[i][j]!=-1)printf("%s :  %d___",arrayOfTerminals[j],parse_table[i][j]);
            else printf("%s : %d___",arrayOfTerminals[j],parse_table[i][j]);
        }
        printf("\n");
    }
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

void createParseTable(int row,int col)
{
    parse_table = (int**)malloc(row*sizeof(int*));
    for(int i=0 ; i<row ; i++){
        parse_table[i] = (int*)malloc(col*sizeof(int));
    }
    for(int i=0 ; i<row ; i++){
        for(int j=0 ; j<col ; j++){
            parse_table[i][j] = -1;
        }
    }
}

void init_parse_table()
{
    row_size = number_of_unique_nonterminals;
    column_size =number_of_unique_terminals;
    createParseTable(row_size,column_size);
}



int searchForRowIndex(char* data)
{
    for(int i=0;i<number_of_unique_nonterminals;i++)
    {
        if(strcmp(data, arrayOfNonTerminals[i])==0)
        {
            return i;
        }
    }
    printf("ERROR : searchForRowIndex couldn't find anything\n");
    return -1;
}

int searchForColIndex(char* data)
{
    for(int i=0;i<number_of_unique_terminals;i++)
    {
        if(strcmp(data, arrayOfTerminals[i])==0)
        {
            return i;
        }
    }
    printf("ERROR : searchForColIndex couldn't find anything\n");
    return -1;
}
void fillParseTable()
{
    for(int i=0;i<NUMBER_OF_RULES;i++)
    {
        NODE lhs = grammar[i]->head;
        int row = searchForRowIndex(lhs->data);
        NODE temp = lhs;
        char **first_set = (char**)malloc(MAX_NUMBER_OF_UNIQUE_TERMINALS*sizeof(char*));
        for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++){
            first_set[i] = (char*)malloc(MAX_LENGTH_OF_TERMINAL*sizeof(char));
        }
        int index = 0;

        while(temp->next!=NULL){
            // printf("%s\n",temp->data);
            temp = temp->next;
            // printf("%s",temp->data);
            if(getTypeOfData(temp->data)==0)
            {
                char** follow_of_lhs=get_follow_set(lhs->data);
                // printf("Eps reached at rule number %d\n",i);
                for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS; i++){
                    if(strcmp("-1",follow_of_lhs[i])==0) break;
                    first_set[index]=follow_of_lhs[i];
                    index++;
                }
            }
            else if(getTypeOfData(temp->data)==1)
            {
                // printf("%s\n",temp->data);
                char** first_of_temp=get_first_set(temp->data);
                //printf("%s 2\n",temp->data);
                //copy all non-eps from this first_of_temp into our first_set
                for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++)
                {
                    if(strcmp(first_of_temp[i],"-1")==0) break;
                    if(strcmp(first_of_temp[i],"eps")!=0)
                    {
                        // printf("first stored: %s\n",first_of_temp[i]);
                        if(set_contains(first_set,MAX_NUMBER_OF_UNIQUE_TERMINALS,first_of_temp[i])==0)
                        {
                            first_set[index] = first_of_temp[i];
                            // printf("copied %s into index : %d \n",first_of_temp[i],index);
                            index++;
                        }
                        // printf("HERE");
                    }
                }
                //check if first_of_temp has eps
                if(contains_epsilon(first_of_temp)==1)
                {
                    //if yes, then temp = temp->next
                    //if temp->next is null then add follow(lhs) and break
                    //else temp = temp->next
                    if(temp->next==NULL){
                        char ** follow_of_lhs = get_follow_set(lhs->data);
                        //copy this into first_set
                        for(int i=0 ; i<MAX_NUMBER_OF_UNIQUE_TERMINALS ; i++)
                        {
                            if(strcmp(follow_of_lhs[i],"-1")==0) break;
                            if(set_contains(first_set,MAX_NUMBER_OF_UNIQUE_TERMINALS,follow_of_lhs[i])==0)
                            {
                                first_set[index] = follow_of_lhs[i];
                                // printf("copied %s into index : %d of first of %s\n",first_of_temp[i],index,nonterminal);
                                index++;
                            }
                        }
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }else{
                    //if no then break;
                    break;
                }
            }
            else
            {
                if(set_contains(first_set,MAX_NUMBER_OF_UNIQUE_TERMINALS,temp->data)==0){
                    first_set[index] = temp->data;
                    // printf("copied %s into index : %d of first of %s\n",first_of_temp[i],index,nonterminal);
                    index++;
                }
                break;
            }
        }
        
        first_set[index] = "-1";

        for(int j=0;j<MAX_NUMBER_OF_UNIQUE_NONTERMINALS;j++){
            if(strcmp(first_set[j],"-1")==0) break;
            int col=searchForColIndex(first_set[j]);
            // printf("comparison func : %s, actual : %s\n",first_set[j],arrayOfTerminals[col]);
            // printf("row : %d, col : %d\n",row,col);
            if(parse_table[row][col]!=-1) printf("NOT LL1 for row=%d ; col=%d",row,col);
            parse_table[row][col]=i;
            // printf("row : %d, col : %d\n",row,col);
        }
            

    }
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

    init_parse_table();
    fillParseTable();
    printParseTable();

    // for(int i=0 ; i<number_of_unique_nonterminals ; i++){
    //     printf("%d. %s\n",i,arrayOfNonTerminals[i]);
    // }

    printf("NUMBER OF UNIQUE TERMINALS : %d\n",number_of_unique_terminals);
    printf("NUMBER OF UNIQUE NON-TERMINALS : %d\n",number_of_unique_nonterminals);


    // printf("NO OF UNIQUE NT : %d\n",x);

    // char ** first = get_first_set("MODULEDECLARATIONS");
    // printf("FINAL PRINT\n");
    // for(int i=0 ; i<NUMBER_OF_UNIQUE_NONTERMINALS ; i++){
    //     printf("%s\n",first[i]);
    //     if(strcmp(first[i],"-1")==0) break;
    // }

    // // Printing follow sets
    // for(int i=0 ; i<number_of_unique_nonterminals ; i++){
    //     printf("PRINTING FOLLOW OF %s:-\n",arrayOfNonTerminals[i]);
    //     for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS ; j++){
    //         // printf("here\n");
    //         if(strcmp(complete_follow_sets[i][j],"-1")==0) break;
    //         printf("%s\n",complete_follow_sets[i][j]);
    //     }
    // }

    // //  Printing first sets
    // for(int i=0 ; i<number_of_unique_nonterminals ; i++){
    //     printf("PRINTING FIRST OF %s:-\n",arrayOfNonTerminals[i]);
    //     for(int j=0 ; j<MAX_NUMBER_OF_UNIQUE_TERMINALS ; j++){
    //         // printf("here\n");
    //         if(strcmp(complete_first_sets[i][j],"-1")==0) break;
    //         printf("%s\n",complete_first_sets[i][j]);
    //     }
    // }

    //init_parser();



    FILE *input_file;
    // Open the input file in read mode
    input_file = fopen("input.txt", "r");
    if (input_file == NULL)
    {
        printf("Unable to open file");
        return 1;
    }
    // printf("File opened successfully\n");

    

    parser(input_file);

    printf("PARSING SUCCESSFULL\n");

    // char** follow = get_follow_set("STATEMENTS");
    // for(int i=0 ; i<number_of_unique_terminals ; i++){
    //     printf("%s\n",follow[i]);
    //     if(strcmp(follow[i],"-1")==0) break;
    // }

}