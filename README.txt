Homework 2: Lexical Analyzer
Sophia Kropivnitskaia and Harshika Jindal

Description: Implementation of a lexical analyzer for the programming language PL/0. Program reads a source program written in
PL/0, identifies some errors and produces an output: source program, lexeme table, and the token list.

Compilation Instructions:
gcc lex.c -o lex
lex.exe input.txt > output.txt

Usage:
The required argument is the input file, where the source program will be read from. 

Example:
Input File:
var x, y;
begin
y := 3;
x := y + 56;
end

Output File:
               
Source Program:
var x, y;
begin
y := 3;
x := y + 56;
end.

Lexeme Table:

lexeme token type
var   29
x     2
,     17
y     2
;     18
begin 21
y     2
:=    20
3     3
;     18
x     2
:=    20
y     2
+     4
56    3
;     18
end   22
.     19

Token List:
29 2 x 17 2 y 18 21 2 y 20 3 3 18 2 x 20 2 y 4 3 56 18 22 19

