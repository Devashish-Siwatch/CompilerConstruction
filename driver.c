#include <stdio.h>
#include "lexer.h"

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
    printf("File opened successfully\n");
    printf("%c", get_next_char(input_file));
    printf("%c", get_next_char(input_file));
    // Close the file
    fclose(input_file);

    return 0;
}
