/* A Bison parser, made by GNU Bison 3.7.5.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/asin.y"

  #include <stdio.h>
  #include <string.h>
  #include "header.h"
  #include "libtds.h"
  #include "libgci.h"

  int mainRef1;
  int mainRef2;
  int tallaGlobal = 0;

#line 83 "asin.c"

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

#include "asin.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MAS_ = 3,                       /* MAS_  */
  YYSYMBOL_MENOS_ = 4,                     /* MENOS_  */
  YYSYMBOL_MULT_ = 5,                      /* MULT_  */
  YYSYMBOL_DIV_ = 6,                       /* DIV_  */
  YYSYMBOL_AND_ = 7,                       /* AND_  */
  YYSYMBOL_OR_ = 8,                        /* OR_  */
  YYSYMBOL_NOT_ = 9,                       /* NOT_  */
  YYSYMBOL_MAYOR_ = 10,                    /* MAYOR_  */
  YYSYMBOL_MENOR_ = 11,                    /* MENOR_  */
  YYSYMBOL_MAYORIG_ = 12,                  /* MAYORIG_  */
  YYSYMBOL_MENORIG_ = 13,                  /* MENORIG_  */
  YYSYMBOL_IGUALDAD_ = 14,                 /* IGUALDAD_  */
  YYSYMBOL_DESIGUALDAD_ = 15,              /* DESIGUALDAD_  */
  YYSYMBOL_IGUAL_ = 16,                    /* IGUAL_  */
  YYSYMBOL_APAR_ = 17,                     /* APAR_  */
  YYSYMBOL_CPAR_ = 18,                     /* CPAR_  */
  YYSYMBOL_ACOR_ = 19,                     /* ACOR_  */
  YYSYMBOL_CCOR_ = 20,                     /* CCOR_  */
  YYSYMBOL_ALLAV_ = 21,                    /* ALLAV_  */
  YYSYMBOL_CLLAV_ = 22,                    /* CLLAV_  */
  YYSYMBOL_PUNTCOMA_ = 23,                 /* PUNTCOMA_  */
  YYSYMBOL_COMA_ = 24,                     /* COMA_  */
  YYSYMBOL_PUNTO_ = 25,                    /* PUNTO_  */
  YYSYMBOL_INT_ = 26,                      /* INT_  */
  YYSYMBOL_BOOL_ = 27,                     /* BOOL_  */
  YYSYMBOL_STRUCT_ = 28,                   /* STRUCT_  */
  YYSYMBOL_READ_ = 29,                     /* READ_  */
  YYSYMBOL_PRINT_ = 30,                    /* PRINT_  */
  YYSYMBOL_RETURN_ = 31,                   /* RETURN_  */
  YYSYMBOL_IF_ = 32,                       /* IF_  */
  YYSYMBOL_ELSE_ = 33,                     /* ELSE_  */
  YYSYMBOL_WHILE_ = 34,                    /* WHILE_  */
  YYSYMBOL_TRUE_ = 35,                     /* TRUE_  */
  YYSYMBOL_FALSE_ = 36,                    /* FALSE_  */
  YYSYMBOL_CTE_ = 37,                      /* CTE_  */
  YYSYMBOL_ID_ = 38,                       /* ID_  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_programa = 40,                  /* programa  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_listaDeclaraciones = 42,        /* listaDeclaraciones  */
  YYSYMBOL_declaracion = 43,               /* declaracion  */
  YYSYMBOL_declaracionVariable = 44,       /* declaracionVariable  */
  YYSYMBOL_45_2 = 45,                      /* @2  */
  YYSYMBOL_tipoSimple = 46,                /* tipoSimple  */
  YYSYMBOL_listaCampos = 47,               /* listaCampos  */
  YYSYMBOL_declaracionFuncion = 48,        /* declaracionFuncion  */
  YYSYMBOL_49_3 = 49,                      /* $@3  */
  YYSYMBOL_50_4 = 50,                      /* @4  */
  YYSYMBOL_parametrosFormales = 51,        /* parametrosFormales  */
  YYSYMBOL_listaParametrosFormales = 52,   /* listaParametrosFormales  */
  YYSYMBOL_bloque = 53,                    /* bloque  */
  YYSYMBOL_54_5 = 54,                      /* @5  */
  YYSYMBOL_declaracionVariableLocal = 55,  /* declaracionVariableLocal  */
  YYSYMBOL_listaInstrucciones = 56,        /* listaInstrucciones  */
  YYSYMBOL_instruccion = 57,               /* instruccion  */
  YYSYMBOL_instruccionAsignacion = 58,     /* instruccionAsignacion  */
  YYSYMBOL_instruccionEntradaSalida = 59,  /* instruccionEntradaSalida  */
  YYSYMBOL_instruccionSeleccion = 60,      /* instruccionSeleccion  */
  YYSYMBOL_61_6 = 61,                      /* @6  */
  YYSYMBOL_62_7 = 62,                      /* @7  */
  YYSYMBOL_instruccionIteracion = 63,      /* instruccionIteracion  */
  YYSYMBOL_64_8 = 64,                      /* @8  */
  YYSYMBOL_65_9 = 65,                      /* @9  */
  YYSYMBOL_expresion = 66,                 /* expresion  */
  YYSYMBOL_expresionIgualdad = 67,         /* expresionIgualdad  */
  YYSYMBOL_expresionRelacional = 68,       /* expresionRelacional  */
  YYSYMBOL_expresionAditiva = 69,          /* expresionAditiva  */
  YYSYMBOL_expresionMultiplicativa = 70,   /* expresionMultiplicativa  */
  YYSYMBOL_expresionUnaria = 71,           /* expresionUnaria  */
  YYSYMBOL_expresionSufija = 72,           /* expresionSufija  */
  YYSYMBOL_73_10 = 73,                     /* $@10  */
  YYSYMBOL_constante = 74,                 /* constante  */
  YYSYMBOL_parametrosActuales = 75,        /* parametrosActuales  */
  YYSYMBOL_listaParametrosActuales = 76,   /* listaParametrosActuales  */
  YYSYMBOL_77_11 = 77,                     /* $@11  */
  YYSYMBOL_operadorLogico = 78,            /* operadorLogico  */
  YYSYMBOL_operadorIgualdad = 79,          /* operadorIgualdad  */
  YYSYMBOL_operadorRelacional = 80,        /* operadorRelacional  */
  YYSYMBOL_operadorAditivo = 81,           /* operadorAditivo  */
  YYSYMBOL_operadorMultiplicativo = 82,    /* operadorMultiplicativo  */
  YYSYMBOL_operadorUnario = 83             /* operadorUnario  */
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
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  157

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    66,    88,    90,    95,    97,   102,   112,
     129,   128,   147,   149,   154,   162,   174,   179,   173,   204,
     207,   211,   220,   232,   232,   259,   260,   264,   265,   269,
     270,   271,   272,   273,   277,   298,   321,   347,   357,   368,
     379,   367,   394,   402,   393,   421,   427,   453,   459,   480,
     486,   507,   513,   532,   538,   557,   563,   593,   600,   606,
     620,   640,   655,   654,   682,   688,   694,   704,   707,   711,
     718,   717,   727,   729,   734,   736,   741,   743,   745,   747,
     752,   754,   759,   761,   766,   768,   770
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
  "\"end of file\"", "error", "\"invalid token\"", "MAS_", "MENOS_",
  "MULT_", "DIV_", "AND_", "OR_", "NOT_", "MAYOR_", "MENOR_", "MAYORIG_",
  "MENORIG_", "IGUALDAD_", "DESIGUALDAD_", "IGUAL_", "APAR_", "CPAR_",
  "ACOR_", "CCOR_", "ALLAV_", "CLLAV_", "PUNTCOMA_", "COMA_", "PUNTO_",
  "INT_", "BOOL_", "STRUCT_", "READ_", "PRINT_", "RETURN_", "IF_", "ELSE_",
  "WHILE_", "TRUE_", "FALSE_", "CTE_", "ID_", "$accept", "programa", "$@1",
  "listaDeclaraciones", "declaracion", "declaracionVariable", "@2",
  "tipoSimple", "listaCampos", "declaracionFuncion", "$@3", "@4",
  "parametrosFormales", "listaParametrosFormales", "bloque", "@5",
  "declaracionVariableLocal", "listaInstrucciones", "instruccion",
  "instruccionAsignacion", "instruccionEntradaSalida",
  "instruccionSeleccion", "@6", "@7", "instruccionIteracion", "@8", "@9",
  "expresion", "expresionIgualdad", "expresionRelacional",
  "expresionAditiva", "expresionMultiplicativa", "expresionUnaria",
  "expresionSufija", "$@10", "constante", "parametrosActuales",
  "listaParametrosActuales", "$@11", "operadorLogico", "operadorIgualdad",
  "operadorRelacional", "operadorAditivo", "operadorMultiplicativo",
  "operadorUnario", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -76,     1,    93,   -76,   -76,   -76,   -12,    93,   -76,   -76,
     -26,   -76,   -76,   -76,    59,   -20,   -18,   -76,     0,    -5,
      87,    18,   -20,    25,     5,    16,    48,    39,    69,   -76,
     -76,    61,    77,   -76,    65,   -76,   -76,   -76,   -20,   -76,
     -76,   -76,    91,   -76,    93,   -76,    70,    21,    59,   -76,
     107,   110,    -1,   111,   -76,    82,   -76,   -76,   -76,   -76,
     -76,    -8,    92,    -1,   -76,   -76,   -76,    -1,   -76,   -76,
     -76,    80,    -3,    96,   105,   119,   120,   -76,   -76,   -76,
      -1,    -1,   112,    -1,    -1,    94,   -76,    85,    38,    84,
     -76,    -1,    95,   -76,   -76,   109,    -1,   -76,   -76,    -1,
     -76,   -76,   -76,   -76,    -1,   -76,   -76,    -1,   -76,   -76,
      -1,   -76,    86,    -1,    56,    66,   118,   113,   114,   -76,
      -1,    68,   -76,   -76,    96,   105,   119,   120,   -76,   -76,
      88,   -76,   122,    -1,   -76,   -76,    20,   117,   -76,   -76,
      28,   -76,    -1,    60,   115,   -76,   -76,    28,    62,   -76,
      -1,   108,   -76,   -76,   -76,    28,   -76
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,    12,    13,     0,     3,     4,     6,
       0,     7,    10,     5,    16,     0,     0,     8,     0,     0,
       0,     0,    20,     0,     0,     0,     0,     0,     0,    19,
      14,     0,     0,     9,    21,    17,    11,    15,     0,    23,
      22,    18,     0,    26,    28,    25,     0,     0,     0,    28,
       0,     0,     0,     0,    42,     0,    27,    30,    32,    31,
      33,     0,     0,     0,    84,    85,    86,     0,    65,    66,
      64,    59,     0,    45,    47,    49,    51,    53,    55,    57,
       0,     0,     0,     0,     0,     0,    29,     0,     0,     0,
      62,     0,     0,    72,    73,     0,     0,    74,    75,     0,
      76,    77,    78,    79,     0,    80,    81,     0,    82,    83,
       0,    56,     0,     0,     0,     0,     0,     0,     0,    58,
      68,     0,    60,    24,    46,    48,    50,    52,    54,    39,
       0,    34,     0,     0,    37,    38,    69,     0,    67,    61,
       0,    43,     0,     0,     0,    63,    40,     0,     0,    36,
       0,     0,    44,    35,    71,     0,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   -76,   133,    98,   -76,     3,   -76,   -76,
     -76,   -76,   -76,   106,   -76,   -76,   -76,    97,   -75,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -52,    47,    46,
      43,    41,   -70,   -76,   -76,   -76,   -76,     2,   -76,   -76,
     -76,   -76,   -76,   -76,   -76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,     9,    15,    10,    20,    11,
      18,    39,    28,    29,    41,    42,    44,    47,    56,    57,
      58,    59,   140,   151,    60,    82,   147,   136,    73,    74,
      75,    76,    77,    78,   120,    79,   137,   138,   144,    96,
      99,   104,   107,   110,    80
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,     3,    64,    65,    93,    94,     4,     5,    66,    12,
     111,    88,    14,    49,    86,    89,    67,    22,    19,    21,
      95,    50,    51,    25,    53,    27,    54,    93,    94,   112,
      55,   114,   115,    23,    68,    69,    70,    71,    26,   121,
     128,    27,    49,    31,   -70,    93,    94,    46,    30,    49,
      50,    51,    52,    53,    32,    54,   118,    50,    51,    55,
      53,   130,    54,    93,    94,   146,    55,    93,    94,    93,
      94,    33,   152,    93,    94,    93,    94,    34,    16,   131,
     156,   143,    17,   149,    36,   153,   132,    35,   139,    38,
     148,    93,    94,    93,    94,    93,    94,    90,    83,    91,
      37,    84,   119,   117,   129,    92,   141,    85,    48,    24,
      97,    98,    43,     4,     5,   100,   101,   102,   103,     4,
       5,     6,   105,   106,    62,   108,   109,    63,    81,   113,
      87,   123,   116,   122,   133,   145,   134,   135,   142,   150,
      13,   155,    45,   124,    40,   125,    61,   126,   127,     0,
       0,     0,   154
};

static const yytype_int16 yycheck[] =
{
      52,     0,     3,     4,     7,     8,    26,    27,     9,    21,
      80,    63,    38,    21,    22,    67,    17,    17,    15,    37,
      23,    29,    30,    20,    32,    22,    34,     7,     8,    81,
      38,    83,    84,    38,    35,    36,    37,    38,    20,    91,
     110,    38,    21,    38,    24,     7,     8,    44,    23,    21,
      29,    30,    31,    32,    38,    34,    18,    29,    30,    38,
      32,   113,    34,     7,     8,   140,    38,     7,     8,     7,
       8,    23,   147,     7,     8,     7,     8,    38,    19,    23,
     155,   133,    23,    23,    23,    23,    20,    18,    20,    24,
     142,     7,     8,     7,     8,     7,     8,    17,    16,    19,
      23,    19,    18,    18,    18,    25,    18,    25,    38,    22,
      14,    15,    21,    26,    27,    10,    11,    12,    13,    26,
      27,    28,     3,     4,    17,     5,     6,    17,    17,    17,
      38,    22,    38,    38,    16,    18,    23,    23,    16,    24,
       7,    33,    44,    96,    38,    99,    49,   104,   107,    -1,
      -1,    -1,   150
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    41,     0,    26,    27,    28,    42,    43,    44,
      46,    48,    21,    43,    38,    45,    19,    23,    49,    46,
      47,    37,    17,    38,    22,    46,    20,    46,    51,    52,
      23,    38,    38,    23,    38,    18,    23,    23,    24,    50,
      52,    53,    54,    21,    55,    44,    46,    56,    38,    21,
      29,    30,    31,    32,    34,    38,    57,    58,    59,    60,
      63,    56,    17,    17,     3,     4,     9,    17,    35,    36,
      37,    38,    66,    67,    68,    69,    70,    71,    72,    74,
      83,    17,    64,    16,    19,    25,    22,    38,    66,    66,
      17,    19,    25,     7,     8,    23,    78,    14,    15,    79,
      10,    11,    12,    13,    80,     3,     4,    81,     5,     6,
      82,    71,    66,    17,    66,    66,    38,    18,    18,    18,
      73,    66,    38,    22,    67,    68,    69,    70,    71,    18,
      66,    23,    20,    16,    23,    23,    66,    75,    76,    20,
      61,    18,    16,    66,    77,    18,    57,    65,    66,    23,
      24,    62,    57,    23,    76,    33,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    41,    40,    42,    42,    43,    43,    44,    44,
      45,    44,    46,    46,    47,    47,    49,    50,    48,    51,
      51,    52,    52,    54,    53,    55,    55,    56,    56,    57,
      57,    57,    57,    57,    58,    58,    58,    59,    59,    61,
      62,    60,    64,    65,    63,    66,    66,    67,    67,    68,
      68,    69,    69,    70,    70,    71,    71,    72,    72,    72,
      72,    72,    73,    72,    74,    74,    74,    75,    75,    76,
      77,    76,    78,    78,    79,    79,    80,    80,    80,    80,
      81,    81,    82,    82,    83,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     3,     6,
       0,     7,     1,     1,     3,     4,     0,     0,     8,     1,
       0,     2,     4,     0,     8,     2,     0,     2,     0,     3,
       1,     1,     1,     1,     4,     7,     6,     5,     5,     0,
       0,     9,     0,     0,     7,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     2,     1,     3,     1,
       3,     4,     0,     5,     1,     1,     1,     1,     0,     1,
       0,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
#line 66 "src/asin.y"
                                            {
                                                /* Variables globales */
                                                niv = 0; /* Nivel */
                                                dvar = 0; /* Desplazamiento */
                                                si = 0; /* Desplazamiento en el Segmento de Codigo */
                                                cargaContexto(niv);
                                                /*GCI*********************/
                                                mainRef1 = creaLans(si);
                                                emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(-1));
                                                mainRef2 = creaLans(si);
                                                emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
                                            }
#line 1287 "asin.c"
    break;

  case 3: /* programa: $@1 listaDeclaraciones  */
#line 79 "src/asin.y"
                                            {
                                                /* En caso de 0, significa que no se ha leído una función main */
                                                if(!(yyvsp[0].cent)) /* Es $2 porque la acción semantica es $1 */
                                                    yyerror("El programa no tiene funcion \"main\"");
                                                else if((yyvsp[0].cent)>1) yyerror("El programa tiene mas de una funcion \"main\"");
                                            }
#line 1298 "asin.c"
    break;

  case 4: /* listaDeclaraciones: declaracion  */
#line 89 "src/asin.y"
                                            { (yyval.cent) = (yyvsp[0].cent); }
#line 1304 "asin.c"
    break;

  case 5: /* listaDeclaraciones: listaDeclaraciones declaracion  */
#line 91 "src/asin.y"
                                            { (yyval.cent) = (yyvsp[-1].cent)+(yyvsp[0].cent); }
#line 1310 "asin.c"
    break;

  case 6: /* declaracion: declaracionVariable  */
#line 96 "src/asin.y"
                                            { (yyval.cent) = 0; /* No es una función main */}
#line 1316 "asin.c"
    break;

  case 7: /* declaracion: declaracionFuncion  */
#line 98 "src/asin.y"
                                            { (yyval.cent) = (yyvsp[0].cent); /* Si es una función main será 1 */}
#line 1322 "asin.c"
    break;

  case 8: /* declaracionVariable: tipoSimple ID_ PUNTCOMA_  */
#line 103 "src/asin.y"
                                            {
                                                if(!insTdS((yyvsp[-1].ident), VARIABLE, (yyvsp[-2].cent), niv, dvar, -1)) 
                                                    yyerror("Identificador de variable repetido");
                                                else{
                                                    dvar += TALLA_TIPO_SIMPLE;
                                                    // En caso de nivel 0 (global)
                                                    if(!niv) tallaGlobal += TALLA_TIPO_SIMPLE;
                                                }
                                            }
#line 1336 "asin.c"
    break;

  case 9: /* declaracionVariable: tipoSimple ID_ ACOR_ CTE_ CCOR_ PUNTCOMA_  */
#line 113 "src/asin.y"
                                            { 
                                                int numelem = (yyvsp[-2].cent);
                                                if (numelem <= 0) {
                                                    yyerror("Talla inapropiada del array");
                                                    numelem = 0;
                                                }
                                                int ref = insTdA((yyvsp[-5].cent), numelem);
                                                if(!insTdS((yyvsp[-4].ident), VARIABLE, T_ARRAY, niv, dvar, ref))
                                                    yyerror("Identificador repetido");
                                                else{
                                                    dvar += numelem * TALLA_TIPO_SIMPLE;
                                                    // En caso de nivel 0 (global)
                                                    if(!niv) tallaGlobal += numelem * TALLA_TIPO_SIMPLE;
                                                } 
                                            }
#line 1356 "asin.c"
    break;

  case 10: /* @2: %empty  */
#line 129 "src/asin.y"
                                            {
                                                (yyval.cent)=dvar;
                                                dvar = 0;
                                            }
#line 1365 "asin.c"
    break;

  case 11: /* declaracionVariable: STRUCT_ ALLAV_ @2 listaCampos CLLAV_ ID_ PUNTCOMA_  */
#line 134 "src/asin.y"
                                            {
                                                dvar = (yyvsp[-4].cent);
                                                if(!insTdS((yyvsp[-1].ident), VARIABLE, T_RECORD, niv, dvar, (yyvsp[-3].listapc).refe))
                                                    yyerror("Identificador repetido");
                                                else{
                                                    dvar += (yyvsp[-3].listapc).tam;
                                                    // En caso de nivel 0 (global)
                                                    if(!niv) tallaGlobal += (yyvsp[-3].listapc).tam;
                                                }
                                            }
#line 1380 "asin.c"
    break;

  case 12: /* tipoSimple: INT_  */
#line 148 "src/asin.y"
                                            { (yyval.cent) = T_ENTERO; }
#line 1386 "asin.c"
    break;

  case 13: /* tipoSimple: BOOL_  */
#line 150 "src/asin.y"
                                            { (yyval.cent) = T_LOGICO; }
#line 1392 "asin.c"
    break;

  case 14: /* listaCampos: tipoSimple ID_ PUNTCOMA_  */
#line 155 "src/asin.y"
                                            {
                                                (yyval.listapc).tam = TALLA_TIPO_SIMPLE;
                                                (yyval.listapc).refe = insTdR(-1, (yyvsp[-1].ident), (yyvsp[-2].cent), dvar);
                                                dvar += (yyval.listapc).tam;
                                                if((yyval.listapc).refe==-1)
                                                    yyerror("Nombre de campo repetido");
                                            }
#line 1404 "asin.c"
    break;

  case 15: /* listaCampos: listaCampos tipoSimple ID_ PUNTCOMA_  */
#line 163 "src/asin.y"
                                            {
                                                (yyval.listapc).tam = TALLA_TIPO_SIMPLE + (yyvsp[-3].listapc).tam;
                                                (yyval.listapc).refe = (yyvsp[-3].listapc).refe;
                                                if(insTdR((yyvsp[-3].listapc).refe, (yyvsp[-1].ident), (yyvsp[-2].cent), dvar)==-1) 
                                                    yyerror("Nombre de campo repetido");
                                                dvar += (yyvsp[-3].listapc).tam;
                                            }
#line 1416 "asin.c"
    break;

  case 16: /* $@3: %empty  */
#line 174 "src/asin.y"
                                            { 
                                                niv = 1; /* En C solo existen 2 niveles (0 y 1) */
                                                cargaContexto(niv);
                                            }
#line 1425 "asin.c"
    break;

  case 17: /* @4: %empty  */
#line 179 "src/asin.y"
                                            {
                                                /* Si ya existe en la TdS */
                                                if(!insTdS((yyvsp[-4].ident), FUNCION, (yyvsp[-5].cent), 0, si, (yyvsp[-1].cent)))
                                                    yyerror("Identificador de funcion repetido");
                                                (yyval.cent)=dvar;
                                                dvar = 0;
                                                /*GCI*********************/
                                                if(strcmp((yyvsp[-4].ident), "main")==0) {
                                                    completaLans(mainRef1, crArgEnt(tallaGlobal));
                                                    completaLans(mainRef2, crArgEtq(si));
                                                }
                                            }
#line 1442 "asin.c"
    break;

  case 18: /* declaracionFuncion: tipoSimple ID_ $@3 APAR_ parametrosFormales CPAR_ @4 bloque  */
#line 192 "src/asin.y"
                                            {
                                                if(verTdS) mostrarTdS();
                                                descargaContexto(niv);
                                                niv = 0;
                                                dvar = (yyvsp[-1].cent);
                                                // Comprobación de si es main
                                                if(strcmp((yyvsp[-6].ident), "main")==0) (yyval.cent) = 1;
                                                else  (yyval.cent) = 0;
                                            }
#line 1456 "asin.c"
    break;

  case 19: /* parametrosFormales: listaParametrosFormales  */
#line 205 "src/asin.y"
                                            { (yyval.cent) = (yyvsp[0].listapc).refe; }
#line 1462 "asin.c"
    break;

  case 20: /* parametrosFormales: %empty  */
#line 207 "src/asin.y"
                                            { (yyval.cent) = insTdD(-1, T_VACIO); }
#line 1468 "asin.c"
    break;

  case 21: /* listaParametrosFormales: tipoSimple ID_  */
#line 212 "src/asin.y"
                                            {
                                                /* Crear una nueva entrada en la TdD */
                                                (yyval.listapc).refe = insTdD(-1, (yyvsp[-1].cent));
                                                int talla = TALLA_TIPO_SIMPLE + TALLA_SEGENLACES;
                                                (yyval.listapc).tam = talla;
                                                if(!insTdS((yyvsp[0].ident), PARAMETRO, (yyvsp[-1].cent), niv, -talla, -1))
                                                    yyerror("Identificador de parametro repetido");
                                            }
#line 1481 "asin.c"
    break;

  case 22: /* listaParametrosFormales: tipoSimple ID_ COMA_ listaParametrosFormales  */
#line 221 "src/asin.y"
                                            {
                                                (yyval.listapc).refe = insTdD((yyvsp[0].listapc).refe, (yyvsp[-3].cent));
                                                int talla = TALLA_TIPO_SIMPLE + (yyvsp[0].listapc).tam;
                                                (yyval.listapc).tam = talla;
                                                if(!insTdS((yyvsp[-2].ident), PARAMETRO, (yyvsp[-3].cent), niv, -talla, -1))
                                                    yyerror("Identificador de parametro repetido");
                                            }
#line 1493 "asin.c"
    break;

  case 23: /* @5: %empty  */
#line 232 "src/asin.y"
                                            {
                                                emite(PUSHFP, crArgNul(), crArgNul(), crArgNul());
                                                emite(FPTOP, crArgNul(), crArgNul(), crArgNul());
                                                (yyval.cent) = creaLans(si);
                                                emite(INCTOP, crArgNul(), crArgNul(), crArgEnt(-1));
                                            }
#line 1504 "asin.c"
    break;

  case 24: /* bloque: @5 ALLAV_ declaracionVariableLocal listaInstrucciones RETURN_ expresion PUNTCOMA_ CLLAV_  */
#line 239 "src/asin.y"
                                            {
                                                /* Informacion de la funcion actual */
                                                INF inf = obtTdD(-1);
                                                if(inf.tipo!=T_ERROR && inf.tipo!=(yyvsp[-2].exp).tipo)
                                                    yyerror("Error de tipos en el \"return\"");
                                                if(inf.tipo!=T_ERROR) {
                                                    /*GCI*********************/
                                                    int returnPos = TALLA_SEGENLACES + inf.tsp + TALLA_TIPO_SIMPLE;                                              
                                                    completaLans((yyvsp[-7].cent), crArgEnt(dvar)); 
                                                    emite(EASIG, crArgPos(niv, (yyvsp[-2].exp).valor), crArgNul(), crArgPos(niv, -returnPos));
                                                    emite(TOPFP, crArgNul(), crArgNul(), crArgNul());
                                                    emite(FPPOP, crArgNul(), crArgNul(), crArgNul());
                                                    if(strcmp(inf.nom, "main")==0)
                                                        emite(FIN, crArgNul(), crArgNul(), crArgNul());
                                                    else emite(RET, crArgNul(), crArgNul(), crArgNul());
                                                }
                                            }
#line 1526 "asin.c"
    break;

  case 34: /* instruccionAsignacion: ID_ IGUAL_ expresion PUNTCOMA_  */
#line 278 "src/asin.y"
                                            {
                                                SIMB simb = obtTdS((yyvsp[-3].ident));
                                                if((yyvsp[-1].exp).tipo != T_ERROR) {
                                                    if(simb.t == T_ERROR)
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t == T_ARRAY)
                                                        yyerror("Error de asignacion a tipo \"array\"");
                                                    else if(simb.t == T_ENTERO && simb.t != (yyvsp[-1].exp).tipo)
                                                        yyerror("Error de tipos en la \"asignacion\" de tipo \"entero\"");
                                                    else if(simb.t == T_LOGICO && simb.t != (yyvsp[-1].exp).tipo)
                                                        yyerror("Error de tipos en la \"asignacion\" de tipo \"logico\"");
                                                    else if(simb.t != (yyvsp[-1].exp).tipo)
                                                        yyerror("Error de tipos en la \"asignacion\"");
                                                    else{
                                                        /*GCI*********************/
                                                        emite(EASIG, crArgPos(niv, (yyvsp[-1].exp).valor), crArgNul(), crArgPos(simb.n, simb.d));
                                                    }
                                                }
                                                (yyval.cent) = (yyvsp[-1].exp).tipo;
                                            }
#line 1551 "asin.c"
    break;

  case 35: /* instruccionAsignacion: ID_ ACOR_ expresion CCOR_ IGUAL_ expresion PUNTCOMA_  */
#line 299 "src/asin.y"
                                            {
                                                SIMB simb = obtTdS((yyvsp[-6].ident));
                                                (yyval.cent) = T_ERROR;
                                                if((yyvsp[-4].exp).tipo != T_ERROR && (yyvsp[-1].exp).tipo != T_ERROR) {
                                                    if(simb.t == T_ERROR) yyerror("Objeto no declarado");
                                                    else if(simb.t != T_ARRAY)
                                                        yyerror("El identificador debe ser de tipo \"array\"");
                                                    else if((yyvsp[-4].exp).tipo != T_ENTERO)
                                                        yyerror("El indice del \"array\" debe ser entero");
                                                    else {
                                                        DIM dim = obtTdA(simb.ref);
                                                        if(dim.telem != (yyvsp[-1].exp).tipo)
                                                            yyerror("Error de tipos en la \"asignacion\" de tipo \"array\"");
                                                        else {
                                                            (yyval.cent) = (yyvsp[-1].exp).tipo;
                                                            /*GCI*********************/
                                                            emite(EVA, crArgPos(simb.n, simb.d), crArgPos(niv, (yyvsp[-4].exp).valor), crArgPos(niv, (yyvsp[-1].exp).valor));
                                                            // simb.d[$3.valor] = $6.valor
                                                        }
                                                    } 
                                                }
                                            }
#line 1578 "asin.c"
    break;

  case 36: /* instruccionAsignacion: ID_ PUNTO_ ID_ IGUAL_ expresion PUNTCOMA_  */
#line 322 "src/asin.y"
                                            {
                                                SIMB simb = obtTdS((yyvsp[-5].ident));
                                                (yyval.cent) = T_ERROR;
                                                if((yyvsp[-1].exp).tipo != T_ERROR){
                                                    if(simb.t == T_ERROR)
                                                        yyerror("Objeto no declarado");
                                                    else if(simb.t != T_RECORD)
                                                        yyerror("El identificador debe ser \"struct\"");
                                                    else {
                                                        CAMP campo = obtTdR(simb.ref, (yyvsp[-3].ident));
                                                        if(campo.t == T_ERROR)
                                                            yyerror("Campo no declarado");
                                                        else if(campo.t != (yyvsp[-1].exp).tipo)
                                                            yyerror("Error de tipos en la \"asignacion\" de tipo \"struct\"");
                                                        else{
                                                            (yyval.cent) = (yyvsp[-1].exp).tipo;
                                                            /*GCI*********************/
                                                            emite(EASIG, crArgPos(niv, (yyvsp[-1].exp).valor), crArgNul(), crArgPos(simb.n, simb.d+campo.d));
                                                        }
                                                    }
                                                }
                                            }
#line 1605 "asin.c"
    break;

  case 37: /* instruccionEntradaSalida: READ_ APAR_ ID_ CPAR_ PUNTCOMA_  */
#line 348 "src/asin.y"
                                            {
                                                SIMB simb = obtTdS((yyvsp[-2].ident));
                                                if(simb.t == T_ERROR)
                                                    yyerror("Objeto no declarado");
                                                else if(simb.t != T_ENTERO) /* read recibe un int como parametro */
                                                    yyerror("El argumento del \"read\" debe ser \"entero\"");
                                                else /*GCI*********************/
                                                    emite(EREAD, crArgNul(), crArgNul(), crArgPos(simb.n, simb.d));
                                            }
#line 1619 "asin.c"
    break;

  case 38: /* instruccionEntradaSalida: PRINT_ APAR_ expresion CPAR_ PUNTCOMA_  */
#line 358 "src/asin.y"
                                            {
                                                if ((yyvsp[-2].exp).tipo != T_ENTERO)
                                                    yyerror("La expresion del \"print\" debe ser \"entera\"");
                                                else /*GCI*********************/
                                                    emite(EWRITE, crArgNul(), crArgNul(), crArgPos(niv, (yyvsp[-2].exp).valor));
                                            }
#line 1630 "asin.c"
    break;

  case 39: /* @6: %empty  */
#line 368 "src/asin.y"
                                            {
                                                if((yyvsp[-1].exp).tipo != T_ERROR && (yyvsp[-1].exp).tipo != T_LOGICO)
                                                    yyerror("La expresion del \"if\" debe ser \"logico\""); 
                                                else {
                                                    /*GCI*********************/
                                                    (yyval.cent) = creaLans(si);
                                                    // En caso de False salta al else
                                                    emite(EIGUAL, crArgPos(niv, (yyvsp[-1].exp).valor), crArgEnt(0), crArgEtq(-1));
                                                }
                                            }
#line 1645 "asin.c"
    break;

  case 40: /* @7: %empty  */
#line 379 "src/asin.y"
                                            {
                                                /*GCI*********************/
                                                (yyval.cent) = creaLans(si);
                                                emite(GOTOS, crArgNul(), crArgNul(), crArgEtq(-1));
                                                completaLans((yyvsp[-1].cent), crArgEtq(si));
                                            }
#line 1656 "asin.c"
    break;

  case 41: /* instruccionSeleccion: IF_ APAR_ expresion CPAR_ @6 instruccion @7 ELSE_ instruccion  */
#line 386 "src/asin.y"
                                            {
                                                /*GCI*********************/
                                                completaLans((yyvsp[-2].cent), crArgEtq(si));
                                            }
#line 1665 "asin.c"
    break;

  case 42: /* @8: %empty  */
#line 394 "src/asin.y"
                                            { 
                                                /*GCI*********************/
                                                (yyval.cent) = si;
                                                // Se guarda la referencia de la primera instrucción 
                                                // de la expresión condicional del while, para comprobarla
                                                // en cada iteración
                                            }
#line 1677 "asin.c"
    break;

  case 43: /* @9: %empty  */
#line 402 "src/asin.y"
                                            {
                                                if((yyvsp[-1].exp).tipo != T_ERROR && (yyvsp[-1].exp).tipo != T_LOGICO)
                                                    yyerror("La expresion del \"while\" debe ser \"logica\"");
                                                else{
                                                    /*GCI*********************/
                                                    (yyval.cent) = creaLans(si);
                                    		        // Si es False salta al final del WHILE
                                                    emite(EIGUAL, crArgPos(niv, (yyvsp[-1].exp).valor), crArgEnt(0), crArgEtq(-1));
                                                }
                                            }
#line 1692 "asin.c"
    break;

  case 44: /* instruccionIteracion: WHILE_ @8 APAR_ expresion CPAR_ @9 instruccion  */
#line 413 "src/asin.y"
                                            {
                                                /*GCI*********************/
                                                emite(GOTOS, crArgNul(), crArgNul(), crArgEtq((yyvsp[-5].cent)));
                                                completaLans((yyvsp[-1].cent), crArgEtq(si));
                                            }
#line 1702 "asin.c"
    break;

  case 45: /* expresion: expresionIgualdad  */
#line 422 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].exp).valor;
                                            }
#line 1712 "asin.c"
    break;

  case 46: /* expresion: expresion operadorLogico expresionIgualdad  */
#line 428 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ERROR;
                                                if((yyvsp[-2].exp).tipo != T_ERROR && (yyvsp[0].exp).tipo != T_ERROR) {
                                                    if((yyvsp[-2].exp).tipo != (yyvsp[0].exp).tipo) 
                                                        yyerror("Error de tipos en \"expresion logica\"");
                                                    else if((yyvsp[-2].exp).tipo != T_LOGICO) 
                                                        yyerror("Operador \"logico\" debe usarse en \"expresiones logicas\"");
                                                    else {
                                                        (yyval.exp).tipo = T_LOGICO;
                                                        
                                                        /*GCI*********************/
                                                        (yyval.exp).valor = creaVarTemp();
                                                        if((yyvsp[-1].cent) == AND) // en caso de AND
                                                            emite(EMULT, crArgPos(niv, (yyvsp[-2].exp).valor), crArgPos(niv, (yyvsp[0].exp).valor), crArgPos(niv, (yyval.exp).valor));
                                                        else { // en caso de OR
                                                            emite(ESUM, crArgPos(niv, (yyvsp[-2].exp).valor), crArgPos(niv, (yyvsp[0].exp).valor), crArgPos(niv, (yyval.exp).valor));
                                                            emite(EMENEQ, crArgPos(niv, (yyval.exp).valor), crArgEnt(1), crArgEtq(si+2));
                                                            emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                        }
                                                    }
                                                }
                                            }
#line 1739 "asin.c"
    break;

  case 47: /* expresionIgualdad: expresionRelacional  */
#line 454 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].exp).valor;
                                            }
#line 1749 "asin.c"
    break;

  case 48: /* expresionIgualdad: expresionIgualdad operadorIgualdad expresionRelacional  */
#line 460 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ERROR;
                                                if((yyvsp[-2].exp).tipo != T_ERROR && (yyvsp[0].exp).tipo != T_ERROR) {
                                                    if((yyvsp[-2].exp).tipo != (yyvsp[0].exp).tipo) 
                                                        yyerror("Error de tipos en \"expresion de igualdad\"");
                                                    else if((yyvsp[-2].exp).tipo != T_ENTERO && (yyvsp[-2].exp).tipo != T_LOGICO) 
                                                        yyerror("Operador de \"igualdad\" debe usarse con variables de tipo \"entero\" o \"logico\"");
                                                    else {
                                                        (yyval.exp).tipo = T_LOGICO;
                                                        /*GCI*********************/
                                                        (yyval.exp).valor = creaVarTemp();
                                                        emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                        emite((yyvsp[-1].cent), crArgPos(niv, (yyvsp[-2].exp).valor), crArgPos(niv, (yyvsp[0].exp).valor), crArgEtq(si+2));
                                                        emite(EASIG, crArgEnt(0), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                    }
                                                }
                                            }
#line 1771 "asin.c"
    break;

  case 49: /* expresionRelacional: expresionAditiva  */
#line 481 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].exp).valor;
                                            }
#line 1781 "asin.c"
    break;

  case 50: /* expresionRelacional: expresionRelacional operadorRelacional expresionAditiva  */
#line 487 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ERROR;
                                                if((yyvsp[-2].exp).tipo != T_ERROR && (yyvsp[0].exp).tipo != T_ERROR) {
                                                    if((yyvsp[-2].exp).tipo != (yyvsp[0].exp).tipo) 
                                                        yyerror("Error de tipos en \"expresion de relacional\"");
                                                    else if((yyvsp[-2].exp).tipo != T_ENTERO)
                                                        yyerror("Operador \"relacional\" debe usarse con variables de tipo \"entero\"");
                                                    else {
                                                        (yyval.exp).tipo = T_LOGICO;
                                                        /*GCI*********************/
                                                        (yyval.exp).valor = creaVarTemp();
                                                        emite(EASIG, crArgEnt(1), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                        emite((yyvsp[-1].cent), crArgPos(niv, (yyvsp[-2].exp).valor), crArgPos(niv, (yyvsp[0].exp).valor), crArgEtq(si+2));
                                                        emite(EASIG, crArgEnt(0), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                    }
                                                }
                                            }
#line 1803 "asin.c"
    break;

  case 51: /* expresionAditiva: expresionMultiplicativa  */
#line 508 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].exp).valor;
                                            }
#line 1813 "asin.c"
    break;

  case 52: /* expresionAditiva: expresionAditiva operadorAditivo expresionMultiplicativa  */
#line 514 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ERROR;
                                                if((yyvsp[-2].exp).tipo != T_ERROR && (yyvsp[0].exp).tipo != T_ERROR) {
                                                    if((yyvsp[-2].exp).tipo != (yyvsp[0].exp).tipo)
                                                        yyerror("Error de tipos en \"expresion aditiva\"");
                                                    else if((yyvsp[-2].exp).tipo != T_ENTERO)
                                                        yyerror("Operador \"aditivo\" debe usarse con variables de tipo \"entero\"");
                                                    else {
                                                        (yyval.exp).tipo = T_ENTERO;
                                                        /*GCI*********************/
                                                        (yyval.exp).valor = creaVarTemp();
                                                        emite((yyvsp[-1].cent), crArgPos(niv, (yyvsp[-2].exp).valor), crArgPos(niv, (yyvsp[0].exp).valor), crArgPos(niv, (yyval.exp).valor));
                                                    }
                                                }
                                            }
#line 1833 "asin.c"
    break;

  case 53: /* expresionMultiplicativa: expresionUnaria  */
#line 533 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].exp).valor;
                                             }
#line 1843 "asin.c"
    break;

  case 54: /* expresionMultiplicativa: expresionMultiplicativa operadorMultiplicativo expresionUnaria  */
#line 539 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ERROR;
                                                if((yyvsp[-2].exp).tipo != T_ERROR && (yyvsp[0].exp).tipo != T_ERROR) {
                                                    if((yyvsp[-2].exp).tipo != (yyvsp[0].exp).tipo)
                                                        yyerror("Error de tipos en \"expresion multiplicativa\"");
                                                    else if((yyvsp[-2].exp).tipo != T_ENTERO)
                                                        yyerror("Operador \"multiplicativo\" debe usarse con variables de tipo \"entero\"");
                                                    else {
                                                        (yyval.exp).tipo = T_ENTERO;
                                                        /*GCI*********************/
                                                        (yyval.exp).valor = creaVarTemp();
                                                        emite((yyvsp[-1].cent), crArgPos(niv, (yyvsp[-2].exp).valor), crArgPos(niv, (yyvsp[0].exp).valor), crArgPos(niv, (yyval.exp).valor));
                                                    }
                                                }
                                            }
#line 1863 "asin.c"
    break;

  case 55: /* expresionUnaria: expresionSufija  */
#line 558 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].exp).valor; 
                                            }
#line 1873 "asin.c"
    break;

  case 56: /* expresionUnaria: operadorUnario expresionUnaria  */
#line 564 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ERROR;
                                                if((yyvsp[0].exp).tipo != T_ERROR) {
                                                    if((yyvsp[0].exp).tipo == T_ENTERO) {
                                                        if((yyvsp[-1].cent) == ESIG) 
                                                            yyerror("Operador \"!\" invalido para tipo \"entero\"");
                                                        else{ 
                                                            (yyval.exp).tipo = T_ENTERO;
                                                            /*GCI*********************/
                                                            (yyval.exp).valor = creaVarTemp();
                                                            emite(ESIG, crArgPos(niv, (yyvsp[0].exp).valor), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                        }
                                                    }
                                                    else if((yyvsp[0].exp).tipo == T_LOGICO) {
                                                        if((yyvsp[-1].cent) != ESIG)
                                                            yyerror("Operador \"+\" y \"-\" invalido para tipo \"logico\"");
                                                        else{
                                                            (yyval.exp).tipo = T_LOGICO;
                                                            /*GCI*********************/
                                                            (yyval.exp).valor = creaVarTemp();
                                                            /*Caso True: 1-0=1 y caso False: 1-1=0*/
                                                            emite(EDIF, crArgEnt(1), crArgPos(niv, (yyvsp[0].exp).valor), crArgPos(niv, (yyval.exp).valor));
                                                        }
                                                    }
                                                }
                                            }
#line 1904 "asin.c"
    break;

  case 57: /* expresionSufija: constante  */
#line 594 "src/asin.y"
                                            { 
                                            	(yyval.exp).tipo = (yyvsp[0].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = creaVarTemp();
                                                emite(EASIG, crArgEnt((yyvsp[0].exp).valor), crArgNul(), crArgPos(niv, (yyval.exp).valor)); 
                                            }
#line 1915 "asin.c"
    break;

  case 58: /* expresionSufija: APAR_ expresion CPAR_  */
#line 601 "src/asin.y"
                                            { 
                                                (yyval.exp).tipo = (yyvsp[-1].exp).tipo;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[-1].exp).valor;
                                            }
#line 1925 "asin.c"
    break;

  case 59: /* expresionSufija: ID_  */
#line 607 "src/asin.y"
                                            { 
                                                /* Comprobamos su tipo */
                                                SIMB simb = obtTdS((yyvsp[0].ident));
                                                if(simb.t == T_ERROR) {
                                                    (yyval.exp).tipo = T_ERROR; yyerror("Objeto no declarado");
                                                }
                                                else{
                                                    (yyval.exp).tipo = simb.t;
                                                    /*GCI*********************/
                                                    (yyval.exp).valor = creaVarTemp();
                                                    emite(EASIG, crArgPos(simb.n, simb.d), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                }
                                            }
#line 1943 "asin.c"
    break;

  case 60: /* expresionSufija: ID_ PUNTO_ ID_  */
#line 621 "src/asin.y"
                                            {
                                                /* Comprobamos su tipo */
                                                SIMB simb = obtTdS((yyvsp[-2].ident));
                                                (yyval.exp).tipo = T_ERROR;
                                                if(simb.t == T_ERROR)
                                                    yyerror("Objeto no declarado");
                                                else if(simb.t != T_RECORD)
                                                    yyerror("El identificador debe ser \"struct\"");
                                                else {
                                                    CAMP campo = obtTdR(simb.ref, (yyvsp[0].ident));
                                                    if(campo.t == T_ERROR)
                                                        yyerror("Campo no declarado");
                                                    else (yyval.exp).tipo = campo.t;
                                                    /*GCI*********************/
                                                    int pos = simb.d + campo.d;
                                                    (yyval.exp).valor = creaVarTemp();
                                                    emite(EASIG, crArgPos(simb.n, pos), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                }
                                            }
#line 1967 "asin.c"
    break;

  case 61: /* expresionSufija: ID_ ACOR_ expresion CCOR_  */
#line 641 "src/asin.y"
                                            {   
                                                SIMB simb = obtTdS((yyvsp[-3].ident));
                                                (yyval.exp).tipo = T_ERROR;
                                                if(simb.t == T_ERROR) yyerror("Objeto no declarado");
                                                else if(simb.t != T_ARRAY ) yyerror("El identificador debe ser de tipo \"array\"");
                                                else {
                                                    DIM dim = obtTdA(simb.ref);
                                                    (yyval.exp).tipo = dim.telem; /* tipo de los elementos */
                                                    /*GCI*********************/
                                                    (yyval.exp).valor = creaVarTemp();
                                                    emite(EAV, crArgPos(simb.n, simb.d), crArgPos(niv, (yyvsp[-1].exp).valor), crArgPos(niv, (yyval.exp).valor));
                                                }
                                            }
#line 1985 "asin.c"
    break;

  case 62: /* $@10: %empty  */
#line 655 "src/asin.y"
                                            { 
                                                emite(EPUSH, crArgNul(), crArgNul(), crArgEnt(0)); 
                                            }
#line 1993 "asin.c"
    break;

  case 63: /* expresionSufija: ID_ APAR_ $@10 parametrosActuales CPAR_  */
#line 659 "src/asin.y"
                                                                {   
                                                SIMB simb = obtTdS((yyvsp[-4].ident));
                                                INF inf = obtTdD(simb.ref);
                                                (yyval.exp).tipo = T_ERROR;
                                                if(simb.t == T_ERROR) yyerror("Objeto no declarado");
                                                else if(inf.tipo == T_ERROR || simb.t == T_ARRAY) 
                                                    yyerror("Indentificador no es una \"función\"");
                                                else if(!cmpDom(simb.ref, (yyvsp[-1].cent))) {
                                                    /* Dominios no coinciden */
                                                    yyerror("Dominios de \"funcion\" y \"parametros\" no coinciden");
                                                }
                                                else {
                                                    (yyval.exp).tipo = inf.tipo;
                                                    /*GCI*********************/
                                                    emite(CALL, crArgNul(), crArgNul(), crArgEtq(simb.d));
                                                    emite(DECTOP, crArgNul(), crArgNul(), crArgEnt(inf.tsp));
                                                    (yyval.exp).valor = creaVarTemp();
                                                    emite(EPOP, crArgNul(), crArgNul(), crArgPos(niv, (yyval.exp).valor));
                                                }
					                        }
#line 2018 "asin.c"
    break;

  case 64: /* constante: CTE_  */
#line 683 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_ENTERO;
                                                /*GCI*********************/
                                                (yyval.exp).valor = (yyvsp[0].cent); // Valor
                                            }
#line 2028 "asin.c"
    break;

  case 65: /* constante: TRUE_  */
#line 689 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_LOGICO;
                                                /*GCI*********************/
                                                (yyval.exp).valor = 1; // Valor
                                            }
#line 2038 "asin.c"
    break;

  case 66: /* constante: FALSE_  */
#line 695 "src/asin.y"
                                            {
                                                (yyval.exp).tipo = T_LOGICO;
                                                /*GCI*********************/
                                                (yyval.exp).valor = 0; // Valor
                                            }
#line 2048 "asin.c"
    break;

  case 67: /* parametrosActuales: listaParametrosActuales  */
#line 705 "src/asin.y"
                                            { (yyval.cent) = (yyvsp[0].cent); }
#line 2054 "asin.c"
    break;

  case 68: /* parametrosActuales: %empty  */
#line 707 "src/asin.y"
                                            { (yyval.cent) = insTdD(-1, T_VACIO); }
#line 2060 "asin.c"
    break;

  case 69: /* listaParametrosActuales: expresion  */
#line 712 "src/asin.y"
                                            { 
                                            	(yyval.cent) = insTdD(-1, (yyvsp[0].exp).tipo); 
                                                /*GCI*********************/
                                            	emite(EPUSH, crArgNul(), crArgNul(), crArgPos(niv, (yyvsp[0].exp).valor));
                                            }
#line 2070 "asin.c"
    break;

  case 70: /* $@11: %empty  */
#line 718 "src/asin.y"
                                            {
                                                /*GCI*********************/
                                                emite(EPUSH, crArgNul(), crArgNul(), crArgPos(niv, (yyvsp[0].exp).valor));
                                            }
#line 2079 "asin.c"
    break;

  case 71: /* listaParametrosActuales: expresion $@11 COMA_ listaParametrosActuales  */
#line 723 "src/asin.y"
                                            { (yyval.cent) = insTdD((yyvsp[0].cent), (yyvsp[-3].exp).tipo); }
#line 2085 "asin.c"
    break;

  case 72: /* operadorLogico: AND_  */
#line 728 "src/asin.y"
                                            { (yyval.cent) = AND; }
#line 2091 "asin.c"
    break;

  case 73: /* operadorLogico: OR_  */
#line 730 "src/asin.y"
                                            { (yyval.cent) = OR; }
#line 2097 "asin.c"
    break;

  case 74: /* operadorIgualdad: IGUALDAD_  */
#line 735 "src/asin.y"
                                            { (yyval.cent) = EIGUAL; }
#line 2103 "asin.c"
    break;

  case 75: /* operadorIgualdad: DESIGUALDAD_  */
#line 737 "src/asin.y"
                                            { (yyval.cent) = EDIST; }
#line 2109 "asin.c"
    break;

  case 76: /* operadorRelacional: MAYOR_  */
#line 742 "src/asin.y"
                                            { (yyval.cent) = EMAY; }
#line 2115 "asin.c"
    break;

  case 77: /* operadorRelacional: MENOR_  */
#line 744 "src/asin.y"
                                            { (yyval.cent) = EMEN; }
#line 2121 "asin.c"
    break;

  case 78: /* operadorRelacional: MAYORIG_  */
#line 746 "src/asin.y"
                                            { (yyval.cent) = EMAYEQ; }
#line 2127 "asin.c"
    break;

  case 79: /* operadorRelacional: MENORIG_  */
#line 748 "src/asin.y"
                                            { (yyval.cent) = EMENEQ; }
#line 2133 "asin.c"
    break;

  case 80: /* operadorAditivo: MAS_  */
#line 753 "src/asin.y"
                                            { (yyval.cent) = ESUM; }
#line 2139 "asin.c"
    break;

  case 81: /* operadorAditivo: MENOS_  */
#line 755 "src/asin.y"
                                            { (yyval.cent) = EDIF; }
#line 2145 "asin.c"
    break;

  case 82: /* operadorMultiplicativo: MULT_  */
#line 760 "src/asin.y"
                                            { (yyval.cent) = EMULT; }
#line 2151 "asin.c"
    break;

  case 83: /* operadorMultiplicativo: DIV_  */
#line 762 "src/asin.y"
                                            { (yyval.cent) = EDIVI; }
#line 2157 "asin.c"
    break;

  case 84: /* operadorUnario: MAS_  */
#line 767 "src/asin.y"
                                            { (yyval.cent) = ESUM; }
#line 2163 "asin.c"
    break;

  case 85: /* operadorUnario: MENOS_  */
#line 769 "src/asin.y"
                                            { (yyval.cent) = EDIF; }
#line 2169 "asin.c"
    break;

  case 86: /* operadorUnario: NOT_  */
#line 771 "src/asin.y"
                                            { (yyval.cent) = ESIG; }
#line 2175 "asin.c"
    break;


#line 2179 "asin.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 774 "src/asin.y"

