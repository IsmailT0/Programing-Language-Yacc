%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <setjmp.h>
    #include <string.h>
    #include "eon.h"
    #include "y.tab.h"

    /* Function-related data structures */
    #define MAX_FUNCTIONS 100
    #define MAX_PARAMS 10

    typedef struct {
        char name[MAX_ID_LENGTH];
        nodeType *body;
        int param_count;
        char params[MAX_PARAMS][MAX_ID_LENGTH];
    } Function;

    /* Global variable definitions (for external declarations in eon.h) */
    Symbol global_symbols[MAX_SYMBOLS];
    Symbol call_stack[MAX_CALL_DEPTH][MAX_SYMBOLS];
    int symbol_count = 0;
    int local_symbol_count[MAX_CALL_DEPTH];
    Function functions[MAX_FUNCTIONS];
    int function_count = 0;

    /* Call stack management */
    int current_frame = -1;
    int in_function_call = 0;
    int return_value = 0;
    int has_returned = 0;

    /* Function to register a new function */
    int register_function(char *name, nodeType *body, int param_count, char params[][MAX_ID_LENGTH]);

    /* Function to find a function by name */
    int find_function(char *name);

    nodeType *opr(int oper, int nops, ...);
    nodeType *id(char *name);
    nodeType *con(int value);

    void freeNode(nodeType *p);
    int ex(nodeType *p);
    int yylex(void);
    void yyerror(char *s);

    /* Exception handling data structures */
    #define MAX_EXCEPTION_HANDLERS 20
    ExceptionHandler exception_handlers[MAX_EXCEPTION_HANDLERS];
    int current_handler = -1;

    /* Implementation of get_symbol_index declared in eon.h */
    int get_symbol_index(char* name, int is_local) {
        Symbol* table;
        int* count;

        if (is_local && current_frame >= 0) {
            table = call_stack[current_frame];
            count = &local_symbol_count[current_frame];
        } else {
            table = global_symbols;
            count = &symbol_count;
        }

        // Look for existing symbol
        for (int i = 0; i < *count; i++) {
            if (strcmp(table[i].name, name) == 0) {
                return i;
            }
        }

        // Add new symbol
        if (*count < MAX_SYMBOLS) {
            strncpy(table[*count].name, name, MAX_ID_LENGTH-1);
            table[*count].name[MAX_ID_LENGTH-1] = '\0';
            table[*count].value = 0;  // Initialize to 0
            // You might want to initialize the type here if you add type tracking
            // table[*count].type = SYM_INT; // Example if using SymbolType from eon.h
            return (*count)++;
        }

        fprintf(stderr, "Symbol table full for %s scope\n", is_local ? "local" : "global");
        exit(1);
        return -1;
    }

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
    char id_name[MAX_ID_LENGTH];
    nodeType *nPtr;
};


%token <integer> INTEGER
%token <id_name> IDENTIFIER
%token WHILE IF PRINT  ELSE_IF END_WHILE COMMENTLINE OPENCOMMENT CLOSECOMMENT TYPE_BOOLEAN STR DINT FLOATING_POINT
%token FUNCTION END_FUNCTION RETURN ELSE DO FOR END_FOR SWITCH CASE IMPORT BREAK CONTINUE ASSIGN
%token SCAN POW PLUS MINUS MULTIPLE DIVIDE MOD LESSTHAN GREATERTHAN NL INCREASE DECREASE
%token COLON SEMICOLON COMMA EQUALORGREAT EQUALORLESS EQUAL ISNOTEQUAL LOGICAL_AND_OPERATOR OR LEFT_PARENTHESIS RIGHT_PARENTHESIS LEFT_BRACE RIGHT_BRACE  LEFTSQRBR RIGHTSQRBR QUOTES
%token TRY CATCH FINALLY THROW

%nonassoc IFX
%nonassoc ELSE

%left LOGICAL_AND_OPERATOR OR
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
          function_defs function_decl  { /* Function registered in action */ }
        | function_defs stmt           { ex($2); freeNode($2); }
        | /* empty */
        ;

function_decl:
        FUNCTION IDENTIFIER LEFT_PARENTHESIS param_list RIGHT_PARENTHESIS LEFT_BRACE stmt_list RIGHT_BRACE END_FUNCTION
        {
            /* Extract parameter names from param_list */
            char params[MAX_PARAMS][MAX_ID_LENGTH];
            int param_count = 0;
            nodeType *param_node = $4;
            nodeType *temp_params[MAX_PARAMS]; // Temporary storage for nodes
            int temp_count = 0;

            // Collect parameter nodes (they are linked right-to-left)
            while (param_node != NULL && temp_count < MAX_PARAMS) {
                if (param_node->type == typeOpr && param_node->opr.oper == COMMA) {
                    temp_params[temp_count++] = param_node->opr.op[1]; // Right operand is a param
                    param_node = param_node->opr.op[0]; // Move left
                } else {
                    temp_params[temp_count++] = param_node; // Last/only param
                    param_node = NULL;
                }
            }

            // Reverse the collected nodes and extract names
            for (int i = temp_count - 1; i >= 0; i--) {
                if (temp_params[i]->type == typeId && param_count < MAX_PARAMS) {
                    strncpy(params[param_count], temp_params[i]->id.name, MAX_ID_LENGTH-1);
                    params[param_count][MAX_ID_LENGTH-1] = '\0';
                    param_count++;
                } else {
                     yyerror("Invalid parameter definition");
                     YYERROR; // Trigger Bison error handling
                }
            }

            /* Register the function */
            if (register_function($2, $7, param_count, params) < 0) {
                // Error handled inside register_function
                YYERROR;
            }
            $$ = NULL; /* No execution result for function declaration */

        }
        ;

param_list:
        IDENTIFIER                      { $$ = id($1); }
        | param_list COMMA IDENTIFIER   { $$ = opr(COMMA, 2, $1, id($3)); }
        | /* empty */                   { $$ = NULL; }
        ;

function_call:
        IDENTIFIER LEFT_PARENTHESIS args_list RIGHT_PARENTHESIS
        {

            $$ = opr(FUNCTION, 2, id($1), $3);
        }
        ;

args_list:
        expr                    { $$ = $1; } // Single argument
        | args_list COMMA expr  { $$ = opr(COMMA, 2, $1, $3); } // Builds right-associative list
        | /* empty */           { $$ = NULL; }
        ;

return_stmt:
        RETURN expr COLON       { $$ = opr(RETURN, 1, $2); }
        ;

stmt:
        COLON                        { $$ = NULL; /* Empty statement */ }
        | expr COLON                 { $$ = $1; }
        | PRINT expr COLON           { $$ = opr(PRINT, 1, $2); }
        | IDENTIFIER ASSIGN expr COLON  { $$ = opr(ASSIGN, 2, id($1), $3); }
        | WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt       { $$ = opr(WHILE, 2, $3, $5); }
        | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
        | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
        | LEFT_BRACE stmt_list RIGHT_BRACE            { $$ = $2; }
        | try_catch_stmt            { $$ = $1; }
        | throw_stmt                { $$ = $1; }
        | function_call COLON       { $$ = $1; } // Execute function call as statement
        | return_stmt               { $$ = $1; }
        ;

/* Try-catch statement grammar rules */
try_catch_stmt:
        TRY stmt catch_clauses                { $$ = opr(TRY, 2, $2, $3); }
        | TRY stmt catch_clauses finally_clause { $$ = opr(TRY, 3, $2, $3, $4); }
        ;

catch_clauses:
        catch_clause                          { $$ = $1; } // Single catch
        | catch_clauses catch_clause          { $$ = opr(COLON, 2, $1, $2); } // Chain catches with COLON
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
        | stmt_list stmt        { $$ = opr(COLON, 2, $1, $2); } // Use COLON to sequence statements
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
        | expr LOGICAL_AND_OPERATOR expr { $$ = opr(LOGICAL_AND_OPERATOR, 2, $1, $3); } 
        | expr OR expr                  { $$ = opr(OR, 2, $1, $3); } 
        | function_call                 { $$ = $1; } // Function call as expression
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

nodeType *id(char *name) {
    nodeType *p;

    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    p->type = typeId;

    strncpy(p->id.name, name, MAX_ID_LENGTH-1);
    p->id.name[MAX_ID_LENGTH-1] = '\0';

    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    // Allocate space for nodeType and operands
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

int register_function(char *name, nodeType *body, int param_count, char params[][MAX_ID_LENGTH]) {
    if (function_count >= MAX_FUNCTIONS) {
        fprintf(stderr, "Error: Maximum number of functions (%d) reached.\n", MAX_FUNCTIONS);
        return -1; // Indicate error
    }

    /* Check if function already exists */
    if (find_function(name) >= 0) {
        fprintf(stderr, "Error: Function '%s' already defined.\n", name);
        return -1; // Indicate error
    }

    strncpy(functions[function_count].name, name, MAX_ID_LENGTH-1);
    functions[function_count].name[MAX_ID_LENGTH-1] = '\0';
    functions[function_count].body = body; // Store the AST body
    functions[function_count].param_count = param_count;

    for (int i = 0; i < param_count; i++) {
        strncpy(functions[function_count].params[i], params[i], MAX_ID_LENGTH-1);
        functions[function_count].params[i][MAX_ID_LENGTH-1] = '\0';
    }

    function_count++;
    return function_count - 1; // Return index of new function
}

int find_function(char *name) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Not found
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    // Only free the node itself. If id nodes store allocated names, free them too.
    free (p);
}

void yyerror(char *s) {
    // Use yylineno from the lexer if available
    extern int yylineno;
    fprintf(stderr, "Syntax error: %s at line %d\n", s, yylineno);
}

int main(void) {
    // Initialize global symbol count
    symbol_count = 0;

    // Initialize all local symbol counts to 0
    for (int i = 0; i < MAX_CALL_DEPTH; i++) {
        local_symbol_count[i] = 0;
    }

    // Initialize exception handler stack
    current_handler = -1;

    yyparse();
    return 0;
}


int ex(nodeType *p) {
    int handler_index;
    int exception_caught;
    int exception_value;
    int result, func_idx;
    int i, j, exception_type;
    int arg_values[MAX_PARAMS]; // To store evaluated argument values
    int arg_count;
    nodeType *arg_node; // To traverse argument list AST

    if (!p) return 0;

    /* Check if we've already returned from a function in this execution path */
    if (in_function_call && has_returned) {
        return 0; // Stop execution in this branch if already returned
    }

    switch(p->type) {
    case typeCon:       return p->con.value;
    case typeId:
        {
            int idx = -1;
            int found = 0;
            /* Read from local frame if in function call */
            if (in_function_call && current_frame >= 0) {
                // Check local scope first
                for (i = 0; i < local_symbol_count[current_frame]; i++) {
                     if (strcmp(call_stack[current_frame][i].name, p->id.name) == 0) {
                         idx = i;
                         found = 1;
                         return call_stack[current_frame][idx].value;
                     }
                }
            }
            /* If not found locally or not in a function, check global scope */
            if (!found) {
                for (i = 0; i < symbol_count; i++) {
                     if (strcmp(global_symbols[i].name, p->id.name) == 0) {
                         idx = i;
                         found = 1;
                         return global_symbols[idx].value;
                     }
                }
            }
            /* If symbol not found anywhere */
            if (!found) {
                fprintf(stderr, "Error: Undefined variable '%s'\n", p->id.name);
                
                exit(1); // Or handle error appropriately
            }
            return 0; // Should not be reached
        }

    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            while(ex(p->opr.op[0])) {
                if (in_function_call && has_returned) return 0; // Check condition eval return
                ex(p->opr.op[1]);
                if (in_function_call && has_returned) return 0; // Check body eval return
            }
            return 0;
        case IF:
            if (ex(p->opr.op[0])) {
                if (in_function_call && has_returned) return 0; // Check condition eval return
                ex(p->opr.op[1]); // Execute 'then' block
            } else if (p->opr.nops > 2) {
                 if (in_function_call && has_returned) return 0; // Check condition eval return (for else)
                ex(p->opr.op[2]); // Execute 'else' block
            }
             // Check for return within the executed branch
            if (in_function_call && has_returned) return 0;
            return 0;
        case PRINT:
            {
                int val = ex(p->opr.op[0]);
                if (in_function_call && has_returned) return 0; // Check expression eval return

                // Check for boolean values
                if (val == 0) {
                    printf("False\n");
                } else if (val == 1) {
                    printf("True\n");
                } else {
                    printf("%d\n", val); // Print as integer otherwise
                }
                return 0;
            }
        case COLON: // Statement separator
            ex(p->opr.op[0]); // Execute first statement
            if (in_function_call && has_returned) return 0; // Check if first statement returned
            return ex(p->opr.op[1]); // Execute and return result of second statement
        case ASSIGN:
            {
                int val_to_assign = ex(p->opr.op[1]); // Evaluate right-hand side first
                if (in_function_call && has_returned) return 0; // Check if rhs evaluation returned

                char *var_name = p->opr.op[0]->id.name;
                int idx = -1;
                int is_local = 0;

                /* Determine scope: local first if in function, then global */
                if (in_function_call && current_frame >= 0) {
                     // Try to find in local scope
                     for(i=0; i < local_symbol_count[current_frame]; ++i) {
                         if(strcmp(call_stack[current_frame][i].name, var_name) == 0) {
                             idx = i;
                             is_local = 1;
                             break;
                         }
                     }
                     // If not found locally, it will be treated as a new local variable
                     if (!is_local) {
                         idx = get_symbol_index(var_name, 1); // Get index for new local var
                         is_local = 1;
                     }
                }

                /* If not assigned locally (or not in function), assign globally */
                if (!is_local) {
                     idx = get_symbol_index(var_name, 0); // Get index for global (find or create)
                }

                /* Perform the assignment */
                if (is_local) {
                     call_stack[current_frame][idx].value = val_to_assign;
                     // Potentially update type: call_stack[current_frame][idx].type = ...;
                } else {
                     global_symbols[idx].value = val_to_assign;
                     // Potentially update type: global_symbols[idx].type = ...;
                }
                return val_to_assign; // Assignment expression returns the assigned value
            }
        case UMINUS:
             result = -ex(p->opr.op[0]);
             if (in_function_call && has_returned) return 0;
             return result;
        case PLUS:
             result = ex(p->opr.op[0]) + ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case MINUS:
             result = ex(p->opr.op[0]) - ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case MULTIPLE:
             result = ex(p->opr.op[0]) * ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case DIVIDE:    {
                            int right_val = ex(p->opr.op[1]);
                            if (in_function_call && has_returned) return 0; // Check right operand eval
                            int left_val = ex(p->opr.op[0]);
                            if (in_function_call && has_returned) return 0; // Check left operand eval

                            if (right_val == 0) {
                                fprintf(stderr, "Error: Division by zero\n");
                                throw_exception(ARITHMETIC_EXCEPTION, 0); /* Division by zero exception */
                                return 0; /* Should not be reached */
                            }
                            return left_val / right_val;
                        }
        case LESSTHAN:
             result = ex(p->opr.op[0]) < ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case GREATERTHAN:
             result = ex(p->opr.op[0]) > ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case EQUALORGREAT:
             result = ex(p->opr.op[0]) >= ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case EQUALORLESS:
             result = ex(p->opr.op[0]) <= ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case ISNOTEQUAL:
             result = ex(p->opr.op[0]) != ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case EQUAL:
             result = ex(p->opr.op[0]) == ex(p->opr.op[1]);
             if (in_function_call && has_returned) return 0;
             return result;
        case LOGICAL_AND_OPERATOR: // &&
             // Short-circuit evaluation
             result = ex(p->opr.op[0]);
             if (in_function_call && has_returned) return 0;
             if (result != 0) { // Only evaluate right if left is true (non-zero)
                 result = ex(p->opr.op[1]);
                 if (in_function_call && has_returned) return 0;
                 return (result != 0); // Return 1 if right is non-zero, 0 otherwise
             }
             return 0; // Left was false (0), result is 0
        case OR: // ||
             // Short-circuit evaluation
             result = ex(p->opr.op[0]);
             if (in_function_call && has_returned) return 0;
             if (result == 0) { // Only evaluate right if left is false (0)
                 result = ex(p->opr.op[1]);
                 if (in_function_call && has_returned) return 0;
                 return (result != 0); // Return 1 if right is non-zero, 0 otherwise
             }
             return 1; // Left was true (non-zero), result is 1

        case FUNCTION: // Function Call
            {
                char *func_name = p->opr.op[0]->id.name;
                func_idx = find_function(func_name);
                if (func_idx < 0) {
                    fprintf(stderr, "Error: Function '%s' not found\n", func_name);
                    exit(1);
                }

                /* Evaluate and collect arguments */
                arg_count = 0;
                arg_node = (p->opr.nops > 1) ? p->opr.op[1] : NULL; // Get the args_list node
                nodeType *temp_arg_nodes[MAX_PARAMS]; // Temp storage for arg nodes
                int temp_arg_count = 0;

                // Collect argument expression nodes (they are linked right-to-left by COMMA)
                while (arg_node != NULL && temp_arg_count < MAX_PARAMS) {
                    if (arg_node->type == typeOpr && arg_node->opr.oper == COMMA) {
                        temp_arg_nodes[temp_arg_count++] = arg_node->opr.op[1]; // Right operand is an arg expr
                        arg_node = arg_node->opr.op[0]; // Move left
                    } else {
                        temp_arg_nodes[temp_arg_count++] = arg_node; // Last/only arg expr
                        arg_node = NULL;
                    }
                }

                // Evaluate arguments in correct order (left-to-right) by reversing the collected nodes
                for (i = temp_arg_count - 1; i >= 0; i--) {
                    if (arg_count < MAX_PARAMS) {
                        arg_values[arg_count++] = ex(temp_arg_nodes[i]);
                        // Check if argument evaluation caused a return
                        if (in_function_call && has_returned) {

                            return 0; // Stop further execution in this call path
                        }
                    } else {
                        fprintf(stderr, "Error: Too many arguments provided for function '%s'\n", func_name);
                        exit(1);
                    }
                }


                /* Check if argument count matches parameter count */
                if (arg_count != functions[func_idx].param_count) {
                    fprintf(stderr, "Error: Function '%s' expects %d arguments but got %d\n",
                            func_name, functions[func_idx].param_count, arg_count);
                    exit(1);
                }

                /* --- Set up new stack frame --- */
                if (current_frame >= MAX_CALL_DEPTH - 1) {
                    fprintf(stderr, "Error: Call stack overflow (calling '%s')\n", func_name);
                    exit(1);
                }

                int previous_frame = current_frame; // Store previous frame index
                int previous_in_function_call = in_function_call; // Store previous state

                current_frame++;
                in_function_call = 1;
                has_returned = 0; // Reset return flag specifically for this new function call

                /* Initialize local symbol count for new frame */
                local_symbol_count[current_frame] = 0;

                /* Initialize local variables (parameters) in the new frame */
                for (i = 0; i < arg_count; i++) {
                    // Use get_symbol_index to add parameter to the new local scope
                    int param_idx = get_symbol_index(functions[func_idx].params[i], 1); // 1 means local
                    if (param_idx >= 0) { // Check if symbol table wasn't full
                        call_stack[current_frame][param_idx].value = arg_values[i];
                        // Optionally set type: call_stack[current_frame][param_idx].type = ...;
                    } else {
                        // Error handled by get_symbol_index
                        exit(1);
                    }
                }

                /* --- Execute function body --- */
                int function_result = 0; // Default return value if no explicit return
                ex(functions[func_idx].body);

                /* --- Clean up stack frame --- */
                // Restore previous state *before* returning the value
                current_frame = previous_frame;
                in_function_call = previous_in_function_call;

                // If execution finished without hitting an explicit return statement
                if (!has_returned) {
                    return_value = 0; // Default return value is 0
                }

                // The actual return value was stored in 'return_value' by the RETURN case or set to 0 default
                int final_return_value = return_value;
                
                int did_function_return = has_returned; // Capture if the function body returned
                has_returned = 0; // Reset for subsequent operations in the caller

                return final_return_value; // Return the stored/default value
            }

        case RETURN:
            /* Handle return statement */
            if (in_function_call && current_frame >= 0) { // Ensure we are actually in a function
                return_value = ex(p->opr.op[0]); // Evaluate the return expression
                // Check if the return expression itself caused a nested return (unlikely but possible)
                if (has_returned) {
                    // If the expression evaluation already set has_returned, just propagate
                    return return_value;
                }
                // Otherwise, set the flag now
                has_returned = 1;
                // Return the evaluated value. This return will propagate up the ex() calls
                // within the current function body until it reaches the FUNCTION case handler.
                return return_value;
            } else {
                fprintf(stderr, "Error: Return statement outside of function\n");
                exit(1);
            }
            return 0; // Should not be reached

        /* Exception handling implementation */
        case TRY:
            handler_index = push_handler();
            exception_caught = 0;

            if (setjmp(exception_handlers[handler_index].env) == 0) {
                /* Execute try block */
                ex(p->opr.op[0]);
                // If try block completes and caused a return, pop handler and propagate
                if (in_function_call && has_returned) { pop_handler(); return 0; }
            } else {
                /* An exception was thrown */
                exception_type = exception_handlers[handler_index].exception_type;
                exception_value = exception_handlers[handler_index].exception_value;
                exception_caught = 0;

                nodeType *catch_clauses_node = p->opr.op[1]; // Node representing catch clauses (CATCH or COLON chain)
                nodeType *current_catch_link = catch_clauses_node;

                // Traverse catch clauses (linked list via COLON, nodes are CATCH)
                while(current_catch_link != NULL && !exception_caught) {
                    nodeType *catch_clause_to_check = NULL;
                    nodeType *next_link = NULL;

                    if (current_catch_link->type == typeOpr && current_catch_link->opr.oper == CATCH) {
                        // Single catch or the last one in a chain
                        catch_clause_to_check = current_catch_link;
                        next_link = NULL; // End of chain
                    } else if (current_catch_link->type == typeOpr && current_catch_link->opr.oper == COLON) {
                        // Part of a chain, the left operand should be the CATCH clause
                        if (current_catch_link->opr.op[0]->type == typeOpr && current_catch_link->opr.op[0]->opr.oper == CATCH) {
                            catch_clause_to_check = current_catch_link->opr.op[0];
                        } else {
                             yyerror("Internal error: Malformed catch clause structure");
                             exit(1);
                        }
                        // The right operand is the rest of the chain
                        next_link = current_catch_link->opr.op[1];
                    } else {
                         yyerror("Internal error: Unexpected node type in catch clauses");
                         exit(1);
                    }

                    // Check the actual CATCH node
                    if (catch_clause_to_check) {
                        int catch_type = catch_clause_to_check->opr.op[0]->con.value; // Exception type code
                        if (catch_type == -1 || catch_type == exception_type) { // -1 catches all
                            ex(catch_clause_to_check->opr.op[1]); // Execute catch block body
                            // If catch block returns, pop handler and propagate
                            if (in_function_call && has_returned) { pop_handler(); return 0; }
                            exception_caught = 1;
                            break; // Exit loop once caught
                        }
                    }
                    current_catch_link = next_link; // Move to the next link in the chain
                }


                /* If exception wasn't caught by any clause, re-throw it */
                if (!exception_caught) {
                    pop_handler(); // Pop this handler first
                    throw_exception(exception_type, exception_value); // Rethrow to outer handler or terminate
                    return 0; // Should not be reached
                }
            }

            /* Execute finally block if present */
            if (p->opr.nops > 2 && p->opr.op[2] != NULL && p->opr.op[2]->type == typeOpr &&
                p->opr.op[2]->opr.oper == FINALLY) {
                ex(p->opr.op[2]->opr.op[0]); // Execute finally body
                // If finally causes a return, it should take precedence over normal flow or caught exception flow
                if (in_function_call && has_returned) { pop_handler(); return 0; }
            }

            pop_handler(); // Pop handler after try/catch/finally completes normally or exception handled
            return 0;


        case THROW:
            result = ex(p->opr.op[0]); // Evaluate the expression to get the exception value
            if (in_function_call && has_returned) return 0; // Check if expression evaluation returned

            // For now, using ARITHMETIC_EXCEPTION as the type. You might want a different default.
            // You could potentially allow throwing specific exception types if you extend the syntax.
            throw_exception(ARITHMETIC_EXCEPTION, result);
            return 0; /* Never reached */

        case CATCH:
        case FINALLY:
            /* These should not be executed directly; they are handled by the TRY case */
            yyerror("Internal error: CATCH or FINALLY node executed directly");
            return 0;
        }
    }
    return 0;
}