#include <setjmp.h>  /* For exception handling */
#include <string.h>  /* For string functions like strcmp */
#include <stdio.h>   /* For fprintf */
#include <stdlib.h>  /* For exit */

#define MAX_ID_LENGTH 64
#define MAX_CALL_DEPTH 100
#define MAX_SYMBOLS 1000

typedef enum { typeCon, typeId, typeOpr } nodeEnum;

typedef struct {
    int value;                  
} conNodeType;

typedef struct {
    int i;                      /* For backward compatibility - index */
    char name[MAX_ID_LENGTH];   /* Actual identifier name */
} idNodeType;

typedef struct {
    int oper;                   
    int nops;                   /* how many operand we have */
    struct nodeTypeTag *op[1];	/* operands, extended at runtime */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* Type of node */

    union {
        conNodeType con;        /* constants */
        idNodeType id;          /* identifiers */
        oprNodeType opr;        /* operators */
    };
} nodeType;

/* Exception handling data structures */
typedef struct {
    jmp_buf env;         /* setjmp/longjmp buffer */
    int exception_type;  /* Type of exception thrown */
    int exception_value; /* Value associated with exception */
    int active;          /* Whether this handler is active */
} ExceptionHandler;

typedef struct {
    char name[MAX_ID_LENGTH];
    int value;
} Symbol;

/* External declarations - not definitions */
extern Symbol global_symbols[MAX_SYMBOLS];
extern int symbol_count;
extern Symbol call_stack[MAX_CALL_DEPTH][MAX_SYMBOLS]; 
extern int local_symbol_count[MAX_CALL_DEPTH];
extern int current_frame;

extern int get_symbol_index(char* name, int is_local);

#define ARITHMETIC_EXCEPTION 1  /* Exception type for arithmetic errors like division by zero */

int push_handler();
void pop_handler();
void throw_exception(int type, int value);