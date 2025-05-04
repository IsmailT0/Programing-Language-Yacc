/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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

#line 203 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
