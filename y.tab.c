/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "eon.y"

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

#line 124 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INTEGER = 258,                 /* INTEGER  */
    IDENTIFIER = 259,              /* IDENTIFIER  */
    WHILE = 260,                   /* WHILE  */
    IF = 261,                      /* IF  */
    PRINT = 262,                   /* PRINT  */
    ELSE_IF = 263,                 /* ELSE_IF  */
    END_WHILE = 264,               /* END_WHILE  */
    COMMENTLINE = 265,             /* COMMENTLINE  */
    OPENCOMMENT = 266,             /* OPENCOMMENT  */
    CLOSECOMMENT = 267,            /* CLOSECOMMENT  */
    TRUE = 268,                    /* TRUE  */
    FALSE = 269,                   /* FALSE  */
    TYPE_BOOLEAN = 270,            /* TYPE_BOOLEAN  */
    STR = 271,                     /* STR  */
    DINT = 272,                    /* DINT  */
    FLOATING_POINT = 273,          /* FLOATING_POINT  */
    FUNCTION = 274,                /* FUNCTION  */
    END_FUNCTION = 275,            /* END_FUNCTION  */
    RETURN = 276,                  /* RETURN  */
    ELSE = 277,                    /* ELSE  */
    DO = 278,                      /* DO  */
    FOR = 279,                     /* FOR  */
    END_FOR = 280,                 /* END_FOR  */
    SWITCH = 281,                  /* SWITCH  */
    CASE = 282,                    /* CASE  */
    IMPORT = 283,                  /* IMPORT  */
    BREAK = 284,                   /* BREAK  */
    CONTINUE = 285,                /* CONTINUE  */
    ASSIGN = 286,                  /* ASSIGN  */
    SCAN = 287,                    /* SCAN  */
    POW = 288,                     /* POW  */
    PLUS = 289,                    /* PLUS  */
    MINUS = 290,                   /* MINUS  */
    MULTIPLE = 291,                /* MULTIPLE  */
    DIVIDE = 292,                  /* DIVIDE  */
    MOD = 293,                     /* MOD  */
    LESSTHAN = 294,                /* LESSTHAN  */
    GREATERTHAN = 295,             /* GREATERTHAN  */
    NL = 296,                      /* NL  */
    INCREASE = 297,                /* INCREASE  */
    DECREASE = 298,                /* DECREASE  */
    COLON = 299,                   /* COLON  */
    SEMICOLON = 300,               /* SEMICOLON  */
    COMMA = 301,                   /* COMMA  */
    EQUALORGREAT = 302,            /* EQUALORGREAT  */
    EQUALORLESS = 303,             /* EQUALORLESS  */
    EQUAL = 304,                   /* EQUAL  */
    ISNOTEQUAL = 305,              /* ISNOTEQUAL  */
    LOGICAL_AND_OPERATOR = 306,    /* LOGICAL_AND_OPERATOR  */
    OR = 307,                      /* OR  */
    LEFT_PARENTHESIS = 308,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 309,       /* RIGHT_PARENTHESIS  */
    LEFT_BRACE = 310,              /* LEFT_BRACE  */
    RIGHT_BRACE = 311,             /* RIGHT_BRACE  */
    LEFTSQRBR = 312,               /* LEFTSQRBR  */
    RIGHTSQRBR = 313,              /* RIGHTSQRBR  */
    QUOTES = 314,                  /* QUOTES  */
    TRY = 315,                     /* TRY  */
    CATCH = 316,                   /* CATCH  */
    FINALLY = 317,                 /* FINALLY  */
    THROW = 318,                   /* THROW  */
    IFX = 319,                     /* IFX  */
    UMINUS = 320                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INTEGER 258
#define IDENTIFIER 259
#define WHILE 260
#define IF 261
#define PRINT 262
#define ELSE_IF 263
#define END_WHILE 264
#define COMMENTLINE 265
#define OPENCOMMENT 266
#define CLOSECOMMENT 267
#define TRUE 268
#define FALSE 269
#define TYPE_BOOLEAN 270
#define STR 271
#define DINT 272
#define FLOATING_POINT 273
#define FUNCTION 274
#define END_FUNCTION 275
#define RETURN 276
#define ELSE 277
#define DO 278
#define FOR 279
#define END_FOR 280
#define SWITCH 281
#define CASE 282
#define IMPORT 283
#define BREAK 284
#define CONTINUE 285
#define ASSIGN 286
#define SCAN 287
#define POW 288
#define PLUS 289
#define MINUS 290
#define MULTIPLE 291
#define DIVIDE 292
#define MOD 293
#define LESSTHAN 294
#define GREATERTHAN 295
#define NL 296
#define INCREASE 297
#define DECREASE 298
#define COLON 299
#define SEMICOLON 300
#define COMMA 301
#define EQUALORGREAT 302
#define EQUALORLESS 303
#define EQUAL 304
#define ISNOTEQUAL 305
#define LOGICAL_AND_OPERATOR 306
#define OR 307
#define LEFT_PARENTHESIS 308
#define RIGHT_PARENTHESIS 309
#define LEFT_BRACE 310
#define RIGHT_BRACE 311
#define LEFTSQRBR 312
#define RIGHTSQRBR 313
#define QUOTES 314
#define TRY 315
#define CATCH 316
#define FINALLY 317
#define THROW 318
#define IFX 319
#define UMINUS 320

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 56 "eon.y"

    int integer;                 
    char ide;               
    nodeType *nPtr;             

#line 313 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_PRINT = 7,                      /* PRINT  */
  YYSYMBOL_ELSE_IF = 8,                    /* ELSE_IF  */
  YYSYMBOL_END_WHILE = 9,                  /* END_WHILE  */
  YYSYMBOL_COMMENTLINE = 10,               /* COMMENTLINE  */
  YYSYMBOL_OPENCOMMENT = 11,               /* OPENCOMMENT  */
  YYSYMBOL_CLOSECOMMENT = 12,              /* CLOSECOMMENT  */
  YYSYMBOL_TRUE = 13,                      /* TRUE  */
  YYSYMBOL_FALSE = 14,                     /* FALSE  */
  YYSYMBOL_TYPE_BOOLEAN = 15,              /* TYPE_BOOLEAN  */
  YYSYMBOL_STR = 16,                       /* STR  */
  YYSYMBOL_DINT = 17,                      /* DINT  */
  YYSYMBOL_FLOATING_POINT = 18,            /* FLOATING_POINT  */
  YYSYMBOL_FUNCTION = 19,                  /* FUNCTION  */
  YYSYMBOL_END_FUNCTION = 20,              /* END_FUNCTION  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_ELSE = 22,                      /* ELSE  */
  YYSYMBOL_DO = 23,                        /* DO  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_END_FOR = 25,                   /* END_FOR  */
  YYSYMBOL_SWITCH = 26,                    /* SWITCH  */
  YYSYMBOL_CASE = 27,                      /* CASE  */
  YYSYMBOL_IMPORT = 28,                    /* IMPORT  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 30,                  /* CONTINUE  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_SCAN = 32,                      /* SCAN  */
  YYSYMBOL_POW = 33,                       /* POW  */
  YYSYMBOL_PLUS = 34,                      /* PLUS  */
  YYSYMBOL_MINUS = 35,                     /* MINUS  */
  YYSYMBOL_MULTIPLE = 36,                  /* MULTIPLE  */
  YYSYMBOL_DIVIDE = 37,                    /* DIVIDE  */
  YYSYMBOL_MOD = 38,                       /* MOD  */
  YYSYMBOL_LESSTHAN = 39,                  /* LESSTHAN  */
  YYSYMBOL_GREATERTHAN = 40,               /* GREATERTHAN  */
  YYSYMBOL_NL = 41,                        /* NL  */
  YYSYMBOL_INCREASE = 42,                  /* INCREASE  */
  YYSYMBOL_DECREASE = 43,                  /* DECREASE  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 45,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 46,                     /* COMMA  */
  YYSYMBOL_EQUALORGREAT = 47,              /* EQUALORGREAT  */
  YYSYMBOL_EQUALORLESS = 48,               /* EQUALORLESS  */
  YYSYMBOL_EQUAL = 49,                     /* EQUAL  */
  YYSYMBOL_ISNOTEQUAL = 50,                /* ISNOTEQUAL  */
  YYSYMBOL_LOGICAL_AND_OPERATOR = 51,      /* LOGICAL_AND_OPERATOR  */
  YYSYMBOL_OR = 52,                        /* OR  */
  YYSYMBOL_LEFT_PARENTHESIS = 53,          /* LEFT_PARENTHESIS  */
  YYSYMBOL_RIGHT_PARENTHESIS = 54,         /* RIGHT_PARENTHESIS  */
  YYSYMBOL_LEFT_BRACE = 55,                /* LEFT_BRACE  */
  YYSYMBOL_RIGHT_BRACE = 56,               /* RIGHT_BRACE  */
  YYSYMBOL_LEFTSQRBR = 57,                 /* LEFTSQRBR  */
  YYSYMBOL_RIGHTSQRBR = 58,                /* RIGHTSQRBR  */
  YYSYMBOL_QUOTES = 59,                    /* QUOTES  */
  YYSYMBOL_TRY = 60,                       /* TRY  */
  YYSYMBOL_CATCH = 61,                     /* CATCH  */
  YYSYMBOL_FINALLY = 62,                   /* FINALLY  */
  YYSYMBOL_THROW = 63,                     /* THROW  */
  YYSYMBOL_IFX = 64,                       /* IFX  */
  YYSYMBOL_UMINUS = 65,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_program = 67,                   /* program  */
  YYSYMBOL_function = 68,                  /* function  */
  YYSYMBOL_stmt = 69,                      /* stmt  */
  YYSYMBOL_try_catch_stmt = 70,            /* try_catch_stmt  */
  YYSYMBOL_catch_clauses = 71,             /* catch_clauses  */
  YYSYMBOL_catch_clause = 72,              /* catch_clause  */
  YYSYMBOL_finally_clause = 73,            /* finally_clause  */
  YYSYMBOL_throw_stmt = 74,                /* throw_stmt  */
  YYSYMBOL_stmt_list = 75,                 /* stmt_list  */
  YYSYMBOL_Comment = 76,                   /* Comment  */
  YYSYMBOL_expr = 77                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   252

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  83

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    87,    87,    91,    92,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   111,   112,   116,   117,
     121,   123,   128,   132,   136,   137,   140,   141,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER",
  "IDENTIFIER", "WHILE", "IF", "PRINT", "ELSE_IF", "END_WHILE",
  "COMMENTLINE", "OPENCOMMENT", "CLOSECOMMENT", "TRUE", "FALSE",
  "TYPE_BOOLEAN", "STR", "DINT", "FLOATING_POINT", "FUNCTION",
  "END_FUNCTION", "RETURN", "ELSE", "DO", "FOR", "END_FOR", "SWITCH",
  "CASE", "IMPORT", "BREAK", "CONTINUE", "ASSIGN", "SCAN", "POW", "PLUS",
  "MINUS", "MULTIPLE", "DIVIDE", "MOD", "LESSTHAN", "GREATERTHAN", "NL",
  "INCREASE", "DECREASE", "COLON", "SEMICOLON", "COMMA", "EQUALORGREAT",
  "EQUALORLESS", "EQUAL", "ISNOTEQUAL", "LOGICAL_AND_OPERATOR", "OR",
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "LEFT_BRACE", "RIGHT_BRACE",
  "LEFTSQRBR", "RIGHTSQRBR", "QUOTES", "TRY", "CATCH", "FINALLY", "THROW",
  "IFX", "UMINUS", "$accept", "program", "function", "stmt",
  "try_catch_stmt", "catch_clauses", "catch_clause", "finally_clause",
  "throw_stmt", "stmt_list", "Comment", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -51,     1,    34,   -51,   -51,   -23,   -37,   -32,    11,   -51,
     -51,    11,   -51,    11,    34,    34,    11,   -51,   -51,   -51,
      34,   151,    11,    11,    11,   -51,   168,   -51,    88,   -51,
      -1,   -26,   185,    34,    11,    11,    11,    11,    11,    11,
     -51,    11,    11,    11,    11,   202,   109,   130,   -51,   -51,
     -51,   -51,   -11,   -50,   -51,   -51,    20,    20,   -51,   -51,
      13,    13,   -17,   -17,   -10,   -10,   -51,    34,    34,     4,
      34,   -51,   -51,   -51,    14,    -3,    34,   -51,    34,    34,
     -51,   -51,   -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    28,    29,     0,     0,     0,    26,
      27,     0,     5,     0,     0,     0,     0,     3,    14,    15,
       0,     0,     0,     0,     0,    29,     0,    30,     0,    24,
       0,     0,     0,    13,     0,     0,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,     0,     0,     7,    41,
      12,    25,     0,    16,    18,    23,    31,    32,    33,    34,
      35,    36,    37,    38,    40,    39,     8,     0,     0,     0,
       0,    19,    17,     9,    10,     0,     0,    22,     0,     0,
      21,    11,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,   -51,    -2,   -51,   -51,     0,   -51,   -51,    40,
     -51,    77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    29,    18,    53,    54,    72,    19,    30,
      20,    21
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,     3,     4,     5,     6,     7,     8,    75,    22,     9,
      10,    52,    70,    31,     4,    25,    23,    34,    35,    36,
      37,    24,    38,    39,    34,    35,    36,    37,    51,    38,
      39,    51,    43,    44,    11,    52,    78,     4,     5,     6,
       7,     8,    69,    12,     9,    10,    11,    34,    35,    36,
      37,    79,    13,    71,    14,    50,    36,    37,    76,    15,
      33,     0,    16,     0,    13,    73,    74,     0,    77,    11,
       0,     0,     0,     0,    80,     0,    81,    82,    12,     0,
       0,     0,     0,     0,     0,    26,     0,    13,    27,    14,
      28,     0,     0,    32,    15,     0,     0,    16,     0,    45,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,    57,    58,    59,    60,    61,     0,    62,    63,
      64,    65,    34,    35,    36,    37,     0,    38,    39,     0,
       0,     0,     0,     0,     0,    41,    42,    43,    44,     0,
       0,     0,    49,    34,    35,    36,    37,     0,    38,    39,
       0,     0,     0,     0,     0,     0,    41,    42,    43,    44,
       0,     0,     0,    67,    34,    35,    36,    37,     0,    38,
      39,     0,     0,     0,     0,     0,     0,    41,    42,    43,
      44,     0,     0,     0,    68,    34,    35,    36,    37,     0,
      38,    39,     0,     0,     0,    40,     0,     0,    41,    42,
      43,    44,    34,    35,    36,    37,     0,    38,    39,     0,
       0,     0,    48,     0,     0,    41,    42,    43,    44,    34,
      35,    36,    37,     0,    38,    39,     0,     0,     0,    55,
       0,     0,    41,    42,    43,    44,    34,    35,    36,    37,
       0,    38,    39,     0,     0,     0,    66,     0,     0,    41,
      42,    43,    44
};

static const yytype_int8 yycheck[] =
{
       2,     0,     3,     4,     5,     6,     7,     3,    31,    10,
      11,    61,    62,    15,     3,     4,    53,    34,    35,    36,
      37,    53,    39,    40,    34,    35,    36,    37,    30,    39,
      40,    33,    49,    50,    35,    61,    22,     3,     4,     5,
       6,     7,    53,    44,    10,    11,    35,    34,    35,    36,
      37,    54,    53,    53,    55,    56,    36,    37,    54,    60,
      20,    -1,    63,    -1,    53,    67,    68,    -1,    70,    35,
      -1,    -1,    -1,    -1,    76,    -1,    78,    79,    44,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,    53,    11,    55,
      13,    -1,    -1,    16,    60,    -1,    -1,    63,    -1,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    -1,    41,    42,
      43,    44,    34,    35,    36,    37,    -1,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,
      -1,    -1,    54,    34,    35,    36,    37,    -1,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      -1,    -1,    -1,    54,    34,    35,    36,    37,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      50,    -1,    -1,    -1,    54,    34,    35,    36,    37,    -1,
      39,    40,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,
      49,    50,    34,    35,    36,    37,    -1,    39,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,    48,    49,    50,    34,
      35,    36,    37,    -1,    39,    40,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    49,    50,    34,    35,    36,    37,
      -1,    39,    40,    -1,    -1,    -1,    44,    -1,    -1,    47,
      48,    49,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    67,    68,     0,     3,     4,     5,     6,     7,    10,
      11,    35,    44,    53,    55,    60,    63,    69,    70,    74,
      76,    77,    31,    53,    53,     4,    77,    77,    77,    69,
      75,    69,    77,    75,    34,    35,    36,    37,    39,    40,
      44,    47,    48,    49,    50,    77,    77,    77,    44,    54,
      56,    69,    61,    71,    72,    44,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    44,    54,    54,    53,
      62,    72,    73,    69,    69,     3,    54,    69,    22,    54,
      69,    69,    69
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      72,    72,    73,    74,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     3,     4,     5,
       5,     7,     3,     2,     1,     1,     3,     4,     1,     2,
       5,     4,     2,     3,     1,     2,     1,     1,     1,     1,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: function  */
#line 87 "eon.y"
                                { exit(0); }
#line 1462 "y.tab.c"
    break;

  case 3: /* function: function stmt  */
#line 91 "eon.y"
                                { ex((yyvsp[0].nPtr)); freeNode((yyvsp[0].nPtr)); }
#line 1468 "y.tab.c"
    break;

  case 5: /* stmt: COLON  */
#line 96 "eon.y"
                                     { (yyval.nPtr) = opr(COLON, 2, NULL, NULL); }
#line 1474 "y.tab.c"
    break;

  case 6: /* stmt: expr COLON  */
#line 97 "eon.y"
                                     { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1480 "y.tab.c"
    break;

  case 7: /* stmt: PRINT expr COLON  */
#line 98 "eon.y"
                                     { (yyval.nPtr) = opr(PRINT, 1, (yyvsp[-1].nPtr)); }
#line 1486 "y.tab.c"
    break;

  case 8: /* stmt: IDENTIFIER ASSIGN expr COLON  */
#line 99 "eon.y"
                                        { (yyval.nPtr) = opr(ASSIGN, 2, id((yyvsp[-3].ide)), (yyvsp[-1].nPtr)); }
#line 1492 "y.tab.c"
    break;

  case 9: /* stmt: WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt  */
#line 100 "eon.y"
                                                                   { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1498 "y.tab.c"
    break;

  case 10: /* stmt: IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt  */
#line 101 "eon.y"
                                                                    { (yyval.nPtr) = opr(IF, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1504 "y.tab.c"
    break;

  case 11: /* stmt: IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt  */
#line 102 "eon.y"
                                                                    { (yyval.nPtr) = opr(IF, 3, (yyvsp[-4].nPtr), (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1510 "y.tab.c"
    break;

  case 12: /* stmt: LEFT_BRACE stmt_list RIGHT_BRACE  */
#line 103 "eon.y"
                                                      { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1516 "y.tab.c"
    break;

  case 13: /* stmt: Comment stmt_list  */
#line 104 "eon.y"
                                    {;}
#line 1522 "y.tab.c"
    break;

  case 14: /* stmt: try_catch_stmt  */
#line 105 "eon.y"
                                    { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1528 "y.tab.c"
    break;

  case 15: /* stmt: throw_stmt  */
#line 106 "eon.y"
                                    { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1534 "y.tab.c"
    break;

  case 16: /* try_catch_stmt: TRY stmt catch_clauses  */
#line 111 "eon.y"
                                              { (yyval.nPtr) = opr(TRY, 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1540 "y.tab.c"
    break;

  case 17: /* try_catch_stmt: TRY stmt catch_clauses finally_clause  */
#line 112 "eon.y"
                                                { (yyval.nPtr) = opr(TRY, 3, (yyvsp[-2].nPtr), (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1546 "y.tab.c"
    break;

  case 18: /* catch_clauses: catch_clause  */
#line 116 "eon.y"
                                              { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1552 "y.tab.c"
    break;

  case 19: /* catch_clauses: catch_clauses catch_clause  */
#line 117 "eon.y"
                                              { (yyval.nPtr) = opr(COLON, 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1558 "y.tab.c"
    break;

  case 20: /* catch_clause: CATCH LEFT_PARENTHESIS INTEGER RIGHT_PARENTHESIS stmt  */
#line 122 "eon.y"
                                               { (yyval.nPtr) = opr(CATCH, 2, con((yyvsp[-2].integer)), (yyvsp[0].nPtr)); }
#line 1564 "y.tab.c"
    break;

  case 21: /* catch_clause: CATCH LEFT_PARENTHESIS RIGHT_PARENTHESIS stmt  */
#line 124 "eon.y"
                                               { (yyval.nPtr) = opr(CATCH, 2, con(-1), (yyvsp[0].nPtr)); }
#line 1570 "y.tab.c"
    break;

  case 22: /* finally_clause: FINALLY stmt  */
#line 128 "eon.y"
                                              { (yyval.nPtr) = opr(FINALLY, 1, (yyvsp[0].nPtr)); }
#line 1576 "y.tab.c"
    break;

  case 23: /* throw_stmt: THROW expr COLON  */
#line 132 "eon.y"
                                               { (yyval.nPtr) = opr(THROW, 1, (yyvsp[-1].nPtr)); }
#line 1582 "y.tab.c"
    break;

  case 24: /* stmt_list: stmt  */
#line 136 "eon.y"
                                { (yyval.nPtr) = (yyvsp[0].nPtr); }
#line 1588 "y.tab.c"
    break;

  case 25: /* stmt_list: stmt_list stmt  */
#line 137 "eon.y"
                                { (yyval.nPtr) = opr(COLON, 2, (yyvsp[-1].nPtr), (yyvsp[0].nPtr)); }
#line 1594 "y.tab.c"
    break;

  case 28: /* expr: INTEGER  */
#line 145 "eon.y"
                                        { (yyval.nPtr) = con((yyvsp[0].integer)); }
#line 1600 "y.tab.c"
    break;

  case 29: /* expr: IDENTIFIER  */
#line 146 "eon.y"
                                        { (yyval.nPtr) = id((yyvsp[0].ide)); }
#line 1606 "y.tab.c"
    break;

  case 30: /* expr: MINUS expr  */
#line 147 "eon.y"
                                        { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[0].nPtr)); }
#line 1612 "y.tab.c"
    break;

  case 31: /* expr: expr PLUS expr  */
#line 148 "eon.y"
                                        { (yyval.nPtr) = opr(PLUS, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1618 "y.tab.c"
    break;

  case 32: /* expr: expr MINUS expr  */
#line 149 "eon.y"
                                        { (yyval.nPtr) = opr(MINUS, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1624 "y.tab.c"
    break;

  case 33: /* expr: expr MULTIPLE expr  */
#line 150 "eon.y"
                                        { (yyval.nPtr) = opr(MULTIPLE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1630 "y.tab.c"
    break;

  case 34: /* expr: expr DIVIDE expr  */
#line 151 "eon.y"
                                        { (yyval.nPtr) = opr(DIVIDE, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1636 "y.tab.c"
    break;

  case 35: /* expr: expr LESSTHAN expr  */
#line 152 "eon.y"
                                        { (yyval.nPtr) = opr(LESSTHAN, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1642 "y.tab.c"
    break;

  case 36: /* expr: expr GREATERTHAN expr  */
#line 153 "eon.y"
                                        { (yyval.nPtr) = opr(GREATERTHAN, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1648 "y.tab.c"
    break;

  case 37: /* expr: expr EQUALORGREAT expr  */
#line 154 "eon.y"
                                    { (yyval.nPtr) = opr(EQUALORGREAT, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1654 "y.tab.c"
    break;

  case 38: /* expr: expr EQUALORLESS expr  */
#line 155 "eon.y"
                                     { (yyval.nPtr) = opr(EQUALORLESS, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1660 "y.tab.c"
    break;

  case 39: /* expr: expr ISNOTEQUAL expr  */
#line 156 "eon.y"
                                        { (yyval.nPtr) = opr(ISNOTEQUAL, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1666 "y.tab.c"
    break;

  case 40: /* expr: expr EQUAL expr  */
#line 157 "eon.y"
                                   { (yyval.nPtr) = opr(EQUAL, 2, (yyvsp[-2].nPtr), (yyvsp[0].nPtr)); }
#line 1672 "y.tab.c"
    break;

  case 41: /* expr: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 158 "eon.y"
                                                           { (yyval.nPtr) = (yyvsp[-1].nPtr); }
#line 1678 "y.tab.c"
    break;


#line 1682 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 161 "eon.y"



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
