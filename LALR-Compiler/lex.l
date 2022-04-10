%{
/*
Date: 2020.12.28
Author: XODRJh
*/
#define YYSTYPE std::string
#include <string.h>
#include <string>
using namespace std;
#include <stdlib.h>
#include "Syntax.tab.h"

int row_num = 1, col_num = 1;  	//行数和列数
FILE *fw;						//指向词法输出文件的指针
char key[15];					//识别的token
%}

KeyWord 	else|if|int|return|void|while
Identifier 	[A-Za-z][A-Za-z]*
Constant 	([0-9])|([1-9][0-9]*)
Operator 	<=|>=|==|!=|[\+\-\*\/\<\>\=]
Delimiter	\/\*|\*\/|[\;\,\[\]\{\}]|\(|\)
Space 		[\ \t\n]
Comment		\/\*(.|\n|\t|\ )*\*\/
Other 		[^{KeyWord}{Identifier}{Constant}{Operator}{Delimiter}{Space}]

%%


{KeyWord} {
	fprintf(fw, "%s : KeyWord, (%d, %d)\n", yytext, row_num, col_num);
	
	col_num += yyleng;
	
	if(!strcmpi(yytext, "ELSE")){
		strcpy(key, "ELSE");
		return ELSE;
	}
	if(!strcmpi(yytext, "IF")){
		strcpy(key, "IF");
		return IF;
	}
	if(!strcmpi(yytext, "INT")){
		strcpy(key, "INT");
		yylval = yytext;
		return INT;
	}
	if(!strcmpi(yytext, "RETURN")){
		strcpy(key, "RETURN");	
		return RETURN;
	}
	if(!strcmpi(yytext, "VOID")){
		strcpy(key, "VOID");
		yylval = yytext;
		return VOID;
	}
	if(!strcmpi(yytext, "WHILE")){
		strcpy(key, "WHILE");
		return WHILE;
	}
}
{Identifier} {
	fprintf(fw, "%s : Identifier, (%d, %d)\n", yytext, row_num, col_num);
	
	col_num += yyleng;
	
	strcpy(key, yytext);

	yylval = yytext;

	return ID;
}  
{Constant} {
	fprintf(fw, "%s : Constant, (%d, %d)\n", yytext, row_num, col_num);
	
	col_num += yyleng;
	
	strcpy(key, yytext);
	
	yylval = yytext;
	
	return NUM;
}
{Operator} {
	fprintf(fw, "%s : Operator, (%d, %d)\n", yytext, row_num, col_num);
	
	col_num += yyleng;
	
	if(!strcmp(yytext, "=")){
		strcpy(key, "CONST");
		return CONST;
	}
	if(!strcmp(yytext, "-")){
		strcpy(key, "MINUS");
		yylval = yytext;
		return MINUS;
	}
	if(!strcmp(yytext, "+")){
		strcpy(key, "PLUS");
		yylval = yytext;
		return PLUS;
	}
	if(!strcmp(yytext, "*")){
		strcpy(key, "MUL");
		yylval = yytext;
		return MUL;
	}
	if(!strcmp(yytext, "/")){
		strcpy(key, "DIV");
		yylval = yytext;
		return DIV;
	}
	if(!strcmp(yytext, "<=")){
		strcpy(key, "LESSEQUAL");
		yylval = yytext;
		return LESSEQUAL;
	}
	if(!strcmp(yytext, "<")){
		strcpy(key, "LESS");
		yylval = yytext;
		return LESS;
	}
	if(!strcmp(yytext, ">")){
		strcpy(key, "GREATER");
		yylval = yytext;
		return GREATER;
	}
	if(!strcmp(yytext, ">=")){
		strcpy(key, "GREATEREQUAL");
		yylval = yytext;
		return GREATEREQUAL;
	}
	if(!strcmp(yytext, "==")){
		strcpy(key, "EQUAL");
		yylval = yytext;
		return EQUAL;
	}
	if(!strcmp(yytext, "!=")){
		strcpy(key, "NOTEQUAL");
		yylval = yytext;
		return NOTEQUAL;
	}
}
{Delimiter} {
	fprintf(fw, "%s : Delimiter, (%d, %d)\n", yytext, row_num, col_num);
	
	col_num += yyleng;
	
	if(!strcmp(yytext, "(")){
		strcpy(key, "LSPAREN");
		return LSPAREN;
	}
	if(!strcmp(yytext, ")")){
		strcpy(key, "RSPAREN");
		return RSPAREN;
	}
	if(!strcmp(yytext, "[")){
		strcpy(key, "LMPAREN");
		return LMPAREN;
	}
	if(!strcmp(yytext, "]")){
		strcpy(key, "RMPAREN");
		return RMPAREN;
	}
	if(!strcmp(yytext, "{")){
		strcpy(key, "LBPAREN");
		return LBPAREN;
	}
	if(!strcmp(yytext, "}")){
		strcpy(key, "RBPAREN");
		return RBPAREN;
	}
	if(!strcmp(yytext, ",")){
		strcpy(key, "COMMA");
		return COMMA;
	}
	if(!strcmp(yytext, ";")){
		strcpy(key, "SEMI");
		return SEMI;
	}
}
{Space} {
	if(!strcmp(yytext, "\n")) {
		row_num ++;
		col_num = 1;
	}
	else {
		col_num ++;
	}
}
{Comment} {
	for(int i = 1; yytext[i]; i ++) {
		if(yytext[i - 1] == '\\' && yytext[i] == 'n') {
			row_num ++;
			col_num = 1;
		}
	}
} 
{Other} {
	fprintf(fw, "%s : Other, (%d, %d)\n", yytext, row_num, col_num);
	
	col_num += yyleng;
}

%%

int yywrap(){
	return 1;
}