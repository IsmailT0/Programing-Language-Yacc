#include <setjmp.h>  /* For exception handling */

typedef enum { typeCon, typeId, typeOpr } nodeEnum;

typedef struct {
    int value;                  
} conNodeType;

typedef struct {
    int i;                     
} idNodeType;

typedef struct {
    int oper;                   
    int nops;                   /* how many operand we have */
    struct nodeTypeTag *op[1];	/* operands, extended at runtime */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* <<< nodun tipi */

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

/* Exception type constants */
#define ARITHMETIC_EXCEPTION 1  /* Exception type for arithmetic errors like division by zero */

/* Exception handling function declarations */
int push_handler();
void pop_handler();
void throw_exception(int type, int value);

extern int sym[26];