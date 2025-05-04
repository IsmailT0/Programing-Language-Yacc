%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <setjmp.h>  /* For exception handling */
    #include "eon.h"
    #include "y.tab.h"

    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i);
    nodeType *con(int value);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    int yylex(void);
    void yyerror(char *s);
    int sym[26];

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

%type <nPtr> stmt expr stmt_list try_catch_stmt catch_clauses catch_clause finally_clause throw_stmt

%%


program:
        function                { exit(0); }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        |
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
    | expr EQUALORLESS expr          { $$ = opr(EQUALORLESS, 2, $1, $3); }
        | expr ISNOTEQUAL expr          { $$ = opr(ISNOTEQUAL, 2, $1, $3); }
        | expr EQUAL expr          { $$ = opr(EQUAL, 2, $1, $3); }
        | LEFT_PARENTHESIS expr RIGHT_PARENTHESIS          { $$ = $2; }
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
    int result;
    int i, exception_type;

    if (!p) return 0;
    
    switch(p->type) {
    case typeCon:       return p->con.value;
    case typeId:        return sym[p->id.i];
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
        case ASSIGN:    return sym[p->opr.op[0]->id.i] = ex(p->opr.op[1]);
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