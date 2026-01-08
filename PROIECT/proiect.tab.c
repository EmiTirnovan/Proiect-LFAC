/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "proiect.y"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "SymTable.h"
#include "AST.h"
#include "Value.h"

std::ofstream runtimeOut;
extern FILE* yyin;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

int errorCount = 0;
SymTable* currentScope = nullptr;
std::vector<std::pair<std::string, std::string>> currentParamTypes;

ASTNode* createSequence(std::vector<ASTNode*>* stmts) {
    if (!stmts || stmts->empty()) return nullptr;
    ASTNode* root = stmts->back();
    for (int i = stmts->size() - 2; i >= 0; --i) {
        ASTNode* current = (*stmts)[i];
        root = new ASTNode("SEQ", ValueType::VOID, current, root);
    }
    return root;
}

#line 101 "proiect.tab.c"

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

#include "proiect.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_TIP = 4,                        /* TIP  */
  YYSYMBOL_STRING_VAL = 5,                 /* STRING_VAL  */
  YYSYMBOL_BOOL_VAL = 6,                   /* BOOL_VAL  */
  YYSYMBOL_INT_VAL = 7,                    /* INT_VAL  */
  YYSYMBOL_FLOAT_VAL = 8,                  /* FLOAT_VAL  */
  YYSYMBOL_ASSIGN = 9,                     /* ASSIGN  */
  YYSYMBOL_CLASS = 10,                     /* CLASS  */
  YYSYMBOL_MAIN = 11,                      /* MAIN  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_PRINT = 14,                     /* PRINT  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_PLUS = 16,                      /* PLUS  */
  YYSYMBOL_MINUS = 17,                     /* MINUS  */
  YYSYMBOL_MUL = 18,                       /* MUL  */
  YYSYMBOL_DIV = 19,                       /* DIV  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_LT = 25,                        /* LT  */
  YYSYMBOL_GT = 26,                        /* GT  */
  YYSYMBOL_LE = 27,                        /* LE  */
  YYSYMBOL_GE = 28,                        /* GE  */
  YYSYMBOL_UMINUS = 29,                    /* UMINUS  */
  YYSYMBOL_30_ = 30,                       /* ';'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* '('  */
  YYSYMBOL_34_ = 34,                       /* ')'  */
  YYSYMBOL_35_ = 35,                       /* ','  */
  YYSYMBOL_36_ = 36,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_progr = 38,                     /* progr  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_declarations = 40,              /* declarations  */
  YYSYMBOL_var_decl = 41,                  /* var_decl  */
  YYSYMBOL_class_decl = 42,                /* class_decl  */
  YYSYMBOL_43_2 = 43,                      /* $@2  */
  YYSYMBOL_class_member_list = 44,         /* class_member_list  */
  YYSYMBOL_func_decl = 45,                 /* func_decl  */
  YYSYMBOL_46_3 = 46,                      /* $@3  */
  YYSYMBOL_47_4 = 47,                      /* $@4  */
  YYSYMBOL_param_list = 48,                /* param_list  */
  YYSYMBOL_param = 49,                     /* param  */
  YYSYMBOL_main = 50,                      /* main  */
  YYSYMBOL_func_body = 51,                 /* func_body  */
  YYSYMBOL_func_statement_list = 52,       /* func_statement_list  */
  YYSYMBOL_func_statement = 53,            /* func_statement  */
  YYSYMBOL_statement_list = 54,            /* statement_list  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_general_expr = 56,              /* general_expr  */
  YYSYMBOL_arith_expr = 57,                /* arith_expr  */
  YYSYMBOL_bool_expr = 58,                 /* bool_expr  */
  YYSYMBOL_call_args = 59,                 /* call_args  */
  YYSYMBOL_args_list = 60,                 /* args_list  */
  YYSYMBOL_if_statement = 61,              /* if_statement  */
  YYSYMBOL_while_statement = 62,           /* while_statement  */
  YYSYMBOL_print_call = 63                 /* print_call  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYLAST   199

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      33,    34,     2,     2,    35,     2,    36,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    67,    83,    83,    83,    83,    85,    93,
     109,   126,   125,   144,   144,   144,   146,   147,   146,   172,
     172,   172,   173,   175,   188,   190,   191,   193,   194,   196,
     197,   199,   210,   234,   273,   274,   275,   276,   282,   282,
     284,   285,   286,   287,   295,   318,   333,   334,   335,   336,
     337,   344,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   366,
     366,   367,   368,   370,   378,   386
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "TIP",
  "STRING_VAL", "BOOL_VAL", "INT_VAL", "FLOAT_VAL", "ASSIGN", "CLASS",
  "MAIN", "IF", "WHILE", "PRINT", "RETURN", "PLUS", "MINUS", "MUL", "DIV",
  "AND", "OR", "NOT", "EQ", "NEQ", "LT", "GT", "LE", "GE", "UMINUS", "';'",
  "'{'", "'}'", "'('", "')'", "','", "'.'", "$accept", "progr", "$@1",
  "declarations", "var_decl", "class_decl", "$@2", "class_member_list",
  "func_decl", "$@3", "$@4", "param_list", "param", "main", "func_body",
  "func_statement_list", "func_statement", "statement_list", "statement",
  "general_expr", "arith_expr", "bool_expr", "call_args", "args_list",
  "if_statement", "while_statement", "print_call", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-77)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -77,     2,   -77,   -77,     8,     5,    10,    12,    -6,   -77,
     -77,   -77,   -77,    -1,    -2,   -77,   -77,   -77,    64,   -77,
      17,    15,    79,   -12,   -77,   -77,   -77,   -77,    72,    64,
      64,    38,   149,   110,    74,   -77,    52,    43,    54,    57,
      64,   -77,   -77,   -77,   -77,    70,    64,    98,    72,   -77,
     149,   -77,   121,    75,   -77,    72,    72,    72,    72,    64,
      64,    72,    72,    72,    72,    64,    64,    64,    64,   101,
      14,   -77,    13,    64,    64,   103,    64,    64,    64,    80,
     -77,   -77,    86,    87,   -77,   107,   -77,   -77,    35,    35,
     -77,   -77,   162,   -77,   162,   -77,   180,   180,   180,   180,
      60,   -14,   162,   -77,   162,   -77,   -77,   -77,    74,    91,
     -77,   -77,    97,    94,   120,   130,   136,   108,   -77,   -77,
      64,   112,   -77,   -77,   -77,   105,    64,   127,   131,   -77,
     -77,   -77,   -77,   122,   -77,   -77,   129,   179,   -77,   100,
     104,   -77,    11,   160,   -77,   -77,   -77,   -77,   -77,    -2
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     0,     0,     0,     0,     0,     5,
       7,     6,     3,     0,    16,    11,    29,    10,     0,     8,
       0,     0,     0,    43,    42,    52,    40,    41,     0,     0,
       0,     0,    38,    39,    19,    13,     0,     0,     0,     0,
       0,    23,    30,    35,    36,     0,    69,     0,     0,    50,
       0,    67,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,     0,     0,    69,     0,     0,     0,     0,     0,
      34,    71,     0,    70,    44,     0,    51,    68,    46,    47,
      48,    49,    53,    63,    58,    64,    54,    55,    56,    57,
      59,    60,    65,    61,    66,    62,    22,    17,     0,     0,
      14,    15,     0,     0,     0,     0,     0,     0,    37,    45,
       0,     0,    21,    12,    31,     0,     0,     0,     0,    75,
      72,    25,    32,     0,    29,    29,     0,    24,    33,     0,
       0,    18,     0,     0,    28,    26,    27,    73,    74,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -77,   -77,   -71,   -77,   -77,   -77,    99,   -77,
     -77,   -77,    61,   -77,   -77,   -77,   -77,   -76,    47,   -18,
     -25,    -3,   111,   -77,   -77,   -77,   -77
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,     9,    10,    21,    72,    11,    20,
     121,    70,    71,    12,   136,   137,   145,    22,    42,    81,
      32,    33,    82,    83,    43,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,   110,     3,    49,    50,    52,    65,    18,    13,    67,
      68,     5,     6,    14,    13,    15,     5,     6,     7,     8,
      73,    46,    79,    85,    47,    16,    51,    53,    19,    17,
      88,    89,    90,    91,    92,    94,    96,    97,    98,    99,
      50,    50,   102,   104,    74,   109,    35,    75,   107,   108,
      34,    50,    50,    57,    58,   112,    93,    95,   139,   140,
     117,    73,   100,   101,   103,   105,   144,    23,    54,    24,
      25,    26,    27,   115,   116,    23,    76,    24,    69,    26,
      27,    28,    36,    67,    68,    74,    29,    77,    75,    28,
      78,    37,    38,    39,    40,    65,    66,    30,    67,    68,
      80,    84,   130,    36,   106,    48,   114,    36,   133,    87,
     118,    41,    37,    38,    39,    40,    37,    38,    39,    40,
     119,   123,   120,    55,    56,    57,    58,   124,   125,   126,
      65,    66,   147,    67,    68,   132,   148,    55,    56,    57,
      58,    86,   129,   131,    59,    60,    61,    62,    63,    64,
      65,    66,   138,    67,    68,    86,    65,    66,   134,    67,
      68,   141,   135,   149,   127,    55,    56,    57,    58,   122,
     128,   111,    59,    60,    61,    62,    63,    64,    55,    56,
      57,    58,   142,   143,   146,   113,     0,    61,    62,    63,
      64,    37,    38,    39,    40,     0,    55,    56,    57,    58
};

static const yytype_int16 yycheck[] =
{
      18,    72,     0,    28,    29,    30,    20,     9,     3,    23,
      24,     3,     4,     3,     3,     3,     3,     4,    10,    11,
       9,    33,    40,    48,    36,    31,    29,    30,    30,    30,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    33,    32,    31,    36,    34,    35,
      33,    76,    77,    18,    19,    73,    59,    60,   134,   135,
      78,     9,    65,    66,    67,    68,   137,     3,    30,     5,
       6,     7,     8,    76,    77,     3,    33,     5,     4,     7,
       8,    17,     3,    23,    24,    33,    22,    33,    36,    17,
      33,    12,    13,    14,    15,    20,    21,    33,    23,    24,
      30,     3,   120,     3,     3,    33,     3,     3,   126,    34,
      30,    32,    12,    13,    14,    15,    12,    13,    14,    15,
      34,    30,    35,    16,    17,    18,    19,    30,    34,     9,
      20,    21,    32,    23,    24,    30,    32,    16,    17,    18,
      19,    34,    34,    31,    23,    24,    25,    26,    27,    28,
      20,    21,    30,    23,    24,    34,    20,    21,    31,    23,
      24,    32,    31,     3,    34,    16,    17,    18,    19,   108,
      34,    72,    23,    24,    25,    26,    27,    28,    16,    17,
      18,    19,     3,     4,   137,    74,    -1,    25,    26,    27,
      28,    12,    13,    14,    15,    -1,    16,    17,    18,    19
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,    39,     0,    40,     3,     4,    10,    11,    41,
      42,    45,    50,     3,     3,     3,    31,    30,     9,    30,
      46,    43,    54,     3,     5,     6,     7,     8,    17,    22,
      33,    56,    57,    58,    33,    31,     3,    12,    13,    14,
      15,    32,    55,    61,    62,    63,    33,    36,    33,    57,
      57,    58,    57,    58,    30,    16,    17,    18,    19,    23,
      24,    25,    26,    27,    28,    20,    21,    23,    24,     4,
      48,    49,    44,     9,    33,    36,    33,    33,    33,    56,
      30,    56,    59,    60,     3,    57,    34,    34,    57,    57,
      57,    57,    57,    58,    57,    58,    57,    57,    57,    57,
      58,    58,    57,    58,    57,    58,     3,    34,    35,    32,
      41,    45,    56,    59,     3,    58,    58,    56,    30,    34,
      35,    47,    49,    30,    30,    34,     9,    34,    34,    34,
      56,    31,    30,    56,    31,    31,    51,    52,    30,    54,
      54,    32,     3,     4,    41,    53,    55,    32,    32,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    39,    38,    40,    40,    40,    40,    41,    41,
      41,    43,    42,    44,    44,    44,    46,    47,    45,    48,
      48,    48,    49,    50,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    62,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     0,     2,     2,     2,     3,     5,
       3,     0,     7,     0,     2,     2,     0,     0,    10,     0,
       1,     3,     2,     4,     1,     0,     2,     1,     1,     0,
       2,     4,     5,     6,     2,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     4,     3,     3,     3,     3,
       2,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     0,
       1,     1,     3,     7,     7,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 67 "proiect.y"
     {
          yylineno = 1;
          currentScope = new SymTable("global");
          std::ofstream fout("tables.txt", std::ios::trunc);
          fout.close();
          runtimeOut.open("runtime.txt", std::ios::trunc);
     }
#line 1259 "proiect.tab.c"
    break;

  case 3: /* progr: $@1 declarations main  */
#line 75 "proiect.y"
     {
          currentScope->printTable();
          runtimeOut.close();
          if(errorCount == 0) std::cout<<"Program compilat cu succes!"<<std::endl;
          else std::cout<<"Programul contine erori!"<<std::endl;
     }
#line 1270 "proiect.tab.c"
    break;

  case 8: /* var_decl: TIP ID ';'  */
#line 86 "proiect.y"
         {
          if (!currentScope->addSymbol(IdInfo((yyvsp[-1].strVal),(yyvsp[-2].strVal),VARIABLE,"")))
          {
               std::string msg = "Variabila '" + std::string((yyvsp[-1].strVal)) + "' a fost deja declarata in acest scope.";
               yyerror(msg.c_str());
          }
         }
#line 1282 "proiect.tab.c"
    break;

  case 9: /* var_decl: TIP ID ASSIGN general_expr ';'  */
#line 94 "proiect.y"
         {
          if (!currentScope->addSymbol(IdInfo((yyvsp[-3].strVal),(yyvsp[-4].strVal),VARIABLE,"initializata")))
               {
                    std::string msg = "Variabila '" + std::string((yyvsp[-3].strVal)) + "' a fost deja declarata in acest scope.";
                    yyerror(msg.c_str());
               }
          if ((yyvsp[-1].node) && (yyvsp[-1].node)->exprType != stringToType((yyvsp[-4].strVal)))
          {
               std::string msg = "Tip incompatibil la initializarea variabilei '" + std::string((yyvsp[-3].strVal)) + 
                                 "': s-a asteptat '" + std::string((yyvsp[-4].strVal)) + "', dar s-a primit '" + 
                                 typeToString((yyvsp[-1].node)->exprType) + "'.";
               yyerror(msg.c_str());
          }
          if((yyvsp[-1].node)) delete (yyvsp[-1].node);
         }
#line 1302 "proiect.tab.c"
    break;

  case 10: /* var_decl: ID ID ';'  */
#line 110 "proiect.y"
         {
          IdInfo* cls = currentScope->lookup((yyvsp[-2].strVal));
          if(!cls || cls->kind != CLASS_NAME)
          {
               std::string msg = "Tipul '" + std::string((yyvsp[-2].strVal)) + "' nu este definit ca o clasa.";
               yyerror(msg.c_str());
          }
          if (!currentScope->addSymbol(IdInfo((yyvsp[-1].strVal),(yyvsp[-2].strVal),VARIABLE,"object")))
               {
                    std::string msg = "Obiectul '" + std::string((yyvsp[-1].strVal)) + "' a fost deja declarat.";
                    yyerror(msg.c_str());
               }
         }
#line 1320 "proiect.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 126 "proiect.y"
           {
               if(!currentScope->addSymbol(IdInfo((yyvsp[0].strVal), "class", CLASS_NAME, "")))
                    {
                         std::string msg = "Clasa '" + std::string((yyvsp[0].strVal)) + "' este deja definita.";
                         yyerror(msg.c_str());
                    }
               currentScope = new SymTable("Class "+std::string((yyvsp[0].strVal)), currentScope);
           }
#line 1333 "proiect.tab.c"
    break;

  case 12: /* class_decl: CLASS ID $@2 '{' class_member_list '}' ';'  */
#line 135 "proiect.y"
           {
               SymTable* clsScope = currentScope; 
               currentScope->printTable();
               currentScope = currentScope->getParent(); 
               IdInfo* clsInfo = currentScope->lookup((yyvsp[-5].strVal));
               if(clsInfo) { clsInfo->defScope = clsScope; currentScope->updateSymbol(*clsInfo); }
           }
#line 1345 "proiect.tab.c"
    break;

  case 16: /* $@3: %empty  */
#line 146 "proiect.y"
                   { currentParamTypes.clear(); }
#line 1351 "proiect.tab.c"
    break;

  case 17: /* $@4: %empty  */
#line 147 "proiect.y"
          {
               IdInfo func((yyvsp[-4].strVal), (yyvsp[-5].strVal), FUNCTION, "");
               for(auto& p : currentParamTypes) func.param_types.push_back(p.first);
               if (!currentScope->addSymbol(func)) {
                    std::string msg = "Functia '" + std::string((yyvsp[-4].strVal)) + "' este deja definita in acest scope.";
                    yyerror(msg.c_str());
               }
               currentScope = new SymTable("Function "+std::string((yyvsp[-4].strVal)), currentScope);
               for (auto& p : currentParamTypes)
                    if (!currentScope->addSymbol(IdInfo(p.second, p.first, VARIABLE, "param")))
                         {
                              std::string msg = "Parametrul '" + p.second + "' este deja definit in functia '" + std::string((yyvsp[-4].strVal)) + "'.";
                              yyerror(msg.c_str());
                         }
          }
#line 1371 "proiect.tab.c"
    break;

  case 18: /* func_decl: TIP ID $@3 '(' param_list ')' $@4 '{' func_body '}'  */
#line 163 "proiect.y"
          {
               SymTable* fnScope = currentScope;
               currentScope->printTable();
               currentScope = currentScope->getParent(); 
               IdInfo* funcInfo = currentScope->lookup((yyvsp[-8].strVal));
               if(funcInfo) { funcInfo->defScope = fnScope; currentScope->updateSymbol(*funcInfo); }
          }
#line 1383 "proiect.tab.c"
    break;

  case 22: /* param: TIP ID  */
#line 173 "proiect.y"
               { currentParamTypes.push_back({(yyvsp[-1].strVal), (yyvsp[0].strVal)}); }
#line 1389 "proiect.tab.c"
    break;

  case 23: /* main: MAIN '{' statement_list '}'  */
#line 176 "proiect.y"
     {
          for(ASTNode* st : *(yyvsp[-1].nodeList)){
               if(!st) continue;
               std::string err;
               st->eval(currentScope, runtimeOut, err, yylineno);
               if(!err.empty()) yyerror(err.c_str());
               delete st;
          }
          delete (yyvsp[-1].nodeList);
     }
#line 1404 "proiect.tab.c"
    break;

  case 24: /* func_body: func_statement_list  */
#line 188 "proiect.y"
                                { if((yyvsp[0].nodeList)) { for(auto n:*(yyvsp[0].nodeList)) if(n) delete n; delete (yyvsp[0].nodeList); } }
#line 1410 "proiect.tab.c"
    break;

  case 25: /* func_statement_list: %empty  */
#line 190 "proiect.y"
                      { (yyval.nodeList) = new std::vector<ASTNode*>(); }
#line 1416 "proiect.tab.c"
    break;

  case 26: /* func_statement_list: func_statement_list func_statement  */
#line 191 "proiect.y"
                                                         { (yyval.nodeList) = (yyvsp[-1].nodeList); if((yyvsp[0].node)) (yyval.nodeList)->push_back((yyvsp[0].node)); }
#line 1422 "proiect.tab.c"
    break;

  case 27: /* func_statement: statement  */
#line 193 "proiect.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1428 "proiect.tab.c"
    break;

  case 28: /* func_statement: var_decl  */
#line 194 "proiect.y"
                          { (yyval.node) = nullptr; }
#line 1434 "proiect.tab.c"
    break;

  case 29: /* statement_list: %empty  */
#line 196 "proiect.y"
                 { (yyval.nodeList) = new std::vector<ASTNode*>(); }
#line 1440 "proiect.tab.c"
    break;

  case 30: /* statement_list: statement_list statement  */
#line 197 "proiect.y"
                                          { (yyval.nodeList) = (yyvsp[-1].nodeList); if((yyvsp[0].node)) (yyval.nodeList)->push_back((yyvsp[0].node)); }
#line 1446 "proiect.tab.c"
    break;

  case 31: /* statement: ID ASSIGN general_expr ';'  */
#line 200 "proiect.y"
          {
               IdInfo* info = currentScope->lookup((yyvsp[-3].strVal));
               if(!info){ std::string msg = "Variabila '" + std::string((yyvsp[-3].strVal)) + "' nu a fost declarata.";
                    yyerror(msg.c_str()); if((yyvsp[-1].node)) delete (yyvsp[-1].node); (yyval.node)=nullptr; }
               else {
                    std::string err;
                    (yyval.node) = ASTNode::makeAssign(ASTNode::id((yyvsp[-3].strVal), stringToType(info->type)), (yyvsp[-1].node), yylineno, err);
                    if(!err.empty()) { yyerror(err.c_str()); delete (yyval.node); (yyval.node)=nullptr; }
               }
          }
#line 1461 "proiect.tab.c"
    break;

  case 32: /* statement: ID '(' call_args ')' ';'  */
#line 211 "proiect.y"
          {
               IdInfo* f = currentScope->lookup((yyvsp[-4].strVal));
               if(!f || f->kind!=FUNCTION) {
                    std::string msg = "Functia '" + std::string((yyvsp[-4].strVal)) + "' nu este declarata.";
                    yyerror(msg.c_str());
               }
               else if((yyvsp[-2].nodeList)->size() != f->param_types.size()) {
                    std::string msg = "Functia '" + std::string((yyvsp[-4].strVal)) + "' asteapta " + std::to_string(f->param_types.size()) + 
                                      " parametri, dar i s-au dat " + std::to_string((yyvsp[-2].nodeList)->size()) + ".";
                    yyerror(msg.c_str());
               }
               else {
                   for(size_t i=0; i<(yyvsp[-2].nodeList)->size(); ++i) 
                       if((*(yyvsp[-2].nodeList))[i]->exprType != stringToType(f->param_types[i])){
                               std::string msg = "Tip incompatibil la apelul functiei '" + std::string((yyvsp[-4].strVal)) + 
                                              "' pentru parametrul " + std::to_string(i+1) + 
                                              ": s-a asteptat '" + f->param_types[i] + "', dar s-a primit '" + 
                                              typeToString((*(yyvsp[-2].nodeList))[i]->exprType) + "'.";
                               yyerror(msg.c_str());
                       }
               }
               for(auto n:*(yyvsp[-2].nodeList)) delete n; delete (yyvsp[-2].nodeList); (yyval.node)=nullptr; 
          }
#line 1489 "proiect.tab.c"
    break;

  case 33: /* statement: ID '.' ID ASSIGN general_expr ';'  */
#line 235 "proiect.y"
          {
                IdInfo* o = currentScope->lookup((yyvsp[-5].strVal));
                std::string fieldType = "unknown";

                if(!o || o->kind!=VARIABLE) {
                    std::string msg = "Obiectul '" + std::string((yyvsp[-5].strVal)) + "' nu este declarat sau nu este un obiect.";
                    yyerror(msg.c_str());
                }
                else {
                     IdInfo* c = currentScope->lookup(o->type);
                     if(!c || !c->defScope) {
                         std::string msg = "Clasa obiectului '" + std::string((yyvsp[-5].strVal)) + "' nu este definita.";
                         yyerror(msg.c_str());
                     }
                     else {
                         IdInfo* f = c->defScope->lookup((yyvsp[-3].strVal));
                         if(!f) {
                               std::string msg = "Campul '" + std::string((yyvsp[-3].strVal)) + "' nu exista in clasa '" + o->type + "'.";
                               yyerror(msg.c_str());
                         }
                         else {
                            if((yyvsp[-1].node)->exprType != stringToType(f->type)) {
                                   std::string msg = "Tip incompatibil la atribuirea campului '" + std::string((yyvsp[-3].strVal)) + 
                                                       "' al obiectului '" + std::string((yyvsp[-5].strVal)) + "': s-a asteptat '" + f->type + 
                                                       "', dar s-a primit '" + typeToString((yyvsp[-1].node)->exprType) + "'.";
                                   yyerror(msg.c_str());
                            }
                            fieldType = f->type;
                         }
                     }
                }
                std::string err;
                ASTNode* objectNode = ASTNode::id((yyvsp[-5].strVal), stringToType(o ? o->type : "unknown"));
                ASTNode* fieldNode = ASTNode::id((yyvsp[-3].strVal), stringToType(fieldType));
                ASTNode* memberAccess = new ASTNode(".", stringToType(fieldType), objectNode, fieldNode);
                (yyval.node) = ASTNode::makeAssign(memberAccess, (yyvsp[-1].node), yylineno, err);
                if(!err.empty()) { yyerror(err.c_str()); delete (yyval.node); (yyval.node)=nullptr; }
          }
#line 1532 "proiect.tab.c"
    break;

  case 34: /* statement: print_call ';'  */
#line 273 "proiect.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1538 "proiect.tab.c"
    break;

  case 35: /* statement: if_statement  */
#line 274 "proiect.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1544 "proiect.tab.c"
    break;

  case 36: /* statement: while_statement  */
#line 275 "proiect.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1550 "proiect.tab.c"
    break;

  case 37: /* statement: RETURN general_expr ';'  */
#line 277 "proiect.y"
          {
               (yyval.node) = new ASTNode("RETURN", (yyvsp[-1].node)->exprType, (yyvsp[-1].node), nullptr);
          }
#line 1558 "proiect.tab.c"
    break;

  case 38: /* general_expr: arith_expr  */
#line 282 "proiect.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1564 "proiect.tab.c"
    break;

  case 39: /* general_expr: bool_expr  */
#line 282 "proiect.y"
                                                   { (yyval.node) = (yyvsp[0].node); }
#line 1570 "proiect.tab.c"
    break;

  case 40: /* arith_expr: INT_VAL  */
#line 284 "proiect.y"
                     { (yyval.node) = ASTNode::literal(Value::fromInt((yyvsp[0].intVal))); }
#line 1576 "proiect.tab.c"
    break;

  case 41: /* arith_expr: FLOAT_VAL  */
#line 285 "proiect.y"
                       { (yyval.node) = ASTNode::literal(Value::fromFloat((yyvsp[0].floatVal))); }
#line 1582 "proiect.tab.c"
    break;

  case 42: /* arith_expr: STRING_VAL  */
#line 286 "proiect.y"
                        { std::string s((yyvsp[0].strVal)); (yyval.node) = ASTNode::literal(Value::fromString(s.substr(1, s.size()-2))); }
#line 1588 "proiect.tab.c"
    break;

  case 43: /* arith_expr: ID  */
#line 287 "proiect.y"
                {
                IdInfo* i = currentScope->lookup((yyvsp[0].strVal));
                (yyval.node) = i ? ASTNode::id((yyvsp[0].strVal), stringToType(i->type)) : ASTNode::other(ValueType::UNKNOWN);
                if(!i) {
                    std::string msg = "Variabila '" + std::string((yyvsp[0].strVal)) + "' nu a fost declarata.";
                    yyerror(msg.c_str());
                }
           }
#line 1601 "proiect.tab.c"
    break;

  case 44: /* arith_expr: ID '.' ID  */
#line 295 "proiect.y"
                       {
                IdInfo* o = currentScope->lookup((yyvsp[-2].strVal));
                ValueType t = ValueType::UNKNOWN;
                if(o && o->kind==VARIABLE) {
                     IdInfo* c = currentScope->lookup(o->type);
                     if(c && c->defScope) {
                         IdInfo* f = c->defScope->lookup((yyvsp[0].strVal));
                         if(f) t = stringToType(f->type); else {
                               std::string msg = "Campul '" + std::string((yyvsp[0].strVal)) + "' nu exista in clasa '" + o->type + "'.";
                               yyerror(msg.c_str());
                         }
                     } else {
                         std::string msg = "Clasa obiectului '" + std::string((yyvsp[-2].strVal)) + "' nu este definita.";
                         yyerror(msg.c_str());
                     }
                } else {
                         std::string msg = "Obiectul '" + std::string((yyvsp[-2].strVal)) + "' nu este declarat sau nu este un obiect.";
                         yyerror(msg.c_str());
                }
                ASTNode* obj = ASTNode::id((yyvsp[-2].strVal), stringToType(o ? o->type : "unknown"));
                ASTNode* field = ASTNode::id((yyvsp[0].strVal), t);
                (yyval.node) = new ASTNode(".", t, obj, field);
           }
#line 1629 "proiect.tab.c"
    break;

  case 45: /* arith_expr: ID '(' call_args ')'  */
#line 318 "proiect.y"
                                  {
                IdInfo* f = currentScope->lookup((yyvsp[-3].strVal));
                ValueType t = ValueType::UNKNOWN;
                if(f && f->kind==FUNCTION) {
                    t = stringToType(f->type);
                    if((yyvsp[-1].nodeList)->size() != f->param_types.size()) {
                         std::string msg = "Apel invalid functie '" + std::string((yyvsp[-3].strVal)) + "': numar parametri gresit.";
                         yyerror(msg.c_str());
                    }
                } else {
                         std::string msg = "Functia '" + std::string((yyvsp[-3].strVal)) + "' nu este declarata.";
                         yyerror(msg.c_str());
                }
                for(auto n:*(yyvsp[-1].nodeList)) delete n; delete (yyvsp[-1].nodeList); (yyval.node)=ASTNode::other(t);
           }
#line 1649 "proiect.tab.c"
    break;

  case 46: /* arith_expr: arith_expr PLUS arith_expr  */
#line 333 "proiect.y"
                                        { std::string e; (yyval.node)=ASTNode::makeBinary("+",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1655 "proiect.tab.c"
    break;

  case 47: /* arith_expr: arith_expr MINUS arith_expr  */
#line 334 "proiect.y"
                                         { std::string e; (yyval.node)=ASTNode::makeBinary("-",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1661 "proiect.tab.c"
    break;

  case 48: /* arith_expr: arith_expr MUL arith_expr  */
#line 335 "proiect.y"
                                       { std::string e; (yyval.node)=ASTNode::makeBinary("*",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1667 "proiect.tab.c"
    break;

  case 49: /* arith_expr: arith_expr DIV arith_expr  */
#line 336 "proiect.y"
                                       { std::string e; (yyval.node)=ASTNode::makeBinary("/",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1673 "proiect.tab.c"
    break;

  case 50: /* arith_expr: MINUS arith_expr  */
#line 338 "proiect.y"
               {
                    std::string e;
                    (yyval.node) = ASTNode::makeUnary("-", (yyvsp[0].node), yylineno, e);
                    if (e.size()) yyerror(e.c_str());
               }
#line 1683 "proiect.tab.c"
    break;

  case 51: /* arith_expr: '(' arith_expr ')'  */
#line 344 "proiect.y"
                                { (yyval.node) = (yyvsp[-1].node); }
#line 1689 "proiect.tab.c"
    break;

  case 52: /* bool_expr: BOOL_VAL  */
#line 347 "proiect.y"
                     { (yyval.node) = ASTNode::literal(Value::fromBool(std::string((yyvsp[0].strVal))=="true")); }
#line 1695 "proiect.tab.c"
    break;

  case 53: /* bool_expr: arith_expr EQ arith_expr  */
#line 348 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare("==",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1701 "proiect.tab.c"
    break;

  case 54: /* bool_expr: arith_expr LT arith_expr  */
#line 349 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare("<",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1707 "proiect.tab.c"
    break;

  case 55: /* bool_expr: arith_expr GT arith_expr  */
#line 350 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare(">",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1713 "proiect.tab.c"
    break;

  case 56: /* bool_expr: arith_expr LE arith_expr  */
#line 351 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare("<=",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1719 "proiect.tab.c"
    break;

  case 57: /* bool_expr: arith_expr GE arith_expr  */
#line 352 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare(">=",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1725 "proiect.tab.c"
    break;

  case 58: /* bool_expr: arith_expr NEQ arith_expr  */
#line 353 "proiect.y"
                                      { std::string e; (yyval.node)=ASTNode::makeCompare("!=",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1731 "proiect.tab.c"
    break;

  case 59: /* bool_expr: bool_expr AND bool_expr  */
#line 354 "proiect.y"
                                    { std::string e; (yyval.node)=ASTNode::makeBinary("AND",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1737 "proiect.tab.c"
    break;

  case 60: /* bool_expr: bool_expr OR bool_expr  */
#line 355 "proiect.y"
                                   { std::string e; (yyval.node)=ASTNode::makeBinary("OR",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1743 "proiect.tab.c"
    break;

  case 61: /* bool_expr: bool_expr EQ bool_expr  */
#line 356 "proiect.y"
                                   { std::string e; (yyval.node)=ASTNode::makeCompare("==",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1749 "proiect.tab.c"
    break;

  case 62: /* bool_expr: bool_expr NEQ bool_expr  */
#line 357 "proiect.y"
                                    { std::string e; (yyval.node)=ASTNode::makeCompare("!=",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1755 "proiect.tab.c"
    break;

  case 63: /* bool_expr: arith_expr EQ bool_expr  */
#line 358 "proiect.y"
                                    { std::string e; (yyval.node)=ASTNode::makeCompare("==",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1761 "proiect.tab.c"
    break;

  case 64: /* bool_expr: arith_expr NEQ bool_expr  */
#line 359 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare("!=",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1767 "proiect.tab.c"
    break;

  case 65: /* bool_expr: bool_expr EQ arith_expr  */
#line 360 "proiect.y"
                                    { std::string e; (yyval.node)=ASTNode::makeCompare("==",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1773 "proiect.tab.c"
    break;

  case 66: /* bool_expr: bool_expr NEQ arith_expr  */
#line 361 "proiect.y"
                                     { std::string e; (yyval.node)=ASTNode::makeCompare("!=",(yyvsp[-2].node),(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1779 "proiect.tab.c"
    break;

  case 67: /* bool_expr: NOT bool_expr  */
#line 362 "proiect.y"
                          { std::string e; (yyval.node)=ASTNode::makeUnary("NOT",(yyvsp[0].node),yylineno,e); if(e.size()) yyerror(e.c_str()); }
#line 1785 "proiect.tab.c"
    break;

  case 68: /* bool_expr: '(' bool_expr ')'  */
#line 363 "proiect.y"
                              { (yyval.node) = (yyvsp[-1].node); }
#line 1791 "proiect.tab.c"
    break;

  case 69: /* call_args: %empty  */
#line 366 "proiect.y"
            { (yyval.nodeList) = new std::vector<ASTNode*>(); }
#line 1797 "proiect.tab.c"
    break;

  case 70: /* call_args: args_list  */
#line 366 "proiect.y"
                                                              { (yyval.nodeList) = (yyvsp[0].nodeList); }
#line 1803 "proiect.tab.c"
    break;

  case 71: /* args_list: general_expr  */
#line 367 "proiect.y"
                         { (yyval.nodeList) = new std::vector<ASTNode*>(); (yyval.nodeList)->push_back((yyvsp[0].node)); }
#line 1809 "proiect.tab.c"
    break;

  case 72: /* args_list: args_list ',' general_expr  */
#line 368 "proiect.y"
                                       { (yyval.nodeList) = (yyvsp[-2].nodeList); (yyval.nodeList)->push_back((yyvsp[0].node)); }
#line 1815 "proiect.tab.c"
    break;

  case 73: /* if_statement: IF '(' bool_expr ')' '{' statement_list '}'  */
#line 371 "proiect.y"
             { 
                ASTNode* block = createSequence((yyvsp[-1].nodeList));
                delete (yyvsp[-1].nodeList);
                (yyval.node) = new ASTNode("If", ValueType::VOID, (yyvsp[-4].node), block);
             }
#line 1825 "proiect.tab.c"
    break;

  case 74: /* while_statement: WHILE '(' bool_expr ')' '{' statement_list '}'  */
#line 379 "proiect.y"
                { 
                ASTNode* block = createSequence((yyvsp[-1].nodeList));
                delete (yyvsp[-1].nodeList);
                (yyval.node) = new ASTNode("While", ValueType::VOID, (yyvsp[-4].node), block);
                }
#line 1835 "proiect.tab.c"
    break;

  case 75: /* print_call: PRINT '(' general_expr ')'  */
#line 386 "proiect.y"
                                        { (yyval.node) = ASTNode::makePrint((yyvsp[-1].node)); }
#line 1841 "proiect.tab.c"
    break;


#line 1845 "proiect.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 387 "proiect.y"


void yyerror(const char * s){ std::cout << "Eroare la linia " << yylineno << ": " << s << std::endl; errorCount++; }
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    yyin = fopen(argv[1], "r");
    int result = yyparse();
    if (result != 0) {
        currentScope->printTable();
    }
    return (errorCount == 0 ? 0 : 1);
}
