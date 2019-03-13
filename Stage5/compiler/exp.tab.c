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
#line 4 "exp.y" /* yacc.c:339  */

    #define YYSTYPE struct ASTnode*
    #include "ASTnode.h"
    #include "Gsymbol.h"
    #include "Lsymbol.h"
    #include "ParamStruct.h"
    #include "Codegen.h"
    #include "ASTLinkedList.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int yylex();
    void yyerror(char *mesg);
    extern FILE *yyin;
    FILE* fout;
    struct Gsymbol *GsymbolTable = NULL;
    struct Lsymbol *LsymbolTable = NULL;
    struct ParamStruct *paramHead = NULL;                   // head of parameter list; definition time
    struct ASTLinkedList *argHead = NULL;                   // head of argument list; usage time
    int currentType;                                        // for making symbol table and parameter entries  
    void Pre_Typecheck_Array_Index(struct ASTnode *node);         // checks whether array index is of int type
    void Pre_Typecheck_Function(struct ASTnode *node);      // compares argument types
    void Confirm_ID_Exists(struct ASTnode *node);           // checks whether the said ID exists in symbol list
    void Confirm_Variable(struct ASTnode *node);
    void Confirm_Array(struct ASTnode *node);
    void Confirm_Function(struct ASTnode *node);
    int Get_Designation(char *IDname);
    int decType;                                            // tracks the declaration type(/return type)

#line 96 "exp.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "exp.tab.h".  */
#ifndef YY_YY_EXP_TAB_H_INCLUDED
# define YY_YY_EXP_TAB_H_INCLUDED
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
    START = 258,
    END = 259,
    NUMBER = 260,
    STRING = 261,
    ID = 262,
    DECL = 263,
    ENDDECL = 264,
    INT = 265,
    STR = 266,
    READ = 267,
    WRITE = 268,
    IF = 269,
    THEN = 270,
    ELSE = 271,
    ENDIF = 272,
    WHILE = 273,
    DO = 274,
    ENDWHILE = 275,
    BREAK = 276,
    CONTINUE = 277,
    MAIN = 278,
    RETURN = 279,
    INTTYPE = 280,
    BOOLTYPE = 281,
    STRTYPE = 282,
    VARIABLE = 283,
    ARRAY = 284,
    FUNCTION = 285,
    CONNECTOR = 286,
    AND = 287,
    OR = 288,
    LT = 289,
    GT = 290,
    LE = 291,
    GE = 292,
    NE = 293,
    EQ = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EXP_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 187 "exp.tab.c" /* yacc.c:358  */

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
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   301

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      49,    50,    42,    40,    46,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
       2,    53,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    72,    72,    73,    74,    79,    80,    83,    84,    87,
      87,    90,    91,    94,    95,    98,   100,   104,   110,   111,
     112,   115,   120,   121,   124,   125,   124,   138,   139,   140,
     143,   144,   147,   150,   151,   154,   155,   161,   161,   169,
     170,   173,   174,   175,   176,   177,   178,   179,   180,   184,
     187,   189,   193,   196,   199,   202,   205,   210,   219,   220,
     221,   222,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   246,   247,   248
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "START", "END", "NUMBER", "STRING", "ID",
  "DECL", "ENDDECL", "INT", "STR", "READ", "WRITE", "IF", "THEN", "ELSE",
  "ENDIF", "WHILE", "DO", "ENDWHILE", "BREAK", "CONTINUE", "MAIN",
  "RETURN", "INTTYPE", "BOOLTYPE", "STRTYPE", "VARIABLE", "ARRAY",
  "FUNCTION", "CONNECTOR", "AND", "OR", "LT", "GT", "LE", "GE", "NE", "EQ",
  "'+'", "'-'", "'*'", "'/'", "'%'", "';'", "','", "'['", "']'", "'('",
  "')'", "'{'", "'}'", "'='", "$accept", "Program", "GDeclBlock",
  "GDeclList", "GDecl", "$@1", "Type", "GIdList", "GId", "ParamList",
  "Param", "FDefBlock", "FDef", "$@2", "$@3", "LDeclBlock", "LDeclList",
  "LDecl", "LIdList", "Body", "MainBlock", "$@4", "StatementList",
  "Statement", "WhileStatement", "IfStatement", "AssignStatement",
  "ReadStatement", "WriteStatement", "ReturnStatement", "Variable", "expr",
  "ArgList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      43,    45,    42,    47,    37,    59,    44,    91,    93,    40,
      41,   123,   125,    61
};
# endif

#define YYPACT_NINF -110

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-110)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      68,    58,   -12,    19,   152,  -110,  -110,  -110,  -110,   112,
    -110,  -110,   -33,  -110,   -12,    41,   152,  -110,  -110,  -110,
    -110,    53,    -5,  -110,  -110,  -110,    38,    79,  -110,  -110,
      21,    70,   170,  -110,    53,    31,   170,    44,    99,   -37,
    -110,  -110,   174,     0,  -110,  -110,   170,  -110,   131,   175,
    -110,  -110,  -110,   180,   150,  -110,   172,   136,   138,  -110,
      98,  -110,  -110,   144,   143,   146,   161,   162,   167,   233,
      16,   172,  -110,  -110,  -110,  -110,  -110,  -110,   273,   226,
    -110,   174,  -110,   274,    16,   275,    16,    16,    16,  -110,
    -110,  -110,  -110,    56,    16,  -110,   182,  -110,   276,  -110,
      16,   175,  -110,   165,   234,    76,    95,   114,    16,   133,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    16,
      16,    16,    16,  -110,  -110,   196,   231,  -110,   240,   241,
     272,   269,   210,    13,  -110,   221,   221,   232,   232,   232,
     232,   232,   232,   -17,   -17,  -110,  -110,  -110,  -110,  -110,
    -110,  -110,   172,   172,    16,  -110,    40,  -110,    59,   210,
     172,   244,   245,    77,  -110,  -110,   246,  -110
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     4,     5,    11,    12,     0,
       7,     9,     0,     1,    11,     0,     0,    22,     3,     6,
       8,     0,     0,    24,    23,     2,    15,     0,    13,    37,
       0,     0,    18,    10,     0,     0,    18,     0,     0,     0,
      19,    14,    27,     0,    16,    21,     0,    17,     0,     0,
      25,    20,    28,     0,     0,    30,     0,     0,     0,    33,
       0,    29,    31,    56,     0,     0,     0,     0,     0,     0,
       0,     0,    39,    44,    43,    45,    41,    42,    46,     0,
      38,    27,    32,     0,     0,     0,     0,     0,     0,    47,
      48,    58,    59,    56,     0,    60,     0,    40,    46,    36,
       0,     0,    34,     0,     0,     0,     0,     0,    76,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,    35,     0,     0,    57,     0,     0,
       0,     0,    77,     0,    62,    74,    75,    70,    71,    72,
      73,    69,    68,    63,    64,    65,    66,    67,    52,    26,
      53,    54,     0,     0,     0,    61,     0,    46,     0,    78,
       0,     0,     0,     0,    50,    49,     0,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,  -110,   283,  -110,     1,  -110,   259,   258,
     249,  -110,   280,  -110,  -110,   216,  -110,   247,  -110,   197,
       8,  -110,  -109,   -70,  -110,  -110,  -110,  -110,  -110,   -53,
     -56,   -80,  -110
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     9,    10,    21,    38,    27,    28,    39,
      40,    16,    17,    30,    58,    49,    54,    55,    60,    57,
       5,    35,    71,    72,    73,    74,    75,    76,    77,   157,
      95,    96,   133
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    97,    11,    78,   103,    15,   105,   106,   107,    46,
      11,    12,    18,    47,   109,    79,    22,    15,    98,    13,
     125,    91,    92,    93,    25,   120,   121,   122,   132,   104,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   156,   158,    29,    46,    63,    23,    53,
      50,   163,    64,    65,    66,    53,   160,   161,    67,   154,
      26,    68,    69,   155,    70,    94,    63,     6,     7,     8,
      36,    64,    65,    66,   159,    37,     1,    67,     2,   162,
      68,    69,    42,    70,    63,    31,    97,    32,    97,    64,
      65,    66,    44,    97,   166,    67,    79,    79,    68,    69,
      79,    70,    79,    84,    79,   108,    45,    79,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,    19,     7,     8,    33,    34,   129,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      52,     7,     8,    82,    83,   130,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,    61,
       7,     8,    14,     8,   131,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,    56,    63,
       7,     8,    48,   134,    64,    65,    66,    59,    80,    81,
      67,    84,    85,    68,    69,    86,    70,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
      87,    88,    89,   127,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   148,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,   120,   121,   122,    99,    90,   100,
     124,   102,    63,   149,   128,   150,   151,   152,   153,   164,
     165,   167,    20,    41,    43,    51,    24,   101,   126,     0,
       0,    62
};

static const yytype_int16 yycheck[] =
{
      56,    71,     1,    56,    84,     4,    86,    87,    88,    46,
       9,    23,     4,    50,    94,    71,    49,    16,    71,     0,
     100,     5,     6,     7,    16,    42,    43,    44,   108,    85,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   152,   153,    50,    46,     7,     7,    48,
      50,   160,    12,    13,    14,    54,    16,    17,    18,    46,
       7,    21,    22,    50,    24,    49,     7,     9,    10,    11,
      49,    12,    13,    14,   154,     5,     8,    18,    10,    20,
      21,    22,    51,    24,     7,    47,   156,    49,   158,    12,
      13,    14,    48,   163,    17,    18,   152,   153,    21,    22,
     156,    24,   158,    47,   160,    49,     7,   163,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,     9,    10,    11,    45,    46,    50,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
       9,    10,    11,    45,    46,    50,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,     9,
      10,    11,    10,    11,    50,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,     3,     7,
      10,    11,     8,    50,    12,    13,    14,     7,    52,    51,
      18,    47,    49,    21,    22,    49,    24,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      49,    49,    45,    48,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,     4,    45,    53,
       4,     7,     7,    52,    50,    45,    45,    15,    19,    45,
      45,    45,     9,    34,    36,    46,    16,    81,   101,    -1,
      -1,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    10,    55,    56,    74,     9,    10,    11,    57,
      58,    60,    23,     0,    10,    60,    65,    66,    74,     9,
      58,    59,    49,     7,    66,    74,     7,    61,    62,    50,
      67,    47,    49,    45,    46,    75,    49,     5,    60,    63,
      64,    62,    51,    63,    48,     7,    46,    50,     8,    69,
      50,    64,     9,    60,    70,    71,     3,    73,    68,     7,
      72,     9,    71,     7,    12,    13,    14,    18,    21,    22,
      24,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      52,    51,    45,    46,    47,    49,    49,    49,    49,    45,
      45,     5,     6,     7,    49,    84,    85,    77,    83,     4,
      53,    69,     7,    85,    84,    85,    85,    85,    49,    85,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,     4,    85,    73,    48,    50,    50,
      50,    50,    85,    86,    50,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    45,    52,
      45,    45,    15,    19,    46,    50,    76,    83,    76,    85,
      16,    17,    20,    76,    45,    45,    17,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    55,    56,    56,    57,    57,    59,
      58,    60,    60,    61,    61,    62,    62,    62,    63,    63,
      63,    64,    65,    65,    67,    68,    66,    69,    69,    69,
      70,    70,    71,    72,    72,    73,    73,    75,    74,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      79,    79,    80,    81,    82,    83,    84,    84,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    86,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     1,     2,     3,     1,     2,     0,
       4,     1,     1,     1,     3,     1,     4,     4,     0,     1,
       3,     2,     1,     2,     0,     0,    11,     0,     2,     3,
       1,     2,     3,     1,     3,     4,     3,     0,     9,     1,
       2,     1,     1,     1,     1,     1,     1,     2,     2,     8,
       8,    10,     4,     5,     5,     3,     1,     4,     1,     1,
       1,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     1,     3
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
        case 6:
#line 80 "exp.y" /* yacc.c:1646  */
    {Print_GsymbolTable(); Initialize();}
#line 1407 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 87 "exp.y" /* yacc.c:1646  */
    {decType = currentType;}
#line 1413 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 90 "exp.y" /* yacc.c:1646  */
    {currentType = INTTYPE;}
#line 1419 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 91 "exp.y" /* yacc.c:1646  */
    {currentType = STRTYPE;}
#line 1425 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 98 "exp.y" /* yacc.c:1646  */
    {struct Gsymbol *temp = GInstall((yyvsp[0])->name,decType,1);
                             temp->designation = VARIABLE;}
#line 1432 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 100 "exp.y" /* yacc.c:1646  */
    {int size = (yyvsp[-1])->intVal;
                             if(size<=0){printf("ERROR: Array '%s' should be initialised with valid size\n",(yyvsp[-3])->name); exit(1);}
                             struct Gsymbol *temp = GInstall((yyvsp[-3])->name,decType,size);
                             temp->designation = ARRAY;}
#line 1441 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 104 "exp.y" /* yacc.c:1646  */
    {struct Gsymbol *temp = GInstall((yyvsp[-3])->name,decType,-1);
                             temp->paramList = paramHead;
                             paramHead = NULL;
                             temp->designation = FUNCTION;}
#line 1450 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 115 "exp.y" /* yacc.c:1646  */
    {InstallParam((yyvsp[0])->name,currentType);}
#line 1456 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "exp.y" /* yacc.c:1646  */
    {decType = currentType;}
#line 1462 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 125 "exp.y" /* yacc.c:1646  */
    {struct Gsymbol *tfunc = GLookup((yyvsp[-4])->name);
                                             if(tfunc == NULL) {printf("ERROR: '%s' function is not declared\n",(yyvsp[-4])->name); exit(1);}
                                             if(tfunc->type != decType){printf("ERROR: Return type mismatch in '%s' function\n",tfunc->name); exit(1);}
                                             Check_Param_Equality(paramHead,tfunc->paramList);
                                             LParam_Install();
                                             paramHead = NULL;
                                             printf("<------------%s------------->\n",(yyvsp[-4])->name);
                                             fprintf(fout,"F%d: ",tfunc->flabel);}
#line 1475 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 133 "exp.y" /* yacc.c:1646  */
    {Print_LsymbolTable();
                                             Generate_Function_Code((yyvsp[-1]));
                                             LsymbolTable = NULL;}
#line 1483 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 150 "exp.y" /* yacc.c:1646  */
    {LInstall((yyvsp[0])->name,currentType);}
#line 1489 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 151 "exp.y" /* yacc.c:1646  */
    {LInstall((yyvsp[0])->name,currentType);}
#line 1495 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 154 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(CONNECTOR,0,(yyvsp[-2]),(yyvsp[-1]));}
#line 1501 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 155 "exp.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1507 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 161 "exp.y" /* yacc.c:1646  */
    {printf("<-------------MAIN------------->\n");
                                         decType = INTTYPE;
                                         fprintf(fout,"MAIN: ");}
#line 1515 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 164 "exp.y" /* yacc.c:1646  */
    {Print_LsymbolTable();
                                         Generate_Function_Code((yyvsp[-1]));
                                         LsymbolTable = NULL;}
#line 1523 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 170 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(CONNECTOR,0,(yyvsp[-1]),(yyvsp[0]));}
#line 1529 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 179 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(BREAK,0,NULL,NULL);}
#line 1535 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 180 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(CONTINUE,0,NULL,NULL);}
#line 1541 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 184 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(WHILE,0,(yyvsp[-5]),(yyvsp[-2]));}
#line 1547 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 187 "exp.y" /* yacc.c:1646  */
    {struct ASTnode *temp = CreateNode(CONNECTOR,0,(yyvsp[-2]),NULL);
                                                                                 (yyval) = CreateNode(IF,0,(yyvsp[-5]),temp);}
#line 1554 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 189 "exp.y" /* yacc.c:1646  */
    {struct ASTnode *temp = CreateNode(CONNECTOR,0,(yyvsp[-4]),(yyvsp[-2]));
                                                                                 (yyval) = CreateNode(IF,0,(yyvsp[-7]),temp);}
#line 1561 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 193 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode('=',0,(yyvsp[-3]),(yyvsp[-1]));}
#line 1567 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 196 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(READ,0,(yyvsp[-2]),NULL);}
#line 1573 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 199 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(WRITE,0,(yyvsp[-2]),NULL);}
#line 1579 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 202 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(RETURN,0,(yyvsp[-1]),NULL);}
#line 1585 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 205 "exp.y" /* yacc.c:1646  */
    {(yyvsp[0])->Gentry = GLookup((yyvsp[0])->name);
                                    (yyvsp[0])->Lentry = LLookup((yyvsp[0])->name);
                                    Confirm_ID_Exists((yyvsp[0]));
                                    Confirm_Variable((yyvsp[0]));
                                    (yyval) = (yyvsp[0]);}
#line 1595 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 210 "exp.y" /* yacc.c:1646  */
    {(yyvsp[-3])->Gentry = GLookup((yyvsp[-3])->name);    
                                    (yyvsp[-3])->Lentry = LLookup((yyvsp[-3])->name);
                                    Confirm_ID_Exists((yyvsp[-3]));
                                    Confirm_Array((yyvsp[-3]));
                                    (yyvsp[-3])->left = (yyvsp[-1]);
                                    Pre_Typecheck_Array_Index((yyvsp[-1]));
                                    (yyval) = (yyvsp[-3]);}
#line 1607 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 222 "exp.y" /* yacc.c:1646  */
    {(yyvsp[-3])->Gentry = GLookup((yyvsp[-3])->name);
                                     (yyvsp[-3])->Lentry = LLookup((yyvsp[-3])->name);
                                     Confirm_ID_Exists((yyvsp[-3]));
                                     Confirm_Function((yyvsp[-3]));
                                     (yyvsp[-3])->argList = argHead;
                                     Pre_Typecheck_Function((yyvsp[-3]));
                                     argHead = NULL;
                                     (yyval) = (yyvsp[-3]);}
#line 1620 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 230 "exp.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1626 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 231 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode('+',INTTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1632 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 232 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode('-',INTTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1638 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 233 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode('*',INTTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1644 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 234 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode('/',INTTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1650 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 235 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode('%',INTTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1656 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 236 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(EQ,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1662 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 237 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(NE,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1668 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 238 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(LT,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1674 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 239 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(GT,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1680 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 240 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(LE,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1686 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 241 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(GE,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1692 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 242 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(AND,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1698 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 243 "exp.y" /* yacc.c:1646  */
    {(yyval) = CreateNode(OR,BOOLTYPE,(yyvsp[-2]),(yyvsp[0]));}
#line 1704 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 247 "exp.y" /* yacc.c:1646  */
    {InstallArgument((yyvsp[0]));}
#line 1710 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 248 "exp.y" /* yacc.c:1646  */
    {InstallArgument((yyvsp[0]));}
#line 1716 "exp.tab.c" /* yacc.c:1646  */
    break;


#line 1720 "exp.tab.c" /* yacc.c:1646  */
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
#line 253 "exp.y" /* yacc.c:1906  */


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./expCompiler <inputFile> <outputFile>\n");
        return 0;
    }

    yyin = fopen(argv[1],"r");
    fout = fopen(argv[2],"w");
    yyparse();
}

void yyerror(char *mesg)
{
    printf("ERROR: %s detected by BISON\n",mesg);
    exit(1);
}

void Confirm_ID_Exists(struct ASTnode *node)
{
    if(node->Lentry == NULL)
        if(node->Gentry == NULL)
        {
            printf("ERROR: '%s' ID does not exist\n",node->name);
            exit(1);
        }
}

void Pre_Typecheck_Array_Index(struct ASTnode *node)
{
    int dataType = Get_Data_Type(node);
    if(dataType != INTTYPE)
    {
        printf("ERROR: Index of array '%s' should be int type\n",node->name);
        exit(1);
    }
}

void Pre_Typecheck_Function(struct ASTnode *node)
{
    struct ParamStruct *paramList = node->Gentry->paramList;
    struct ASTLinkedList *argList = Get_ArgumentList_Tail();

    if(paramList == NULL && argList == NULL)    return;

    while(paramList != NULL && argList != NULL)
    {
        if(paramList->type == Get_Data_Type(argList->node))
        {
            paramList = paramList->next;
            argList = argList->previous;
            continue;
        }
        printf("ERROR: Parameter mismatch in '%s' function usage\n",node->name);
        exit(1);
    }
    if(!(paramList == NULL && argList == NULL))
    {
        printf("ERROR: Parameter mismatch in '%s' function usage\n",node->name);
        exit(1);
    }
}

void Confirm_Variable(struct ASTnode *node)
{
    int designation = Get_Designation(node->name);
    if(designation != VARIABLE)
    {
        printf("ERROR: ID '%s' cannot be used like a variable\n",node->name);
        exit(1);
    }  
}

void Confirm_Array(struct ASTnode *node)
{
    int designation = Get_Designation(node->name);
    if(designation != ARRAY)
    {
        printf("ERROR: ID '%s' cannot be used like a ARRAY\n",node->name);
        exit(1);
    }
}

void Confirm_Function(struct ASTnode *node)
{
    int designation = Get_Designation(node->name);
    if(designation != FUNCTION)
    {
        printf("ERROR: ID '%s' cannot be used like a function\n",node->name);
        exit(1);
    }
}

int Get_Designation(char *IDname)
{
    struct Lsymbol *Literator = LsymbolTable;
    while(Literator != NULL)
    {
        if(!(strcmp(IDname,Literator->name)))
        {
            return VARIABLE;
        }  
        Literator =  Literator->next;
    }

    struct Gsymbol *iterator = GsymbolTable;
    while(iterator != NULL)
    {
        if(!(strcmp(IDname,iterator->name)))
        {
            return iterator->designation;
        }
        iterator = iterator->next;
    }
    return 0;
}

/*
 * <-----------------IF Node Structure---------------------->
 * 
 *
 *                 (IF)                                                     
 *                 /  \
 *                /    \
 *               /      \
 *            (expr)     \
 *                        \
 *                     (CONNECTOR)
 *                      /       \
 *                     /         \
 *                    /           \
 *        (IF statement list)   (ELSE statement list )
 *                              (NULL if else condition is not present)   
 *
 *
 *
*/
