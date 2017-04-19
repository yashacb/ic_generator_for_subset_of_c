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

#include "mystring.c"
#include "func.c"
#include "ic.c"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

symbol_table_row* resolve(symbol_table_row* str , list* dimlist) ;
char* datatype_to_string(symbol_table_row* str) ;
int expr_type(int t1 , int t2) ;
int is_int(int t) ;
int is_array(int t) ;
int is_struct(int t) ;
int parse_error = 0 ;

func_table* ft = NULL ;
symbol_table* st = NULL ;
struct_def* sdf = NULL ;
scope_stack* sstk = NULL ;
scope_map* sm = NULL ;
inter_code* ic = NULL ;

int ind_dim = 0 ;
int line_no = 1 ;
int cur_scope = 0 ;
int cur_dt = 0 ;
int cur_arr_index = -1 ;
int sdt ;
func_table_row* cur_func_ptr = NULL ; // the functions which is being defiend 
func_table_row* call_func_ptr = NULL ; // the functions which is being called
char* to_str_eletype(int type) ;
symbol_table_row* add_offsets(symbol_table_row* o1 , symbol_table_row* o2) ;
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

typedef struct expr{
	int type ;
	symbol_table_row* temp ;
	int constant ; // is this a constant ?
	char* val ; // if yes , then this is the value .
}expr ;

typedef struct arr_list{
	expr e ;
	struct arr_list* next ;
}arr_list ;

typedef struct id{
	int type ; // this contains the element type and not if it is SMIPLE , ARRAY or STRUCT ! This you need to get from ptr !
	char* val ;
	symbol_table_row* ptr ;
	symbol_table* st ;
	arr_list* arrlist ;
	list* dimlist ; // this is used in lvalue .
	symbol_table_row* offset ;
}id ;

typedef struct constant{
	int type ;
	int i_val ;
	float f_val ;
	char c_val ;
} constant;
//
list* arr_to_list(arr_list* al) ;
symbol_table_row* calculate_offset(arr_list* al , list* dimlist , int size) ;
int sdf_struct_size(struct_def* sdf , int ind) ;
int get_size(int eletype) ;
symbol_table_row* sdf_offset(struct_def* sdf , int eletype , char* name) ;

#line 150 "bison.tab.c" /* yacc.c:339  */

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
#line 84 "bison.y" /* yacc.c:355  */

	char op ;
	decl d ;
	expr e ;
	constant c ;
	id i ;
	list* l ;
	arr_list* al ;
	func_table_row* f ;
	symbol_table_row* a ; // argument list for function calls
	int np ; // no. of parameters . Used by PARAM_LIST . This is also used fot ARG_LIST , but in this 
	// case it respresents the 'np' the argument in the function call .

#line 213 "bison.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 230 "bison.tab.c" /* yacc.c:358  */

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
#define YYLAST   129

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
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
       0,   132,   132,   133,   134,   136,   152,   136,   167,   167,
     171,   176,   180,   184,   186,   186,   216,   217,   220,   238,
     260,   261,   265,   261,   268,   269,   270,   271,   273,   274,
     276,   277,   277,   279,   279,   288,   290,   295,   301,   322,
     325,   329,   336,   345,   356,   359,   363,   415,   415,   443,
     443,   483,   530,   531,   553,   554,   556,   588,   595,   596,
     598,   629,   636,   642,   650,   657,   664,   684,   685,   686
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
  "LVALUE_CHECK", "ARR_LIST", "ASOP", "EXPR", "MDOP", "TERM", "FACTOR",
  "TYPE", YY_NULLPTR
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

#define YYPACT_NINF -78

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define YYTABLE_NINF -15

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      71,   -78,   -78,   -78,   -78,     5,    71,    71,    11,    25,
     -78,   -78,   -78,    23,    52,   -78,    38,    46,    53,    56,
     -78,   -78,   -78,    77,    75,    84,    91,    83,   -78,   -78,
      85,    71,   -78,    94,    96,    93,    56,    86,    98,    74,
     -78,    34,   -78,    56,   -78,   100,   -78,    97,   -78,    90,
      85,   -78,   -78,   -78,    74,    95,     1,    55,   -78,   -78,
     -78,   -78,   -78,    99,   101,   -78,   -78,     8,   103,    85,
     -78,   -78,    74,   -78,   -78,    74,    85,    51,    84,   -78,
     -78,    85,   -78,    55,   -78,   102,    24,   -78,    51,   104,
      51,    51,    72,    28,   -78,   -78,   -78,    84,   108,    51,
     -78,   -78,   -78,   -78,    74,    51,   -78,   -78,    74,   106,
      50,   -78,   -78,   109,   107,    73,   -78,   -78,   110,    74,
      51,   -78,    73,   -78
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    67,    68,    69,    31,     0,     4,     4,     0,     0,
       1,     2,     3,    43,     0,    40,     0,     0,    41,     0,
      30,    38,    33,     0,    35,    13,     0,    42,    43,    39,
      52,     0,    32,     0,     0,     0,     0,     0,     0,     0,
      36,     0,    29,     0,    43,     0,     6,     8,    44,     0,
      52,    63,    64,    65,     0,    66,     0,    57,    61,    34,
      28,    37,    38,     0,     0,    45,    47,     0,     0,    52,
      54,    55,     0,    58,    59,     0,    52,    27,    13,    51,
      62,    52,    53,    56,    60,    11,    52,    21,    27,     0,
      27,    27,    66,     0,     9,    48,    49,    13,     0,    27,
      25,     7,    20,    24,     0,    27,    51,    12,    17,     0,
       0,    26,    50,     0,    16,    19,    22,    46,     0,     0,
      27,    15,    18,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,    92,   -78,   -78,   -78,   -70,   -78,   -78,   -78,   -78,
     -78,   -77,   -78,   -78,   -78,     3,   -78,   -78,   -78,   -78,
      62,   -78,    -7,    68,   -78,   -78,   -73,   -78,   -78,     9,
     -28,   -78,   -38,   -78,    42,    54,     0
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    17,    63,    35,    64,    88,    98,   113,
     114,    89,    99,   120,    41,    90,     9,    23,    31,    24,
      30,    14,    15,    18,    27,    91,    55,    79,   106,    95,
      66,    72,    93,    75,    57,    58,    43
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       8,    56,    40,     7,    92,    10,     8,     8,    94,     7,
       7,   100,    29,   102,   103,    92,    67,    92,    92,    13,
      69,    80,   109,    70,    71,    36,    92,   107,   111,    47,
      70,    71,    92,    16,    42,    -5,   -14,     1,     2,     3,
       4,    82,    39,   123,    60,   105,    21,    92,    85,    59,
      70,    71,    22,    96,     1,     2,     3,     4,    25,    86,
      51,    52,    53,    54,    28,    87,   110,   117,    19,    20,
     115,    26,    70,    71,     1,     2,     3,     4,    36,    73,
      74,   122,    50,    51,    52,    53,    54,     1,     2,     3,
      34,    33,   104,    68,    32,    70,    71,    36,    11,    12,
      37,    38,    44,    39,    45,    48,    46,    49,    62,    65,
     -10,    81,    61,    77,    83,   112,    68,    78,    97,   101,
     108,   116,   118,   119,    76,     0,     0,   121,     0,    84
};

static const yytype_int8 yycheck[] =
{
       0,    39,    30,     0,    77,     0,     6,     7,    78,     6,
       7,    88,    19,    90,    91,    88,    54,    90,    91,     8,
      19,    13,    99,    22,    23,    25,    99,    97,   105,    36,
      22,    23,   105,     8,    31,    12,    12,     3,     4,     5,
       6,    69,    18,   120,    41,    17,     8,   120,    76,    15,
      22,    23,    14,    81,     3,     4,     5,     6,    12,     8,
       9,    10,    11,    12,     8,    14,   104,    17,    16,    17,
     108,    18,    22,    23,     3,     4,     5,     6,    78,    24,
      25,   119,     8,     9,    10,    11,    12,     3,     4,     5,
       6,    16,    20,    21,    17,    22,    23,    97,     6,     7,
       9,    18,     8,    18,     8,    19,    13,     9,     8,    19,
      13,     8,    44,    14,    72,   106,    21,    16,    16,    15,
      12,    15,    13,    16,    62,    -1,    -1,    17,    -1,    75
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,    27,    28,    41,    62,    42,
       0,    27,    27,     8,    47,    48,     8,    29,    49,    16,
      17,     8,    14,    43,    45,    12,    18,    50,     8,    48,
      46,    44,    17,    16,     6,    31,    62,     9,    18,    18,
      56,    40,    41,    62,     8,     8,    13,    48,    19,     9,
       8,     9,    10,    11,    12,    52,    58,    60,    61,    15,
      41,    49,     8,    30,    32,    19,    56,    58,    21,    19,
      22,    23,    57,    24,    25,    59,    46,    14,    16,    53,
      13,     8,    56,    60,    61,    56,     8,    14,    33,    37,
      41,    51,    52,    58,    31,    55,    56,    16,    34,    38,
      37,    15,    37,    37,    20,    17,    54,    31,    12,    37,
      58,    37,    55,    35,    36,    58,    15,    17,    13,    16,
      39,    17,    58,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    26,    27,    27,    27,    29,    30,    28,    32,    31,
      31,    31,    31,    31,    34,    33,    35,    35,    36,    36,
      37,    38,    39,    37,    37,    37,    37,    37,    40,    40,
      41,    42,    41,    44,    43,    43,    45,    45,    46,    47,
      47,    48,    48,    49,    50,    50,    51,    53,    52,    54,
      52,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    62,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     0,     0,    10,     0,     5,
       2,     5,     7,     0,     0,     6,     1,     0,     3,     1,
       2,     0,     0,     6,     2,     2,     3,     0,     2,     1,
       3,     0,     5,     0,     4,     1,     3,     4,     0,     3,
       1,     2,     3,     0,     3,     4,     4,     0,     4,     0,
       6,     0,     0,     4,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1
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
#line 136 "bison.y" /* yacc.c:1646  */
    {
		if(ft_find(ft , (yyvsp[0].i).val) != NULL)
		{
			printf("Function '%s' already defined .\n", (yyvsp[0].i).val) ; // Think of improving this .
			exit(0) ;
		}
		cur_func_ptr = ft_add(ft , (yyvsp[0].i).val , NULL , NULL , (yyvsp[-1].d).type , 0) ;

		char code[100] ;
		sprintf(code , "function begin %s" , (yyvsp[0].i).val) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;

		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	}
#line 1405 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 152 "bison.y" /* yacc.c:1646  */
    {
		cur_func_ptr -> param_list = st_new() ;
		cur_func_ptr -> param_list -> list = st -> list ;		
		cur_func_ptr -> num_param = (yyvsp[-1].np) ;
	}
#line 1415 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 156 "bison.y" /* yacc.c:1646  */
    { 
		char code[100] ;
		sprintf(code , "func end") ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;

		cur_func_ptr -> local_list = st ;
		cur_scope = sstk_pop(sstk) ;
		st = sm_find(sm , cur_scope) ;
		cur_func_ptr = NULL ;
		(yyval.f) = NULL ; }
#line 1430 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 167 "bison.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].d).ptr != NULL)
			(yyvsp[0].d).ptr -> eletype = (yyvsp[-1].d).type ;
	}
#line 1439 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 170 "bison.y" /* yacc.c:1646  */
    { (yyval.np) = 1 +  (yyvsp[0].np) ; }
#line 1445 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 171 "bison.y" /* yacc.c:1646  */
    {
		if((yyvsp[0].d).ptr != NULL)
			(yyvsp[0].d).ptr -> eletype = (yyvsp[-1].d).type ;
		(yyval.np) = 1 ;
	}
#line 1455 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 176 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = 1 ; 
		st_add(st , (yyvsp[-2].i).val , STRUCT_T , (yyvsp[-1].d).type , arr_to_list((yyvsp[0].al)) , cur_scope) ;
	}
#line 1464 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 180 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = 1 + (yyvsp[0].np) ; 
		st_add(st , (yyvsp[-4].i).val , STRUCT_T , (yyvsp[-3].d).type , arr_to_list((yyvsp[-2].al)) , cur_scope) ;
	}
#line 1473 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 184 "bison.y" /* yacc.c:1646  */
    { (yyval.np) = 0 ; }
#line 1479 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 186 "bison.y" /* yacc.c:1646  */
    { 
		call_func_ptr = ft_find(ft , (yyvsp[0].i).val) ;		
		if(call_func_ptr == NULL)
		{
			printf("Unknown function '%s' on line_no : %d .\n\n", (yyvsp[0].i).val , line_no) ;
			parse_error = 1 ;
		}
	}
#line 1492 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 193 "bison.y" /* yacc.c:1646  */
    { 
		int called_params = (yyvsp[-2].np) ;
		if(call_func_ptr != NULL)
		{
			if(call_func_ptr -> num_param != called_params + 1 )
			{
				printf("Error incorrect number of arguments for function '%s' on line no : %d .\n" , call_func_ptr -> name , line_no) ;
				printf("Expected : %d , but found : %d . \n\n", call_func_ptr -> num_param , called_params + 1) ;
				parse_error = 1 ;
			}
			else
			{
				char code[100] ;
				symbol_table_row* ret_temp = st_new_temp(st , call_func_ptr -> res_type , cur_scope) ;
				sprintf(code , "refparam %s" , ret_temp -> name) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
				sprintf(code , "call %s %d" , call_func_ptr -> name , call_func_ptr -> num_param) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
			}
		}
		(yyval.f) = NULL ;
	}
#line 1519 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 216 "bison.y" /* yacc.c:1646  */
    {(yyval.np) = (yyvsp[0].np) ;}
#line 1525 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 217 "bison.y" /* yacc.c:1646  */
    {(yyval.np) = -1 ; // don't change this :p
	 }
#line 1532 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 220 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = (yyvsp[-2].np) + 1 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - (yyval.np)) ;			
			symbol_table_row* found = (yyvsp[0].e).temp ;		
			if(st_compare(expected , found) != 1)
			{
				printf("Incorrect argument %d for function '%s' on line no : %d .\n", (yyval.np) + 1 , call_func_ptr -> name , line_no) ;
				printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
				parse_error = 1 ;
			}
			char code[100] ;
			sprintf(code , "param %s" , (yyvsp[0].e).temp -> name) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
	}
#line 1555 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 238 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.np) = 0 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - (yyval.np)) ;
			symbol_table_row* found = (yyvsp[0].e).temp ;			
			if(st_compare(expected , found) != 1)
			{
				printf("Incorrect argument %d for function '%s' on line no : %d .\n", (yyval.np) + 1 , call_func_ptr -> name , line_no) ;
				printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
				parse_error = 1 ;
			}
			else
			{
				char code[100] ;
				sprintf(code , "param %s" , (yyvsp[0].e).temp -> name) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
			}
		}
	}
#line 1581 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 261 "bison.y" /* yacc.c:1646  */
    { sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	}
#line 1591 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 265 "bison.y" /* yacc.c:1646  */
    { cur_scope = sstk_pop(sstk) ; 
		st = sm_find(sm , cur_scope) ;
	}
#line 1599 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 277 "bison.y" /* yacc.c:1646  */
    {cur_dt = T_STRUCT ;}
#line 1605 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 279 "bison.y" /* yacc.c:1646  */
    { 
		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		st = st_new() ;
		}
#line 1615 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 283 "bison.y" /* yacc.c:1646  */
    {
		cur_scope = sstk_pop(sstk) ;
		sdf_add(sdf , (yyvsp[-4].i).val , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ; 
	}
#line 1625 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 290 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-1].d).type ; 
		if((yyval.d).type != -1)
			st_add(st , (yyvsp[-2].i).val , STRUCT_T , (yyvsp[-1].d).type , arr_to_list((yyvsp[0].al)) , cur_scope) ;
	}
#line 1635 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 295 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-3].d).type ; 
		if((yyval.d).type != -1)
			st_add(st , (yyvsp[-1].i).val , STRUCT_T , (yyvsp[-3].d).type , NULL , cur_scope) ;
	}
#line 1645 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 301 "bison.y" /* yacc.c:1646  */
    {
		if(st_find_strict(st , (yyvsp[0].i).val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable '%s' in current scope on line no : %d\n\n" , (yyvsp[0].i).val , line_no) ;
			parse_error = 1 ;
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
				parse_error = 1 ;
			}
			(yyval.d).type = ind ; // this is eletype !
		}
	}
#line 1670 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 322 "bison.y" /* yacc.c:1646  */
    {
		(yyval.d).type = (yyvsp[0].d).type ;
	}
#line 1678 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 325 "bison.y" /* yacc.c:1646  */
    {
		(yyval.d).type = (yyvsp[0].d).type ;
	}
#line 1686 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 329 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-1].i).type ; 
		if((yyvsp[0].d).type != -1)
			(yyval.d).ptr = st_add(st , (yyvsp[-1].i).val , SIMPLE , (yyvsp[-1].i).type , NULL , cur_scope) ;
		else
			(yyval.d).ptr = NULL ;
	}
#line 1698 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 336 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.d).type = (yyvsp[-2].i).type ; 
		if((yyvsp[-1].d).type != -1)
			(yyval.d).ptr = st_add(st , (yyvsp[-2].i).val , ARRAY , (yyvsp[-2].i).type , list_reverse((yyvsp[0].l)) , cur_scope) ;
		else
			(yyval.d).ptr = NULL ;
	}
#line 1710 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 345 "bison.y" /* yacc.c:1646  */
    {
		if(st_find_strict(st , (yyvsp[0].i).val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable '%s' in current scope on line no : %d .\n\n" , (yyvsp[0].i).val , line_no) ;
			parse_error = 1 ;
			(yyval.d).type = -1 ;
		}
		else
			(yyval.d).type = (yyvsp[0].i).type ;
	}
#line 1725 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 356 "bison.y" /* yacc.c:1646  */
    {
		(yyval.l) = list_add(NULL , (yyvsp[-1].c).i_val) ;
	}
#line 1733 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 359 "bison.y" /* yacc.c:1646  */
    {
		(yyval.l) = list_add((yyvsp[-3].l) , (yyvsp[-1].c).i_val) ;
	}
#line 1741 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 363 "bison.y" /* yacc.c:1646  */
    {
		symbol_table_row* resolved = resolve((yyvsp[-3].i).ptr , (yyvsp[-3].i).dimlist) ;	
		if(resolved != NULL && resolved -> type == ARRAY)
		{
			printf("Cannot assign to array '%s' on line no : %d\n\n", (yyvsp[-3].i).val , line_no) ;
			parse_error = 1 ;
		}
		if((yyvsp[-1].e).temp != NULL && (yyvsp[-1].e).temp -> type == ARRAY)
		{
			printf("Cannot assign an array to lvalue on line no : %d\n\n", line_no) ;
			parse_error = 1 ;	
		}
		char* lname = get_first((yyvsp[-3].i).val) ;
		int expr_t = expr_type((yyvsp[-3].i).type , (yyvsp[-1].e).type) ; // cmopares eletypes !
		if(expr_t == -1)
		{
			if((yyvsp[-3].i).type == -1)
			{
				printf("Unknown type for '%s' on line no : %d .\n\n", (yyvsp[-3].i).val , line_no) ;
			}
			else
			{
				printf("Assignment of incompatible types on line no : %d .\n", line_no) ;
				printf("Assigning '%s' to '%s' \n\n", to_str_eletype((yyvsp[-1].e).type) , datatype_to_string(resolve((yyvsp[-3].i).ptr , (yyvsp[-3].i).dimlist))) ;
				parse_error = 1 ;
			}
		}
		else
		{
			if((yyvsp[-3].i).ptr != NULL && parse_error == 0)
			{
				char code[100] ;
				if((yyvsp[-3].i).offset != NULL)
				{
					if((yyvsp[-1].e).constant == 0)
						sprintf(code , "%s[%s] = %s" , lname , (yyvsp[-3].i).offset -> name , (yyvsp[-1].e).temp -> name) ;
					else
						sprintf(code , "%s[%s] = %s" , lname , (yyvsp[-3].i).offset -> name , (yyvsp[-1].e).val) ;
				}
				else
				{
					if((yyvsp[-1].e).constant == 0)
						sprintf(code , "%s = %s" , lname , (yyvsp[-1].e).temp -> name) ;
					else
						sprintf(code , "%s = %s" , lname , (yyvsp[-1].e).val) ;
				}
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
			}
		}		
		(yyval.c).type = (yyvsp[-3].i).type ;
	}
#line 1797 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 415 "bison.y" /* yacc.c:1646  */
    { (yyval.i).st = st ; }
#line 1803 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 415 "bison.y" /* yacc.c:1646  */
    {		
		(yyval.i).type = (yyvsp[0].i).type ;
		(yyval.i).ptr = (yyvsp[0].i).ptr ;
		(yyval.i).st = (yyvsp[0].i).st ;
		(yyval.i).val = (yyvsp[0].i).val ;
		(yyval.i).dimlist = arr_to_list((yyvsp[-2].al)) ;
		(yyval.i).arrlist = (yyvsp[-2].al) ;
		(yyval.i).offset = NULL ;

		if((yyval.i).ptr != NULL)
		{
			symbol_table_row* offset = calculate_offset((yyval.i).arrlist , (yyval.i).ptr -> dimlist , get_size((yyval.i).ptr -> eletype)) ;			
		
			(yyval.i).offset = offset ;
			(yyval.i).val = (char*) malloc(30*sizeof(30)) ;
			(yyval.i).val = strcat2((yyval.i).val , (yyvsp[-3].i).val) ;
			list* cur = arr_to_list((yyvsp[-2].al)) ;
			while(cur != NULL)
			{
				cur = cur -> next ;
				(yyval.i).val = strcat2((yyval.i).val , "[]") ;
			}
		}
		else
		{
			printf("'%s' is not declared in current scope on line no : %d. \n\n", (yyvsp[-3].i).val , line_no) ;
		}
	}
#line 1836 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 443 "bison.y" /* yacc.c:1646  */
    { (yyval.i).st = (yyvsp[-3].i).st ; }
#line 1842 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 443 "bison.y" /* yacc.c:1646  */
    {
		(yyval.i).type = (yyvsp[0].i).type ;
		(yyval.i).ptr = (yyvsp[0].i).ptr ;
		(yyval.i).st = (yyvsp[0].i).st ;
		(yyval.i).val = dupstr((yyvsp[-5].i).val) ;
		(yyval.i).val = strcat2((yyval.i).val , ".") ;
		(yyval.i).val = strcat2((yyval.i).val , (yyvsp[-3].i).val) ;
		list* cur = arr_to_list((yyvsp[-2].al)) ;
		while(cur != NULL)
		{
			cur = cur -> next ;
			(yyval.i).val = strcat2((yyval.i).val , "[]") ;
		}
		(yyval.i).dimlist = arr_to_list((yyvsp[-2].al)) ;
		(yyval.i).arrlist = (yyvsp[-2].al) ;
		if((yyval.i).ptr != NULL)
		{
			symbol_table_row* right = calculate_offset((yyval.i).arrlist , (yyval.i).ptr -> dimlist , get_size((yyval.i).ptr -> eletype)) ;
			symbol_table_row* struct_offset = sdf_offset(sdf , (yyvsp[-5].i).ptr -> eletype , (yyvsp[-3].i).val) ;

			symbol_table_row* offset = (yyvsp[-5].i).offset ;
			offset = add_offsets(offset , struct_offset) ;
			offset = add_offsets(offset , right) ;

			(yyval.i).offset = offset ;			
		}
		else
		{
			if((yyvsp[-5].i).ptr != NULL && (yyvsp[-5].i).ptr -> type == STRUCT_T)
				printf("'%s' not declared in scope of '%s' on line no : %d\n\n", (yyvsp[-3].i).val , (yyvsp[-5].i).val , line_no) ;
		}

		if((yyvsp[-5].i).ptr == NULL || list_length((yyvsp[-5].i).dimlist) < list_length((yyvsp[-5].i).ptr -> dimlist) || (yyvsp[-5].i).ptr -> type != STRUCT_T)
		{
			printf("Cannot de-reference a non-struct type '%s' on line no : %d\n\n", (yyvsp[-5].i).val , line_no) ;
			parse_error = 1 ;
			(yyval.i).type = -1 ;
		}
	}
#line 1886 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 483 "bison.y" /* yacc.c:1646  */
    {	
		char* val = (yyvsp[(-2) - (0)].i).val ;
		list* cur = arr_to_list((yyvsp[(-1) - (0)].al)) ;
		symbol_table* cur_st = (yyvsp[0].i).st ;
		symbol_table_row* res = st_find(cur_st , val , cur_scope) ;
		if(res == NULL)
		{
			(yyval.i).type = -1 ;
			parse_error = 1 ;
		}
		else
		{
			list* dimlist = res -> dimlist ;
			if(list_length(cur) > list_length(dimlist))
			{
				printf("Number of dimensions exceeded for '%s' on line no : %d .\n", val , line_no) ;
				printf("Declared dimensions : %d . Found dimensions : %d\n\n", list_length(dimlist) , list_length(cur)) ;
				parse_error = 1 ;
			}
			int ind = 0 ;
			while(cur != NULL && dimlist != NULL)
			{
				if(cur -> val != -1)
				{
					if(cur -> val >= dimlist -> val)
					{
						printf("Array index %d out of bounds for '%s' on line no : %d . \n", ind , val , line_no) ;
						printf("Actual size : %d . Found index : %d\n\n", dimlist -> val , cur -> val) ;
						parse_error = 1 ;
					}
				}
				ind ++ ;
				cur = cur -> next ;
				dimlist = dimlist -> next ;
			}
		}
		(yyval.i).ptr = res ;
		(yyval.i).val = val ;
		(yyval.i).type = res != NULL ? res -> eletype : -1 ;
		if(res != NULL && res -> type == STRUCT_T)
		{
			(yyval.i).st = sdf_find_row(sdf , res -> eletype) == NULL ? NULL : sdf_find_row(sdf , res -> eletype) -> st ;
		}
		else
			(yyval.i).st = NULL ;
	}
#line 1937 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 530 "bison.y" /* yacc.c:1646  */
    { (yyval.al) = NULL ; cur_arr_index = 0 ;}
#line 1943 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 531 "bison.y" /* yacc.c:1646  */
    {
		if((yyvsp[-2].e).constant != 0 && (yyvsp[-2].e).constant != V_INT)
		{
			printf("Array index no. %d (from last) is not an integer on line no : %d\n\n", cur_arr_index , line_no) ;
			parse_error = 1 ;
		}
		else if((yyvsp[-2].e).temp != NULL && (yyvsp[-2].e).temp -> eletype != T_INT)
		{
			printf("Array index %d (from last) is not an integer on line no : %d\n\n", cur_arr_index , line_no) ;	
			parse_error = 1 ;
		}
		(yyval.al) = (arr_list*) malloc(sizeof(arr_list)) ;
		(yyval.al) -> next = (yyvsp[0].al) ;
		(yyval.al) -> e.type = (yyvsp[-2].e).type ;
		(yyval.al) -> e.temp = (yyvsp[-2].e).temp ;
		(yyval.al) -> e.constant = (yyvsp[-2].e).constant ;
		(yyval.al) -> e.val = (yyvsp[-2].e).val ;
		(yyval.al) -> next = (yyvsp[0].al) ;
		cur_arr_index ++ ;
	}
#line 1968 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 553 "bison.y" /* yacc.c:1646  */
    { (yyval.op) = '+' ; }
#line 1974 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 554 "bison.y" /* yacc.c:1646  */
    { (yyval.op) = '-' ; }
#line 1980 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 556 "bison.y" /* yacc.c:1646  */
    { 
		int expr_t = expr_type((yyvsp[-2].e).type , (yyvsp[0].e).type) ;
		if(expr_t == -1 || is_struct((yyvsp[-2].e).type))
		{
			printf("Invalid operands for \'+\' on line_no : %d\n", line_no) ;
			parse_error = 1 ;
		}

		else if((yyvsp[-2].e).temp -> type == ARRAY || (yyvsp[0].e).temp -> type == ARRAY)
		{
			printf("Arrays cannot be used as operands for '%c' on line no : %d .\n\n", (yyvsp[-1].op) , line_no) ;
			parse_error = 1 ;
		}
		else
		{
			(yyval.e).temp =  st_new_temp(st , expr_t , cur_scope) ;
			char left[100] ;
			if((yyvsp[-2].e).constant != 0)
				sprintf(left , "%s" , (yyvsp[-2].e).val) ;
			else
				sprintf(left , "%s" , (yyvsp[-2].e).temp -> name) ;
			char right[100] ;
			if((yyvsp[0].e).constant != 0)
				sprintf(right , "%s" , (yyvsp[0].e).val) ;
			else
				sprintf(right , "%s" , (yyvsp[0].e).temp -> name) ;
			char code[100] ;
			sprintf(code , "%s = %s %c %s" , (yyval.e).temp -> name , left , (yyvsp[-1].op) , right) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		(yyval.e).type = expr_t ; 
	}
#line 2017 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 588 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.e).type = (yyvsp[0].e).type ; 
		(yyval.e).temp = (yyvsp[0].e).temp ;
		(yyval.e).constant = (yyvsp[0].e).constant ;
		(yyval.e).val = (yyvsp[0].e).val ;
	}
#line 2028 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 595 "bison.y" /* yacc.c:1646  */
    { (yyval.op) = '*' ; }
#line 2034 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 596 "bison.y" /* yacc.c:1646  */
    { (yyval.op) = '/' ; }
#line 2040 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 598 "bison.y" /* yacc.c:1646  */
    { 
		int expr_t = expr_type((yyvsp[-2].e).type , (yyvsp[0].e).type) ;
		if(expr_t == -1 || is_struct((yyvsp[-2].e).type))
		{
			printf("Invalid operands for \'*\' on line_no : %d\n\n", line_no) ;
			parse_error = 1 ;
		}
		else if((yyvsp[-2].e).temp -> type == ARRAY || (yyvsp[0].e).temp -> type == ARRAY)
		{
			printf("Arrays cannot be used as operands for '%c' on line no : %d .\n\n", (yyvsp[-1].op) , line_no) ;
			parse_error ;
		}
		else
		{
			(yyval.e).temp =  st_new_temp(st , expr_t , cur_scope) ;
			char left[100] ;
			if((yyvsp[-2].e).constant != 0)
				sprintf(left , "%s" , (yyvsp[-2].e).val) ;
			else
				sprintf(left , "%s" , (yyvsp[-2].e).temp -> name) ;
			char right[100] ;
			if((yyvsp[0].e).constant != 0)
				sprintf(right , "%s" , (yyvsp[0].e).val) ;
			else
				sprintf(right , "%s" , (yyvsp[0].e).temp -> name) ;
			char code[100] ;
			sprintf(code , "%s = %s %c %s" , (yyval.e).temp -> name , left , (yyvsp[-1].op) , right) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		(yyval.e).type = expr_t ;
	}
#line 2076 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 629 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.e).type = (yyvsp[0].e).type ; 
		(yyval.e).temp = (yyvsp[0].e).temp ;
		(yyval.e).constant = (yyvsp[0].e).constant ;
		(yyval.e).val = (yyvsp[0].e).val ;
	}
#line 2087 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 636 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.e).type = (yyvsp[-1].e).type ; 
		(yyval.e).temp = (yyvsp[-1].e).temp ; 
		(yyval.e).constant = (yyvsp[-1].e).constant ;
		(yyval.e).val = (yyvsp[-1].e).val ;
	}
#line 2098 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 642 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.e).type = (yyvsp[0].c).type ; 
		(yyval.e).temp = NULL ;
		(yyval.e).constant = V_INT ;
		char* val = (char*) malloc(21*sizeof(char)) ;
		sprintf(val , "%d" , (yyvsp[0].c).i_val) ;
		(yyval.e).val = val ;
	}
#line 2111 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 650 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.e).constant = V_FLOAT ;
		(yyval.e).type = (yyvsp[0].c).type ; 
		char* val = (char*) malloc(21*sizeof(char)) ;
		sprintf(val , "%f" , (yyvsp[0].c).f_val) ;
		(yyval.e).val = val ;
	}
#line 2123 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 657 "bison.y" /* yacc.c:1646  */
    { 
		(yyval.e).constant = V_CHAR ;
		(yyval.e).type = (yyvsp[0].c).type ; 
		char* val = (char*) malloc(2*sizeof(char)) ;
		sprintf(val , "%c" , (yyvsp[0].c).c_val) ;
		(yyval.e).val = val ;
	}
#line 2135 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 664 "bison.y" /* yacc.c:1646  */
    {
		(yyval.e).type = (yyvsp[0].i).type ; 
		(yyval.e).temp = (yyvsp[0].i).ptr ;
		(yyval.e).constant = 0 ;
		(yyval.e).val = (yyvsp[0].i).val ;

		if((yyvsp[0].i).ptr != NULL)
		{
			symbol_table_row* resolved = resolve((yyvsp[0].i).ptr , (yyvsp[0].i).dimlist) ;
			if((yyvsp[0].i).offset != NULL)
			{
				symbol_table_row* temp = st_new_temp_from_row(st , resolved , cur_scope) ;
				char code[100] ;		
				sprintf(code , "%s = %s[%s]" , temp -> name , get_first((yyvsp[0].i).val) , (yyvsp[0].i).offset -> name) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
				(yyval.e).temp = temp ;
			}
		}
	}
#line 2159 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 684 "bison.y" /* yacc.c:1646  */
    { (yyval.d).type = T_INT ; cur_dt = T_INT ;}
#line 2165 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 685 "bison.y" /* yacc.c:1646  */
    { (yyval.d).type = T_FLOAT ; cur_dt = T_FLOAT ;}
#line 2171 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 686 "bison.y" /* yacc.c:1646  */
    { (yyval.d).type = T_CHAR ; cur_dt = T_CHAR ;}
#line 2177 "bison.tab.c" /* yacc.c:1646  */
    break;


#line 2181 "bison.tab.c" /* yacc.c:1646  */
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
#line 688 "bison.y" /* yacc.c:1906  */

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

int arr_length(arr_list* al)
{
	int len = 0 ;
	while(al != NULL)
	{
		len++ ;
		al = al -> next ;
	}
	return len ;
}

int arr_get_int(arr_list* al)
{
	if(al -> e.constant == 0)
		return -1 ;
	return atoi(al -> e.val) ;
}

list* arr_to_list(arr_list* al)
{
	list* ret = NULL ;
	while(al != NULL)
	{		
		ret = list_add(ret , arr_get_int(al)) ;
		al = al -> next ;
	}
	return list_reverse(ret) ;
}

symbol_table_row* sdf_offset(struct_def* sdf , int eletype , char* name) // offset of element eletype within the structure . (reverse from actual order)
{
	struct_def_row* sdfr = sdf_find_row(sdf , eletype) ;
	if(sdfr == NULL)
		return NULL ;
	symbol_table_row* cur = sdfr -> st -> list ;
	symbol_table_row* offset = NULL ;
	while(cur != NULL)
	{
		if(strcmp(cur -> name , name) == 0)
		{
			return offset ;
		}
		int size = get_size(cur -> eletype) ;
		if(cur -> dimlist != NULL)
		{
			int ttt = 1 ;
			list* d = cur -> dimlist ;
			while(d != NULL)
			{
				ttt *= d -> val ;
				d = d -> next ;
			}
			size = size * ttt ;
		}
		if(offset == NULL)
		{
			offset = st_new_temp(st , T_INT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %d" , offset -> name , size) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		else
		{
			symbol_table_row* temp = st_new_temp(st , T_INT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %s + %d" , temp -> name , offset -> name , size) ;
			offset = temp ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		cur = cur -> next ;
	}
	return NULL ;
}

int sdf_struct_size(struct_def* sdf , int ind)
{
	struct_def_row* sdfr = sdf_find_row(sdf , ind) ;
	if(sdfr == NULL)
		return 0 ;
	symbol_table_row* cur = sdfr -> st -> list ;
	int size = 0 ;
	while(cur != NULL)
	{
		int cur_size = 0 ;
		if(cur -> eletype == T_INT)
			cur_size = 4 ;
		else if(cur -> eletype == T_FLOAT)
			cur_size = 8 ;
		else if(cur -> eletype == T_CHAR)
			cur_size = 2 ;
		else
			cur_size = sdf_struct_size(sdf , cur -> eletype) ;
		if(cur -> dimlist != NULL)
		{
			int arr_size = 1 ;
			list* dims = cur -> dimlist ;
			while(dims != NULL)
			{
				arr_size = arr_size*dims -> val ;
				dims = dims -> next ;
			}
			cur_size = cur_size*arr_size ;
		}
		size += cur_size ;
		cur = cur -> next ;
	}
	return size ;
}

symbol_table_row* add_offsets(symbol_table_row* o1 , symbol_table_row* o2)
{
	if(o1 == NULL && o2 == NULL)
		return NULL ;
	else if(o1 != NULL && o2 != NULL)
	{
		symbol_table_row* res = st_new_temp(st , T_INT , cur_scope) ;
		char code[100] ;
		sprintf(code , "%s = %s + %s" , res -> name , o1 -> name , o2 -> name) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		return res ;
	}
	else if(o1 != NULL)
		return o1 ;
	return o2 ;
}

symbol_table_row* calculate_offset(arr_list* al , list* dimlist , int size) // dimlist is the dimension list of the declaration !
{	
	if(arr_length(al) > list_length(dimlist))
		return NULL ;
	if(dimlist == NULL || al == NULL)
		return NULL ;
	dimlist = dimlist -> next ;
	arr_list* i1 = al ;
	arr_list* i2 = al -> next ;	
	symbol_table_row* res = NULL ;
	while(i2 != NULL && dimlist != NULL)
	{
		symbol_table_row* t1 = st_new_temp(st , T_INT , cur_scope) ;
		char code[100] ;
		if(i1 -> e.constant == 0 )
			sprintf(code , "%s = %s * %d" , t1 -> name , i1 -> e.temp -> name , dimlist -> val) ; // t1 = i1*n2
		else
			sprintf(code , "%s = %s * %d" , t1 -> name , i1 -> e.val , dimlist -> val) ; // t1 = i1*n2
		ic = ic_add(ic , NOT_GOTO , code , -1) ;

		symbol_table_row* t2 = st_new_temp(st , T_INT , cur_scope) ;
		if(i2 -> e.constant == 0 )
			sprintf(code , "%s = %s + %s" , t2 -> name , t1 -> name , i2-> e.temp -> name) ; // t2 = t1 + i2
		else		
			sprintf(code , "%s = %s + %s" , t2 -> name , t1 -> name ,  i2 -> e.val) ; // t2 = t1 + i2
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		res = t2 ;

		arr_list* next = (arr_list*) malloc(sizeof(arr_list)) ;
		next -> e.temp = t2 ;
		next -> e.constant = 0 ;
		next -> e.val = "" ;
		next -> next = NULL ;

		i1 = next ;
		i2 = i2 -> next ;
		dimlist = dimlist -> next ;
	}
	int s = 1 ;
	while(dimlist != NULL)
	{
		s *= dimlist -> val ;
		dimlist = dimlist -> next ;
	}
	size *= s ;
	if(res == NULL)
	{
		res = i1 -> e.temp ;	
		symbol_table_row* t3 = st_new_temp(st , T_INT , cur_scope) ;
		char code[100] ;
		if(i1 -> e.constant == 0)
			sprintf(code , "%s = %s*%d" , t3 -> name , res -> name , size) ;
		else
			sprintf(code , "%s = %s*%d" , t3 -> name , i1 -> e.val , size) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		res = t3 ;
	}
	else
	{
		char code[100] ;
		symbol_table_row* t3 = st_new_temp(st , T_INT , cur_scope) ;
		sprintf(code , "%s = %s*%d" , t3 -> name , res -> name , size) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		res = t3 ;
	}
	return res ;
}

int get_size(int eletype)
{
	int size ;
	if(eletype == T_INT)
		size = 4 ;
	else if(eletype == T_FLOAT)
		size = 8 ;
	else if(eletype == T_CHAR)
		size = 2 ;
	else
		size = sdf_struct_size(sdf , eletype) ;
	return size ;
}
