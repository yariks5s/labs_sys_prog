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

#ifndef YY_YY_MYAPP_HPP_INCLUDED
# define YY_YY_MYAPP_HPP_INCLUDED
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
    TOKEN_CHARCONST = 258,         /* TOKEN_CHARCONST  */
    TOKEN_INTCONST = 259,          /* TOKEN_INTCONST  */
    TOKEN_FLOATCONST = 260,        /* TOKEN_FLOATCONST  */
    TOKEN_STRINGCONST = 261,       /* TOKEN_STRINGCONST  */
    TOKEN_ID = 262,                /* TOKEN_ID  */
    TOKEN_WHITESPACEspace = 263,   /* TOKEN_WHITESPACEspace  */
    TOKEN_WHITESPACEtab = 264,     /* TOKEN_WHITESPACEtab  */
    TOKEN_WHITESPACEnewLine = 265, /* TOKEN_WHITESPACEnewLine  */
    TOKEN_ARITHMATICOP_MINUS = 266, /* TOKEN_ARITHMATICOP_MINUS  */
    TOKEN_ARITHMATICOP_DIV = 267,  /* TOKEN_ARITHMATICOP_DIV  */
    TOKEN_ARITHMATICOP_POW = 268,  /* TOKEN_ARITHMATICOP_POW  */
    TOKEN_ARITHMATICOP_PLUS = 269, /* TOKEN_ARITHMATICOP_PLUS  */
    TOKEN_ARITHMATICOP_MULT = 270, /* TOKEN_ARITHMATICOP_MULT  */
    TOKEN_BITWISEOP = 271,         /* TOKEN_BITWISEOP  */
    TOKEN_LOGICOP = 272,           /* TOKEN_LOGICOP  */
    TOKEN_RELATIONOP = 273,        /* TOKEN_RELATIONOP  */
    TOKEN_ASSIGNOP = 274,          /* TOKEN_ASSIGNOP  */
    TOKEN_LOGICOP_NOT = 275,       /* TOKEN_LOGICOP_NOT  */
    TOKEN_LEFTPAREN = 276,         /* TOKEN_LEFTPAREN  */
    TOKEN_RIGHTPAREN = 277,        /* TOKEN_RIGHTPAREN  */
    TOKEN_LCB = 278,               /* TOKEN_LCB  */
    TOKEN_RCB = 279,               /* TOKEN_RCB  */
    TOKEN_SEMICOLON = 280,         /* TOKEN_SEMICOLON  */
    TOKEN_COMMA = 281,             /* TOKEN_COMMA  */
    TOKEN_UNTIL = 282,             /* TOKEN_UNTIL  */
    TOKEN_LB = 283,                /* TOKEN_LB  */
    TOKEN_RB = 284,                /* TOKEN_RB  */
    TOKEN_PRFUNC = 285,            /* TOKEN_PRFUNC  */
    TOKEN_ELSECONDITION = 286,     /* TOKEN_ELSECONDITION  */
    TOKEN_INTTYPE = 287,           /* TOKEN_INTTYPE  */
    TOKEN_VOIDTYPE = 288,          /* TOKEN_VOIDTYPE  */
    TOKEN_DOUBLETYPE = 289,        /* TOKEN_DOUBLETYPE  */
    TOKEN_FLOATTYPE = 290,         /* TOKEN_FLOATTYPE  */
    TOKEN_CHARTYPE = 291,          /* TOKEN_CHARTYPE  */
    TOKEN_STRINGTYPE = 292,        /* TOKEN_STRINGTYPE  */
    TOKEN_BREAKSTMT = 293,         /* TOKEN_BREAKSTMT  */
    TOKEN_CONTINUESTMT = 294,      /* TOKEN_CONTINUESTMT  */
    TOKEN_MAINFUNC = 295,          /* TOKEN_MAINFUNC  */
    TOKEN_LOOP = 296,              /* TOKEN_LOOP  */
    TOKEN_RETURN = 297,            /* TOKEN_RETURN  */
    TOKEN_IFCONDITION = 298,       /* TOKEN_IFCONDITION  */
    TOKEN_COMMENT = 299            /* TOKEN_COMMENT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 61 "Bison_Rule.y"

    int intVal;
	char chVal;
    char* string;
    float floatVal;
	struct tnode *node;

#line 116 "myapp.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MYAPP_HPP_INCLUDED  */
