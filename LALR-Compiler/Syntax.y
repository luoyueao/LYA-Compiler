%{
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


%}
//%debug


%start program
%token ID
%token NUM
%token PLUS MINUS MUL DIV 
%token LESSEQUAL LESS GREATEREQUAL GREATER EQUAL NOTEQUAL
%token CONST
%token ELSE IF INT RETURN VOID WHILE
%token LSPAREN RSPAREN LMPAREN RMPAREN LBPAREN RBPAREN
%token COMMA SEMI

%right CONST
%left PLUS MINUS 
%left MUL DIV
%nonassoc ELSE
%left LSPAREN RSPAREN
%left LBPAREN RBPAREN
%left LMPAREN RMPAREN
%left LESSEQUAL GREATEREQUAL LESS GREATER EQUAL NOTEQUAL


%%
	 
program     	:		declaration-list {
							fprintf(fi, "program -> declaration-list\n");
							Reduce("program", 1);
							tree.root = stack_pop();
							PreOrderTravel(tree.root, 0);
						}
				; 

declaration-list:		declaration-list declaration {
							fprintf(fi, "declaration-list -> declaration-list declaration\n"); 
							Reduce("declaration-list", 2);
						}
            	|       declaration {
							fprintf(fi, "declaration-list -> declaration\n"); 
							Reduce("declaration-list", 1);
						}
				;

declaration     : 		var-declaration {
							fprintf(fi, "declaration -> var-declaration\n"); 
							Reduce("declaration", 1);
						}
            	|		fun-declaration {
							fprintf(fi, "declaration -> fun-declaration\n"); 
							Reduce("declaration", 1);
						}
				;

var-declaration	:		type-specifier ID SEMI {
							if(is_defined_local($2)) {
								cout << "ERROR: ID '" << $2 << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var($2, $1);
							}
							fprintf(fi, "var-declaration -> type-specifier ID ;\n"); 
							Reduce("var-declaration", 3);
						}
				|		type-specifier ID LMPAREN NUM RMPAREN SEMI {
							if(is_defined_local($2)) {
								cout << "ERROR: ID '" << $2 << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var($2, $1);
							}
							fprintf(fi, "var-declaration -> type-specifier ID [ NUM ] ;\n"); 
							Reduce("var-declaration", 6);
						}
				;

type-specifier	:		INT {
							$$ = $1;
							fprintf(fi, "type-specifier -> INT\n"); 
							Reduce("type-specifier", 1);
						}
				|		VOID {
							$$ = $1;
							fprintf(fi, "type-specifier -> VOID\n");
							Reduce("type-specifier", 1);
						}
				;
				
fun-declaration	:		type-specifier ID {
							current_st = $2;
						}
						LSPAREN params RSPAREN {
							int temp_num = stoi($5);
							if(is_defined_global($2)) {
								if(st[current_st][$2].num == temp_num) {
									cout << "ERROR: FUNC '" << $2 << "' has been defined! (" << row_num << ", " << col_num << ")\n";
									exit(0);
								}
							}
							else {
								define_func($2, $1, temp_num);
							}
							emit("Prog " + $2, "(Prog, -, -, " + $2);
							fprintf(fi, "fun-declaration -> type-specifier ID ( params )\n"); 
							Reduce("fun-declaration", 5);
						}
				|		compound-stmt {
							current_st = "#";
							fprintf(fi, "fun-declaration -> compound-stmt\n"); 
							Reduce("fun-declaration", 1);
						}
				;

params			:		params-list {
							$$ = $1;
							fprintf(fi, "params -> params-list\n"); 
							Reduce("params", 1);
						}
				|		VOID {
							$$ = "0";
							fprintf(fi, "params -> VOID\n"); 
							Reduce("params", 1);
						}
				;

params-list		:		params-list COMMA param {
							$$ = to_string(stoi($1) + 1);
							fprintf(fi, "params-list -> params-list , param\n"); 
							Reduce("params-list", 3);
						}
				|		param {
							$$ = "1";
							fprintf(fi, "params-list -> param\n"); 
							Reduce("params-list", 1);
						}
				;

param			:		type-specifier ID {
							if(is_defined_local($2)) {
								cout << "ERROR: ID '" << $2 << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var($2, $1);
							}
						}
				|		type-specifier ID LMPAREN RMPAREN {
							if(is_defined_local($2)) {
								cout << "ERROR: ID '" << $2 << "' has been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							else {
								define_var($2, $1);
							}
							fprintf(fi, "param -> type-specifier ID [ ]\n"); 
							Reduce("param", 4);
						}
				;

compound-stmt   :		LBPAREN local-declarations statement-list RBPAREN {
							fprintf(fi, "compound-stmt -> { local-declarations statement-list }\n"); 
							Reduce("compound-stmt", 4);
						}
				; 				
				
local-declarations:		local-declarations var-declaration {
							fprintf(fi, "local-declarations -> local-declarations var-declaration\n"); 
							Reduce("local-declarations", 2);
						}
				|		{
							fprintf(fi, "local-declarations -> empty\n"); 
							Reduce("local-declarations", 0);
						}
				;				
				
statement-list	:		statement-list statement {
							fprintf(fi, "statement-list -> statement-list statement\n"); 
							Reduce("statement-list", 2);
						}
				|		{
							fprintf(fi, "statement-list -> empty\n"); 
							Reduce("statement-list", 0);
						}
				;				
				
statement		:		expression-stmt {
							fprintf(fi, "statement -> expression-stmt\n"); 
							Reduce("statement", 1);
						}
				|		compound-stmt {
							fprintf(fi, "statement -> compound-stmt\n"); 
							Reduce("statement", 1);
						}
				|		selection-stmt {
							fprintf(fi, "statement -> selection-stmt\n"); 
							Reduce("statement", 1);
						}
				|		iteration-stmt {
							fprintf(fi, "statement -> iteration-stmt\n"); 
							Reduce("statement", 1);
						}
				|		return-stmt {
							fprintf(fi, "statement -> return-stmt\n"); 
							Reduce("statement", 1);
						}
				;				
							
expression-stmt	:		expression SEMI {
							fprintf(fi, "expression-stmt -> expression ;\n"); 
							Reduce("expression-stmt", 2);	
						}
				|		SEMI {
							fprintf(fi, "expression-stmt -> ;\n"); 
							Reduce("expression-stmt", 1);
						}
				;				

selection-stmt	:		IF LSPAREN expression RSPAREN {
							string dest = to_string(code.size() + 102);
							emit("if " + $3 + "==1 Goto " + dest, "(jnz, " + $3 + ", -, " + dest);
							falsestack.push(code.size());
							emit("Goto ", "(j, -, -, ");
						}
						statement {
							truestack.push(code.size());
							emit("Goto ", "(j, -, -, ");
						}
						selection-stmts {
							fprintf(fi, "selection-stmt -> IF ( expression ) statement selection-stmts\n"); 
							Reduce("selection-stmt", 6);
						}
				;

selection-stmts	:		ELSE {
							backpatch(falsestack);
						}
						statement {
							backpatch(truestack);
							fprintf(fi, "selection-stmts -> ELSE statement\n"); 
							Reduce("selection-stmts", 2);
						}
				|		{
							backpatch(falsestack);
							backpatch(truestack);
							fprintf(fi, "selection-stmts -> empty\n");
							Reduce("selection-stmts", 0);
						}
				;
				
iteration-stmt  :		WHILE LSPAREN {
							truestack.push(code.size());
						}
						expression RSPAREN {
							string dest = to_string(code.size() + 102);
							emit("if " + $4 + "==1 Goto " + dest, "(jnz, " + $4 + ", -, " + dest);
							falsestack.push(code.size());
							emit("Goto ", "(j, -, -, ");
						}
						statement {
							string dest = to_string(truestack.top() + 100);
							truestack.pop();
							emit("Goto " + dest, "(j, -, -, " + dest);
							backpatch(falsestack);
							fprintf(fi, "iteration-stmt -> WHILE ( expression ) statement\n"); 
							Reduce("iteration-stmt", 5);
						}
				; 				
				
return-stmt		:		RETURN SEMI {
							emit("return", "(ret, -, -, -");
							fprintf(fi, "return-stmt -> return ;\n"); 
							Reduce("return-stmt", 2);
						}
				|		RETURN expression SEMI {
							emit("return " + $2, "(ret, -, -, " + $2);
							fprintf(fi, "return-stmt -> RETURN expression ;\n"); 
							Reduce("return-stmt", 3);
						}
				;				
				
expression		:		var CONST expression {
							emit($1 + " := " + $3, "(:=, " + $3 + ", -, " + $1);
							$1 = $3;
							fprintf(fi, "expression -> var = expression\n"); 
							Reduce("expression", 3);
						}
				|		simple-expression {
							$$ = $1;
							fprintf(fi, "expression -> simple-expression\n"); 
							Reduce("expression", 1);
						}
				;

var				:		ID {
							if(!is_defined($1)) {
								cout << "ERROR: ID '" << $1 << "' has not been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							$$ = $1; 
							fprintf(fi, "var -> ID\n"); 
							Reduce("var", 1);
						}
				|		ID LMPAREN expression RMPAREN {
							if(!is_defined($1)) {
								cout << "ERROR: ID '" << $1 << "' has not been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							$$ = $1 + "[" + $3 + "]";
							fprintf(fi, "var -> ID [ expression ]\n"); 
							Reduce("var", 4);
						}
				;		

simple-expression:		additive-expression relop additive-expression {
							$$ = newtemp();
							emit($$ + " := " + $1 + " " + $2 + " " + $3, "(" + $2 + ", " + $1 + ", " + $3 + ", " + $$);
							fprintf(fi, "simple-expression -> additive-expression relop additive-expression\n"); 
							Reduce("simple-expression", 3);
						}
				|		additive-expression {
							$$ = $1;
							fprintf(fi, "simple-expression -> additive-expression\n"); 
							Reduce("simple-expression", 1);
						}
				;

relop			:		LESSEQUAL {
							$$ = $1;
							fprintf(fi, "relop -> <=\n"); 
							Reduce("relop", 1);
						}
				|		LESS {
							$$ = $1; 
							fprintf(fi, "relop -> <\n"); 
							Reduce("relop", 1);
						}
				|		GREATER {
							$$ = $1;
							fprintf(fi, "relop -> >\n"); 
							Reduce("relop", 1);
						}
				|		GREATEREQUAL {
							$$ = $1; 
							fprintf(fi, "relop -> >=\n"); 
							Reduce("relop", 1);
						}
				|		EQUAL {
							$$ = $1; 
							fprintf(fi, "relop -> ==\n"); 
							Reduce("relop", 1);
						}
				|		NOTEQUAL {
							$$ = $1;
							fprintf(fi, "relop -> !=\n"); 
							Reduce("relop", 1);
						}
				;	

additive-expression:	additive-expression addop term {
							$$ = newtemp();
							emit($$ + " := " + $1 + " " + $2 + " " + $3, "(" + $2 + ", " + $1 + ", " + $3 + ", " + $$);
							fprintf(fi, "additive-expression -> additive-expression addop term\n"); 
							Reduce("additive-expression", 3);
						}
				|		term {
							$$ = $1; 
							fprintf(fi, "additive-expression -> term\n"); 
							Reduce("additive-expression", 1);
						}
				;					
				
addop			:		PLUS {
							$$ = $1;
							fprintf(fi, "addop -> +\n"); 
							Reduce("addop", 1);
						}
				|		MINUS {
							$$ = $1;
							fprintf(fi, "addop -> -\n"); 
							Reduce("addop", 1);
						}
				;					
				
term			:		term mulop factor {
							$$ = newtemp();
							emit($$ + " := " + $1 + " " + $2 + " " + $3, "(" + $2 + ", " + $1 + ", " + $3 + ", " + $$);
							fprintf(fi, "term -> term mulop factor\n"); 
							Reduce("term", 3);
						}
				|		factor {
							$$ = $1;
							fprintf(fi, "term -> factor\n"); 
							Reduce("term", 1);
						}
				;
		
mulop			:		MUL {
							$$ = $1;
							fprintf(fi, "mulop -> *\n"); 
							Reduce("mulop", 1);
						}
				|		DIV {
							$$ = $1;
							fprintf(fi, "mulop -> /\n"); 
							Reduce("mulop", 1);
						}
				;				

factor			:		LSPAREN expression RSPAREN {
							$$ = $2;
							fprintf(fi, "factor -> ( expression )\n"); 
							Reduce("factor", 3);
						}
				|		var {
							$$ = $1;
							fprintf(fi, "factor -> var\n"); 
							Reduce("factor", 1);
						}
				|		call {
							$$ = $1;
							fprintf(fi, "factor -> call\n"); 
							Reduce("factor", 1);
						}
				|		NUM {
							$$ = $1;
							fprintf(fi, "factor -> NUM\n"); 
							Reduce("factor", 1);
						}
				;

call			:		ID LSPAREN args RSPAREN {
							if(!is_defined($1)) {
								cout << "ERROR: ID '" << $1 << "' hasn't been defined! (" << row_num << ", " << col_num << ")\n";
								exit(0);
							}
							$$ = newtemp();
							emit($$ + " := " + "call " + $1, "(call, " + $1 + ", -, " + $$);
							fprintf(fi, "call -> ID ( args )\n"); 
							Reduce("call", 4);
						}
				;				
				
args			:		arg-list {
							const char *split = ",";
							char *p = strtok((char *)$1.c_str(), split);
							while( p != NULL )
							{
								emit((string)"param " + p, (string)"(param, -, -, " + p);
								p = strtok(NULL,split);
							}
							fprintf(fi, "args -> arg-list\n"); 
							Reduce("args", 1);
						}
				|		{
							fprintf(fi, "args -> empty\n"); 
							Reduce("args", 0);
						}
				;
				
arg-list		:		arg-list COMMA expression {
							$$ = $1 + "," + $3;
							fprintf(fi, "arg-list -> arg-list , expression\n"); 
							Reduce("arg-list", 3);
						}
				|		expression {
							$$ = $1;
							fprintf(fi, "arg-list -> expression\n"); 
							Reduce("arg-list", 1);
						}
				;
%% 

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