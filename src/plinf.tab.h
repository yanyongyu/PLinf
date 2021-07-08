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
    INTEGER = 259,
    REAL = 260,
    BOOLEAN = 261,
    ARRAY = 262,
    NUMBER = 263,
    REAL_NUMBER = 264,
    TRUE = 265,
    FALSE = 266,
    CONST = 267,
    TYPE = 268,
    VAR = 269,
    PROCEDURE = 270,
    FUNCTION = 271,
    OF = 272,
    IF = 273,
    THEN = 274,
    ELSE = 275,
    WRITE = 276,
    READ = 277,
    WHILE = 278,
    DO = 279,
    EXIT = 280,
    OR = 281,
    AND = 282,
    NOT = 283,
    DIV = 284,
    MOD = 285,
    RELOP = 286,
    PERIOD = 287,
    PERIOD_PERIOD = 288,
    COLON = 289,
    SEMI = 290,
    COMMA = 291,
    LPAREN = 292,
    RPAREN = 293,
    LBRACE = 294,
    RBRACE = 295,
    CALL = 296,
    ODD = 297,
    BLOCK_BEGIN = 298,
    BLOCK_END = 299,
    ASSIGN = 300,
    EQ = 301,
    PLUS = 302,
    MINUS = 303,
    DIVIDE = 304,
    TIMES = 305,
    LOWER_THAN_ELSE = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "src/plinf.y"

  char *id;
  ID_LIST *id_list;
  PARAM_LIST *param_list;
  ICODE *icode;
  VAR_VALUE *var_value;
  TYPE_VALUE *type_value;
  CONST_VALUE *const_value;

#line 119 "src/plinf.tab.h"

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
