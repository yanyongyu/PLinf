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
/* "%code requires" blocks.  */
#line 20 "src/plinf.y"

  #include "intermediate.h"

#line 52 "src/plinf.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER_ = 258,
    WRITE = 259,
    READ = 260,
    INTEGER = 261,
    REAL = 262,
    BOOLEAN = 263,
    ARRAY = 264,
    NUMBER = 265,
    REAL_NUMBER = 266,
    TRUE = 267,
    FALSE = 268,
    CONST_ = 269,
    TYPE_ = 270,
    VAR_ = 271,
    PROCEDURE_ = 272,
    FUNCTION_ = 273,
    OF = 274,
    IF = 275,
    THEN = 276,
    ELSE = 277,
    WHILE = 278,
    DO = 279,
    CONTINUE = 280,
    EXIT = 281,
    OR = 282,
    AND = 283,
    NOT = 284,
    DIV = 285,
    MOD = 286,
    LE = 287,
    LEQ = 288,
    GE = 289,
    GEQ = 290,
    EQ = 291,
    NEQ = 292,
    PLUS = 293,
    MINUS = 294,
    DIVIDE = 295,
    TIMES = 296,
    PERIOD = 297,
    PERIOD_PERIOD = 298,
    COLON = 299,
    SEMI = 300,
    COMMA = 301,
    LPAREN = 302,
    RPAREN = 303,
    LBRACE = 304,
    RBRACE = 305,
    CALL = 306,
    ODD = 307,
    BLOCK_BEGIN = 308,
    BLOCK_END = 309,
    ASSIGN_ = 310,
    LOWER_THAN_ELSE = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "src/plinf.y"

  VAR_LIST *var_list;
  PARAM_LIST *param_list;
  NODE *node;
  TYPE *type;
  ARRAY_OFFSET *offset;
  CONST *const_value;
  IDENTIFIER *id;
  IDENTIFIER_REF *id_ref;

#line 131 "src/plinf.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SRC_PLINF_TAB_H_INCLUDED  */
