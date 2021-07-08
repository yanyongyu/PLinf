/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/plinf.y"

#include <stdio.h>
#include <stdlib.h>

#include "intermediate.h"

int icode_index = 0;
ICODE *global_result;
extern int yylineno;

int yylex(void);
void yyerror(const char *);
SYMBOL *create_symbol(SYMBOL_TYPE);
ICODE *create_icode(OPERATION);
ICODE *concat_icode(ICODE *, ICODE *);
ID_LIST *concat_id_list(ID_LIST *, ID_LIST *);
PARAM_LIST *concat_param_list(PARAM_LIST *, PARAM_LIST *);

#line 89 "src/plinf.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 203 "src/plinf.tab.c"

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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  200

#define YYUNDEFTOK  2
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    76,    82,    87,    90,    93,    96,    99,
     102,   105,   108,   111,   114,   117,   120,   123,   126,   129,
     132,   137,   142,   145,   150,   160,   170,   180,   192,   197,
     200,   205,   217,   220,   223,   226,   232,   240,   245,   263,
     283,   288,   295,   301,   307,   313,   321,   324,   329,   341,
     354,   367,   383,   389,   397,   398,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   414,   415,   418,
     419,   422,   423,   426,   427,   430,   431,   432,   435,   436,
     437,   438,   439,   440,   443,   444,   445,   446,   447,   448,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INTEGER", "REAL",
  "BOOLEAN", "ARRAY", "NUMBER", "REAL_NUMBER", "TRUE", "FALSE", "CONST",
  "TYPE", "VAR", "PROCEDURE", "FUNCTION", "OF", "IF", "THEN", "ELSE",
  "WRITE", "READ", "WHILE", "DO", "EXIT", "OR", "AND", "NOT", "DIV", "MOD",
  "RELOP", "PERIOD", "PERIOD_PERIOD", "COLON", "SEMI", "COMMA", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "CALL", "ODD", "BLOCK_BEGIN", "BLOCK_END",
  "ASSIGN", "EQ", "PLUS", "MINUS", "DIVIDE", "TIMES", "LOWER_THAN_ELSE",
  "$accept", "program", "before_program", "block", "declarepart",
  "const_declare", "const_define", "const_definition", "type_declare",
  "type_define", "type_definition", "type_expression", "var_declare",
  "var_define", "identifier_list", "type", "procedure_declare",
  "procedure_define", "param_define", "statements", "statement",
  "identifier_refs", "identifier_ref", "indexs", "params", "expression",
  "simple_expression", "term", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

#define YYPACT_NINF (-177)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -177,    13,   148,  -177,    25,    45,    49,    54,    58,    12,
      27,    94,   137,    23,    23,  -177,    30,    48,  -177,    34,
      69,  -177,  -177,    70,    59,   120,    41,  -177,  -177,   137,
      23,    23,    23,    23,    23,  -177,   169,    25,   177,    45,
      49,   182,    81,   148,   110,   182,   110,    76,    23,    23,
      23,    23,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
      83,  -177,  -177,   134,  -177,  -177,  -177,  -177,  -177,  -177,
      88,    98,   153,    92,   154,    96,    26,   108,   112,    26,
    -177,   162,  -177,  -177,   121,   124,    23,   165,   182,  -177,
     182,   195,   166,   148,   168,    26,   164,  -177,  -177,  -177,
    -177,   130,    26,   197,   167,   130,   130,  -177,   186,   128,
     -18,  -177,    26,   203,   183,   171,    93,  -177,    26,   -23,
    -177,  -177,   175,   148,   176,   182,   170,    26,  -177,   174,
     178,    26,   -18,   -18,   103,   130,    26,    26,   130,   130,
     130,   130,   130,   130,   130,   157,  -177,     5,  -177,   103,
      26,  -177,  -177,   205,   199,   182,   179,  -177,   184,  -177,
     180,  -177,    26,    24,   198,   -18,    38,    38,   -18,   -18,
    -177,  -177,  -177,  -177,  -177,    26,  -177,  -177,  -177,  -177,
     158,   181,   177,  -177,  -177,   148,  -177,   161,  -177,   103,
    -177,  -177,   200,  -177,   187,  -177,  -177,   177,  -177,  -177
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    20,     1,     0,     0,     0,     0,     0,     0,
       0,    16,    17,    18,    19,    47,     0,     0,    23,     0,
       0,    30,    41,     0,     0,     0,     0,     2,    55,    10,
      12,    11,    14,    13,    15,    46,     0,    21,     0,    28,
      37,     0,     0,    20,     0,     0,     0,    66,     6,     7,
       8,     9,    24,    25,    26,    27,    22,    32,    33,    34,
       0,    31,    29,     0,    45,    42,    43,    44,    39,    40,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
      61,     0,    55,     4,     0,     0,     5,     0,     0,    48,
       0,     0,     0,    20,     0,     0,    70,    91,    92,    98,
      99,     0,     0,     0,     0,     0,     0,    90,     0,    75,
      83,    89,     0,     0,     0,    62,    66,    54,     0,     0,
      38,    53,     0,    20,     0,     0,     0,     0,    94,     0,
      95,     0,    81,    82,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    74,     0,    68,    66,
       0,    59,    56,     0,     0,     0,     0,    50,     0,    72,
       0,    93,     0,     0,    57,    80,    76,    77,    78,    79,
      88,    86,    87,    85,    84,     0,    64,    65,    67,    60,
       0,     0,     0,    52,    49,    20,    71,     0,    97,    66,
      73,    63,     0,    35,     0,    96,    58,     0,    51,    36
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -177,  -177,  -177,   -42,  -177,  -177,  -177,   188,   212,  -177,
     185,  -176,     4,  -177,   189,   -43,   118,    -9,   190,   144,
    -131,  -177,   -47,  -177,   -97,   -72,  -117,   -79,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     9,    10,    11,    17,    18,    12,    20,
      21,    61,    13,    23,    24,    68,    14,    15,    72,    47,
      84,   147,   107,    96,   145,   146,   109,   110,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      85,    70,    73,   164,   108,    35,   193,   114,    75,   140,
     153,   141,   142,     3,   163,    30,    32,   154,   179,   166,
     167,   199,    35,   126,    35,    35,   132,   133,    16,    75,
     129,   143,   144,    48,    97,    98,    99,   100,     7,     8,
      35,    35,    35,   177,    27,   120,   152,   121,    19,   128,
     135,   124,    22,   180,   101,   160,   165,    25,   196,   168,
     169,    26,   188,   102,   135,   187,   148,   103,   104,    85,
      28,   138,   139,   105,   106,    45,    36,    35,    46,    75,
      38,   156,   158,    37,    69,   138,   139,    85,   170,   171,
     172,   173,   174,    41,    76,    42,    75,    77,    78,    79,
     178,    80,    85,   190,    39,    40,    75,     5,     6,     7,
       8,    76,   183,    71,    77,    78,    79,    81,    80,    82,
      83,    76,    87,    89,    77,    78,    79,    93,    80,    31,
      33,    34,    90,    75,    81,    95,    82,   151,    97,    98,
      99,   100,    85,   194,    81,   112,    82,    49,    50,   113,
      51,     6,     7,     8,   135,    43,   117,    44,   101,   136,
       4,     5,     6,     7,     8,   115,    86,   102,    88,   118,
      42,   103,   104,   119,   137,   138,   139,    52,    53,    54,
      55,    57,    58,    59,    60,    64,    65,    66,    67,    91,
      91,    92,    94,   175,   175,   176,   191,   175,   122,   195,
     130,   123,   125,   127,   131,   134,    75,   149,   150,   155,
     159,   157,   161,   181,   184,   162,   182,   197,   189,   185,
     186,   192,   198,    29,    62,    56,   116,     0,     0,    63,
       0,     0,     0,     0,     0,     0,    74
};

static const yytype_int16 yycheck[] =
{
      47,    43,    45,   134,    76,    14,   182,    79,     3,    27,
      33,    29,    30,     0,   131,    11,    12,    40,   149,   136,
     137,   197,    31,    95,    33,    34,   105,   106,     3,     3,
     102,    49,    50,    29,     8,     9,    10,    11,    15,    16,
      49,    50,    51,    38,    32,    88,   118,    90,     3,   101,
      26,    93,     3,   150,    28,   127,   135,     3,   189,   138,
     139,     3,    38,    37,    26,   162,   113,    41,    42,   116,
      43,    47,    48,    47,    48,    34,    46,    86,    37,     3,
      46,   123,   125,    35,     3,    47,    48,   134,   140,   141,
     142,   143,   144,    34,    18,    36,     3,    21,    22,    23,
     147,    25,   149,   175,    35,    35,     3,    13,    14,    15,
      16,    18,   155,     3,    21,    22,    23,    41,    25,    43,
      44,    18,    39,    35,    21,    22,    23,    35,    25,    11,
      12,    13,    34,     3,    41,    39,    43,    44,     8,     9,
      10,    11,   189,   185,    41,    37,    43,    29,    30,    37,
      32,    14,    15,    16,    26,    35,    35,    37,    28,    31,
      12,    13,    14,    15,    16,     3,    48,    37,    34,    45,
      36,    41,    42,     8,    46,    47,    48,     8,     9,    10,
      11,     4,     5,     6,     7,     3,     4,     5,     6,    36,
      36,    38,    38,    36,    36,    38,    38,    36,     3,    38,
       3,    35,    34,    39,    37,    19,     3,    24,    37,    34,
      40,    35,    38,     8,    35,    37,    17,    17,    20,    35,
      40,    40,    35,    11,    39,    37,    82,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    53,    54,     0,    12,    13,    14,    15,    16,    55,
      56,    57,    60,    64,    68,    69,     3,    58,    59,     3,
      61,    62,     3,    65,    66,     3,     3,    32,    43,    60,
      64,    68,    64,    68,    68,    69,    46,    35,    46,    35,
      35,    34,    36,    35,    37,    34,    37,    71,    64,    68,
      68,    68,     8,     9,    10,    11,    59,     4,     5,     6,
       7,    63,    62,    66,     3,     4,     5,     6,    67,     3,
      55,     3,    70,    67,    70,     3,    18,    21,    22,    23,
      25,    41,    43,    44,    72,    74,    68,    39,    34,    35,
      34,    36,    38,    35,    38,    39,    75,     8,     9,    10,
      11,    28,    37,    41,    42,    47,    48,    74,    77,    78,
      79,    80,    37,    37,    77,     3,    71,    35,    45,     8,
      67,    67,     3,    35,    55,    34,    77,    39,    80,    77,
       3,    37,    79,    79,    19,    26,    31,    46,    47,    48,
      27,    29,    30,    49,    50,    76,    77,    73,    74,    24,
      37,    44,    77,    33,    40,    34,    55,    35,    67,    40,
      77,    38,    37,    78,    72,    79,    78,    78,    79,    79,
      80,    80,    80,    80,    80,    36,    38,    38,    74,    72,
      76,     8,    17,    67,    35,    35,    40,    76,    38,    20,
      77,    38,    40,    63,    55,    38,    72,    17,    35,    63
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    55,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    57,    58,    58,    59,    59,    59,    59,    60,    61,
      61,    62,    63,    63,    63,    63,    63,    64,    65,    65,
      66,    66,    67,    67,    67,    67,    68,    68,    69,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    77,    78,    78,
      78,    78,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     4,     4,     3,     3,     3,     3,
       2,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       0,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     1,     1,     1,     6,     8,     3,     5,     3,
       3,     1,     1,     1,     1,     1,     2,     1,     5,     8,
       7,    10,     5,     3,     3,     0,     3,     4,     6,     3,
       4,     1,     2,     5,     4,     4,     0,     2,     1,     1,
       2,     4,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     2,     2,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     3,     2,     2,     5,     4,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 71 "src/plinf.y"
                                     {
      global_result = (yyvsp[-1].icode);
    }
#line 1635 "src/plinf.tab.c"
    break;

  case 3:
#line 76 "src/plinf.y"
                {
      // clear icode index and begin a new analysis
      icode_index = 0;
    }
#line 1644 "src/plinf.tab.c"
    break;

  case 4:
#line 82 "src/plinf.y"
                                                    {
      (yyval.icode) = (yyvsp[-3].icode);
    }
#line 1652 "src/plinf.tab.c"
    break;

  case 5:
#line 87 "src/plinf.y"
                                                                      {
      (yyval.icode) = concat_icode((yyvsp[-3].icode), concat_icode((yyvsp[-2].icode), concat_icode((yyvsp[-1].icode), (yyvsp[0].icode))));
    }
#line 1660 "src/plinf.tab.c"
    break;

  case 6:
#line 90 "src/plinf.y"
                                           {
      (yyval.icode) = concat_icode((yyvsp[-2].icode), concat_icode((yyvsp[-1].icode), (yyvsp[0].icode)));
    }
#line 1668 "src/plinf.tab.c"
    break;

  case 7:
#line 93 "src/plinf.y"
                                                 {
      (yyval.icode) = concat_icode((yyvsp[-2].icode), concat_icode((yyvsp[-1].icode), (yyvsp[0].icode)));
    }
#line 1676 "src/plinf.tab.c"
    break;

  case 8:
#line 96 "src/plinf.y"
                                                {
      (yyval.icode) = concat_icode((yyvsp[-2].icode), concat_icode((yyvsp[-1].icode), (yyvsp[0].icode)));
    }
#line 1684 "src/plinf.tab.c"
    break;

  case 9:
#line 99 "src/plinf.y"
                                               {
      (yyval.icode) = concat_icode((yyvsp[-2].icode), concat_icode((yyvsp[-1].icode), (yyvsp[0].icode)));
    }
#line 1692 "src/plinf.tab.c"
    break;

  case 10:
#line 102 "src/plinf.y"
                               {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 1700 "src/plinf.tab.c"
    break;

  case 11:
#line 105 "src/plinf.y"
                                    {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 1708 "src/plinf.tab.c"
    break;

  case 12:
#line 108 "src/plinf.y"
                              {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 1716 "src/plinf.tab.c"
    break;

  case 13:
#line 111 "src/plinf.y"
                                   {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 1724 "src/plinf.tab.c"
    break;

  case 14:
#line 114 "src/plinf.y"
                             {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 1732 "src/plinf.tab.c"
    break;

  case 15:
#line 117 "src/plinf.y"
                                  {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 1740 "src/plinf.tab.c"
    break;

  case 16:
#line 120 "src/plinf.y"
                  {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 1748 "src/plinf.tab.c"
    break;

  case 17:
#line 123 "src/plinf.y"
                 {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 1756 "src/plinf.tab.c"
    break;

  case 18:
#line 126 "src/plinf.y"
                {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 1764 "src/plinf.tab.c"
    break;

  case 19:
#line 129 "src/plinf.y"
                      {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 1772 "src/plinf.tab.c"
    break;

  case 20:
#line 132 "src/plinf.y"
    {
      (yyval.icode) = create_icode(op_nop);
    }
#line 1780 "src/plinf.tab.c"
    break;

  case 21:
#line 137 "src/plinf.y"
                                       {
      (yyval.icode) = (yyvsp[-1].icode);
    }
#line 1788 "src/plinf.tab.c"
    break;

  case 22:
#line 142 "src/plinf.y"
                                                 {
      (yyval.icode) = concat_icode((yyvsp[-2].icode), (yyvsp[0].icode));
    }
#line 1796 "src/plinf.tab.c"
    break;

  case 23:
#line 145 "src/plinf.y"
                     {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 1804 "src/plinf.tab.c"
    break;

  case 24:
#line 150 "src/plinf.y"
                                       {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->identifier = (yyvsp[-2].id);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = (yyvsp[0].const_value);
      (yyval.icode) = temp;
    }
#line 1819 "src/plinf.tab.c"
    break;

  case 25:
#line 160 "src/plinf.y"
                              {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = (yyvsp[0].const_value);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->identifier = (yyvsp[-2].id);
      (yyval.icode) = temp;
    }
#line 1834 "src/plinf.tab.c"
    break;

  case 26:
#line 170 "src/plinf.y"
                       {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = (yyvsp[0].const_value);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->identifier = (yyvsp[-2].id);
      (yyval.icode) = temp;
    }
#line 1849 "src/plinf.tab.c"
    break;

  case 27:
#line 180 "src/plinf.y"
                        {
      ICODE *temp = create_icode(op_const_declare);
      SYMBOL *number = create_symbol(st_const);
      temp->symbol[0] = number;
      number->const_value = (yyvsp[0].const_value);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->identifier = (yyvsp[-2].id);
      (yyval.icode) = temp;
    }
#line 1864 "src/plinf.tab.c"
    break;

  case 28:
#line 192 "src/plinf.y"
                                    {
      (yyval.icode) = (yyvsp[-1].icode);
    }
#line 1872 "src/plinf.tab.c"
    break;

  case 29:
#line 197 "src/plinf.y"
                                              {
      (yyval.icode) = concat_icode((yyvsp[-2].icode), (yyvsp[0].icode));
    }
#line 1880 "src/plinf.tab.c"
    break;

  case 30:
#line 200 "src/plinf.y"
                    {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 1888 "src/plinf.tab.c"
    break;

  case 31:
#line 205 "src/plinf.y"
                                               {
      ICODE *temp = create_icode(op_type_declare);
      SYMBOL *id = create_symbol(st_identifier);
      temp->symbol[2] = id;
      id->identifier = (yyvsp[-2].id);
      SYMBOL *type = create_symbol(st_type);
      temp->symbol[0] = type;
      type->type_value = (yyvsp[0].type_value);
      (yyval.icode) = temp;
    }
#line 1903 "src/plinf.tab.c"
    break;

  case 32:
#line 217 "src/plinf.y"
                         {
      (yyval.type_value) = (yyvsp[0].type_value);
    }
#line 1911 "src/plinf.tab.c"
    break;

  case 33:
#line 220 "src/plinf.y"
         {
      (yyval.type_value) = (yyvsp[0].type_value);
    }
#line 1919 "src/plinf.tab.c"
    break;

  case 34:
#line 223 "src/plinf.y"
            {
      (yyval.type_value) = (yyvsp[0].type_value);
    }
#line 1927 "src/plinf.tab.c"
    break;

  case 35:
#line 226 "src/plinf.y"
                                                  {
      (yyvsp[-5].type_value)->array_start = 0;
      (yyvsp[-5].type_value)->array_end = (yyvsp[-3].const_value)->num - 1;
      (yyvsp[-5].type_value)->sub_value = (yyvsp[0].type_value);
      (yyval.type_value) = (yyvsp[-5].type_value);
    }
#line 1938 "src/plinf.tab.c"
    break;

  case 36:
#line 232 "src/plinf.y"
                                                                       {
      (yyvsp[-7].type_value)->array_start = (yyvsp[-5].const_value)->num;
      (yyvsp[-7].type_value)->array_end = (yyvsp[-3].const_value)->num;
      (yyvsp[-7].type_value)->sub_value = (yyvsp[0].type_value);
      (yyval.type_value) = (yyvsp[-7].type_value);
    }
#line 1949 "src/plinf.tab.c"
    break;

  case 37:
#line 240 "src/plinf.y"
                                 {
      (yyval.icode) = (yyvsp[-1].icode);
    }
#line 1957 "src/plinf.tab.c"
    break;

  case 38:
#line 245 "src/plinf.y"
                                                       {
      SYMBOL *var, *id;
      ICODE *define, *start, *temp = create_icode(op_nop);
      ID_LIST *id_list = (yyvsp[-2].id_list);
      start = temp;
      do {
        define = temp->next = create_icode(op_var_declare);
        id = create_symbol(st_identifier);
        id->identifier = id_list->name;
        define->symbol[2] = id;
        var = create_symbol(st_var);
        var->var_value = (yyvsp[0].var_value);
        define->symbol[0] = var;
        temp = temp->next;
        id_list = id_list->next;
      } while (id_list);
      (yyval.icode) = concat_icode((yyvsp[-4].icode), start->next);
    }
#line 1980 "src/plinf.tab.c"
    break;

  case 39:
#line 263 "src/plinf.y"
                               {
      SYMBOL *var, *id;
      ICODE *define, *start, *temp = create_icode(op_nop);
      ID_LIST *id_list = (yyvsp[-2].id_list);
      start = temp;
      do {
        define = temp->next = create_icode(op_var_declare);
        id = create_symbol(st_identifier);
        id->identifier = id_list->name;
        define->symbol[2] = id;
        var = create_symbol(st_var);
        var->var_value = (yyvsp[0].var_value);
        define->symbol[0] = var;
        temp = temp->next;
        id_list = id_list->next;
      } while (id_list);
      (yyval.icode) = start->next;
    }
#line 2003 "src/plinf.tab.c"
    break;

  case 40:
#line 283 "src/plinf.y"
                                                  {
      ID_LIST *temp = (ID_LIST *)calloc(1, sizeof(ID_LIST));
      temp->name = (yyvsp[0].id);
      (yyval.id_list) = concat_id_list((yyvsp[-2].id_list), temp);
    }
#line 2013 "src/plinf.tab.c"
    break;

  case 41:
#line 288 "src/plinf.y"
               {
      ID_LIST *temp = (ID_LIST *)calloc(1, sizeof(ID_LIST));
      temp->name = (yyvsp[0].id);
      (yyval.id_list) = temp;
    }
#line 2023 "src/plinf.tab.c"
    break;

  case 42:
#line 295 "src/plinf.y"
              {
      VAR_VALUE *temp = (VAR_VALUE *)calloc(1, sizeof(VAR_VALUE));
      temp->type = vt_type;
      temp->detail = (yyvsp[0].type_value);
      (yyval.var_value) = temp;
    }
#line 2034 "src/plinf.tab.c"
    break;

  case 43:
#line 301 "src/plinf.y"
         {
      VAR_VALUE *temp = (VAR_VALUE *)calloc(1, sizeof(VAR_VALUE));
      temp->type = vt_type;
      temp->detail = (yyvsp[0].type_value);
      (yyval.var_value) = temp;
    }
#line 2045 "src/plinf.tab.c"
    break;

  case 44:
#line 307 "src/plinf.y"
            {
      VAR_VALUE *temp = (VAR_VALUE *)calloc(1, sizeof(VAR_VALUE));
      temp->type = vt_type;
      temp->detail = (yyvsp[0].type_value);
      (yyval.var_value) = temp;
    }
#line 2056 "src/plinf.tab.c"
    break;

  case 45:
#line 313 "src/plinf.y"
               {
      VAR_VALUE *temp = (VAR_VALUE *)calloc(1, sizeof(VAR_VALUE));
      temp->type = vt_identifier;
      temp->identifier = (yyvsp[0].id);
      (yyval.var_value) = temp;
    }
#line 2067 "src/plinf.tab.c"
    break;

  case 46:
#line 321 "src/plinf.y"
                                                      {
      (yyval.icode) = concat_icode((yyvsp[-1].icode), (yyvsp[0].icode));
    }
#line 2075 "src/plinf.tab.c"
    break;

  case 47:
#line 324 "src/plinf.y"
                     {
      (yyval.icode) = (yyvsp[0].icode);
    }
#line 2083 "src/plinf.tab.c"
    break;

  case 48:
#line 329 "src/plinf.y"
                                                       {
      ICODE *temp = create_icode(op_procedure_declare);
      PROCEDURE_VALUE *procedure_value = (PROCEDURE_VALUE *)calloc(1, sizeof(PROCEDURE_VALUE));
      procedure_value->icode_list = (yyvsp[-1].icode);
      SYMBOL *procedure = create_symbol(st_procedure);
      procedure->procedure_value = procedure_value;
      temp->symbol[0] = procedure;
      SYMBOL *id = create_symbol(st_identifier);
      id->identifier = (yyvsp[-3].id);
      temp->symbol[2] = id;
      (yyval.icode) = temp;
    }
#line 2100 "src/plinf.tab.c"
    break;

  case 49:
#line 341 "src/plinf.y"
                                                                    {
      ICODE *temp = create_icode(op_procedure_declare);
      PROCEDURE_VALUE *procedure_value = (PROCEDURE_VALUE *)calloc(1, sizeof(PROCEDURE_VALUE));
      procedure_value->param_list = (yyvsp[-4].param_list);
      procedure_value->icode_list = (yyvsp[-1].icode);
      SYMBOL *procedure = create_symbol(st_procedure);
      procedure->procedure_value = procedure_value;
      temp->symbol[0] = procedure;
      SYMBOL *id = create_symbol(st_identifier);
      id->identifier = (yyvsp[-6].id);
      temp->symbol[2] = id;
      (yyval.icode) = temp;
    }
#line 2118 "src/plinf.tab.c"
    break;

  case 50:
#line 354 "src/plinf.y"
                                                   {
      ICODE *temp = create_icode(op_function_declare);
      FUNCTION_VALUE *function_value = (FUNCTION_VALUE *)calloc(1, sizeof(FUNCTION_VALUE));
      function_value->return_var = (yyvsp[-3].var_value);
      function_value->icode_list = (yyvsp[-1].icode);
      SYMBOL *function = create_symbol(st_function);
      function->function_value = function_value;
      temp->symbol[0] = function;
      SYMBOL *id = create_symbol(st_identifier);
      id->identifier = (yyvsp[-5].id);
      temp->symbol[2] = id;
      (yyval.icode) = temp;
    }
#line 2136 "src/plinf.tab.c"
    break;

  case 51:
#line 367 "src/plinf.y"
                                                                              {
      ICODE *temp = create_icode(op_function_declare);
      FUNCTION_VALUE *function_value = (FUNCTION_VALUE *)calloc(1, sizeof(FUNCTION_VALUE));
      function_value->param_list = (yyvsp[-6].param_list);
      function_value->return_var = (yyvsp[-3].var_value);
      function_value->icode_list = (yyvsp[-1].icode);
      SYMBOL *function = create_symbol(st_function);
      function->function_value = function_value;
      temp->symbol[0] = function;
      SYMBOL *id = create_symbol(st_identifier);
      id->identifier = (yyvsp[-8].id);
      temp->symbol[2] = id;
      (yyval.icode) = temp;
    }
#line 2155 "src/plinf.tab.c"
    break;

  case 52:
#line 383 "src/plinf.y"
                                                       {
      PARAM_LIST *temp = (PARAM_LIST *)calloc(1, sizeof(PARAM_LIST));
      temp->name = (yyvsp[-2].id);
      temp->var_value = (yyvsp[0].var_value);
      (yyval.param_list) = concat_param_list((yyvsp[-4].param_list), temp);
    }
#line 2166 "src/plinf.tab.c"
    break;

  case 53:
#line 389 "src/plinf.y"
                          {
      PARAM_LIST *temp = (PARAM_LIST *)calloc(1, sizeof(PARAM_LIST));
      temp->name = (yyvsp[-2].id);
      temp->var_value = (yyvsp[0].var_value);
      (yyval.param_list) = temp;
    }
#line 2177 "src/plinf.tab.c"
    break;


#line 2181 "src/plinf.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 463 "src/plinf.y"


void yyerror(const char *msg) {
  fprintf(stderr, "%s at line %d\n", msg, yylineno);
}

SYMBOL *create_symbol(SYMBOL_TYPE type) {
  SYMBOL *symbol = (SYMBOL *)calloc(1, sizeof(SYMBOL));
  symbol->type = type;
  return symbol;
}

ICODE *create_icode(OPERATION operation) {
  ICODE *icode = (ICODE *)calloc(1, sizeof(ICODE));
  icode->index = icode_index;
  icode->op = operation;
  icode_index++;
  return icode;
}

ICODE *concat_icode(ICODE *first, ICODE *second) {
  ICODE *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}

ID_LIST *concat_id_list(ID_LIST *first, ID_LIST *second) {
  ID_LIST *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}

PARAM_LIST *concat_param_list(PARAM_LIST *first, PARAM_LIST *second) {
  PARAM_LIST *temp = first;
  while (temp->next) temp = temp->next;
  temp->next = second;
  return first;
}
