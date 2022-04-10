/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "Syntax.y"

/*
Date: 2020.12.28
Author: XODRJH
*/
#define YYSTYPE std::string
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
using namespace std;


/* ********************* 变量声明部分 ********************* */
FILE *fi;  								//指向输出文件的指针
FILE *fh;  								//指向输出层次结构的指针
FILE *ft;  								//指向临时文件的指针
extern FILE *fw;						//指向词法输出文件的指针
fstream fp;  							//指向输出middlecode文件的指针
fstream fq;  							//指向输出middlecode(四元式)文件的指针
fstream fs;								//指向符号表输出文件的指针
extern int row_num, col_num;  			//行数和列数
extern char key[15];					//识别的token

typedef struct node{
	char* data;
	struct node* left;
	struct node* right;
}Node;									//树节点（左孩子-右兄弟）

#define maxsize 50
typedef Node* elem;

typedef struct{
	Node* root;
}Tree;									//树

typedef struct{
	int top;
	elem index[maxsize];
}Stack;									//符号栈

Stack _stack;
Tree tree;

struct symbol {							//符号表一个元素 
	string name;						//变量名
	string type;						//变量类型(void, int, *)
	string property;					//变量属性(func, var)
	int num;							//func的参数个数
};

map<string, map<string, symbol> > st; 	//符号表(函数名->变量名->变量信息)
string current_st = "#";				//当前所处函数域的函数名(#为全局)
int T_num;								//产生临时变量
stack<int> truestack, falsestack;		//true栈和false栈
vector<string> code;					//输出的中间代码
vector<string> code_qua;				//输出的中间代码(四元式)


/* ********************* 函数声明部分 ********************* */
int yylex();
int yyerror(char *s);
void Process(char* temp);				//移进
void left_insert(Node* parent, Node* son);	//son-parent
void right_insert(Node* node, Node* bro);	//node-brother
void stack_init();						//初始化符号栈
elem stack_pop();						//出栈
void stack_push(elem p);				//进栈
void PreOrderTravel(Node* T, int k);	//先序遍历树T，k表示层数
void Reduce(char* name, int num);		//规约

void symbol_table_init();				//初始化符号表
bool is_defined(string name);			//判断符号是否被定义（在当前函数和全局中搜索）
bool is_defined_local(string name);		//判断符号在当前函数中是否被定义
bool is_defined_global(string name);	//判断符号在全局表中是否被定义
void define_var(string name, string type);			//定义变量
void define_func(string name, string type, int num);//定义函数
string newtemp();						//获取新的临时变量（T0,T1,...）
void backpatch(stack<int> &S);			//回填
void emit(string content1, string content2);		//产生中间代码
void Output();							//输出符号表和中间代码到文件



/* Line 371 of yacc.c  */
#line 161 "Syntax.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "Syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     NUM = 259,
     PLUS = 260,
     MINUS = 261,
     MUL = 262,
     DIV = 263,
     LESSEQUAL = 264,
     LESS = 265,
     GREATEREQUAL = 266,
     GREATER = 267,
     EQUAL = 268,
     NOTEQUAL = 269,
     CONST = 270,
     ELSE = 271,
     IF = 272,
     INT = 273,
     RETURN = 274,
     VOID = 275,
     WHILE = 276,
     LSPAREN = 277,
     RSPAREN = 278,
     LMPAREN = 279,
     RMPAREN = 280,
     LBPAREN = 281,
     RBPAREN = 282,
     COMMA = 283,
     SEMI = 284
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 256 "Syntax.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   99

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    25,
      27,    29,    30,    37,    39,    41,    43,    47,    49,    52,
      57,    62,    65,    66,    69,    70,    72,    74,    76,    78,
      80,    83,    85,    86,    87,    96,    97,   101,   102,   103,
     104,   112,   115,   119,   123,   125,   127,   132,   136,   138,
     140,   142,   144,   146,   148,   150,   154,   156,   158,   160,
     164,   166,   168,   170,   174,   176,   178,   180,   185,   187,
     188,   192
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      31,     0,    -1,    32,    -1,    32,    33,    -1,    33,    -1,
      34,    -1,    36,    -1,    35,     3,    29,    -1,    35,     3,
      24,     4,    25,    29,    -1,    18,    -1,    20,    -1,    -1,
      35,     3,    37,    22,    38,    23,    -1,    41,    -1,    39,
      -1,    20,    -1,    39,    28,    40,    -1,    40,    -1,    35,
       3,    -1,    35,     3,    24,    25,    -1,    26,    42,    43,
      27,    -1,    42,    34,    -1,    -1,    43,    44,    -1,    -1,
      45,    -1,    41,    -1,    46,    -1,    51,    -1,    54,    -1,
      55,    29,    -1,    29,    -1,    -1,    -1,    17,    22,    55,
      23,    47,    44,    48,    49,    -1,    -1,    16,    50,    44,
      -1,    -1,    -1,    -1,    21,    22,    52,    55,    23,    53,
      44,    -1,    19,    29,    -1,    19,    55,    29,    -1,    56,
      15,    55,    -1,    57,    -1,     3,    -1,     3,    24,    55,
      25,    -1,    59,    58,    59,    -1,    59,    -1,     9,    -1,
      10,    -1,    12,    -1,    11,    -1,    13,    -1,    14,    -1,
      59,    60,    61,    -1,    61,    -1,     5,    -1,     6,    -1,
      61,    62,    63,    -1,    63,    -1,     7,    -1,     8,    -1,
      22,    55,    23,    -1,    56,    -1,    64,    -1,     4,    -1,
       3,    22,    65,    23,    -1,    66,    -1,    -1,    66,    28,
      55,    -1,    55,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   126,   130,   136,   140,   146,   157,   170,
     175,   182,   182,   200,   207,   212,   219,   224,   231,   240,
     253,   259,   263,   269,   273,   279,   283,   287,   291,   295,
     301,   305,   311,   317,   311,   327,   327,   335,   343,   346,
     343,   362,   367,   374,   380,   387,   396,   407,   413,   420,
     425,   430,   435,   440,   445,   452,   458,   465,   470,   477,
     483,   490,   495,   502,   507,   512,   517,   524,   536,   547,
     553,   558
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUM", "PLUS", "MINUS", "MUL",
  "DIV", "LESSEQUAL", "LESS", "GREATEREQUAL", "GREATER", "EQUAL",
  "NOTEQUAL", "CONST", "ELSE", "IF", "INT", "RETURN", "VOID", "WHILE",
  "LSPAREN", "RSPAREN", "LMPAREN", "RMPAREN", "LBPAREN", "RBPAREN",
  "COMMA", "SEMI", "$accept", "program", "declaration-list", "declaration",
  "var-declaration", "type-specifier", "fun-declaration", "$@1", "params",
  "params-list", "param", "compound-stmt", "local-declarations",
  "statement-list", "statement", "expression-stmt", "selection-stmt",
  "$@2", "$@3", "selection-stmts", "$@4", "iteration-stmt", "$@5", "$@6",
  "return-stmt", "expression", "var", "simple-expression", "relop",
  "additive-expression", "addop", "term", "mulop", "factor", "call",
  "args", "arg-list", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    34,    34,    35,
      35,    37,    36,    36,    38,    38,    39,    39,    40,    40,
      41,    42,    42,    43,    43,    44,    44,    44,    44,    44,
      45,    45,    47,    48,    46,    50,    49,    49,    52,    53,
      51,    54,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    63,    64,    65,    65,
      66,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     0,     6,     1,     1,     1,     3,     1,     2,     4,
       4,     2,     0,     2,     0,     1,     1,     1,     1,     1,
       2,     1,     0,     0,     8,     0,     3,     0,     0,     0,
       7,     2,     3,     3,     1,     1,     4,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     4,     1,     0,
       3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,    22,     0,     2,     4,     5,     0,     6,
      13,    24,     1,     3,    11,    21,     0,     0,     0,     7,
       0,     0,    45,    66,     0,     0,     0,     0,    20,    31,
      26,    23,    25,    27,    28,    29,     0,    64,    44,    48,
      56,    60,    65,     0,     0,    69,     0,     0,    41,     0,
      38,     0,    30,     0,    57,    58,    49,    50,    52,    51,
      53,    54,     0,     0,    61,    62,     0,     0,    10,     0,
       0,    14,    17,    71,     0,    68,     0,     0,    42,     0,
      63,    43,    64,    47,    55,    59,     8,    18,    12,     0,
      67,     0,    46,    32,     0,     0,    16,    70,     0,    39,
      19,    33,     0,    37,    40,    35,    34,     0,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    20,    70,    71,
      72,    30,    11,    17,    31,    32,    33,    98,   103,   106,
     107,    34,    79,   102,    35,    36,    37,    38,    62,    39,
      63,    40,    66,    41,    42,    74,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int8 yypact[] =
{
      -2,   -89,   -89,   -89,    11,    -2,   -89,   -89,     2,   -89,
     -89,   -16,   -89,   -89,    -9,   -89,    14,     9,    33,   -89,
      20,    -9,    46,   -89,    31,     3,    35,     5,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -89,    45,    49,   -89,    38,
      65,   -89,   -89,    50,    51,     5,     5,     5,   -89,    47,
     -89,    54,   -89,     5,   -89,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,     5,     5,   -89,   -89,     5,    52,    56,    57,
      59,    55,   -89,   -89,    61,    58,    60,    64,   -89,     5,
     -89,   -89,   -89,    40,    65,   -89,   -89,    66,   -89,   -16,
     -89,     5,   -89,   -89,    68,    63,   -89,   -89,    37,   -89,
     -89,   -89,    37,    73,   -89,   -89,   -89,    37,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -89,   -89,   -89,    75,    81,   -11,   -89,   -89,   -89,   -89,
       4,    34,   -89,   -89,   -88,   -89,   -89,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,   -89,   -24,    -1,   -89,   -89,    32,
     -89,    36,   -89,    29,   -89,   -89,   -89
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int8 yytable[] =
{
      16,    49,     1,    51,     2,    14,    22,    23,    22,    23,
     101,    12,    22,    23,   104,    18,     1,    21,     2,   108,
      19,    73,    76,    77,     3,    27,    24,    27,    25,    81,
      26,    27,    48,    69,    10,     3,    28,    43,    29,    10,
      22,    23,    44,    54,    55,    54,    55,    56,    57,    58,
      59,    60,    61,    47,    24,    94,    25,    50,    26,    27,
      87,    82,    82,     3,    53,    82,    29,    97,    45,     1,
      46,    68,    64,    65,    52,    67,    78,    80,    69,   -15,
      13,    86,    88,    89,    90,    92,    91,    93,   100,   105,
      95,    99,    15,    96,    83,    85,     0,     0,     0,    84
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      11,    25,    18,    27,    20,     3,     3,     4,     3,     4,
      98,     0,     3,     4,   102,    24,    18,     3,    20,   107,
      29,    45,    46,    47,    26,    22,    17,    22,    19,    53,
      21,    22,    29,    44,     0,    26,    27,     4,    29,     5,
       3,     4,    22,     5,     6,     5,     6,     9,    10,    11,
      12,    13,    14,    22,    17,    79,    19,    22,    21,    22,
       3,    62,    63,    26,    15,    66,    29,    91,    22,    18,
      24,    20,     7,     8,    29,    25,    29,    23,    89,    23,
       5,    29,    23,    28,    23,    25,    28,    23,    25,    16,
      24,    23,    11,    89,    62,    66,    -1,    -1,    -1,    63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    20,    26,    31,    32,    33,    34,    35,    36,
      41,    42,     0,    33,     3,    34,    35,    43,    24,    29,
      37,     3,     3,     4,    17,    19,    21,    22,    27,    29,
      41,    44,    45,    46,    51,    54,    55,    56,    57,    59,
      61,    63,    64,     4,    22,    22,    24,    22,    29,    55,
      22,    55,    29,    15,     5,     6,     9,    10,    11,    12,
      13,    14,    58,    60,     7,     8,    62,    25,    20,    35,
      38,    39,    40,    55,    65,    66,    55,    55,    29,    52,
      23,    55,    56,    59,    61,    63,    29,     3,    23,    28,
      23,    28,    25,    23,    55,    24,    40,    55,    47,    23,
      25,    44,    53,    48,    44,    16,    49,    50,    44
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

    Process(key);                      YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 118 "Syntax.y"
    {
							fprintf(fi, "program -> declaration-list\n");
							Reduce("program", 1);
							tree.root = stack_pop();
							PreOrderTravel(tree.root, 0);
						}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 126 "Syntax.y"
    {
							fprintf(fi, "declaration-list -> declaration-list declaration\n"); 
							Reduce("declaration-list", 2);
						}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 130 "Syntax.y"
    {
							fprintf(fi, "declaration-list -> declaration\n"); 
							Reduce("declaration-list", 1);
						}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 136 "Syntax.y"
    {
							fprintf(fi, "declaration -> var-declaration\n"); 
							Reduce("declaration", 1);
						}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 140 "Syntax.y"
    {
							fprintf(fi, "declaration -> fun-declaration\n"); 
							Reduce("declaration", 1);
						}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 146 "Syntax.y"
    {
							if(is_defined_local((yyvsp[(2) - (3)]))) {
								cout << "ERROR: ID '" << (yyvsp[(2) - (3)]) << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)]));
							}
							fprintf(fi, "var-declaration -> type-specifier ID ;\n"); 
							Reduce("var-declaration", 3);
						}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 157 "Syntax.y"
    {
							if(is_defined_local((yyvsp[(2) - (6)]))) {
								cout << "ERROR: ID '" << (yyvsp[(2) - (6)]) << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var((yyvsp[(2) - (6)]), (yyvsp[(1) - (6)]));
							}
							fprintf(fi, "var-declaration -> type-specifier ID [ NUM ] ;\n"); 
							Reduce("var-declaration", 6);
						}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 170 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "type-specifier -> INT\n"); 
							Reduce("type-specifier", 1);
						}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 175 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "type-specifier -> VOID\n");
							Reduce("type-specifier", 1);
						}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 182 "Syntax.y"
    {
							current_st = (yyvsp[(2) - (2)]);
						}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 185 "Syntax.y"
    {
							int temp_num = stoi((yyvsp[(5) - (6)]));
							if(is_defined_global((yyvsp[(2) - (6)]))) {
								if(st[current_st][(yyvsp[(2) - (6)])].num == temp_num) {
									cout << "ERROR: FUNC '" << (yyvsp[(2) - (6)]) << "' has been defined! (" << row_num << ", " << col_num << ")\n";
									exit(0);
								}
							}
							else {
								define_func((yyvsp[(2) - (6)]), (yyvsp[(1) - (6)]), temp_num);
							}
							emit("Prog " + (yyvsp[(2) - (6)]), "(Prog, -, -, " + (yyvsp[(2) - (6)]));
							fprintf(fi, "fun-declaration -> type-specifier ID ( params )\n"); 
							Reduce("fun-declaration", 5);
						}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 200 "Syntax.y"
    {
							current_st = "#";
							fprintf(fi, "fun-declaration -> compound-stmt\n"); 
							Reduce("fun-declaration", 1);
						}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 207 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "params -> params-list\n"); 
							Reduce("params", 1);
						}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 212 "Syntax.y"
    {
							(yyval) = "0";
							fprintf(fi, "params -> VOID\n"); 
							Reduce("params", 1);
						}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 219 "Syntax.y"
    {
							(yyval) = to_string(stoi((yyvsp[(1) - (3)])) + 1);
							fprintf(fi, "params-list -> params-list , param\n"); 
							Reduce("params-list", 3);
						}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 224 "Syntax.y"
    {
							(yyval) = "1";
							fprintf(fi, "params-list -> param\n"); 
							Reduce("params-list", 1);
						}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 231 "Syntax.y"
    {
							if(is_defined_local((yyvsp[(2) - (2)]))) {
								cout << "ERROR: ID '" << (yyvsp[(2) - (2)]) << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var((yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]));
							}
						}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 240 "Syntax.y"
    {
							if(is_defined_local((yyvsp[(2) - (4)]))) {
								cout << "ERROR: ID '" << (yyvsp[(2) - (4)]) << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var((yyvsp[(2) - (4)]), (yyvsp[(1) - (4)]));
							}
							fprintf(fi, "param -> type-specifier ID [ ]\n"); 
							Reduce("param", 4);
						}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 253 "Syntax.y"
    {
							fprintf(fi, "compound-stmt -> { local-declarations statement-list }\n"); 
							Reduce("compound-stmt", 4);
						}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 259 "Syntax.y"
    {
							fprintf(fi, "local-declarations -> local-declarations var-declaration\n"); 
							Reduce("local-declarations", 2);
						}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 263 "Syntax.y"
    {
							fprintf(fi, "local-declarations -> empty\n"); 
							Reduce("local-declarations", 0);
						}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 269 "Syntax.y"
    {
							fprintf(fi, "statement-list -> statement-list statement\n"); 
							Reduce("statement-list", 2);
						}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 273 "Syntax.y"
    {
							fprintf(fi, "statement-list -> empty\n"); 
							Reduce("statement-list", 0);
						}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 279 "Syntax.y"
    {
							fprintf(fi, "statement -> expression-stmt\n"); 
							Reduce("statement", 1);
						}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 283 "Syntax.y"
    {
							fprintf(fi, "statement -> compound-stmt\n"); 
							Reduce("statement", 1);
						}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 287 "Syntax.y"
    {
							fprintf(fi, "statement -> selection-stmt\n"); 
							Reduce("statement", 1);
						}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 291 "Syntax.y"
    {
							fprintf(fi, "statement -> iteration-stmt\n"); 
							Reduce("statement", 1);
						}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 295 "Syntax.y"
    {
							fprintf(fi, "statement -> return-stmt\n"); 
							Reduce("statement", 1);
						}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 301 "Syntax.y"
    {
							fprintf(fi, "expression-stmt -> expression ;\n"); 
							Reduce("expression-stmt", 2);	
						}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 305 "Syntax.y"
    {
							fprintf(fi, "expression-stmt -> ;\n"); 
							Reduce("expression-stmt", 1);
						}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 311 "Syntax.y"
    {
							string dest = to_string(code.size() + 102);
							emit("if " + (yyvsp[(3) - (4)]) + "==1 Goto " + dest, "(jnz, " + (yyvsp[(3) - (4)]) + ", -, " + dest);
							falsestack.push(code.size());
							emit("Goto ", "(j, -, -, ");
						}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 317 "Syntax.y"
    {
							truestack.push(code.size());
							emit("Goto ", "(j, -, -, ");
						}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 321 "Syntax.y"
    {
							fprintf(fi, "selection-stmt -> IF ( expression ) statement selection-stmts\n"); 
							Reduce("selection-stmt", 6);
						}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 327 "Syntax.y"
    {
							backpatch(falsestack);
						}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 330 "Syntax.y"
    {
							backpatch(truestack);
							fprintf(fi, "selection-stmts -> ELSE statement\n"); 
							Reduce("selection-stmts", 2);
						}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 335 "Syntax.y"
    {
							backpatch(falsestack);
							backpatch(truestack);
							fprintf(fi, "selection-stmts -> empty\n");
							Reduce("selection-stmts", 0);
						}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 343 "Syntax.y"
    {
							truestack.push(code.size());
						}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 346 "Syntax.y"
    {
							string dest = to_string(code.size() + 102);
							emit("if " + (yyvsp[(4) - (5)]) + "==1 Goto " + dest, "(jnz, " + (yyvsp[(4) - (5)]) + ", -, " + dest);
							falsestack.push(code.size());
							emit("Goto ", "(j, -, -, ");
						}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 352 "Syntax.y"
    {
							string dest = to_string(truestack.top() + 100);
							truestack.pop();
							emit("Goto " + dest, "(j, -, -, " + dest);
							backpatch(falsestack);
							fprintf(fi, "iteration-stmt -> WHILE ( expression ) statement\n"); 
							Reduce("iteration-stmt", 5);
						}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 362 "Syntax.y"
    {
							emit("return", "(ret, -, -, -");
							fprintf(fi, "return-stmt -> return ;\n"); 
							Reduce("return-stmt", 2);
						}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 367 "Syntax.y"
    {
							emit("return " + (yyvsp[(2) - (3)]), "(ret, -, -, " + (yyvsp[(2) - (3)]));
							fprintf(fi, "return-stmt -> RETURN expression ;\n"); 
							Reduce("return-stmt", 3);
						}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 374 "Syntax.y"
    {
							emit((yyvsp[(1) - (3)]) + " := " + (yyvsp[(3) - (3)]), "(:=, " + (yyvsp[(3) - (3)]) + ", -, " + (yyvsp[(1) - (3)]));
							(yyvsp[(1) - (3)]) = (yyvsp[(3) - (3)]);
							fprintf(fi, "expression -> var = expression\n"); 
							Reduce("expression", 3);
						}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 380 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "expression -> simple-expression\n"); 
							Reduce("expression", 1);
						}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 387 "Syntax.y"
    {
							if(!is_defined((yyvsp[(1) - (1)]))) {
								cout << "ERROR: ID '" << (yyvsp[(1) - (1)]) << "' has not been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							(yyval) = (yyvsp[(1) - (1)]); 
							fprintf(fi, "var -> ID\n"); 
							Reduce("var", 1);
						}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 396 "Syntax.y"
    {
							if(!is_defined((yyvsp[(1) - (4)]))) {
								cout << "ERROR: ID '" << (yyvsp[(1) - (4)]) << "' has not been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							(yyval) = (yyvsp[(1) - (4)]) + "[" + (yyvsp[(3) - (4)]) + "]";
							fprintf(fi, "var -> ID [ expression ]\n"); 
							Reduce("var", 4);
						}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 407 "Syntax.y"
    {
							(yyval) = newtemp();
							emit((yyval) + " := " + (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + " " + (yyvsp[(3) - (3)]), "(" + (yyvsp[(2) - (3)]) + ", " + (yyvsp[(1) - (3)]) + ", " + (yyvsp[(3) - (3)]) + ", " + (yyval));
							fprintf(fi, "simple-expression -> additive-expression relop additive-expression\n"); 
							Reduce("simple-expression", 3);
						}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 413 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "simple-expression -> additive-expression\n"); 
							Reduce("simple-expression", 1);
						}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 420 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "relop -> <=\n"); 
							Reduce("relop", 1);
						}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 425 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]); 
							fprintf(fi, "relop -> <\n"); 
							Reduce("relop", 1);
						}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 430 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "relop -> >\n"); 
							Reduce("relop", 1);
						}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 435 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]); 
							fprintf(fi, "relop -> >=\n"); 
							Reduce("relop", 1);
						}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 440 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]); 
							fprintf(fi, "relop -> ==\n"); 
							Reduce("relop", 1);
						}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 445 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "relop -> !=\n"); 
							Reduce("relop", 1);
						}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 452 "Syntax.y"
    {
							(yyval) = newtemp();
							emit((yyval) + " := " + (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + " " + (yyvsp[(3) - (3)]), "(" + (yyvsp[(2) - (3)]) + ", " + (yyvsp[(1) - (3)]) + ", " + (yyvsp[(3) - (3)]) + ", " + (yyval));
							fprintf(fi, "additive-expression -> additive-expression addop term\n"); 
							Reduce("additive-expression", 3);
						}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 458 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]); 
							fprintf(fi, "additive-expression -> term\n"); 
							Reduce("additive-expression", 1);
						}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 465 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "addop -> +\n"); 
							Reduce("addop", 1);
						}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 470 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "addop -> -\n"); 
							Reduce("addop", 1);
						}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 477 "Syntax.y"
    {
							(yyval) = newtemp();
							emit((yyval) + " := " + (yyvsp[(1) - (3)]) + " " + (yyvsp[(2) - (3)]) + " " + (yyvsp[(3) - (3)]), "(" + (yyvsp[(2) - (3)]) + ", " + (yyvsp[(1) - (3)]) + ", " + (yyvsp[(3) - (3)]) + ", " + (yyval));
							fprintf(fi, "term -> term mulop factor\n"); 
							Reduce("term", 3);
						}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 483 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "term -> factor\n"); 
							Reduce("term", 1);
						}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 490 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "mulop -> *\n"); 
							Reduce("mulop", 1);
						}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 495 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "mulop -> /\n"); 
							Reduce("mulop", 1);
						}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 502 "Syntax.y"
    {
							(yyval) = (yyvsp[(2) - (3)]);
							fprintf(fi, "factor -> ( expression )\n"); 
							Reduce("factor", 3);
						}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 507 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "factor -> var\n"); 
							Reduce("factor", 1);
						}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 512 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "factor -> call\n"); 
							Reduce("factor", 1);
						}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 517 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "factor -> NUM\n"); 
							Reduce("factor", 1);
						}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 524 "Syntax.y"
    {
							if(!is_defined((yyvsp[(1) - (4)]))) {
								cout << "ERROR: ID '" << (yyvsp[(1) - (4)]) << "' hasn't been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							(yyval) = newtemp();
							emit((yyval) + " := " + "call " + (yyvsp[(1) - (4)]), "(call, " + (yyvsp[(1) - (4)]) + ", -, " + (yyval));
							fprintf(fi, "call -> ID ( args )\n"); 
							Reduce("call", 4);
						}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 536 "Syntax.y"
    {
							const char *split = ",";
							char *p = strtok((char *)(yyvsp[(1) - (1)]).c_str(), split);
							while( p != NULL )
							{
								emit((string)"param " + p, (string)"(param, -, -, " + p);
								p = strtok(NULL,split);
							}
							fprintf(fi, "args -> arg-list\n"); 
							Reduce("args", 1);
						}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 547 "Syntax.y"
    {
							fprintf(fi, "args -> empty\n"); 
							Reduce("args", 0);
						}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 553 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (3)]) + "," + (yyvsp[(3) - (3)]);
							fprintf(fi, "arg-list -> arg-list , expression\n"); 
							Reduce("arg-list", 3);
						}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 558 "Syntax.y"
    {
							(yyval) = (yyvsp[(1) - (1)]);
							fprintf(fi, "arg-list -> expression\n"); 
							Reduce("arg-list", 1);
						}
    break;


/* Line 1792 of yacc.c  */
#line 2284 "Syntax.tab.c"
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 564 "Syntax.y"
 

int main(){
	//yydebug = 1;
    fw = fopen("output/token.txt", "w+");
    fi = fopen("output/reduce.txt", "w+");
    fh = fopen("output/hierarchy.txt", "w+");
	ft = fopen("output/trush.txt", "w+");
	fp.open("output/middlecode.txt", ios::out);
	fq.open("output/middlecode_qua.txt", ios::out);
	fs.open("output/symboltable.txt", ios::out);
    stack_init();
	symbol_table_init();

    yyparse();

	Output();
	
	fclose(fi);
	fclose(fh);
	fclose(ft);
	fp.close();
	fq.close();
	fs.close();

    return 1;
}

int yyerror(char *s){
    printf("%s, (%d,%d)\n", s, row_num, col_num);
    return 1;
}



/* ********************* Tree 操作 ********************* */
//添加son
void left_insert(Node* parent, Node* son){
	parent -> left = son;
}

//添加brother
void right_insert(Node* node, Node* bro){
	node -> right = bro;
}



/* ********************* 符号栈 操作 ********************* */
//初始化符号栈
void stack_init(){
	_stack.top = -1;
}


//出栈
elem stack_pop(){
	int i;
	if(_stack.top == -1){
		printf("Overflow stack pop size.\n");
		return 0;
	}
	return _stack.index[_stack.top --];
}


//进栈
void stack_push(elem p){
	_stack.index[++_stack.top] = p;
}


//先序遍历，T表示树，k表示层数
void PreOrderTravel(Node* T, int k){
	if(T==NULL) return;
	fprintf(fh, "%2d:|\t", k);
	for(int i=0; i<k-1; i++) fprintf(fh, "|\t");
	fprintf(fh, "%s\n",T->data);
	PreOrderTravel(T->left, k+1);
	PreOrderTravel(T->right, k);
}



//移进
void Process(char* temp){
	Node* tnode = (Node*)malloc(sizeof(Node));
	tnode -> right = NULL;
	tnode -> data = temp;
	tnode -> left = NULL;
	stack_push(tnode);
}



//规约
void Reduce(char* name, int num){
    elem t[num];
	//printf("***************\n");
	for (int i = 0; i < num; i++){
		t[i] = stack_pop();
		//printf("%s\n", t[i]->data);
	}
	//printf("||\n");
	//printf("%1s", name);
	//printf("%s\n", name);
	//printf("***************\n");
	fprintf(ft, "%s\n", name);
	Node* n = (Node*)malloc(sizeof(Node));
	n -> data = name;
	n -> left = NULL;
	n -> right = NULL;
	left_insert(n, t[num-1]);
	for (int i = num-1; i > 0; i--){
		right_insert(t[i], t[i-1]);
	}
	stack_push(n);
}


//初始化符号表
void symbol_table_init() {
	define_func("input", "*", 0);
	define_func("output", "*", 0);
}


//判断符号是否定义（局部）
bool is_defined_local(string name) {
	if(st[current_st].count(name)) {
		return true;
	}
	else {
		return false;
	}
}


//判断符号是否定义（全局）
bool is_defined_global(string name) {
	if(st["#"].count(name)) {
		return true;
	}
	else {
		return false;
	}
}


//判断符号是否定义（局部+全局）
bool is_defined(string name) {
	return is_defined_local(name) | is_defined_global(name);
}


//定义变量
void define_var(string name, string type) {
	st[current_st][name].name = name;
	st[current_st][name].type = type;
	st[current_st][name].property = "var";
}


//定义函数
void define_func(string name, string type, int num) {
	st[current_st][name].name = name;
	st[current_st][name].type = type;
	st[current_st][name].property = "func";
	st[current_st][name].num = num;
	if(current_st.compare("#")) {
		st["#"][name].name = name;
		st["#"][name].type = type;
		st["#"][name].property = "func";
		st["#"][name].num = num;	
	}
}


//获取新的临时变量(T0,T1,...)
string newtemp() {
	string tmp = "T";
	tmp += to_string(T_num);
	T_num ++;
	return tmp;
}


//产生中间代码
void emit(string content1, string content2){
    code.push_back(content1);
	code_qua.push_back(content2);
}


//回填
void backpatch(stack<int> &S) {
	int backnum = S.top();
	S.pop();
	code[backnum] += to_string(code.size() + 100);
	code_qua[backnum] += to_string(code.size() + 100);
}


//输出符号表和中间代码到文件
void Output(){
	for(int i = 0; i < code.size(); i++){
		fp << i + 100 << " " << code[i] << endl;
		fq << i + 100 << " " << code_qua[i] << ")" << endl;
	}
	
	for(map<string, map<string, symbol> >::iterator it1 = st.begin(); it1 != st.end(); it1 ++) {
		
		fs.flags(ios::left);
		fs << "函数名：" << it1->first << endl;
		fs << setw(24) << "变量名" << setw(22) << "类型" << setw(20) << "属性" << setw(20) << "参数个数" << endl;
		for(map<string, symbol>::iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); it2 ++) {
			fs << setw(20) << it2->second.name << setw(20) << it2->second.type << setw(20) << it2->second.property << setw(20) << it2->second.num << endl;
		}
		fs << endl << endl;
	}
}