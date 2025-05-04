%{
    #include <stdlib.h>
    #include "eon.h"
    #include "y.tab.h"
    int multiline_comment_start = 0;
    char currentType[32];
    char currentID[32];
    char currentValue[32];
    char currentOp[10];
    int globalScope = 0;
    void yyerror(char *);
%}

%option yylineno
WHITESPACE          [ \t\r\f\v]+
%x COMMENT


%%

{WHITESPACE}                ;

"-*"                        {multiline_comment_start = yylineno; BEGIN COMMENT;}

<COMMENT>.|{WHITESPACE}     ;
<COMMENT>\n                 ;
<COMMENT>"*-"               {BEGIN INITIAL;}
<COMMENT><<EOF>>            {yyterminate();}
"---".*                     {;}


"True"              { yylval.integer = 1; return INTEGER; }
"False"             { yylval.integer = 0; return INTEGER; }
"bool"   	        {return TYPE_BOOLEAN;}
"method"            {return FUNCTION;}
"ENDF"		        {return END_FUNCTION;}
"return"            {return RETURN;}
"when"              {return IF;}
"otherwise"         {return ELSE;}
"unless"            {return ELSE_IF;}
"cnloop"            {return WHILE;}
"ctloop"		    {return FOR;}
"try"		        {return TRY;}
"catch"		        {return CATCH;}
"finally"		    {return FINALLY;}
"throw"             {return THROW;}
"ArithmeticException" {yylval.integer = ARITHMETIC_EXCEPTION; return INTEGER;}
"select"	        {return SWITCH;}
"option"		        {return CASE;}
"break"		        {return BREAK;}
"contiune"	        {return CONTINUE;}
"write"	            {return PRINT;}
"input"	            {return SCAN;}


"^"             {return POW;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return MULTIPLE;}
"/"             {return DIVIDE;}
"%"             {return MOD;}
"<"             {return LESSTHAN;}
">"             {return GREATERTHAN;}
"++"		    {return INCREASE;}
"--"		    {return DECREASE;}
":"		        {return COLON;}
"::"            {return ASSIGN;}

","		        {return COMMA;}
">="		    {return EQUALORGREAT;}
"<="	        {return EQUALORLESS;}
"=="		    {return EQUAL;}
"!="		    {return ISNOTEQUAL;}
"&&"		    {return LOGICAL_AND_OPERATOR;}
"||"		    {return OR;}
"("		        {return LEFT_PARENTHESIS;}
")"		        {return RIGHT_PARENTHESIS;}
"{"		        {return LEFT_BRACE;}
"}"		        {return RIGHT_BRACE;}
\[		        {return LEFTSQRBR;}
\]		        {return RIGHTSQRBR;}
\"		        {return QUOTES;}


0                           {yylval.integer = atoi(yytext); return INTEGER; }
[1-9][0-9]*                 {yylval.integer = atoi(yytext); return INTEGER; }

[a-zA-Z_][a-zA-Z0-9_]*     {
    strncpy(yylval.id_name, yytext, MAX_ID_LENGTH-1);
    yylval.id_name[MAX_ID_LENGTH-1] = '\0';
    return IDENTIFIER;
}

[-()<>=+*/;{}.]             {return *yytext; }
[ \t\n]		                ;
.		                    yyerror("Unknown character");
%%

int yywrap (void) {return 1;}