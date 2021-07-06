/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SRC_PLINF_TAB_H_INCLUDED
# define YY_YY_SRC_PLINF_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    NUMBER = 259,
    CONST = 260,
    TYPE = 261,
    VAR = 262,
    PROCEDURE = 263,
    FUNCTION = 264,
    INTEGER = 265,
    REAL = 266,
    BOOLEAN = 267,
    ARRAY = 268,
    OF = 269,
    TRUE = 270,
    FALSE = 271,
    IF = 272,
    THEN = 273,
    ELSE = 274,
    WRITE = 275,
    READ = 276,
    WHILE = 277,
    DO = 278,
    EXIT = 279,
    OR = 280,
    AND = 281,
    NOT = 282,
    DIV = 283,
    MOD = 284,
    RELOP = 285,
    PERIOD = 286,
    COLON = 287,
    SEMI = 288,
    COMMA = 289,
    LPAREN = 290,
    RPAREN = 291,
    LBRACE = 292,
    RBRACE = 293,
    CALL = 294,
    ODD = 295,
    BLOCK_BEGIN = 296,
    BLOCK_END = 297,
    ASSIGN = 298,
    EQ = 299,
    PLUS = 300,
    MINUS = 301,
    DIVIDE = 302,
    TIMES = 303,
    LOWER_THAN_ELSE = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 5 "src/plinf.y"

  char *id;
  long num;

#line 112 "src/plinf.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PLINF_TAB_H_INCLUDED  */
