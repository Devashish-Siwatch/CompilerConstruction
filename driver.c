/*
Group - 41
Praneet Karna - 2020A7PS1202P
Kshitij Tandon - 2020A7PS0972P
Devashish Siwatch - 2020A7PS0113P
Samyak Jain - 2020A7PS0089P
Chaitanya Iyer - 2020A7PS0012P
*/

#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include <time.h>
#include <stdlib.h>

char *enum_to_token_name_string[] = {
    "ID",
    "NUM",
    "RNUM",
    "AND",
    "OR",
    "TRUE",
    "FALSE",
    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "LT",
    "LE",
    "GT",
    "GE",
    "EQ",
    "NE",
    "DEF",
    "ENDDEF",
    "DRIVERDEF",
    "DRIVERENDDEF",
    "COLON",
    "RANGEOP",
    "SEMICOL",
    "COMMA",
    "ASSIGNOP",
    "SQBO",
    "SQBC",
    "BO",
    "BC",
    "INTEGER",
    "REAL",
    "BOOLEAN",
    "OF",
    "ARRAY",
    "START",
    "END",
    "DECLARE",
    "MODULE",
    "DRIVER",
    "PROGRAM",
    "GET_VALUE",
    "PRINT",
    "USE",
    "WITH",
    "PARAMETERS",
    "TAKES",
    "INPUT",
    "RETURNS",
    "FOR",
    "IN",
    "SWITCH",
    "CASE",
    "BREAK",
    "DEFAULT",
    "WHILE",
    "EOFILE"
    // "COMMENTMARK"
};

// saving all the tokens generated by the lexer in a file
void save_all_tokens(FILE *input_file, FILE *output_file)
{
    initialize_lexer_variables(input_file);
    Token token;
    while (1)
    {
        token = get_next_token(input_file);
        if (token.token_name == EOFILE)
        {
            break;
        }
        printf("\n%-5d\t%-20s\t%-20s\n", token.line_no, enum_to_token_name_string[token.token_name], token.id.str);
        fprintf(output_file, "%-20s %-20d %-20s\n", enum_to_token_name_string[token.token_name], token.line_no, token.id.str);
        //  break;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("\033[31mPlease provide correct number of arguments\n\033[0m");
        return 1;
    }
    FILE *input_file, *output_file;
    input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("\033[31mUnable to open input file\033[0m\n");
        return 1;
    }
    output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("\033[31mUnable to open output file\033[0m\n");
        return 1;
    }
    printf("Status: \n\n");
    printf("FIRST AND FOLLOW SET AUTOMATED\n");
    printf("Both lexical and syntax analysis modules implemented\n");
    printf("Parse tree constructed\n");
    printf("Modules worked correctly with all the provided 6 testcases\n\n");

    // BUFFER_SIZE = atoi(argv[3]);
    // MAX_LEXEME_LENGTH = BUFFER_SIZE/2;
    BUFFER_SIZE = 2*atoi(argv[3]);
    MAX_LEXEME_LENGTH = BUFFER_SIZE/2;
    printf("SINGLE_BUFFER_SIZE = %d", BUFFER_SIZE/2);
    
    int choice;
    while (1)
    {
        printf("\nChoose an option:\n");
        printf("0. Exit\n");
        printf("1. Run lexer (Print Tokens)\n");
        printf("2. Run parser (Print Parse Tree)\n");
        printf("3. Print Abstract Syntax Tree\n");
        printf("4. Print Memory Used by Parse Tree and AST\n");
        printf("5. Print Symbol Table\n");
        printf("6. Print activation record size\n");
        printf("7. Print array information\n");
        printf("8. Print all errors and total compile time\n");
        printf("9. Generate assembly code\n\n");

        scanf("%d", &choice);
        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            // char ch;
            // input_file = fopen(argv[1], "r");
            // // Open the input file in read mode
            // // open the file to save the tokens generated by the lexer
            // FILE *comment_file = fopen("removed_comments.txt", "w");
            // // If the file doesn't exist or can't be opened, exit the program
            // if (comment_file == NULL)
            // {
            //     printf("Unable to open file");
            //     return 1;
            // }
            // printf("Output File opened successfully\n");

            // removeComments(input_file, comment_file);
            // fclose(input_file);
            // fclose(output_file);
            char ch;
            input_file = fopen(argv[1], "r");
            // open the file to save the tokens generated by the lexer
            FILE *token_file = fopen("token_output.txt", "w");
            // If the file doesn't exist or can't be opened, exit the program
            if (token_file == NULL)
            {
                printf("Unable to open file");
                return 1;
            }
            printf("Token output File opened successfully\n");
            save_all_tokens(input_file, token_file);

            // Close the file
            fclose(token_file);

        }
        else if (choice == 2)
        {
            FILE *input_file;
            input_file = fopen(argv[1], "r");

            if (input_file == NULL)
            {
                printf("Unable to open file");
                return 1;
            }

            FILE *output_file;
            output_file = fopen(argv[2], "w");
            if (output_file == NULL)
            {
                printf("\033[31mUnable to open output file\033[0m\n");
                return 1;
            }

            int parse = parse_tree_func(input_file);
            fclose(input_file);
            fclose(output_file);            
        }
        else if (choice == 3)
        {
            FILE *input_file;
            input_file = fopen(argv[1], "r");

            if (input_file == NULL)
            {
                printf("Unable to open file");
                return 1;
            }

            FILE *output_file;
            output_file = fopen(argv[2], "w");
            if (output_file == NULL)
            {
                printf("\033[31mUnable to open output file\033[0m\n");
                return 1;
            }
            parse_tree_formation_ast_printing(input_file);         
        }
        else if (choice == 4)
        {
            FILE *input_file;
            input_file = fopen(argv[1], "r");

            if (input_file == NULL)
            {
                printf("Unable to open file");
                return 1;
            }

            FILE *output_file;
            output_file = fopen(argv[2], "w");
            if (output_file == NULL)
            {
                printf("\033[31mUnable to open output file\033[0m\n");
                return 1;
            }
            int parse = parser_complete_functionality(input_file, output_file);
            printf("AST Function Goes Here\n"); 
            printf("Memory Taken Function Goes Here\n");            
        }
        else if (choice == 5)
        {
            printf("Symbol Table print Goes Here\n");            
        }
        else if (choice == 6)
        {
            printf("Activation record size Goes Here\n");            
        }
        else if (choice == 7)
        {
            printf("Array Info Goes Here\n");            
        }
        else if (choice == 8)
        {
            printf("Error reporting and total compile time Goes Here\n");            
        }
        else if (choice == 9)
        {
            printf("Code Generation Goes Here\n");            
        }
        else
        {
            printf("\n\033[31mInvalid choice\033[0m\n");
        }
    }

    return 0;
}