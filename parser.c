#include <stdio.h>
#include "parser.h"

// char* get_reqd_substring(char* a, int index){
//     printf("\n%s___",a);
//     char* str;
//     for(int i=0 ; i<index ; i++){
//         str[i] = a[i];
//         if(i==index-1) str[i+1] = '\0';
//     }
//     printf("             :::::%s",str);
//     return str;
// }

void init_parser(){
    
}
void populate_grammar(){
    FILE *grammar_input_file;
    grammar_input_file = fopen("grammar.txt", "r");
    char str[30];
    int index=0;
    char ch;
    int line_number = 0;

    Grammar_Rule *grammar_rule = (Grammar_Rule*) malloc(sizeof(Grammar_Rule));
    grammar_rule->lhs = NULL;
    grammar_rule->head = NULL;
    grammar_rule->tail = NULL;

    while((ch = fgetc(grammar_input_file)) != EOF){
        if(ch!=' ' && ch!='\n'){
            // printf("in line number : %d, char:%c \n",line_number,ch);
            str[index++] = ch;
        }else if(ch==' '){
            // printf("in line number : %d,index is %d, got space \n",line_number,index);
            Element* element = (Element*)malloc(sizeof(Element));
            element->element_name = NULL;
            element->next = NULL;
            char a[index+1];
            for(int i=0 ; i<index ; i++){
                a[i] = str[i];
                if(i==index-1) a[i+1] = '\0';
            }
            // printf("A : %s\n",a);
            element->element_name = a;
            // printf("Element.name : %s\n",element->element_name);
            Element* nextElement = (Element*) malloc(sizeof(Element));
            nextElement->element_name = NULL;
            nextElement->next = NULL;
            // printf("reached here\n");
            element->next = &nextElement;
            // printf("reached here\n");
            if(grammar_rule->lhs==NULL){
                // printf("reached NULL\n");
                grammar_rule->lhs = element;
                // printf("BC: %s\n",grammar_rule.lhs->element_name);
            } 
            else{
                // printf("reached here\n");
                if(grammar_rule->tail==NULL){
                    // printf("reached here where tail is null\n");
                    grammar_rule->head = element;
                    grammar_rule->tail = element;
                }else{
                    // printf("reached here where tail is not null\n");
                    grammar_rule->tail->next = element;
                    grammar_rule->tail = element;
                    grammar_rule->tail->next = NULL;
                }
            }

            index = 0;
            element = nextElement;
        }else{
            // printf("in line number : %d,index is %d, got space \n",line_number,index);
            Element* element = (Element*)malloc(sizeof(Element));
            element->element_name = NULL;
            element->next = NULL;
            char a[index+1];
            for(int i=0 ; i<index ; i++){
                a[i] = str[i];
                if(i==index-1) a[i+1] = '\0';
            }
            // printf("A : %s\n",a);
            element->element_name = a;
            // printf("Element.name : %s\n",element->element_name);
            // printf("reached here\n");
            element->next = NULL;
            // printf("reached here\n");
            if(grammar_rule->lhs==NULL){
                // printf("reached NULL\n");
                grammar_rule->lhs = element;
                // printf("BC: %s\n",grammar_rule.lhs->element_name);
            } 
            else{
                // printf("reached here\n");
                if(grammar_rule->tail==NULL){
                    // printf("reached here where tail is null\n");
                    grammar_rule->head = element;
                    grammar_rule->tail = element;
                }else{
                    // printf("reached here where tail is not null\n");
                    grammar_rule->tail->next = element;
                    grammar_rule->tail = element;
                    grammar_rule->tail->next = NULL;
                }
            }
            index = 0;
            //updating line number and initialising new grammar_rules
            grammar[line_number++] = *grammar_rule;

            printf("RULE Number : %d, LHS : %s, RHS's head : %s, RHS's tail : %s\n",line_number,grammar_rule->lhs->element_name,grammar_rule->head->element_name,grammar_rule->tail->element_name);


            // printf("FINAL %s ",grammar[line_number-1].lhs->element_name);
            Grammar_Rule* new_grammar_rule = (Grammar_Rule*)malloc(sizeof(Grammar_Rule));
            grammar_rule = new_grammar_rule;
            grammar_rule->lhs = NULL;
            grammar_rule->head = NULL;
            grammar_rule->tail = NULL;
        }
    }
    fclose(grammar_input_file);
}

void print_grammar(){
    for(int i=0 ; i<NUMBER_OF_RULES ; i++){
        printf("RULE Number : %d, LHS : %s, RHS's head : %s, RHS's tail : %s\n",i,grammar[i].lhs->element_name,grammar[i].head->element_name, grammar[i].tail->element_name);
    }
}

int main(){
    populate_grammar();
    print_grammar();
}