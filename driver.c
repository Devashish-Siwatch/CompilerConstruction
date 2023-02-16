#include <stdio.h>
#define MAX_LEXEME_LENGTH 100

// List of valid token names in the language
typedef enum valid_token_names
{
    ID,
    NUM,
    RNUM,
    AND,
    OR,
    TRUE,
    FALSE,
    PLUS,
    MINUS,
    MUL,
    DIV,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    DEF,
    ENDDEF,
    DRIVERDEF,
    DRIVERENDDEF,
    COLON,
    RANGEOP,
    SEMICOL,
    COMMA,
    ASSIGNOP,
    SQBO,
    SQBC,
    BO,
    BC,
    COMMENTMARK
} valid_token_names;

// Defining token and its structure
typedef struct token
{
    valid_token_names token_name;
    union
    {
        struct
        {
            char str[MAX_LEXEME_LENGTH];
        } id;
        int numeric_value;
        double real_numeric_value;
    };
    int line_no;
} Token;

int main()
{
    FILE *input_file;
    char ch;

    // Open the input file in read mode
    input_file = fopen("input.txt", "r");

    // If the file doesn't exist or can't be opened, exit the program
    if (input_file == NULL)
    {
        printf("Unable to open file");
        return 1;
    }

    // Read and print each character in the file
    while ((ch = fgetc(input_file)) != EOF)
    {
        printf("%c", ch);
    }

    // Close the file
    fclose(input_file);

    return 0;
}
