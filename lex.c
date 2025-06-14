// Sophia Kropivnitskaia
// Course: Systems Software
// Semester: Summer 2025
// HW 2

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
    gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18,
    periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24,
    whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32 , elsesym = 33

} token_type;

#define MAX_ID_LEN 11
#define MAX_NUM_LEN 5
#define MAX 50000
#define MAX_LINE_LEN 256

int hasError = 0;

int tokens[MAX];
int tokenSize = 0;

const char *reservedWords[] = {
    "const", "var", "procedure", "call", "begin", "end", "if",
    "fi", "then", "else", "while", "do", "read", "write"
};

// reserved words symbols
const int reservedTokens[] = {
    constsym, varsym, procsym, callsym, beginsym, endsym, ifsym,
    fisym, thensym, elsesym, whilesym, dosym, readsym, writesym
};

//special Symbols
const char symbols[] = {
    '+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':'
};


int isLetter(char c) {
    return isalpha(c);
}

int isNumber(char c) {
    return isdigit(c);
}

//returns 1 if a character is a special symbol, 0 otherwise
int isASpecialSymbol(char input)
{
    int i;
    for(i=0; i < 13; i++)
    {
        if(input == symbols[i])
            return 1;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    //char* InputFile = argv[1];
    char* InputFile = "input.txt";
    FILE *input_f = fopen(InputFile, "r");
    FILE *output_f = fopen("output.txt", "w");

    char ch;
    char buffer[MAX]; //without white space
    int size = 0;
    int i = 0;

    while (fscanf(input_f, "%c", &ch) != EOF)
    {
        buffer[i++] = ch;
        size++;
    }

    //print the sourse program 
    printf("Source Program:\n");
    printf(buffer);
    printf("\n");
    fprintf(output_f, "Source Program:\n%s\n", buffer); 

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

        //reserved words
        //const, var, procedure, call, begin, end, if, fi, then, else, while, do, read, write
        if (buffer[i] >= 'a' && buffer[i] <= 'z') {
            switch ((int) buffer[i]) {
                case (int) 'c':
                    if ((buffer[i+1] == 'o') && (buffer[i+2] == 'n') && (buffer[i+3] == 's') && (buffer[i+4] == 't')) {
                        i+=4;
                        tokens[tokenSize] = constsym;
                        tokenSize++;
                        continue;
                    }
                    else if ((buffer[i+1] == 'a') && (buffer[i+2] == 'l') && (buffer[i+3] == 'l')) {
                        i+=3;
                        tokens[tokenSize] = callsym;
                        tokenSize++;
                        continue;
                    }
                case (int) 'v':
                    if((buffer[i+1] == 'a') && (buffer[i+2] == 'r')) {
						i+=2;
						tokens[tokenSize] = varsym;
						tokenSize++;
						continue;
					}
                case (int) 'p':
                    if ((buffer[i+1] == 'r') && (buffer[i+2] == 'o') && (buffer[i+3] == 'c') && (buffer[i+4] == 'e') && (buffer[i+5] == 'd') && (buffer[i+6] == 'u') && (buffer[i+7] == 'r') && (buffer[i+8] == 'e')) {
                        i+=8;
                        tokens[tokenSize] = procsym;
                        tokenSize++;
                        continue;
                    }    
                case (int) 'b':
                    if ((buffer[i+1] == 'e') && (buffer[i+2] == 'g') && (buffer[i+3] == 'i') && (buffer[i+4] == 'n')) {
                        i += 4;
                        tokens[tokenSize] = beginsym;
                        tokenSize++;
                        continue;
                    }
                
                case (int) 'e':
                    if ((buffer[i+1] == 'n') && (buffer[i+2] == 'd')) {
                        i+=2;
                        tokens[tokenSize] = endsym;
                        tokenSize++;
                        continue;
                    }
                    else if ((buffer[i+1] == 'l') && (buffer[i+2] == 's') && (buffer[i+3] == 'e')) {
                        i+=3;
                        tokens[tokenSize] = elsesym;
                        tokenSize++;
                        continue;
                    }
                case (int) 'i':
                    if (buffer[i+1] == 'f') {
                        i += 1;
                        tokens[tokenSize] = ifsym;
                        tokenSize++;
                        continue;
                    }
                case (int) 't':
                    if ((buffer[i+1] == 'h') && (buffer[i+2] == 'e') && (buffer[i+3] == 'n')) {
                        i += 3;
                        tokens[tokenSize] = thensym;
                        tokenSize++;
                        continue;
                    }
                case (int) 'w':
                    if ((buffer[i+1] == 'h') && (buffer[i+2] == 'i') && (buffer[i+3] == 'l') && (buffer[i+4] == 'e')) {
                        i += 4;
                        tokens[tokenSize] = whilesym;
                        tokenSize++;
                        continue;
                    }
                    else if ((buffer[i+1] == 'r') && (buffer[i+2] == 'i') && (buffer[i+3] == 't') && (buffer[i+4] == 'e')) {
                        i += 4;
                        tokens[tokenSize] = writesym;
                        tokenSize++;
                        continue;
                    }
                case (int) 'd':
                    if (buffer[i+1] == 'o') {
                        i+=1;
                        tokens[tokenSize] = dosym;
                        tokenSize++;
                        continue;
                    }
                case (int) 'o':
                    if ((buffer[i+1] == 'd') && (buffer[i+2] == 'd')) {
                        i+=2;
                        tokens[tokenSize] = fisym;
                        tokenSize++;
                        continue;
                    }
                case (int) 'r':
                    if ((buffer[i+1] == 'e') && (buffer[i+2] == 'a') && (buffer[i+3] == 'd')) {
                        i+=3;
                        tokens[tokenSize] = readsym;
                        tokenSize++;
                        continue;
                    }

                //if it's not a reserved word
                default:
                    break;
            }
        }
    }

    //Print output statements 
    printf("Lexeme Table:\n");
    printf("\nlexemetoken\ttype\n");
}
