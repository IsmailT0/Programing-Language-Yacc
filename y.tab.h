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
    TRY = 281,                     /* TRY  */
    CATCH = 282,                   /* CATCH  */
    THEN = 283,                    /* THEN  */
    SWITCH = 284,                  /* SWITCH  */
    CASE = 285,                    /* CASE  */
    IMPORT = 286,                  /* IMPORT  */
    BREAK = 287,                   /* BREAK  */
    CONTINUE = 288,                /* CONTINUE  */
    ASSIGN = 289,                  /* ASSIGN  */
    SCAN = 290,                    /* SCAN  */
    POW = 291,                     /* POW  */
    PLUS = 292,                    /* PLUS  */
    MINUS = 293,                   /* MINUS  */
    MULTIPLE = 294,                /* MULTIPLE  */
    DIVIDE = 295,                  /* DIVIDE  */
    MOD = 296,                     /* MOD  */
    LESSTHAN = 297,                /* LESSTHAN  */
    GREATERTHAN = 298,             /* GREATERTHAN  */
    NL = 299,                      /* NL  */
    INCREASE = 300,                /* INCREASE  */
    DECREASE = 301,                /* DECREASE  */
    COLON = 302,                   /* COLON  */
    SEMICOLON = 303,               /* SEMICOLON  */
    COMMA = 304,                   /* COMMA  */
    EQUALORGREAT = 305,            /* EQUALORGREAT  */
    EQUALORLESS = 306,             /* EQUALORLESS  */
    EQUAL = 307,                   /* EQUAL  */
    ISNOTEQUAL = 308,              /* ISNOTEQUAL  */
    LOGICAL_AND_OPERATOR = 309,    /* LOGICAL_AND_OPERATOR  */
    OR = 310,                      /* OR  */
    LEFT_PARENTHESIS = 311,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 312,       /* RIGHT_PARENTHESIS  */
    LEFT_BRACE = 313,              /* LEFT_BRACE  */
    RIGHT_BRACE = 314,             /* RIGHT_BRACE  */
    LEFTSQRBR = 315,               /* LEFTSQRBR  */
    RIGHTSQRBR = 316,              /* RIGHTSQRBR  */
    QUOTES = 317,                  /* QUOTES  */
    IFX = 318,                     /* IFX  */
    UMINUS = 319                   /* UMINUS  */
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
#define TRY 281
#define CATCH 282
#define THEN 283
#define SWITCH 284
#define CASE 285
#define IMPORT 286
#define BREAK 287
#define CONTINUE 288
#define ASSIGN 289
#define SCAN 290
#define POW 291
#define PLUS 292
#define MINUS 293
#define MULTIPLE 294
#define DIVIDE 295
#define MOD 296
#define LESSTHAN 297
#define GREATERTHAN 298
#define NL 299
#define INCREASE 300
#define DECREASE 301
#define COLON 302
#define SEMICOLON 303
#define COMMA 304
#define EQUALORGREAT 305
#define EQUALORLESS 306
#define EQUAL 307
#define ISNOTEQUAL 308
#define LOGICAL_AND_OPERATOR 309
#define OR 310
#define LEFT_PARENTHESIS 311
#define RIGHT_PARENTHESIS 312
#define LEFT_BRACE 313
#define RIGHT_BRACE 314
#define LEFTSQRBR 315
#define RIGHTSQRBR 316
#define QUOTES 317
#define IFX 318
#define UMINUS 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "eon.y"

    int integer;                 
    char ide;               
    nodeType *nPtr;             

#line 201 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
