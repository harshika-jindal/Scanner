
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h


#define MAX_ID_LEN 11
#define MAX_NUM_LEN 5
#define MAX_LINE_LEN 256


typedef enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, 
multsym = 6,  slashsym = 7, fisym = 8,  eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, 
beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, 
readsym = 32, elsesym = 33

} tokenType;


// reserved words

typedef char *words[]
{
    "const", "var", "procedure", "call", "begin", "end", "if",
     "fi", "then", "else", "while", "do", "read","write"
}
reservedWords;

//special Symbols

char symbols[] = {'+', '-', '*', '/', '(', ')', '=', ',','.', '<', '>', ';' , ':'};


int isLetter(char input){
    if isalpha(input)
        return 1;

    return 0;
}

int isnumber(char input){
    if isdigit(input)
        return 1;

    return 0;
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



