/* A Bison parser, made by GNU Bison 3.7.5.  */

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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_ASIN_H_INCLUDED
# define YY_YY_ASIN_H_INCLUDED
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
    MAS_ = 258,                    /* MAS_  */
    MENOS_ = 259,                  /* MENOS_  */
    MULT_ = 260,                   /* MULT_  */
    DIV_ = 261,                    /* DIV_  */
    AND_ = 262,                    /* AND_  */
    OR_ = 263,                     /* OR_  */
    NOT_ = 264,                    /* NOT_  */
    MAYOR_ = 265,                  /* MAYOR_  */
    MENOR_ = 266,                  /* MENOR_  */
    MAYORIG_ = 267,                /* MAYORIG_  */
    MENORIG_ = 268,                /* MENORIG_  */
    IGUALDAD_ = 269,               /* IGUALDAD_  */
    DESIGUALDAD_ = 270,            /* DESIGUALDAD_  */
    IGUAL_ = 271,                  /* IGUAL_  */
    APAR_ = 272,                   /* APAR_  */
    CPAR_ = 273,                   /* CPAR_  */
    ACOR_ = 274,                   /* ACOR_  */
    CCOR_ = 275,                   /* CCOR_  */
    ALLAV_ = 276,                  /* ALLAV_  */
    CLLAV_ = 277,                  /* CLLAV_  */
    PUNTCOMA_ = 278,               /* PUNTCOMA_  */
    COMA_ = 279,                   /* COMA_  */
    PUNTO_ = 280,                  /* PUNTO_  */
    INT_ = 281,                    /* INT_  */
    BOOL_ = 282,                   /* BOOL_  */
    STRUCT_ = 283,                 /* STRUCT_  */
    READ_ = 284,                   /* READ_  */
    PRINT_ = 285,                  /* PRINT_  */
    RETURN_ = 286,                 /* RETURN_  */
    IF_ = 287,                     /* IF_  */
    ELSE_ = 288,                   /* ELSE_  */
    WHILE_ = 289,                  /* WHILE_  */
    TRUE_ = 290,                   /* TRUE_  */
    FALSE_ = 291,                  /* FALSE_  */
    CTE_ = 292,                    /* CTE_  */
    ID_ = 293                      /* ID_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "src/asin.y"
 
    char* ident; 
    int cent;
    LPC listapc;
    EXP exp;
    LOOP loop;

#line 110 "asin.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASIN_H_INCLUDED  */
