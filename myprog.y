%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define TypeInfo structure
struct TypeInfo {
    enum {
        TYPE_INTEGER,
        TYPE_FLOAT,
        TYPE_STRING,
        TYPE_CHAR,
        TYPE_BOOLEAN
    } type;
    
    union {
        int int_val;
        float float_val;
        char* str_val;
        char char_val;
        int bool_val;
    } value;
};

// Symbol table structure
#define MAX_SYMBOLS 1000

struct Symbol {
    char* name;
    struct TypeInfo type_info;
    int is_initialized;
};

struct Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

// Function declarations
void add_symbol(char* name, struct TypeInfo type_info);
struct Symbol* lookup_symbol(char* name);

void yyerror(char *s);
int yylex();

// Symbol table
int symbols[52];
int symbolVal(char symbol);
void updateSymbolVal(char symbol, int val);
%}

// Add semantic value types
%union {
    int int_val;
    float float_val;
    char* str_val;
    struct TypeInfo type_info;
}

// Modify token declarations to include types
%token <str_val> IDENTIFIER
%token <int_val> INTEGER_POSITIVE INTEGER_NEGATIVE
%token <float_val> FLOAT_POSITIVE FLOAT_NEGATIVE
%token <str_val> LITERAL_STRING LITERAL_CHAR

// Add type for non-terminals
%type <type_info> type expression
%type <type_info> term factor

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
    | IDENTIFIER TYPE_DECLARE type OP_ASSIGN expression STMT_END {
        struct TypeInfo type_info;
        type_info.type = $3.type;
        
        // Type checking
        if ($3.type != $5.type) {
            yyerror("Type mismatch in assignment");
        } else {
            add_symbol($1, type_info);
        }
    }
    ;

type:
    TYPE_INT     { $$.type = TYPE_INTEGER; }
    | TYPE_FLOAT { $$.type = TYPE_FLOAT; }
    | TYPE_STRING { $$.type = TYPE_STRING; }
    | TYPE_CHAR  { $$.type = TYPE_CHAR; }
    | TYPE_BOOL  { $$.type = TYPE_BOOLEAN; }
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
    term { 
        $$.type = $1.type;
        $$.value = $1.value;
    }
    | expression OP_PLUS term {
        if ($1.type != $3.type) {
            yyerror("Type mismatch in addition");
        } else {
            $$.type = $1.type;
            switch($1.type) {
                case TYPE_INTEGER:
                    $$.value.int_val = $1.value.int_val + $3.value.int_val;
                    break;
                case TYPE_FLOAT:
                    $$.value.float_val = $1.value.float_val + $3.value.float_val;
                    break;
                default:
                    yyerror("Invalid type for addition");
            }
        }
    }
    | expression OP_MINUS term {
        if ($1.type != $3.type) {
            yyerror("Type mismatch in subtraction");
        } else {
            $$.type = $1.type;
            switch($1.type) {
                case TYPE_INTEGER:
                    $$.value.int_val = $1.value.int_val - $3.value.int_val;
                    break;
                case TYPE_FLOAT:
                    $$.value.float_val = $1.value.float_val - $3.value.float_val;
                    break;
                default:
                    yyerror("Invalid type for subtraction");
            }
        }
    }
    ;

term:
    factor {
        $$.type = $1.type;
        $$.value = $1.value;
    }
    | term OP_MULTIPLY factor {
        if ($1.type != $3.type) {
            yyerror("Type mismatch in multiplication");
        } else {
            $$.type = $1.type;
            switch($1.type) {
                case TYPE_INTEGER:
                    $$.value.int_val = $1.value.int_val * $3.value.int_val;
                    break;
                case TYPE_FLOAT:
                    $$.value.float_val = $1.value.float_val * $3.value.float_val;
                    break;
                default:
                    yyerror("Invalid type for multiplication");
            }
        }
    }
    | term OP_DIVIDE factor {
        if ($1.type != $3.type) {
            yyerror("Type mismatch in division");
        } else {
            $$.type = $1.type;
            switch($1.type) {
                case TYPE_INTEGER:
                    if ($3.value.int_val == 0) {
                        yyerror("Division by zero");
                    } else {
                        $$.value.int_val = $1.value.int_val / $3.value.int_val;
                    }
                    break;
                case TYPE_FLOAT:
                    if ($3.value.float_val == 0.0) {
                        yyerror("Division by zero");
                    } else {
                        $$.value.float_val = $1.value.float_val / $3.value.float_val;
                    }
                    break;
                default:
                    yyerror("Invalid type for division");
            }
        }
    }
    ;

factor:
    IDENTIFIER {
        struct Symbol* sym = lookup_symbol($1);
        if (sym == NULL) {
            yyerror("Undefined variable");
        } else {
            $$.type = sym->type_info.type;
            $$.value = sym->type_info.value;
        }
    }
    | INTEGER_POSITIVE {
        $$.type = TYPE_INTEGER;
        $$.value.int_val = $1;
    }
    | INTEGER_NEGATIVE {
        $$.type = TYPE_INTEGER;
        $$.value.int_val = $1;
    }
    | FLOAT_POSITIVE {
        $$.type = TYPE_FLOAT;
        $$.value.float_val = $1;
    }
    | FLOAT_NEGATIVE {
        $$.type = TYPE_FLOAT;
        $$.value.float_val = $1;
    }
    | BOOLEAN_TRUE {
        $$.type = TYPE_BOOLEAN;
        $$.value.bool_val = 1;
    }
    | BOOLEAN_FALSE {
        $$.type = TYPE_BOOLEAN;
        $$.value.bool_val = 0;
    }
    | LITERAL_STRING {
        $$.type = TYPE_STRING;
        $$.value.str_val = strdup($1);
    }
    | LITERAL_CHAR {
        $$.type = TYPE_CHAR;
        $$.value.char_val = $1[0];
    }
    | PAREN_OPEN expression PAREN_CLOSE {
        $$.type = $2.type;
        $$.value = $2.value;
    }
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

void add_symbol(char* name, struct TypeInfo type_info) {
    if (symbol_count >= MAX_SYMBOLS) {
        yyerror("Symbol table full");
        return;
    }
    
    struct Symbol* existing = lookup_symbol(name);
    if (existing != NULL) {
        yyerror("Variable already declared");
        return;
    }
    
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type_info = type_info;
    symbol_table[symbol_count].is_initialized = 1;
    symbol_count++;
}

struct Symbol* lookup_symbol(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    return NULL;
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