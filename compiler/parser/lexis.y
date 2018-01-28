%{
#include <stdlib.h>
#include <string>
using std::string;
#include "grammar.tab.hpp"
extern YYLTYPE yylloc;
void BeginToken(const char *);
int currentLine = 1;
int currentColumn = 0;
%}
%option noyywrap
%%
[\+-]?[0-9]+			{ yylval.intV = atoi(yytext); return INT_LITERAL;}
[\+-]?[0-9]+\.[0-9]*		{ yylval.doubleV = atof(yytext); return FLOAT_LITERAL;}
true|false			{ yylval.boolV = !strcmp(yytext, "true"); return BOOL_LITERAL;}
\+				return TOK_PLUS;
-				return TOK_MINUS;
\*				return TOK_MULTIPLY;
\/				return TOK_DIVIDE;
%				return TOK_MODULO;
\^				return TOK_POW;
not				return TOK_NOT;
\(				return TOK_OPEN_BRACKET;
\)				return TOK_CLOSE_BRACKET;
;				return TOK_SEMICOLON;
:				return TOK_COLON;
if 				return TOK_IF;
else 				return TOK_ELSE;
while				return TOK_WHILE;
for 				return TOK_FOR;
[a-zA-Z]+[0-9]*			{yylval.strV = string(yytext); return IDENTIFIER; }
\"([^"]|(\\\"))*\"		return STRING_LITERAL;
('.')|('\\'')			{ BeginToken(yytext); return CHAR_LITERAL; }
\n				{ ++currentLine; currentColumn = 0; }
[ \t]				{ ++currentColumn; }
.				return ERROR;
%%
void BeginToken(const char * token) {
	// actions for bison location tracking
	yylloc.first_line = currentLine;
	yylloc.first_column = currentColumn;
	yylloc.last_line = currentLine;
	currentColumn += strlen(token);
	yylloc.last_column = currentColumn;
	// actions for bison semantic value tracking
	yylval.strV = string(token);
}
