%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);
int yylex();

// Symbol table
int symbols[52];
int symbolVal(char symbol);
void updateSymbolVal(char symbol, int val);
%}

%token TYPE_INT TYPE_FLOAT TYPE_STRING TYPE_CHAR TYPE_BOOL
%token CONSTANT_DECLARE
%token CONDITIONAL_WHEN CONDITIONAL_UNLESS CONDITIONAL_OTHERWISE
%token LOOP_FOR LOOP_WHILE
%token BOOLEAN_TRUE BOOLEAN_FALSE
%token OP_INCREMENT OP_DECREMENT
%token OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MULT_ASSIGN OP_DIV_ASSIGN
%token OP_PLUS OP_MINUS OP_DIVIDE OP_MULTIPLY
%token OP_BITWISE_AND OP_BITWISE_XOR OP_BITWISE_OR
%token OP_LOGICAL_AND OP_LOGICAL_XOR OP_LOGICAL_OR
%token OP_GREATER OP_GREATER_EQUAL OP_LESS OP_LESS_EQUAL OP_EQUAL
%token FUNC_DECLARE FUNC_RETURN
%token IO_WRITE IO_READ
%token ARROW PAREN_OPEN PAREN_CLOSE BRACE_OPEN BRACE_CLOSE
%token TYPE_DECLARE STMT_END OP_ASSIGN
%token BRACKET_OPEN BRACKET_CLOSE DELIMITER_COMMA
%token IDENTIFIER
%token INTEGER_POSITIVE INTEGER_NEGATIVE FLOAT_POSITIVE FLOAT_NEGATIVE
%token LITERAL_STRING LITERAL_CHAR

%%

program:
    /* empty */ 
    | program statement
    ;

statement:
    declaration
    | assignment
    | conditional
    | loop
    | function_decl
    | function_call
    | io_statement
    ;

declaration:
    type IDENTIFIER STMT_END
    | type IDENTIFIER OP_ASSIGN expression STMT_END
    | CONSTANT_DECLARE type IDENTIFIER OP_ASSIGN expression STMT_END
    ;

type:
    TYPE_INT
    | TYPE_FLOAT
    | TYPE_STRING
    | TYPE_CHAR
    | TYPE_BOOL
    ;

assignment:
    IDENTIFIER OP_ASSIGN expression STMT_END
    | IDENTIFIER OP_PLUS_ASSIGN expression STMT_END
    | IDENTIFIER OP_MINUS_ASSIGN expression STMT_END
    | IDENTIFIER OP_MULT_ASSIGN expression STMT_END
    | IDENTIFIER OP_DIV_ASSIGN expression STMT_END
    | IDENTIFIER OP_INCREMENT STMT_END
    | IDENTIFIER OP_DECREMENT STMT_END
    ;

expression:
    term
    | expression OP_PLUS term
    | expression OP_MINUS term
    ;

term:
    factor
    | term OP_MULTIPLY factor
    | term OP_DIVIDE factor
    ;

factor:
    IDENTIFIER
    | INTEGER_POSITIVE
    | INTEGER_NEGATIVE
    | FLOAT_POSITIVE
    | FLOAT_NEGATIVE
    | BOOLEAN_TRUE
    | BOOLEAN_FALSE
    | LITERAL_STRING
    | LITERAL_CHAR
    | PAREN_OPEN expression PAREN_CLOSE
    ;

conditional:
    CONDITIONAL_WHEN PAREN_OPEN expression PAREN_CLOSE BRACE_OPEN program BRACE_CLOSE
    | CONDITIONAL_WHEN PAREN_OPEN expression PAREN_CLOSE BRACE_OPEN program BRACE_CLOSE CONDITIONAL_OTHERWISE BRACE_OPEN program BRACE_CLOSE
    | CONDITIONAL_UNLESS PAREN_OPEN expression PAREN_CLOSE BRACE_OPEN program BRACE_CLOSE
    ;

loop:
    LOOP_FOR PAREN_OPEN statement expression STMT_END expression PAREN_CLOSE BRACE_OPEN program BRACE_CLOSE
    | LOOP_WHILE PAREN_OPEN expression PAREN_CLOSE BRACE_OPEN program BRACE_CLOSE
    ;

function_decl:
    FUNC_DECLARE IDENTIFIER PAREN_OPEN param_list PAREN_CLOSE type_return BRACE_OPEN program BRACE_CLOSE
    ;

type_return:
    /* empty */
    | ARROW type
    ;

param_list:
    /* empty */
    | param
    | param_list DELIMITER_COMMA param
    ;

param:
    type IDENTIFIER
    ;

function_call:
    IDENTIFIER PAREN_OPEN arg_list PAREN_CLOSE STMT_END
    ;

arg_list:
    /* empty */
    | expression
    | arg_list DELIMITER_COMMA expression
    ;

io_statement:
    IO_WRITE PAREN_OPEN expression PAREN_CLOSE STMT_END
    | IO_READ PAREN_OPEN IDENTIFIER PAREN_CLOSE STMT_END
    ;

%%

int symbolVal(char symbol) {
    int bucket = (symbol >= 'a' && symbol <= 'z') ? symbol - 'a' : symbol - 'A' + 26;
    return symbols[bucket];
}

void updateSymbolVal(char symbol, int val) {
    int bucket = (symbol >= 'a' && symbol <= 'z') ? symbol - 'a' : symbol - 'A' + 26;
    symbols[bucket] = val;
}

int main(void) {
    /* Initialize symbol table */
    int i;
    for(i = 0; i < 52; i++) {
        symbols[i] = 0;
    }
    
    return yyparse();
}

void yyerror(char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}