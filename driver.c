#include <stdio.h>

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
