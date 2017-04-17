/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "bison.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "func.c"
#include "mystring.c"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

symbol_table_row* resolve(symbol_table_row* str , list* dimlist) ;
char* datatype_to_string(symbol_table_row* str) ;

int expr_type(int t1 , int t2) ;
int is_int(int t) ;
int is_array(int t) ;
int is_struct(int t) ;

func_table* ft = NULL ;
symbol_table* st = NULL ;
struct_def* sdf = NULL ;
scope_stack* sstk = NULL ;
scope_map* sm = NULL ;
int ind_dim = 0 ;

int line_no = 1 ;
int cur_scope = 0 ;
int cur_dt = 0 ;
int sdt ;
func_table_row* cur_func_ptr = NULL ; // the functions which is being defiend 
func_table_row* call_func_ptr = NULL ; // the functions which is being called

char* to_str_eletype(int type) ;

void yyerror (char const *s)
{
	printf("Parse error on line no. %d : %s\n" , line_no , s) ;
	exit(0) ;
}

// Union types
typedef struct decl{
	int type ;
	symbol_table_row* ptr ;
}decl ;

typedef struct id{
	int type ; // this contains the element type and not if it is SMIPLE , ARRAY or STRUCT ! This you need to get from ptr !
	char* val ;
	symbol_table_row* ptr ;
	symbol_table* st ;
	list* dimlist ; // this is used in lvalue .
}id ;

typedef struct expr{
	int type ;
}expr ;

typedef struct constant{
	int type ;
	int i_val ;
	float f_val ;
	char c_val ;
} constant;
//


#line 135 "bison.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


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
    T_INT = 258,
    T_FLOAT = 259,
    T_CHAR = 260,
    T_STRUCT = 261,
    T_ERROR = 262,
    ID = 263,
    V_INT = 264,
    V_FLOAT = 265,
    V_CHAR = 266
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "bison.y" /* yacc.c:355  */

	decl d ;
	expr e ;
	constant c ;
	id i ;
	list* l ;
	func_table_row* f ;
	symbol_table_row* a ; // argument list for function calls
	int np ; // no. of parameters . Used by PARAM_LIST . This is also used fot ARG_LIST , but in this 
	// case it respresents the 'np' the argument in the function call .

#line 196 "bison.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 213 "bison.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   266

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      12,    13,    24,    22,    16,    23,    21,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    17,
       2,    20,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    18,     2,    19,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    14,     2,    15,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   121,   122,   124,   135,   124,   146,   146,
     150,   155,   159,   163,   165,   165,   184,   185,   188,   202,
     218,   219,   223,   219,   226,   227,   228,   230,   231,   233,
     234,   234,   236,   236,   245,   247,   252,   258,   277,   280,
     284,   291,   300,   310,   313,   318,   333,   333,   348,   348,
     369,   410,   411,   419,   427,   436,   444,   446,   454,   462,
     464,   465,   466,   467,   468,   471,   472,   473
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_INT", "T_FLOAT", "T_CHAR", "T_STRUCT",
  "T_ERROR", "ID", "V_INT", "V_FLOAT", "V_CHAR", "'('", "')'", "'{'",
  "'}'", "','", "';'", "'['", "']'", "'='", "'.'", "'+'", "'-'", "'*'",
  "'/'", "$accept", "S", "FUNC_DEF", "$@1", "$@2", "PARAM_LIST", "$@3",
  "FUNC_CALL", "$@4", "ARGS_LIST", "ARG_LIST", "STMTS", "$@5", "$@6",
  "DECL_LIST", "DECL", "$@7", "TEMP", "$@8", "SVAR_LIST", "SVAR_CHECK",
  "VAR_LIST", "VAR", "VAR_CHECK", "DIM_LIST", "ASG", "LVALUE", "@9", "@10",
  "LVALUE_CHECK", "ARR_LIST", "EXPR", "TERM", "FACTOR", "TYPE", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    40,    41,   123,   125,    44,    59,    91,    93,
      61,    46,    43,    45,    42,    47
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -15

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      64,   -73,   -73,   -73,   -73,    18,    64,    64,    19,    30,
     -73,   -73,   -73,    41,    33,   -73,    27,    53,    57,    73,
     -73,   -73,   -73,    70,    77,    74,    81,    76,   -73,   -73,
      78,    64,   -73,    87,    89,    85,    73,    80,    91,    47,
     -73,    11,   -73,    73,   -73,    93,   -73,    90,   -73,    83,
      78,    86,    26,   -73,   -73,   -73,   -73,    92,    88,   -73,
     -73,    78,    78,    99,    78,    16,    74,   -73,   -73,   -73,
      78,    94,    34,   -73,    16,    96,    16,    16,    37,   -73,
     -73,   -73,    74,    97,    16,   -73,   -73,   -73,   -73,    52,
     -73,   -73,   100,    98,   -73,   -73,   -73,    52,    95,    14,
      59,   -73,   -73,   101,   102,    95,   -73,    10,   -73,    52,
      52,    52,    52,   103,   100,    16,   -73,    59,    59,   -73,
     -73,   -73,    95,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    65,    66,    67,    30,     0,     4,     4,     0,     0,
       1,     2,     3,    42,     0,    39,     0,     0,    40,     0,
      29,    37,    32,     0,    34,    13,     0,    41,    42,    38,
      51,     0,    31,     0,     0,     0,     0,     0,     0,     0,
      35,     0,    28,     0,    42,     0,     6,     8,    43,     0,
      51,     0,     0,    33,    27,    36,    37,     0,     0,    44,
      46,    51,    51,     0,    51,    26,    13,    50,    52,    53,
      51,    11,    51,    21,    26,     0,    26,    26,     0,     9,
      47,    48,    13,     0,    26,    25,     7,    20,    24,     0,
      50,    12,    17,     0,    61,    62,    63,     0,    64,     0,
      56,    59,    49,     0,    16,    19,    22,     0,    45,     0,
       0,     0,     0,     0,     0,    26,    60,    54,    55,    57,
      58,    15,    18,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,    79,   -73,   -73,   -73,   -53,   -73,   -73,   -73,   -73,
     -73,   -72,   -73,   -73,   -73,     3,   -73,   -73,   -73,   -73,
      56,   -73,    -8,    71,   -73,   -73,   -38,   -73,   -73,    29,
     -22,    20,   -21,   -20,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    17,    57,    35,    58,    74,    83,   103,
     104,    75,    84,   115,    41,    76,     9,    23,    31,    24,
      30,    14,    15,    18,    27,    77,    78,    67,    90,    80,
      60,    99,   100,   101,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       8,    52,    85,     7,    87,    88,     8,     8,    40,     7,
       7,    29,    93,    79,     1,     2,     3,     4,    10,     1,
       2,     3,     4,   116,    72,    36,    53,    13,    47,    91,
      73,   108,   109,   110,    42,    21,   109,   110,    16,    68,
      69,    22,    71,   123,    54,    62,   -14,    63,    81,    19,
      20,    98,    39,    -5,   105,    50,    51,    89,    63,    98,
      50,    94,    95,    96,    97,    25,    36,     1,     2,     3,
       4,    98,    98,    98,    98,    26,   122,     1,     2,     3,
      34,    28,    36,   111,   112,    11,    12,    32,   117,   118,
      37,   119,   120,    33,    38,    44,    39,    45,    46,    48,
      49,    56,    59,   -10,    66,    61,    65,    70,    50,    92,
      82,    86,    64,   106,   113,    55,    63,   107,   114,   102,
     121
};

static const yytype_uint8 yycheck[] =
{
       0,    39,    74,     0,    76,    77,     6,     7,    30,     6,
       7,    19,    84,    66,     3,     4,     5,     6,     0,     3,
       4,     5,     6,    13,     8,    25,    15,     8,    36,    82,
      14,    17,    22,    23,    31,     8,    22,    23,     8,    61,
      62,    14,    64,   115,    41,    19,    12,    21,    70,    16,
      17,    89,    18,    12,    92,     8,     9,    20,    21,    97,
       8,     9,    10,    11,    12,    12,    66,     3,     4,     5,
       6,   109,   110,   111,   112,    18,   114,     3,     4,     5,
       6,     8,    82,    24,    25,     6,     7,    17,   109,   110,
       9,   111,   112,    16,    18,     8,    18,     8,    13,    19,
       9,     8,    19,    13,    16,    19,    14,     8,     8,    12,
      16,    15,    56,    15,    13,    44,    21,    97,    16,    90,
      17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    27,    28,    41,    60,    42,
       0,    27,    27,     8,    47,    48,     8,    29,    49,    16,
      17,     8,    14,    43,    45,    12,    18,    50,     8,    48,
      46,    44,    17,    16,     6,    31,    60,     9,    18,    18,
      56,    40,    41,    60,     8,     8,    13,    48,    19,     9,
       8,     9,    52,    15,    41,    49,     8,    30,    32,    19,
      56,    19,    19,    21,    46,    14,    16,    53,    56,    56,
       8,    56,     8,    14,    33,    37,    41,    51,    52,    31,
      55,    56,    16,    34,    38,    37,    15,    37,    37,    20,
      54,    31,    12,    37,     9,    10,    11,    12,    52,    57,
      58,    59,    55,    35,    36,    52,    15,    57,    17,    22,
      23,    24,    25,    13,    16,    39,    13,    58,    58,    59,
      59,    17,    52,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    27,    27,    27,    29,    30,    28,    32,    31,
      31,    31,    31,    31,    34,    33,    35,    35,    36,    36,
      37,    38,    39,    37,    37,    37,    37,    40,    40,    41,
      42,    41,    44,    43,    43,    45,    45,    46,    47,    47,
      48,    48,    49,    50,    50,    51,    53,    52,    54,    52,
      55,    56,    56,    56,    57,    57,    57,    58,    58,    58,
      59,    59,    59,    59,    59,    60,    60,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     0,     0,    10,     0,     5,
       2,     5,     7,     0,     0,     6,     1,     0,     3,     1,
       2,     0,     0,     6,     2,     2,     0,     2,     1,     3,
       0,     5,     0,     4,     1,     3,     4,     0,     3,     1,
       2,     3,     0,     3,     4,     4,     0,     4,     0,     6,
       0,     0,     4,     4,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 5:
#line 124 "bison.y" /* yacc.c:1646  */
    {
		if(ft_find(ft , (yyvsp[0].i).val) != NULL)
		{
			printf("Function '%s' already defined .\n", (yyvsp[0].i).val) ; // Think of improving this .
			exit(0) ;
		}
		cur_func_ptr = ft_add(ft , (yyvsp[0].i).val , NULL , NULL , (yyvsp[-1].d).type , 0) ;
		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	}
#line 1382 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 135 "bison.y" /* yacc.c:1646  */
    {
		cur_func_ptr -> param_list = st_new() ;
		cur_func_ptr -> param_list -> list = st -> list ;		
		cur_func_ptr -> num_param = (yyvsp[-1].np) ;
	}
#line 1392 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 139 "bison.y" /* yacc.c:1646  */
    { 
		cur_func_ptr -> local_list = st ;
		cur_scope = sstk_pop(sstk) ;
		st = sm_find(sm , cur_scope) ;
		cur_func_ptr = NULL ;
		(yyval.f) = NULL ; }
#line 1403 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 146 "bison.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].d).ptr != NULL)
			(yyvsp[0].d).ptr -> eletype = (yyvsp[-1].d).type ;
	}
#line 1412 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 149 "bison.y" /* yacc.c:1646  */
    { (yyval.np) = 1 +  (yyvsp[0].np) ; }
#line 1418 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 150 "bison.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].d).ptr != NULL)
			(yyvsp[0].d).ptr -> eletype = (yyvsp[-1].d).type ;
		(yyval.np) = 1 ;
	}
#line 1428 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 155 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = 1 ; 
		st_add(st , (yyvsp[-2].i).val , STRUCT_T , (yyvsp[-1].d).type , (yyvsp[0].l) , cur_scope) ;
	}
#line 1437 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 159 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = 1 + (yyvsp[0].np) ; 
		st_add(st , (yyvsp[-4].i).val , STRUCT_T , (yyvsp[-3].d).type , (yyvsp[-2].l) , cur_scope) ;
	}
#line 1446 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 163 "bison.y" /* yacc.c:1646  */
    { (yyval.np) = 0 ; }
#line 1452 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 165 "bison.y" /* yacc.c:1646  */
    { 
		call_func_ptr = ft_find(ft , (yyvsp[0].i).val) ;		
		if(call_func_ptr == NULL)
		{
			printf("Unknown function '%s' on line_no : %d .\n\n", (yyvsp[0].i).val , line_no) ;
		}
	}
#line 1464 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 171 "bison.y" /* yacc.c:1646  */
    { 
		int called_params = (yyvsp[-2].np) ;
		if(call_func_ptr != NULL)
		{
			if(call_func_ptr -> num_param != called_params + 1 )
			{
				printf("Error incorrect number of arguments for function '%s' on line no : %d .\n" , call_func_ptr -> name , line_no) ;
				printf("Expected : %d , but found : %d . \n\n", call_func_ptr -> num_param , called_params + 1) ;
			}
		}
		(yyval.f) = NULL ;
	}
#line 1481 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 184 "bison.y" /* yacc.c:1646  */
    {(yyval.np) = (yyvsp[0].np) ;}
#line 1487 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 185 "bison.y" /* yacc.c:1646  */
    {(yyval.np) = -1 ; // don't change this :p
	 }
#line 1494 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 188 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = (yyvsp[-2].np) + 1 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - (yyval.np)) ;			
			symbol_table_row* found = resolve((yyvsp[0].i).ptr , (yyvsp[0].i).dimlist) ;			
			if(st_compare(expected , found) != 1)
			{
				printf("Incorrect argument %d for function '%s' on line no : %d .\n", (yyval.np) + 1 , call_func_ptr -> name , line_no) ;
				printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
			}
		}
	}
#line 1513 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 202 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = 0 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - (yyval.np)) ;
			symbol_table_row* found = resolve((yyvsp[0].i).ptr , (yyvsp[0].i).dimlist) ;
			if(st_compare(expected , found) != 1)
			{
				printf("Incorrect argument %d for function '%s' on line no : %d .\n", (yyval.np) + 1 , call_func_ptr -> name , line_no) ;
				printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
			}
		}
	}
#line 1532 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 219 "bison.y" /* yacc.c:1646  */
    { sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	}
#line 1542 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 223 "bison.y" /* yacc.c:1646  */
    { cur_scope = sstk_pop(sstk) ; 
		st = sm_find(sm , cur_scope) ;
	}
#line 1550 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 234 "bison.y" /* yacc.c:1646  */
    {cur_dt = T_STRUCT ;}
#line 1556 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 236 "bison.y" /* yacc.c:1646  */
    { 
		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		st = st_new() ;
		}
#line 1566 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 240 "bison.y" /* yacc.c:1646  */
    {
		cur_scope = sstk_pop(sstk) ;
		sdf_add(sdf , (yyvsp[-4].i).val , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ; 
	}
#line 1576 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 247 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-1].d).type ; 
		if((yyval.d).type != -1)
			st_add(st , (yyvsp[-2].i).val , STRUCT_T , (yyvsp[-1].d).type , (yyvsp[0].l) , cur_scope) ;
	}
#line 1586 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 252 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-3].d).type ; 
		if((yyval.d).type != -1)
			st_add(st , (yyvsp[-1].i).val , STRUCT_T , (yyvsp[-3].d).type , NULL , cur_scope) ;
	}
#line 1596 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 258 "bison.y" /* yacc.c:1646  */
    {
		if(st_find_strict(st , (yyvsp[0].i).val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable '%s' in current scope on line no : %d\n\n" , (yyvsp[0].i).val , line_no) ;
			(yyval.d).type = -1 ;
		}
		else
		{
			int ind = sdf_find(sdf , (yyvsp[(-1) - (0)].i).val) ; // This index is from the last !!
			if(ind != -1)
				; // :p
			else
			{
				printf("Unknown type '%s' for variable '%s' on line no : %d\n\n" , (yyvsp[(-1) - (0)].i).val , (yyvsp[0].i).val , line_no) ;
			}
			(yyval.d).type = ind ;
		}
	}
#line 1619 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 277 "bison.y" /* yacc.c:1646  */
    {
		(yyval.d).type = (yyvsp[0].d).type ;
	}
#line 1627 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 280 "bison.y" /* yacc.c:1646  */
    {
		(yyval.d).type = (yyvsp[0].d).type ;
	}
#line 1635 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 284 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-1].i).type ; 
		if((yyvsp[0].d).type != -1)
			(yyval.d).ptr = st_add(st , (yyvsp[-1].i).val , SIMPLE , (yyvsp[-1].i).type , NULL , cur_scope) ;
		else
			(yyval.d).ptr = NULL ;
	}
#line 1647 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 291 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-2].i).type ; 
		if((yyvsp[-1].d).type != -1)
			(yyval.d).ptr = st_add(st , (yyvsp[-2].i).val , ARRAY , (yyvsp[-2].i).type , list_reverse((yyvsp[0].l)) , cur_scope) ;
		else
			(yyval.d).ptr = NULL ;
	}
#line 1659 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 300 "bison.y" /* yacc.c:1646  */
    {
		if(st_find_strict(st , (yyvsp[0].i).val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable '%s' in current scope on line no : %d .\n\n" , (yyvsp[0].i).val , line_no) ;
			(yyval.d).type = -1 ;
		}
		else
			(yyval.d).type = (yyvsp[0].i).type ;
	}
#line 1673 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 310 "bison.y" /* yacc.c:1646  */
    {
		(yyval.l) = list_add(NULL , (yyvsp[-1].c).i_val) ;
	}
#line 1681 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 313 "bison.y" /* yacc.c:1646  */
    {
		(yyval.l) = list_add((yyvsp[-3].l) , (yyvsp[-1].c).i_val) ;
	}
#line 1689 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 318 "bison.y" /* yacc.c:1646  */
    {
		symbol_table_row* resolved = resolve((yyvsp[-3].i).ptr , (yyvsp[-3].i).dimlist) ;		
		if(resolved != NULL && resolved -> type == ARRAY)
		{
			printf("Cannot assign to array '%s' on line no : %d\n\n", (yyvsp[-3].i).val , line_no) ;
		}
		int expr_t = expr_type((yyvsp[-3].i).type , (yyvsp[-1].e).type) ;
		if(expr_t == -1)
		{
			printf("Assignment of incompatible types on line no : %d .\n", line_no) ;
			printf("Assigning '%s' to '%s' \n\n", to_str_eletype((yyvsp[-1].e).type) , datatype_to_string(resolve((yyvsp[-3].i).ptr , (yyvsp[-3].i).dimlist))) ;
		}
		(yyval.c).type = (yyvsp[-3].i).type ; 
	}
#line 1708 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 333 "bison.y" /* yacc.c:1646  */
    { (yyval.i).st = st ; }
#line 1714 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 333 "bison.y" /* yacc.c:1646  */
    {		
		(yyval.i).type = (yyvsp[0].i).type ;
		(yyval.i).ptr = (yyvsp[0].i).ptr ;
		(yyval.i).st = (yyvsp[0].i).st ;
		(yyval.i).val = (yyvsp[0].i).val ;
		(yyval.i).dimlist = (yyvsp[-2].l) ;
		(yyval.i).val = (char*) malloc(30*sizeof(30)) ;
		(yyval.i).val = strcat2((yyval.i).val , (yyvsp[-3].i).val) ;
		list* cur = (yyvsp[-2].l) ;
		while(cur != NULL)
		{
			cur = cur -> next ;
			(yyval.i).val = strcat2((yyval.i).val , "[]") ;
		}	
	}
#line 1734 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 348 "bison.y" /* yacc.c:1646  */
    { (yyval.i).st = (yyvsp[-3].i).st ; }
#line 1740 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 348 "bison.y" /* yacc.c:1646  */
    {		
		(yyval.i).type = (yyvsp[0].i).type ;
		(yyval.i).ptr = (yyvsp[0].i).ptr ;
		(yyval.i).st = (yyvsp[0].i).st ;		
		(yyval.i).val = dupstr((yyvsp[-5].i).val) ;
		(yyval.i).val = strcat2((yyval.i).val , ".") ;
		(yyval.i).val = strcat2((yyval.i).val , (yyvsp[-3].i).val) ;
		list* cur = (yyvsp[-2].l) ;
		while(cur != NULL)
		{
			cur = cur -> next ;
			(yyval.i).val = strcat2((yyval.i).val , "[]") ;
		}
		(yyval.i).dimlist = (yyvsp[-2].l) ;
		if(list_length((yyvsp[-5].i).dimlist) < list_length((yyvsp[-5].i).ptr -> dimlist))
		{
			printf("Cannot de-reference a non-struct type '%s' on line no : %d\n", (yyvsp[-5].i).val , line_no) ;
			(yyval.i).type = -1 ;
		}
	}
#line 1765 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 369 "bison.y" /* yacc.c:1646  */
    {		
		char* val = (yyvsp[(-2) - (0)].i).val ;
		list* cur = (yyvsp[(-1) - (0)].l) ;
		symbol_table* cur_st = (yyvsp[0].i).st ;
		symbol_table_row* res = st_find(cur_st , val , cur_scope) ;
		if(res == NULL)
		{
			(yyval.i).type = -1 ;
			printf("'%s' is not declared in current scope on line no : %d\n\n", val , line_no) ;
		}
		else
		{
			list* dimlist = res -> dimlist ;
			if(list_length(cur) > list_length(dimlist))
			{
				printf("Number of dimensions exceeded for '%s' on line no : %d .\n", val , line_no) ;
				printf("Declared dimensions : %d . Found dimensions : %d\n\n", list_length(dimlist) , list_length(cur)) ;
			}
			while(cur != NULL && dimlist != NULL)
			{
				if(cur -> val != -1)
				{
					if(cur -> val >= dimlist -> val)
					{
						printf("Array index out of bounds for '%s' on line no : %d . \n", val , line_no) ;
						printf("Actual size : %d . Found index : %d\n\n", dimlist -> val , cur -> val) ;
					}
				}
				cur = cur -> next ;
				dimlist = dimlist -> next ;
			}
		}
		(yyval.i).ptr = res ;
		(yyval.i).val = val ;
		(yyval.i).type = res != NULL ? res -> eletype : -1 ;
		if(res != NULL && res -> type == STRUCT_T)
			(yyval.i).st = sdf_find_row(sdf , res -> eletype) -> st ;			
		else
			(yyval.i).st = NULL ;
	}
#line 1810 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 410 "bison.y" /* yacc.c:1646  */
    { (yyval.l) = NULL ; }
#line 1816 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 411 "bison.y" /* yacc.c:1646  */
    { 
		if((yyvsp[-2].c).i_val < 0) 
		{
			printf("Array index out of bounds on line no : %d\n\n", line_no) ;
		}
		else
			(yyval.l) = list_add((yyvsp[0].l) , (yyvsp[-2].c).i_val) ;
	}
#line 1829 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 419 "bison.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].i).ptr == NULL || (yyvsp[-2].i).ptr -> eletype != T_INT)
		{
			printf("Array index '%s' is not an integer on line no : %d\n\n", (yyvsp[-2].i).val , line_no) ;
		}
		(yyval.l) = list_add((yyvsp[0].l) , -1) ;
	}
#line 1841 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 427 "bison.y" /* yacc.c:1646  */
    { 
		int expr_t = expr_type((yyvsp[-2].e).type , (yyvsp[0].e).type) ;
		if(expr_t == -1 || is_struct((yyvsp[-2].e).type))
		{
			printf("Invalid operands for \'+\' on line_no : %d\n", line_no) ;
			exit(0) ;
		}
		(yyval.e).type = expr_t ; 
	}
#line 1855 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 436 "bison.y" /* yacc.c:1646  */
    { 
		int expr_t = expr_type((yyvsp[-2].e).type , (yyvsp[0].e).type) ;
		if(expr_t == -1 || is_struct((yyvsp[-2].e).type))
		{
			printf("Invalid operands for \'-\' on line_no : %d\n\n", line_no) ;
		}
		(yyval.e).type = expr_t ; 
	}
#line 1868 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 444 "bison.y" /* yacc.c:1646  */
    { (yyval.e).type = (yyvsp[0].e).type ; }
#line 1874 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 446 "bison.y" /* yacc.c:1646  */
    { 
		int expr_t = expr_type((yyvsp[-2].e).type , (yyvsp[0].e).type) ;
		if(expr_t == -1 || is_struct((yyvsp[-2].e).type))
		{
			printf("Invalid operands for \'*\' on line_no : %d\n\n", line_no) ;
		}
		(yyval.e).type = expr_t ; 
	}
#line 1887 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 454 "bison.y" /* yacc.c:1646  */
    { 
		int expr_t = expr_type((yyvsp[-2].e).type , (yyvsp[0].e).type) ;
		if(expr_t == -1 || is_struct((yyvsp[-2].e).type))
		{
			printf("Invalid operands for \'/\' on line_no : %d\n\n", line_no) ;
		}
		(yyval.e).type = expr_t ; 
	}
#line 1900 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 462 "bison.y" /* yacc.c:1646  */
    { (yyval.e).type = (yyvsp[0].e).type ; }
#line 1906 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 464 "bison.y" /* yacc.c:1646  */
    { (yyval.e).type = (yyvsp[-1].e).type ; }
#line 1912 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 465 "bison.y" /* yacc.c:1646  */
    { (yyval.e).type = (yyvsp[0].c).type ; }
#line 1918 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 466 "bison.y" /* yacc.c:1646  */
    { (yyval.e).type = (yyvsp[0].c).type ; }
#line 1924 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 467 "bison.y" /* yacc.c:1646  */
    { (yyval.e).type = (yyvsp[0].c).type ; }
#line 1930 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 468 "bison.y" /* yacc.c:1646  */
    {(yyval.e).type = (yyvsp[0].i).type ; }
#line 1936 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 471 "bison.y" /* yacc.c:1646  */
    { (yyval.d).type = T_INT ; cur_dt = T_INT ;}
#line 1942 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 472 "bison.y" /* yacc.c:1646  */
    { (yyval.d).type = T_FLOAT ; cur_dt = T_FLOAT ;}
#line 1948 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 473 "bison.y" /* yacc.c:1646  */
    { (yyval.d).type = T_CHAR ; cur_dt = T_CHAR ;}
#line 1954 "bison.tab.c" /* yacc.c:1646  */
    break;


#line 1958 "bison.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
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
                  yystos[*yyssp], yyvsp);
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
#line 476 "bison.y" /* yacc.c:1906  */


symbol_table_row* resolve(symbol_table_row* str , list* dimlist)
{	
	if(str == NULL)
		return NULL ;
	symbol_table_row* dup = (symbol_table_row*)	 malloc(sizeof(symbol_table_row)) ;
	dup -> type = str -> type ;
	dup -> eletype = str -> eletype ;
	dup -> next = NULL ;
	dup -> dimlist = str -> dimlist ;
	dup -> name = str -> name ;
	if(list_length(dimlist) == list_length(str -> dimlist))
	{
		dup -> dimlist = NULL ;
		if(is_struct(dup -> eletype))
			dup -> type = STRUCT_T ;
		else
			dup -> type = SIMPLE ;
		return dup ;
	}
	while(dimlist != NULL && dup -> dimlist != NULL)
	{
		dimlist = dimlist -> next ;
		dup -> dimlist = dup -> dimlist -> next ;
	}
	return dup ;
}

char* datatype_to_string(symbol_table_row* str)
{	
	if(str == NULL)
		return "(unknown)" ;
	char* res = (char*) malloc(100*sizeof(char)) ;
	memset(res , 0 , 100*sizeof(char)) ;
	if(str -> type == SIMPLE || str -> type == ARRAY)
	{
		if(str -> eletype == T_INT)
			res = strcat2(res , "int") ;
		if(str -> eletype == T_FLOAT)
			res = strcat2(res , "float") ;
		if(str -> eletype == T_CHAR)
			res = strcat2(res , "char") ;
		list* cur = str -> dimlist ;
		while(cur != NULL)
		{
			res = strcat2(res , "[]") ;
			cur = cur -> next ;
		}
	}
	else
	{
		struct_def_row* ret = sdf_find_row(sdf , str -> eletype) ;		
		res = strcat2(res , "struct ") ;
		res = strcat2(res , ret -> name) ;		
		list* cur = str -> dimlist ;
		while(cur != NULL)
		{
			res = strcat2(res , "[]") ;
			cur = cur -> next ;
		}
	}
	return res ;
}
