%{
#include "y.tab.h"
void yyerror (char *s);
int yylex();
%}

%%
[ \t\r\n]+     ; 

"---".*         { printf("SINGLE_LINE_COMMENT\n"); }
"-*"([^-]|-+[^*])*"*-" { printf("MULTI_LINE_COMMENT\n"); }

"int"           { printf("TYPE_INT\n"); }
"float"         { printf("TYPE_FLOAT\n"); }
"string"        { printf("TYPE_STRING\n"); }
"ch"            { printf("TYPE_CHAR\n"); }
"bool"          { printf("TYPE_BOOL\n"); }

"CON"           { printf("CONSTANT_DECLARE\n"); }

"when"          { printf("CONDITIONAL_WHEN\n"); }
"unless"        { printf("CONDITIONAL_UNLESS\n"); }
"otherwise"     { printf("CONDITIONAL_OTHERWISE\n"); }
"ctloop"        { printf("LOOP_FOR\n"); }
"cnloop"        { printf("LOOP_WHILE\n"); }

"True"          { printf("BOOLEAN_TRUE\n"); }
"False"         { printf("BOOLEAN_FALSE\n"); }

"++"            { printf("OP_INCREMENT\n"); }
"--"            { printf("OP_DECREMENT\n"); }
"+="            { printf("OP_PLUS_ASSIGN\n"); }
"-="            { printf("OP_MINUS_ASSIGN\n"); }
"*="            { printf("OP_MULT_ASSIGN\n"); }
"/="            { printf("OP_DIV_ASSIGN\n"); }
"+"             { printf("OP_PLUS\n"); }
"-"             { printf("OP_MINUS\n"); }
"/"             { printf("OP_DIVIDE\n"); }
"*"             { printf("OP_MULTIPLY\n"); }
"&"             { printf("OP_BITWISE_AND\n"); }
"^"             { printf("OP_BITWISE_XOR\n"); }
"|"             { printf("OP_BITWISE_OR\n"); }
"&&"            { printf("OP_LOGICAL_AND\n"); }
"^^"            { printf("OP_LOGICAL_XOR\n"); }
"||"            { printf("OP_LOGICAL_OR\n"); }
">"             { printf("OP_GREATER\n"); }
">="            { printf("OP_GREATER_EQUAL\n"); }
"<"             { printf("OP_LESS\n"); }
"<="            { printf("OP_LESS_EQUAL\n"); }
"=="            { printf("OP_EQUAL\n"); }

"method"        { printf("FUNC_DECLARE\n"); }
"return"        { printf("FUNC_RETURN\n"); }

"write"         { printf("IO_WRITE\n"); }
"input"         { printf("IO_READ\n"); }

"->"            { printf("ARROW\n"); }
"("             { printf("PAREN_OPEN\n"); }
")"             { printf("PAREN_CLOSE\n"); }
"{"             { printf("BRACE_OPEN\n"); }
"}"             { printf("BRACE_CLOSE\n"); }
"::"            { printf("TYPE_DECLARE\n"); }
":"             { printf("STMT_END\n"); }
"="             { printf("OP_ASSIGN\n"); }
"["             { printf("BRACKET_OPEN\n"); }
"]"             { printf("BRACKET_CLOSE\n"); }
","             { printf("DELIMITER_COMMA\n"); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER\n"); }

\+?[0-9]+      { printf("INTEGER_POSITIVE\n"); }
-[0-9]+        { printf("INTEGER_NEGATIVE\n"); }
\+?[0-9]+\.[0-9]+  { printf("FLOAT_POSITIVE\n"); }
-[0-9]+\.[0-9]+    { printf("FLOAT_NEGATIVE\n"); }

'([^'\\]|\\.)*'  { printf("LITERAL_STRING\n"); }
\"([^"\\]|\\.)\"  { printf("LITERAL_CHAR\n"); }
.               { printf("INVALID_TOKEN\n"); } 
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}