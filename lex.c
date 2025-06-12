//Sophia Kropivnitskaia
// Course: Systems Software
// Semester: Summer 2025
//HW 2

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
    gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18,
    periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24,
    whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32 , elsesym = 33

} token_type;

#define IDENTIFYLEN 11
#define NUMLEN 5
#define MAX 5000

int tokens[MAX];

int main(void)
{
    //char* InputFile = argv[1];
    char* InputFile = "input.txt";
    FILE *input_f = fopen(InputFile, "r");
    FILE *output_f = fopen("output.txt", "w");

    char ch;
    char buffer[MAX]; //without white space
    int size = 0;
    char temp[MAX]; //with white space
    int i = 0, j = 0;

    while (fscanf(input_f, "%c", &ch) != EOF)
    {
        buffer[j++] = ch;
        size++;
    }

    fclose(input_f);

    //accounting for comments
    for (i = 0; i < size; i++) 
    {
        if (buffer[i] == '/' && buffer[i + 1] == '*') 
        {
            int j = i + 2;

            while (!(buffer[j] == '*' && buffer[j + 1] == '/')) 
            {
                j++;
            }
            i = j + 2;
            continue;
        }

        if (buffer[i] == '\n') 
        {
            continue;
        }
        if (buffer[i] == ' ') 
        {
            continue;
        }
        if (buffer[i] == '\t') 
        {
            continue;
        }
    }

    //Print statments 
    printf("Source Program:\n%s\n", buffer);
    fprintf(output_f, "Source Program:\n%s\n", buffer); 

    printf("Lexeme Table:\n");
    printf("\nlexemetoken\ttype\n");
}

