/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 5 "nico.y"

  /* Aqui, pode-se inserir qualquer codigo C necessario ah compilacao
   * final do parser. Sera copiado tal como esta no inicio do y.tab.c
   * gerado por Yacc.
   */
  #include <stdio.h>
  #include <stdlib.h>
  #include "node.h"

  #include "lista.h"
  #include "lista.c"
  #include "symbol_table.h"
  #include "symbol_table.c"


     //Definicoes de tamanho de variaveis e erros
   #define UNDEFINED_SYMBOL_ERROR -21
    #define CHAR_TYPE   0
    #define INT_TYPE    1
    #define REAL_TYPE   2
    #define DOUBLE_TYPE 3

    #define CHAR_SIZE   1
    #define INT_SIZE    4
    #define REAL_SIZE   4
    #define DOUBLE_SIZE 8 

    extern symbol_t symbol_table;
    int tipo_idf = 0;
    int vars_size = 0;
    int temps_size = 0;
    
    char* gera_temp(int type) {
        int size = 0;
        switch (type) {
            case CHAR_TYPE:     size = CHAR_SIZE; break;
            case INT_TYPE:      size = INT_SIZE; break;
            case REAL_TYPE:     size = REAL_SIZE; break;
            case DOUBLE_TYPE:   size = DOUBLE_SIZE; break;
        }
        //TEMP = REGISTRADOR Rx + DESLOCAMENTO DE Rx.
        //ddd(Rx) ddd é o valor da variável temps_size(Tamanho da pilha)
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(Rx)", temps_size);//retorna topo da pilha
        temps_size += size;//incrementa a pilha com o tamanho do tipo
        return ret;
    }
    
    void AddSymbolOnTable(char *lexeme){
    	if(!lookup(symbol_table, lexeme)){//testa se já existe esta entrada na tabela
					
		 entry_t* new_entry=(entry_t *) malloc(sizeof(entry_t));
    		
		    new_entry->name = lexeme;
		    new_entry->type = tipo_idf;
		    new_entry->desloc = vars_size;

		    switch(tipo_idf){
		        	case INT_TYPE:		new_entry->size = INT_SIZE;
						    vars_size += INT_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case DOUBLE_TYPE:	new_entry->size = DOUBLE_SIZE;
						    vars_size += DOUBLE_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case REAL_TYPE:		new_entry->size = REAL_SIZE;
						    vars_size += REAL_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case CHAR_TYPE:		new_entry->size = CHAR_SIZE;
						    vars_size += CHAR_SIZE;
    		//printf("%s %d\n",lexeme,vars_size);
		    }
		    if(insert(&symbol_table, new_entry)){
			    printf("Ocorreu um erro ao alocar o simbolo %s na tabela de simbolos.\n",lexeme);
			    exit(0);
		    }

	}
	    else{
	    	printf("Símbolo %s foi definido múltiplas vezes. \n", lexeme);
			exit(0);		   
	    }
    }
    
 /*
    Essa funcao consulta a tabela atras de um identificador e retorna o conteudo para 
    a string "local" caso o identificador esteja na tabela, caso contrario retorna o proprio identificador
    */
    
	char* lookupOnTable(char* identificador) {
        entry_t* entrada;
        entrada = lookup(symbol_table, identificador);
        if(entrada == NULL)
        return NULL;
        
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(SP)", entrada->desloc);
        return ret;
    }


    /*
    * Cria um nodo auxiliar
    */
    Node* cnode(Node_type t, char* lexeme){
    	return create_node(0, t, lexeme, NULL);
    }     
   



/* Line 268 of yacc.c  */
#line 185 "nico.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDF = 258,
     INT = 259,
     DOUBLE = 260,
     REAL = 261,
     CHAR = 262,
     QUOTE = 263,
     SWAP = 264,
     LE = 265,
     GE = 266,
     EQ = 267,
     NE = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     IF = 272,
     THEN = 273,
     ELSE = 274,
     WHILE = 275,
     INT_LIT = 276,
     F_LIT = 277,
     END = 278,
     TRUE = 279,
     FALSE = 280,
     STRING = 281,
     CONST = 282,
     STR_LIT = 283,
     FOR = 284,
     NEXT = 285,
     PRINTF = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 118 "nico.y"

  char* cadeia;
  struct _node * no;



/* Line 293 of yacc.c  */
#line 259 "nico.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 284 "nico.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  36
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   173

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNRULES -- Number of states.  */
#define YYNSTATES  124

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,    44,    42,    34,    43,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    32,
      47,    41,    46,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    36,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    11,    15,    19,    21,    25,
      27,    29,    31,    33,    35,    37,    42,    47,    52,    57,
      61,    67,    69,    72,    77,    82,    85,    87,    89,    93,
      95,   100,   102,   106,   110,   114,   118,   122,   126,   128,
     130,   132,   134,   139,   147,   155,   157,   161,   163,   165,
     169,   173,   177,   180,   184,   188,   192,   196,   200
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    58,    -1,    58,    -1,    52,    32,
      -1,    51,    52,    32,    -1,    54,    33,    53,    -1,     3,
      -1,     3,    48,    53,    -1,    55,    -1,    56,    -1,     5,
      -1,     6,    -1,     7,    -1,     4,    -1,     4,    37,    57,
      38,    -1,     5,    37,    57,    38,    -1,     6,    37,    57,
      38,    -1,     7,    37,    57,    38,    -1,    21,    33,    21,
      -1,    21,    33,    21,    34,    57,    -1,    59,    -1,    59,
      58,    -1,    61,    41,    63,    32,    -1,    61,     9,    61,
      32,    -1,    63,    32,    -1,    65,    -1,    60,    -1,    31,
      63,    32,    -1,     3,    -1,     3,    35,    62,    36,    -1,
      63,    -1,    63,    34,    62,    -1,    63,    42,    63,    -1,
      63,    43,    63,    -1,    63,    44,    63,    -1,    63,    45,
      63,    -1,    37,    63,    38,    -1,    21,    -1,    22,    -1,
      61,    -1,    64,    -1,     3,    37,    62,    38,    -1,    17,
      37,    67,    38,    18,    58,    66,    -1,    20,    37,    67,
      38,    39,    58,    40,    -1,    23,    -1,    19,    58,    23,
      -1,    24,    -1,    25,    -1,    37,    67,    38,    -1,    67,
      14,    67,    -1,    67,    15,    67,    -1,    16,    67,    -1,
      63,    46,    63,    -1,    63,    47,    63,    -1,    63,    10,
      63,    -1,    63,    11,    63,    -1,    63,    12,    63,    -1,
      63,    13,    63,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   204,   204,   216,   223,   227,   232,   237,   239,   245,
     246,   250,   251,   252,   253,   256,   265,   275,   286,   297,
     306,   318,   323,   334,   353,   379,   386,   388,   392,   407,
     426,   437,   439,   447,   459,   471,   483,   495,   509,   511,
     513,   515,   518,   529,   542,   556,   558,   567,   569,   571,
     580,   589,   594,   599,   604,   609,   614,   619,   624
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDF", "INT", "DOUBLE", "REAL", "CHAR",
  "QUOTE", "SWAP", "LE", "GE", "EQ", "NE", "AND", "OR", "NOT", "IF",
  "THEN", "ELSE", "WHILE", "INT_LIT", "F_LIT", "END", "TRUE", "FALSE",
  "STRING", "CONST", "STR_LIT", "FOR", "NEXT", "PRINTF", "';'", "':'",
  "','", "'['", "']'", "'('", "')'", "'{'", "'}'", "'='", "'+'", "'-'",
  "'*'", "'/'", "'>'", "'<'", "\",\"", "$accept", "code", "declaracoes",
  "declaracao", "listadeclaracao", "tipo", "tipounico", "tipolista",
  "listadupla", "acoes", "comando", "enunciado", "lvalue", "listaexpr",
  "expr", "chamaproc", "bloco", "fiminstcontrole", "expbool", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    59,    58,    44,    91,    93,    40,    41,   123,
     125,    61,    43,    45,    42,    47,    62,    60,   287
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    53,    53,    54,
      54,    55,    55,    55,    55,    56,    56,    56,    56,    57,
      57,    58,    58,    59,    59,    59,    59,    59,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    64,    65,    65,    66,    66,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     2,     3,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     4,     4,     4,     4,     3,
       5,     1,     2,     4,     4,     2,     1,     1,     3,     1,
       4,     1,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     4,     7,     7,     1,     3,     1,     1,     3,
       3,     3,     2,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    29,    14,    11,    12,    13,     0,     0,    38,    39,
       0,     0,     0,     0,     0,     0,     9,    10,     3,    21,
      27,    40,     0,    41,    26,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,     1,     0,     2,     4,
       0,    22,     0,     0,    25,     0,     0,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,     0,     0,     0,    28,    37,     5,     7,     6,    29,
       0,     0,    33,    34,    35,    36,    30,     0,    42,     0,
      15,    16,    17,    18,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,    23,
      32,    19,    49,    55,    56,    57,    58,    53,    54,    50,
      51,     0,     0,     8,     0,     0,     0,    20,     0,    45,
      43,    44,     0,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    13,    14,    68,    15,    16,    17,    53,    18,
      19,    20,    33,    49,    22,    23,    24,   120,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -27
static const yytype_int16 yypact[] =
{
     110,    50,    -9,    -4,     2,    16,    23,    32,   -27,   -27,
      45,    45,    11,   110,    51,    56,   -27,   -27,   -27,    37,
     -27,    -3,   -22,   -27,   -27,    45,    45,    44,    44,    44,
      44,   136,   136,   -27,    77,   106,   -27,    52,   -27,   -27,
      87,   -27,   102,    45,   -27,    45,    45,    45,    45,    71,
     -18,    70,    95,    72,   104,   107,   108,   136,   -27,   -27,
     136,    33,     3,    17,   -27,   -27,   -27,    92,   -27,   124,
     130,   111,    28,    28,   -27,   -27,   -27,    45,   -27,   142,
     -27,   -27,   -27,   -27,   -27,    91,    48,    45,    45,    45,
      45,    45,    45,   136,   136,   146,   126,    87,   -27,   -27,
     -27,   132,   -27,    81,    81,    81,    81,    81,    81,   -27,
     153,    37,    37,   -27,    44,   -11,   128,   -27,    37,   -27,
     -27,   -27,   147,   -27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -27,   -27,   -27,   156,    74,   -27,   -27,   -27,   -26,   -12,
     -27,   -27,     0,   -21,     4,   -27,   -27,   -27,   -23
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      21,    38,    54,    55,    56,    51,    42,    41,   118,    63,
      44,    36,   119,    21,    34,    35,    77,    93,    94,    21,
      45,    46,    47,    48,    45,    46,    47,    48,    27,    50,
      50,    93,    94,    28,    84,    61,    61,    86,    43,    29,
       1,    95,    70,    87,    88,    89,    90,    71,     1,    72,
      73,    74,    75,    30,     6,    96,   100,     7,     8,     9,
      31,    61,    93,    94,    85,    52,     8,     9,    10,    32,
     109,   110,    47,    48,    11,    45,    46,    47,    48,    91,
      92,    50,    11,    39,    66,    25,   102,    26,   117,    40,
      67,   103,   104,   105,   106,   107,   108,    61,    61,   115,
     116,    87,    88,    89,    90,    69,   122,    76,    78,    64,
      80,    21,    21,     1,     2,     3,     4,     5,    21,    45,
      46,    47,    48,    45,    46,    47,    48,     6,    79,    65,
       7,     8,     9,    45,    46,    47,    48,    91,    92,     1,
      97,    10,    81,    99,    65,    82,    83,    11,    45,    46,
      47,    48,    57,    45,    46,    47,    48,     8,     9,    25,
      58,    59,    98,   101,   111,   112,   114,    93,   121,    37,
     123,   113,     0,    60
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-27))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       0,    13,    28,    29,    30,    26,     9,    19,    19,    32,
      32,     0,    23,    13,    10,    11,    34,    14,    15,    19,
      42,    43,    44,    45,    42,    43,    44,    45,    37,    25,
      26,    14,    15,    37,    57,    31,    32,    60,    41,    37,
       3,    38,    42,    10,    11,    12,    13,    43,     3,    45,
      46,    47,    48,    37,    17,    38,    77,    20,    21,    22,
      37,    57,    14,    15,    60,    21,    21,    22,    31,    37,
      93,    94,    44,    45,    37,    42,    43,    44,    45,    46,
      47,    77,    37,    32,    32,    35,    38,    37,   114,    33,
       3,    87,    88,    89,    90,    91,    92,    93,    94,   111,
     112,    10,    11,    12,    13,     3,   118,    36,    38,    32,
      38,   111,   112,     3,     4,     5,     6,     7,   118,    42,
      43,    44,    45,    42,    43,    44,    45,    17,    33,    38,
      20,    21,    22,    42,    43,    44,    45,    46,    47,     3,
      48,    31,    38,    32,    38,    38,    38,    37,    42,    43,
      44,    45,    16,    42,    43,    44,    45,    21,    22,    35,
      24,    25,    32,    21,    18,    39,    34,    14,    40,    13,
      23,    97,    -1,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    17,    20,    21,    22,
      31,    37,    50,    51,    52,    54,    55,    56,    58,    59,
      60,    61,    63,    64,    65,    35,    37,    37,    37,    37,
      37,    37,    37,    61,    63,    63,     0,    52,    58,    32,
      33,    58,     9,    41,    32,    42,    43,    44,    45,    62,
      63,    62,    21,    57,    57,    57,    57,    16,    24,    25,
      37,    63,    67,    67,    32,    38,    32,     3,    53,     3,
      61,    63,    63,    63,    63,    63,    36,    34,    38,    33,
      38,    38,    38,    38,    67,    63,    67,    10,    11,    12,
      13,    46,    47,    14,    15,    38,    38,    48,    32,    32,
      62,    21,    38,    63,    63,    63,    63,    63,    63,    67,
      67,    18,    39,    53,    34,    58,    58,    57,    19,    23,
      66,    40,    58,    23
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 204 "nico.y"
    { 

					(yyval.no) = create_node((yylsp[(1) - (2)]).first_line, code_node, "code", (yyvsp[(1) - (2)].no), (yyvsp[(2) - (2)].no), NULL); 
					cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (2)].no)->code)); //new 

					FILE * out = fopen("teste_raiz", "w"); 
							print_tac(out, (yyval.no)->code);
							fclose(out);

					syntax_tree = (yyval.no);
					}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 216 "nico.y"
    { 
					(yyval.no) = (yyvsp[(1) - (1)].no); 

					syntax_tree = (yyval.no);  
					}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 223 "nico.y"
    { 
					(yyval.no) = create_node((yylsp[(1) - (2)]).first_line, declaracoes_node, "declaracoes", (yyvsp[(1) - (2)].no), cnode(semicolon_node, ";"), NULL); 
					}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 227 "nico.y"
    {					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, declaracoes_node, "declaracoes", (yyvsp[(1) - (3)].no), (yyvsp[(2) - (3)].no), cnode(semicolon_node, ";"), NULL); 
					}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 232 "nico.y"
    {					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, declaracao_node, "declaracao", (yyvsp[(1) - (3)].no), cnode(colon_node, ":"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 237 "nico.y"
    {(yyval.no) = create_node((yylsp[(1) - (1)]).first_line, idf_node, (yyvsp[(1) - (1)].cadeia), NULL); AddSymbolOnTable((yyvsp[(1) - (1)].cadeia));  }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 239 "nico.y"
    {
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, listadeclaracao_node, "listadeclaracao", create_node((yylsp[(1) - (3)]).first_line, idf_node, (yyvsp[(1) - (3)].cadeia), NULL), cnode(comma_node, ","), (yyvsp[(3) - (3)].no), NULL); 
					AddSymbolOnTable((yyvsp[(1) - (3)].cadeia));
					}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 245 "nico.y"
    { (yyval.no) = (yyvsp[(1) - (1)].no); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 246 "nico.y"
    { (yyval.no) = (yyvsp[(1) - (1)].no); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 250 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, double_node, "double", NULL);  tipo_idf = DOUBLE_TYPE;}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 251 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, real_node, "real", NULL); tipo_idf = REAL_TYPE; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 252 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, char_node, "char", NULL);  tipo_idf = CHAR_TYPE; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 253 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, int_node, "int", NULL); tipo_idf = INT_TYPE; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 256 "nico.y"
    {			 	
					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "tipolista"
							, create_node((yylsp[(1) - (4)]).first_line, int_node, "int", NULL)
							, create_node((yylsp[(1) - (4)]).first_line, openpar_node, "(", NULL)
							, (yyvsp[(3) - (4)].no)
							, create_node((yylsp[(1) - (4)]).first_line, closepar_node, ")", NULL)
							, NULL); 
					}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 265 "nico.y"
    {

					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "tipolista"
						, create_node((yylsp[(1) - (4)]).first_line, double_node, "double", NULL)
						, create_node((yylsp[(1) - (4)]).first_line, openpar_node, "(", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, closepar_node, ")", NULL)
						, NULL); 
					}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 275 "nico.y"
    {
 	
					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "tipolista"
						, create_node((yylsp[(1) - (4)]).first_line, real_node, "real", NULL)
						, create_node((yylsp[(1) - (4)]).first_line, openpar_node, "(", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, closepar_node, ")", NULL)
						, NULL); 

					}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 286 "nico.y"
    {
					 	
					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, tipolista_node, "tipolista"
						, create_node((yylsp[(1) - (4)]).first_line, char_node, "char", NULL)
						, create_node((yylsp[(1) - (4)]).first_line, openpar_node, "(", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, closepar_node, ")", NULL)
						, NULL); 
					}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 297 "nico.y"
    {
				
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, listadupla_node, "listadupla"
						, create_node((yylsp[(1) - (3)]).first_line, intlit_node, (yyvsp[(1) - (3)].cadeia), NULL)
						, create_node((yylsp[(1) - (3)]).first_line, colon_node, ":", NULL)
						, create_node((yylsp[(1) - (3)]).first_line, intlit_node, (yyvsp[(3) - (3)].cadeia), NULL)
						, NULL); 
					}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 306 "nico.y"
    { 
							
							(yyval.no) = create_node((yylsp[(1) - (5)]).first_line, listadupla_node, "listadupla"
								, create_node((yylsp[(1) - (5)]).first_line, intlit_node, (yyvsp[(1) - (5)].cadeia), NULL)
								, create_node((yylsp[(1) - (5)]).first_line, colon_node, ":", NULL)
								, create_node((yylsp[(1) - (5)]).first_line, intlit_node, (yyvsp[(3) - (5)].cadeia), NULL)
								, create_node((yylsp[(1) - (5)]).first_line, comma_node, ",", NULL)
								, (yyvsp[(5) - (5)].no)
								, NULL); 
							}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 318 "nico.y"
    {  
	(yyval.no) = (yyvsp[(1) - (1)].no);  	

}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 323 "nico.y"
    {  
				(yyval.no) = create_node((yylsp[(1) - (2)]).first_line, acoes_node, "acoes", (yyvsp[(1) - (2)].no), (yyvsp[(2) - (2)].no), NULL);

							
				cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (2)].no)->code)); //new
             	cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (2)].no)->code)); //new
		
         }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 334 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, comando_node, "comando"
						, (yyvsp[(1) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, atb_node, "=", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, semicolon_node, ";", NULL)
						, NULL); 



					
        			cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (4)].no)->code));

        			struct tac* new_tac = create_inst_tac((yyvsp[(1) - (4)].no)->local,(yyvsp[(3) - (4)].no)->local,"","");        			
			        append_inst_tac(&((yyval.no)->code),new_tac);					

					}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 353 "nico.y"
    {
					 
					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, comando_node, "comando"
						, (yyvsp[(1) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, swap_node, "SWAP", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, semicolon_node, ";", NULL)
						, NULL);


					//A SWAP B:
					//temp = A
					//A = B
					//B = temp
					
					char * temp = gera_temp(INT_TYPE);
                    struct tac* new_tac1 = create_inst_tac(temp,(yyvsp[(1) - (4)].no)->local,"","");
                    struct tac* new_tac2 = create_inst_tac((yyvsp[(1) - (4)].no)->local,(yyvsp[(3) - (4)].no)->local,"","");
                    struct tac* new_tac3 = create_inst_tac((yyvsp[(3) - (4)].no)->local,temp,"","");
                    					
           			append_inst_tac(&((yyval.no)->code),new_tac1);
          			append_inst_tac(&((yyval.no)->code),new_tac2);
           			append_inst_tac(&((yyval.no)->code),new_tac3); 

					}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 379 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (2)]).first_line, comando_node, "comando", (yyvsp[(1) - (2)].no), cnode(semicolon_node, ";"), NULL);
					(yyval.no)->local = (yyvsp[(1) - (2)].no)->local;	
				    cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (2)].no)->code));
					}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 386 "nico.y"
    {  (yyval.no) = (yyvsp[(1) - (1)].no);  }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 388 "nico.y"
    { (yyval.no) = (yyvsp[(1) - (1)].no); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 392 "nico.y"
    { 
							(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, enunciado_node, "enunciado"
							, create_node((yylsp[(1) - (3)]).first_line, printf_node, (yyvsp[(1) - (3)].cadeia), NULL)
							, (yyvsp[(2) - (3)].no)							
							, create_node((yylsp[(1) - (3)]).first_line, semicolon_node, ";", NULL)
							, NULL);

							cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (3)].no)->code));							
							append_inst_tac(&((yyval.no)->code), create_inst_tac("", "","PRINT", (yyvsp[(2) - (3)].no)->local)) ;	

							

						}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 407 "nico.y"
    { 
						

							char *temp = lookupOnTable((yyvsp[(1) - (1)].cadeia));
				                    if(temp) {
										(yyval.no) = create_node((yylsp[(1) - (1)]).first_line, idf_node, (yyvsp[(1) - (1)].cadeia), NULL);                 
								    	(yyval.no)->local = temp;

								    	printf("============= %s\n", temp);
				                    }
				                    else {
						                printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", (yyvsp[(1) - (1)].cadeia));
							            return( UNDEFINED_SYMBOL_ERROR );
								}
						
						
											
				}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 426 "nico.y"
    {
					 
					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, lvalue_node, "lvalue"
						, create_node((yylsp[(1) - (4)]).first_line, idf_node, (yyvsp[(1) - (4)].cadeia), NULL)
						, create_node((yylsp[(1) - (4)]).first_line, openbra_node, "[", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, closebra_node, "]", NULL)
						, NULL); 
					}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 437 "nico.y"
    { (yyval.no) = (yyvsp[(1) - (1)].no); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 439 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, listaexpr_node, "listaexpr", (yyvsp[(1) - (3)].no), cnode(comma_node, ","), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 447 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, "expr", (yyvsp[(1) - (3)].no), cnode(plus_node, "+"), (yyvsp[(3) - (3)].no), NULL); 

					(yyval.no)->local = gera_temp(INT_TYPE);
				   struct tac* new_tac = create_inst_tac((yyval.no)->local,(yyvsp[(1) - (3)].no)->local,"ADD",(yyvsp[(3) - (3)].no)->local);
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			    append_inst_tac(&((yyval.no)->code),new_tac);

					}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 459 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, "expr", (yyvsp[(1) - (3)].no), cnode(minus_node, "-"), (yyvsp[(3) - (3)].no), NULL); 

					(yyval.no)->local = gera_temp(INT_TYPE);
				    struct tac* new_tac = create_inst_tac((yyval.no)->local,(yyvsp[(1) - (3)].no)->local,"SUB",(yyvsp[(3) - (3)].no)->local);
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			    append_inst_tac(&((yyval.no)->code),new_tac);

   					}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 471 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, "expr", (yyvsp[(1) - (3)].no), cnode(mult_node, "*"), (yyvsp[(3) - (3)].no), NULL); 

					(yyval.no)->local = gera_temp(INT_TYPE);
				    struct tac* new_tac = create_inst_tac((yyval.no)->local,(yyvsp[(1) - (3)].no)->local,"MUL",(yyvsp[(3) - (3)].no)->local);
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			    append_inst_tac(&((yyval.no)->code),new_tac);

					}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 483 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, "expr", (yyvsp[(1) - (3)].no), cnode(div_node, "/"), (yyvsp[(3) - (3)].no), NULL);

					(yyval.no)->local = gera_temp(INT_TYPE);
				    struct tac* new_tac = create_inst_tac((yyval.no)->local,(yyvsp[(1) - (3)].no)->local,"DIV",(yyvsp[(3) - (3)].no)->local);
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(1) - (3)].no)->code));
       			    cat_tac(&((yyval.no)->code), &((yyvsp[(3) - (3)].no)->code));
       			    append_inst_tac(&((yyval.no)->code),new_tac);  

					}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 495 "nico.y"
    {
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expr_node, "expr"
						, create_node((yylsp[(1) - (3)]).first_line, openpar_node, "(", NULL)
						, (yyvsp[(2) - (3)].no)
						, create_node((yylsp[(1) - (3)]).first_line, closepar_node, ")", NULL)
						, NULL); 


					//TAC
					(yyval.no)->local = (yyvsp[(2) - (3)].no)->local;	 
               		cat_tac(&((yyval.no)->code), &((yyvsp[(2) - (3)].no)->code));
					}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 509 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, intlit_node, (yyvsp[(1) - (1)].cadeia), NULL); (yyval.no)->local = (yyvsp[(1) - (1)].cadeia) ;}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 511 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, flit_node, (yyvsp[(1) - (1)].cadeia), NULL); (yyval.no)->local = (yyvsp[(1) - (1)].cadeia) ;}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 513 "nico.y"
    { (yyval.no) = (yyvsp[(1) - (1)].no); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 515 "nico.y"
    { (yyval.no) = (yyvsp[(1) - (1)].no); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 518 "nico.y"
    {

					(yyval.no) = create_node((yylsp[(1) - (4)]).first_line, chamaproc_node, "chamaproc"
						, create_node((yylsp[(1) - (4)]).first_line, idf_node, (yyvsp[(1) - (4)].cadeia), NULL)
						, create_node((yylsp[(1) - (4)]).first_line, openpar_node, "(", NULL)
						, (yyvsp[(3) - (4)].no)
						, create_node((yylsp[(1) - (4)]).first_line, closepar_node, ")", NULL)
						, NULL); 
					}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 529 "nico.y"
    {
												 					
							(yyval.no) = create_node((yylsp[(1) - (7)]).first_line, bloco_node, "bloco"
								, create_node((yylsp[(1) - (7)]).first_line, if_node, "IF", NULL)
								, create_node((yylsp[(1) - (7)]).first_line, openpar_node, "(", NULL)
								, (yyvsp[(3) - (7)].no)
								, create_node((yylsp[(1) - (7)]).first_line, closepar_node, ")", NULL)
								, create_node((yylsp[(1) - (7)]).first_line, then_node, "THEN", NULL)
								, (yyvsp[(6) - (7)].no)
								, (yyvsp[(7) - (7)].no)
								, NULL); 
							}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 542 "nico.y"
    {
											 						
							(yyval.no) = create_node((yylsp[(1) - (7)]).first_line, bloco_node, "bloco"
								, create_node((yylsp[(1) - (7)]).first_line, while_node, "WHILE", NULL)
								, create_node((yylsp[(1) - (7)]).first_line, openpar_node, "(", NULL)
								, (yyvsp[(3) - (7)].no)
								, create_node((yylsp[(1) - (7)]).first_line, closepar_node, ")", NULL)
								, create_node((yylsp[(1) - (7)]).first_line, opencur_node, "{", NULL)
								, (yyvsp[(6) - (7)].no)
								, create_node((yylsp[(1) - (7)]).first_line, closecur_node, "}", NULL)
								, NULL); 
							}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 556 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, end_node, "END", NULL); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 558 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, fiminstcontrole_node, "fiminstcontrole"
						, create_node((yylsp[(1) - (3)]).first_line, else_node, "ELSE", NULL)
						, (yyvsp[(2) - (3)].no)
						, create_node((yylsp[(1) - (3)]).first_line, end_node, "END", NULL)
						, NULL); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 567 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, true_node, "true", NULL); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 569 "nico.y"
    { (yyval.no) = create_node((yylsp[(1) - (1)]).first_line, false_node, "false", NULL); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 571 "nico.y"
    {
														
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool"
						, create_node((yylsp[(1) - (3)]).first_line, openpar_node, "(", NULL)
						, (yyvsp[(2) - (3)].no)
						, create_node((yylsp[(1) - (3)]).first_line, closepar_node, ")", NULL)
						, NULL); 
					}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 580 "nico.y"
    { 
							
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool"
						, (yyvsp[(1) - (3)].no)
						, create_node((yylsp[(1) - (3)]).first_line, and_node, "AND", NULL)
						, (yyvsp[(3) - (3)].no)
						, NULL); 
					}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 589 "nico.y"
    { 
								
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(or_node, "GE"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 594 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (2)]).first_line, expbool_node, "expbool", cnode(not_node, "NOT"), (yyvsp[(2) - (2)].no), NULL); 
					}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 599 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(greater_node, ">"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 604 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(less_node, "<"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 609 "nico.y"
    { 
							
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(le_node, "GE"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 614 "nico.y"
    { 
					(yyvsp[(2) - (3)].cadeia) = create_node((yylsp[(1) - (3)]).first_line, ge_node, "GE", NULL);			
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(ge_node, "GE"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 619 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(eq_node, "EQ"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 624 "nico.y"
    { 
					
					(yyval.no) = create_node((yylsp[(1) - (3)]).first_line, expbool_node, "expbool", (yyvsp[(1) - (3)].no), cnode(ne_node, "NE"), (yyvsp[(3) - (3)].no), NULL); 
					}
    break;



/* Line 1806 of yacc.c  */
#line 2357 "nico.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 631 "nico.y"
