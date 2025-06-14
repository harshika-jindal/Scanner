// Sophia Kropivnitskaia and Harshika Jindal
// Course: Systems Software
// Semester: Summer 2025
// HW 2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_ID_LEN 11
#define MAX_NUM_LEN 5
#define MAX_LINE_LEN 256

typedef enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, 
    multsym = 6,  slashsym = 7, fisym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, 
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, 
    readsym = 32, elsesym = 33

} tokenType;

int hasError = 0;

// reserved words
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


int isLetter(char c) 
{
    return isalpha(c);
}

int isNumber(char c) 
{
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
void printSourceProgram(FILE *input) {
    char buffer[MAX_LINE_LEN];
    printf("Source Program:\n");
    rewind(input);
    while (fgets(buffer, sizeof(buffer), input)) {
        printf("%s", buffer);
    }
    rewind(input);
    
}

//reserved words
//const, var, procedure, call, begin, end, if, fi, then, else, while, do, read, write
int isReservedWord(const char* id) {
    if (strcmp(id, "const") == 0) return constsym;
    if (strcmp(id, "var") == 0) return varsym;
    if (strcmp(id, "procedure") == 0) return procsym;
    if (strcmp(id, "call") == 0) return callsym;
    if (strcmp(id, "begin") == 0) return beginsym;
    if (strcmp(id, "end") == 0) return endsym;
    if (strcmp(id, "if") == 0) return ifsym;
    if (strcmp(id, "then") == 0) return thensym;
    if (strcmp(id, "fi") == 0) return fisym;
    if (strcmp(id, "else") == 0) return elsesym;
    if (strcmp(id, "while") == 0) return whilesym;
    if (strcmp(id, "do") == 0) return dosym;
    if (strcmp(id, "read") == 0) return readsym;
    if (strcmp(id, "write") == 0) return writesym;
    return 0; // not a reserved word
}

// scans the source file for tokens and prints both the lexeme table and token list.
void scanTokens(FILE *input) {
    char buffer[MAX_LINE_LEN];

    printf("\nLexeme Table:\n\nlexeme\t\ttoken type\n");

    while (fgets(buffer, sizeof(buffer), input)) {
        int i = 0;
        while (buffer[i] != '\0') {
            char c = buffer[i];

            // checks for white space
            if (isspace(c)) { 
                i++; 
                continue; 
            }

            if (buffer[i] == '/' && buffer[i + 1] == '*') {
                int j = i + 2;

                while (!(buffer[j] == '*' && buffer[j + 1] == '/')) 
                {
                    j++;
                }
                i = j + 2;
                continue;
            }

            //processes identifiers and reserved words.
            if (isLetter(c)) {
                char id[100]; 
                int j = 0;
                while (isLetter(buffer[i]) || isNumber(buffer[i])) 
                {
                    if (j < 99) id[j++] = buffer[i];
                    i++;
                }
                id[j] = '\0';

                if (strlen(id) > MAX_ID_LEN) {
                    printf("%s\t\tError: Identifier too long\n", id); 
                    hasError = 1;
                } else {
                    int token = isReservedWord(id);

                    if (token) printf("%s\t\t%d\n", id, token);

                    else printf("%s\t\t%d\n", id, identsym);
                }

                continue;
            }
            // handles numeric literals and checks their length.
            if (isNumber(c)) {
                char num[100]; 
                int j = 0;
                while (isNumber(buffer[i])) 
                {
                    if (j < 99) num[j++] = buffer[i];
                    i++;
                }
                num[j] = '\0';
                if (strlen(num) > MAX_NUM_LEN) {
                    printf("%s\t\tError: Number too long\n", num); 
                    hasError = 1;
                } else {
                    printf("%s\t\t%d\n", num, numbersym);
                }
                continue;
            }

            //  handles special symbols.
            switch (c) {

                case '+': printf("+\t\t%d\n", plussym); break;
                case '-': printf("-\t\t%d\n", minussym); break;
                case '*': printf("*\t\t%d\n", multsym); break;
                case '/': printf("/\t\t%d\n", slashsym); break;
                case '(': printf("(\t\t%d\n", lparentsym); break;
                case ')': printf(")\t\t%d\n", rparentsym); break;
                case '=': printf("=\t\t%d\n", eqlsym); break;
                case ',': printf(",\t\t%d\n", commasym); break;
                case '.': printf(".\t\t%d\n", periodsym); break;
                case '<':
                    if (buffer[i+1] == '=') { printf("<=\t\t%d\n", leqsym); i++; }
                    else if (buffer[i+1] == '>') { printf("<>\t\t%d\n", neqsym); i++; }
                    else { printf("<\t\t%d\n", lessym); }
                    break;

                case '>':
                    if (buffer[i+1] == '=') { printf(">=\t\t%d\n", geqsym); i++; }
                    else { printf(">\t\t%d\n", gtrsym); }
                    break;

                case ';': printf(";\t\t%d\n", semicolonsym); break;
                
                case ':':
                    if (buffer[i+1] == '=') { printf(":=\t\t%d\n", becomessym); i++; }
                    else { printf(":\t\tError: invalid symbol\n"); hasError = 1; }
                    break;
                default:
                    printf("\t\tError: invalid symbol \"%c\"\n", c); hasError = 1; break;
            }
            i++;
        }
    }

    if (!hasError) {
        rewind(input);
        printf("\nToken List:\n");
        while (fgets(buffer, sizeof(buffer), input)) 
        {
            int i = 0;
            while (buffer[i] != '\0') 
            {
                char c = buffer[i];
                if (isspace(c)) {
                    i++; 
                    continue; 
                }

                if (isLetter(c)) {
                    char id[100]; int j = 0;
                    while (isLetter(buffer[i]) || isNumber(buffer[i])) 
                    {
                        if (j < 99) id[j++] = buffer[i];
                        i++;
                    }
                    id[j] = '\0';
                    int token = isReservedWord(id);
                    if (token) printf("%d ", token);
                    else printf("%d %s ", identsym, id);
                    continue;
                }

                if (isNumber(c)) {
                    char num[100]; int j = 0;
                    while (isNumber(buffer[i])) 
                    {
                        if (j < 99) num[j++] = buffer[i];
                        i++;
                    }
                    num[j] = '\0';
                    printf("%d %s ", numbersym, num);
                    continue;
                }

                switch (c) {
                    case '+': printf("%d ", plussym); break;
                    case '-': printf("%d ", minussym); break;
                    case '*': printf("%d ", multsym); break;
                    case '/': printf("%d ", slashsym); break;
                    case '(': printf("%d ", lparentsym); break;
                    case ')': printf("%d ", rparentsym); break;
                    case '=': printf("%d ", eqlsym); break;
                    case ',': printf("%d ", commasym); break;
                    case '.': printf("%d ", periodsym); break;
                    case '<':
                        if (buffer[i+1] == '=') { printf("%d ", leqsym); i++; }
                        else if (buffer[i+1] == '>') { printf("%d ", neqsym); i++; }
                        else { printf("%d ", lessym); }
                        break;
                    case '>':
                        if (buffer[i+1] == '=') { printf("%d ", geqsym); i++; }
                        else { printf("%d ", gtrsym); }
                        break;
                    case ';': printf("%d ", semicolonsym); break;
                    case ':':
                        if (buffer[i+1] == '=') { printf("%d ", becomessym); i++; }
                        break;
                }
                i++;
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }    

    char* InputFile = argv[1];
    //char* InputFile = "input.txt";
    FILE *input = fopen(InputFile, "r");
    if (!input) {
        perror("Error opening file");
        return 1;
    }

    printSourceProgram(input);
    scanTokens(input);
    fclose(input);
    return 0;
}
