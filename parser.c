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

    Grammar_Rule grammar_rule;
    grammar_rule.lhs = NULL;
    grammar_rule.head = NULL;
    grammar_rule.tail = NULL;

    while((ch = fgetc(grammar_input_file)) != EOF){
        if(ch!=' ' && ch!='\n'){
            // printf("in line number : %d, char:%c \n",line_number,ch);
            str[index++] = ch;
        }else if(ch==' '){
            printf("in line number : %d,index is %d, got space \n",line_number,index);
            Element element;
            element.element_name = NULL;
            element.next = NULL;
            // printf("here index is %d\n",index);
            char a[index+1];
            for(int i=0 ; i<index ; i++){
                // printf("inside func \n");
                a[i] = str[i];
                if(i==index-1) a[i+1] = '\0';
            }
            // printf("A : %s\n",a);
            element.element_name = a;
            // printf("Element.name : %s\n",element.element_name);
            Element nextElement;
            // printf("reached here\n");
            element.next = &nextElement;
            // printf("reached here\n");
            if(grammar_rule.lhs==NULL){
                // printf("reached NULL\n");
                grammar_rule.lhs = &element;
                printf("BC: %s\n",grammar_rule.lhs->element_name);
            } 
            else{
                // printf("reached here\n");
                if(grammar_rule.tail==NULL){
                    // printf("reached here\n");
                    grammar_rule.head = &element;
                    grammar_rule.tail = &element;
                }else{
                    grammar_rule.tail->next = &element;
                    grammar_rule.tail = &element;
                    grammar_rule.tail->next = NULL;
                }
            }

            index = 0;
            element = nextElement;
        }else{
            // printf("in line number : %d, got space \n",line_number);
            Element element;
            // printf("here index is %d\n",index);
            char a[index+1];
            for(int i=0 ; i<index ; i++){
                // printf("inside func \n");
                a[i] = str[i];
                if(i==index-1) a[i+1] = '\0';
            }
            // printf("A : %s\n",a);
            element.element_name = a;
            // printf("Element.name : %s\n",element.element_name);

            Element nextElement;
            element.next = &nextElement;
            if(grammar_rule.lhs==NULL) grammar_rule.lhs = &element;
            else{
                if(grammar_rule.tail==NULL){
                    grammar_rule.head = &element;
                    grammar_rule.tail = &element;
                }else{
                    grammar_rule.tail->next = &element;
                    grammar_rule.tail = &element;
                    grammar_rule.tail->next = NULL;
                }
            }
            index = 0;
            element = nextElement;
            //updating line number and initialising new grammar_rule
            grammar[line_number++] = grammar_rule;
            Grammar_Rule new_grammar_rule;
            grammar_rule = new_grammar_rule;
            grammar_rule.lhs = NULL;
            grammar_rule.head = NULL;
            grammar_rule.tail = NULL;
        }
    }
    fclose(grammar_input_file);
}

void print_grammar(){
    for(int i=0 ; i<NUMBER_OF_RULES ; i++){
        printf("RULE Number : %d, LHS : %s, RHS's head : %s, RHS's tail : %s\n",i,grammar[i].lhs->element_name,grammar[i].head->element_name, grammar[i].tail->element_name);
        // printf("\n rue num : %d, lhs : %s",i,grammar[i].lhs->element_name);
        // if(grammar[i].lhs->element_name==NULL){
        //     printf("idhar null hai : %d", i);
        // }
    }
}

int main(){
    populate_grammar();
    print_grammar();
}