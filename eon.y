%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <setjmp.h>  /* For exception handling */
    #include <string.h>  /* For function handling */
    #include "eon.h"
    #include "y.tab.h"

    /* Function-related data structures */
    #define MAX_FUNCTIONS 100
    #define MAX_PARAMS 10
    
    typedef struct {
        char name;               /* Single char function name */
        nodeType *body;          /* Function body */
        int param_count;         /* Number of parameters */
        char params[MAX_PARAMS]; /* Parameter names (single chars) */
    } Function;
    
    Function functions[MAX_FUNCTIONS];
    int function_count = 0;
    
    /* Call stack for managing function calls */
    #define MAX_CALL_DEPTH 100
    int call_stack[MAX_CALL_DEPTH][26];  /* Store local vars for each stack frame */
    int current_frame = -1;              /* Current stack frame */
    int in_function_call = 0;            /* Flag to indicate if we're executing a function */
    int return_value = 0;                /* Return value from function */
    int has_returned = 0;                /* Flag to indicate if function has returned */
    
    /* Function to register a new function */
    int register_function(char name, nodeType *body, int param_count, char *params);
    
    /* Function to find a function by name */
    int find_function(char name);
    
    /* Function call handling */
    int call_function(int func_idx, int arg_count, ...);

    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *con(int value);
    nodeType *func_call(char name, nodeType *args);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    int yylex(void);
    void yyerror(char *s);
    int sym[26];  /* Global symbol table */

    /* Exception handling data structures */
    #define MAX_EXCEPTION_HANDLERS 20
    ExceptionHandler exception_handlers[MAX_EXCEPTION_HANDLERS];
    int current_handler = -1;

    /* Push/pop exception handlers */
    int push_handler() {
        if (current_handler >= MAX_EXCEPTION_HANDLERS - 1) {
            fprintf(stderr, "Too many nested try blocks\n");
            exit(1);
        }
        current_handler++;
        exception_handlers[current_handler].active = 1;
        return current_handler;
    }

    void pop_handler() {
        if (current_handler >= 0) {
            exception_handlers[current_handler].active = 0;
            current_handler--;
        }
    }

    /* Throw an exception */
    void throw_exception(int type, int value) {
        if (current_handler >= 0) {
            exception_handlers[current_handler].exception_type = type;
            exception_handlers[current_handler].exception_value = value;
            longjmp(exception_handlers[current_handler].env, 1);
        } else {
            fprintf(stderr, "Unhandled exception: %d (value: %d)\n", type, value);
            exit(1);
        }
    }
%}

// Yacc definitions

%union {
    int integer;                 
    char ide;               
    nodeType *nPtr;             
};


%token <integer> INTEGER
%token <ide> IDENTIFIER
%token WHILE IF PRINT  ELSE_IF END_WHILE COMMENTLINE OPENCOMMENT CLOSECOMMENT TRUE FALSE TYPE_BOOLEAN STR DINT FLOATING_POINT
%token FUNCTION END_FUNCTION RETURN ELSE DO FOR END_FOR SWITCH CASE IMPORT BREAK CONTINUE ASSIGN
%token SCAN POW PLUS MINUS MULTIPLE DIVIDE MOD LESSTHAN GREATERTHAN NL INCREASE DECREASE
%token COLON SEMICOLON COMMA EQUALORGREAT EQUALORLESS EQUAL ISNOTEQUAL LOGICAL_AND_OPERATOR OR LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE RIGHT_BRACE  LEFTSQRBR RIGHTSQRBR QUOTES
%token TRY CATCH FINALLY THROW

%nonassoc IFX
%nonassoc ELSE

%left EQUALORGREAT EQUALORLESS
%left EQUAL ISNOTEQUAL
%left GREATERTHAN LESSTHAN
%left PLUS MINUS
%left MULTIPLE DIVIDE
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list try_catch_stmt catch_clauses catch_clause finally_clause throw_stmt param_list args_list function_decl function_call return_stmt

%%


program:
        function_defs           { exit(0); }
        ;

function_defs:
          function_defs function_decl  { /* Store function definition */ }
        | function_defs stmt           { ex($2); freeNode($2); }
        |
        ;

function_decl:
        FUNCTION IDENTIFIER LEFT_PARENTHESIS param_list RIGHT_PARENTHESIS LEFT_BRACE stmt_list RIGHT_BRACE END_FUNCTION
        {
            /* Extract parameter names from param_list */
            char params[MAX_PARAMS];
            int param_count = 0;
            
            nodeType *param = $4;
            while (param && param->type == typeOpr && param->opr.oper == COMMA) {
                /* Extract rightmost parameter first */
                if (param->opr.op[1]->type == typeId) {
                    params[param_count++] = param->opr.op[1]->id.i;
                }
                param = param->opr.op[0]; /* Move to next parameter */
            }
            /* Handle the last/only parameter */
            if (param && param->type == typeId) {
                params[param_count++] = param->id.i;
            }
            
            /* Reverse parameter order since we extracted right-to-left */
            for (int i = 0; i < param_count / 2; i++) {
                char temp = params[i];
                params[i] = params[param_count - i - 1];
                params[param_count - i - 1] = temp;
            }
            
            /* Register the function */
            register_function($2, $7, param_count, params);
            $$ = NULL; /* No execution result for function declaration */
        }
        ;

param_list:
        IDENTIFIER                      { $$ = id($1); }
        | param_list COMMA IDENTIFIER   { $$ = opr(COMMA, 2, $1, id($3)); }
        |                               { $$ = NULL; } /* Empty parameter list */
        ;

function_call:
        IDENTIFIER LEFT_PARENTHESIS args_list RIGHT_PARENTHESIS
        {
            $$ = opr(FUNCTION, 2, id($1), $3); /* First arg is function name, second is args list */
        }
        ;

args_list:
        expr                    { $$ = $1; }
        | args_list COMMA expr  { $$ = opr(COMMA, 2, $1, $3); }
        |                       { $$ = NULL; } /* Empty args list */
        ;

return_stmt:
        RETURN expr COLON       { $$ = opr(RETURN, 1, $2); }
        ;

stmt:
        COLON                        { $$ = opr(COLON, 2, NULL, NULL); }
        | expr COLON                 { $$ = $1; }
        | PRINT expr COLON           { $$ = opr(PRINT, 1, $2); }
        | IDENTIFIER ASSIGN expr COLON  { $$ = opr(ASSIGN, 2, id($1), $3); }
        | WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt       { $$ = opr(WHILE, 2, $3, $5); }
        | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        | LEFT_BRACE stmt_list RIGHT_BRACE            { $$ = $2; }
        | Comment stmt_list         {;}
        | try_catch_stmt            { $$ = $1; }
        | throw_stmt                { $$ = $1; }
        | function_call COLON       { $$ = $1; }
        | return_stmt               { $$ = $1; }
        ;

/* Try-catch statement grammar rules */
try_catch_stmt:
        TRY stmt catch_clauses                { $$ = opr(TRY, 2, $2, $3); }
        | TRY stmt catch_clauses finally_clause { $$ = opr(TRY, 3, $2, $3, $4); }
        ;

catch_clauses:
        catch_clause                          { $$ = $1; }
        | catch_clauses catch_clause          { $$ = opr(COLON, 2, $1, $2); }
        ;

catch_clause:
        CATCH LEFT_PARENTHESIS INTEGER RIGHT_PARENTHESIS stmt  
                                               { $$ = opr(CATCH, 2, con($3), $5); }
        | CATCH LEFT_PARENTHESIS RIGHT_PARENTHESIS stmt        
                                               { $$ = opr(CATCH, 2, con(-1), $4); } /* -1 means catch all */
        ;

finally_clause:
        FINALLY stmt                          { $$ = opr(FINALLY, 1, $2); }
        ;

throw_stmt:
        THROW expr COLON                       { $$ = opr(THROW, 1, $2); }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(COLON, 2, $1, $2); }
        ;

Comment	: 		COMMENTLINE
                | OPENCOMMENT
                ;

expr:
        INTEGER                         { $$ = con($1); }
        | IDENTIFIER                    { $$ = id($1); }
        | MINUS expr %prec UMINUS       { $$ = opr(UMINUS, 1, $2); }
        | expr PLUS expr                { $$ = opr(PLUS, 2, $1, $3); }
        | expr MINUS expr               { $$ = opr(MINUS, 2, $1, $3); }
        | expr MULTIPLE expr            { $$ = opr(MULTIPLE, 2, $1, $3); }
        | expr DIVIDE expr              { $$ = opr(DIVIDE, 2, $1, $3); }
        | expr LESSTHAN expr            { $$ = opr(LESSTHAN, 2, $1, $3); }
        | expr GREATERTHAN expr         { $$ = opr(GREATERTHAN, 2, $1, $3); }
        | expr EQUALORGREAT expr        { $$ = opr(EQUALORGREAT, 2, $1, $3); }
        | expr EQUALORLESS expr         { $$ = opr(EQUALORLESS, 2, $1, $3); }
        | expr ISNOTEQUAL expr          { $$ = opr(ISNOTEQUAL, 2, $1, $3); }
        | expr EQUAL expr               { $$ = opr(EQUAL, 2, $1, $3); }
        | function_call                 { $$ = $1; }
        | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  { $$ = $2; }
        ;

%%


nodeType *con(int value) {
    nodeType *p;

    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *id(int i) {
    nodeType *p;

    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    p->type = typeId;
    p->id.i = i;

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

/* Register a new function */
int register_function(char name, nodeType *body, int param_count, char *params) {
    if (function_count >= MAX_FUNCTIONS) {
        fprintf(stderr, "Too many functions defined\n");
        exit(1);
    }
    
    /* Check if function already exists */
    int existing = find_function(name);
    if (existing >= 0) {
        fprintf(stderr, "Function %c already defined\n", name);
        exit(1);
    }
    
    functions[function_count].name = name;
    functions[function_count].body = body;
    functions[function_count].param_count = param_count;
    
    for (int i = 0; i < param_count; i++) {
        functions[function_count].params[i] = params[i];
    }
    
    function_count++;
    return function_count - 1;
}

/* Find function by name */
int find_function(char name) {
    for (int i = 0; i < function_count; i++) {
        if (functions[i].name == name) {
            return i;
        }
    }
    return -1;
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}

int ex(nodeType *p) {
    int handler_index;
    int exception_caught;
    int exception_value;
    int result, func_idx;
    int i, j, exception_type;
    int arg_values[MAX_PARAMS];
    int arg_count;
    nodeType *arg;

    if (!p) return 0;
    
    /* Check if we've already returned from a function */
    if (in_function_call && has_returned) {
        return 0;
    }
    
    switch(p->type) {
    case typeCon:       return p->con.value;
    case typeId:        
        /* Read from local frame if in function call, otherwise from global */
        if (in_function_call && current_frame >= 0) {
            return call_stack[current_frame][p->id.i];
        }
        return sym[p->id.i];
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:     while(ex(p->opr.op[0])) ex(p->opr.op[1]); return 0;
        case IF:        if (ex(p->opr.op[0]))
                            ex(p->opr.op[1]);
                        else if (p->opr.nops > 2)
                            ex(p->opr.op[2]);
                        return 0;
        case PRINT:     printf("%d\n", ex(p->opr.op[0])); return 0;
        case COLON:     ex(p->opr.op[0]); return ex(p->opr.op[1]);
        case ASSIGN:    
            /* Store to local frame if in function call, otherwise to global */
            if (in_function_call && current_frame >= 0) {
                return call_stack[current_frame][p->opr.op[0]->id.i] = ex(p->opr.op[1]);
            }
            return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
        case UMINUS:    return -ex(p->opr.op[0]);
        case PLUS:      return ex(p->opr.op[0]) + ex(p->opr.op[1]);
        case MINUS:     return ex(p->opr.op[0]) - ex(p->opr.op[1]);
        case MULTIPLE:  return ex(p->opr.op[0]) * ex(p->opr.op[1]);
        case DIVIDE:    {
                            int divisor = ex(p->opr.op[1]);
                            if (divisor == 0) {
                                throw_exception(ARITHMETIC_EXCEPTION, 0); /* Division by zero exception */
                                return 0; /* Never reached */
                            }
                            return ex(p->opr.op[0]) / divisor;
                        }
        case LESSTHAN:  return ex(p->opr.op[0]) < ex(p->opr.op[1]);
        case GREATERTHAN: return ex(p->opr.op[0]) > ex(p->opr.op[1]);
        case EQUALORGREAT: return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
        case EQUALORLESS: return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
        case ISNOTEQUAL: return ex(p->opr.op[0]) != ex(p->opr.op[1]);
        case EQUAL:     return ex(p->opr.op[0]) == ex(p->opr.op[1]);
        
        case FUNCTION:  /* Function call */
            {
                /* Get function index */
                char func_name = p->opr.op[0]->id.i;
                func_idx = find_function(func_name);
                if (func_idx < 0) {
                    fprintf(stderr, "Function %c not found\n", func_name);
                    exit(1);
                }
                
                /* Evaluate and collect arguments */
                arg_count = 0;
                
                /* Process argument list */
                if (p->opr.nops > 1 && p->opr.op[1]) {
                    nodeType *args = p->opr.op[1];
                    
                    /* Handle single argument case */
                    if (args->type != typeOpr || args->opr.oper != COMMA) {
                        arg_values[arg_count++] = ex(args);
                    } else {
                        /* Process comma-separated arguments recursively */
                        nodeType *current = args;
                        int temp_args[MAX_PARAMS];
                        int temp_count = 0;
                        
                        /* Collect arguments (they come in reverse order) */
                        while (current && current->type == typeOpr && current->opr.oper == COMMA) {
                            temp_args[temp_count++] = ex(current->opr.op[1]);
                            current = current->opr.op[0];
                        }
                        
                        /* Add the first/last argument */
                        if (current) {
                            temp_args[temp_count++] = ex(current);
                        }
                        
                        /* Add arguments in correct order */
                        for (i = temp_count - 1; i >= 0; i--) {
                            arg_values[arg_count++] = temp_args[i];
                        }
                    }
                }
                
                /* Check if argument count matches parameter count */
                if (arg_count != functions[func_idx].param_count) {
                    fprintf(stderr, "Function %c expects %d arguments but got %d\n", 
                            func_name, functions[func_idx].param_count, arg_count);
                    exit(1);
                }
                
                /* Set up new stack frame */
                if (current_frame >= MAX_CALL_DEPTH - 1) {
                    fprintf(stderr, "Call stack overflow\n");
                    exit(1);
                }
                current_frame++;
                in_function_call = 1;
                has_returned = 0;
                
                /* Initialize local variables for parameters */
                for (i = 0; i < arg_count; i++) {
                    call_stack[current_frame][functions[func_idx].params[i]] = arg_values[i];
                }
                
                /* Execute function body */
                ex(functions[func_idx].body);
                
                /* Clean up stack frame */
                in_function_call = (current_frame > 0); /* Still in a function if frames remain */
                current_frame--;
                
                /* Return function result */
                has_returned = 0; /* Reset return flag for next call */
                return return_value;
            }
            
        case RETURN:    
            /* Handle return statement */
            if (in_function_call) {
                return_value = ex(p->opr.op[0]);
                has_returned = 1;
                return return_value;
            } else {
                fprintf(stderr, "Return statement outside of function\n");
                exit(1);
            }
            return 0;
            
        /* Exception handling implementation */
        case TRY:
            handler_index = push_handler();
            exception_caught = 0;
            
            /* Set up for exception handling */
            if (setjmp(exception_handlers[handler_index].env) == 0) {
                /* Execute try block */
                ex(p->opr.op[0]);
            } else {
                /* An exception was thrown, handle it */
                exception_type = exception_handlers[handler_index].exception_type;
                exception_value = exception_handlers[handler_index].exception_value;
                exception_caught = 0;
                
                /* Process catch clauses */
                nodeType *catch_clauses = p->opr.op[1];
                if (catch_clauses->type == typeOpr) {
                    if (catch_clauses->opr.oper == CATCH) {
                        /* Single catch clause */
                        int catch_type = catch_clauses->opr.op[0]->con.value;
                        if (catch_type == -1 || catch_type == exception_type) {
                            ex(catch_clauses->opr.op[1]);
                            exception_caught = 1;
                        }
                    } else if (catch_clauses->opr.oper == COLON) {
                        /* Process multiple catch clauses */
                        nodeType *current = catch_clauses;
                        while (current && current->type == typeOpr && 
                               current->opr.oper == COLON && !exception_caught) {
                            
                            /* Check if this is a catch clause or contains a catch clause */
                            if (current->opr.op[0]->type == typeOpr && 
                                current->opr.op[0]->opr.oper == CATCH) {
                                int catch_type = current->opr.op[0]->opr.op[0]->con.value;
                                if (catch_type == -1 || catch_type == exception_type) {
                                    ex(current->opr.op[0]->opr.op[1]);
                                    exception_caught = 1;
                                    break;
                                }
                            }
                            
                            /* Check the second operand if it exists */
                            if (current->opr.nops > 1 && current->opr.op[1] && 
                                current->opr.op[1]->type == typeOpr && 
                                current->opr.op[1]->opr.oper == CATCH) {
                                int catch_type = current->opr.op[1]->opr.op[0]->con.value;
                                if (catch_type == -1 || catch_type == exception_type) {
                                    ex(current->opr.op[1]->opr.op[1]);
                                    exception_caught = 1;
                                    break;
                                }
                            }
                            
                            /* Move to next catch clause */
                            if (current->opr.nops > 1)
                                current = current->opr.op[1];
                            else
                                break;
                        }
                    }
                }
                
                /* If exception wasn't caught, propagate it up the stack */
                if (!exception_caught) {
                    pop_handler();
                    throw_exception(exception_type, exception_value);
                }
            }
            
            /* Execute finally block if present */
            if (p->opr.nops > 2 && p->opr.op[2]->type == typeOpr && 
                p->opr.op[2]->opr.oper == FINALLY) {
                ex(p->opr.op[2]->opr.op[0]);
            }
            
            pop_handler();
            return 0;
            
        case THROW:
            /* Evaluate the expression to throw and get its value */
            result = ex(p->opr.op[0]);
            /* Throw exception type ARITHMETIC_EXCEPTION with the value */
            throw_exception(ARITHMETIC_EXCEPTION, result);
            return 0; /* Never reached */
            
        case CATCH:
        case FINALLY:
            /* These should not be executed directly, they are handled by TRY */
            return 0;
        }
    }
    return 0;
}