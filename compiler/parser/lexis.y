%{
#include <stdlib.h>
#include "grammar.tab.hpp"
int currentLine = 1;
%}
%option noyywrap
%%
[\+-]?[0-9]+			{yylval.intV = atoi(yytext); return INT_LITERAL;}
[\+-]?[0-9]+\.[0-9]*		{yylval.doubleV = atof(yytext); return FLOAT_LITERAL;}
true|false			{yylval.boolV = !strcmp(yytext, "true"); return BOOL_LITERAL;}
\+				return TOK_PLUS;
-				return TOK_MINUS;
\*				return TOK_MULTIPLY;
\/				return TOK_DIVIDE;
%				return TOK_MODULO;
\^				return TOK_POW;
not				return TOK_NOT;
\(				return TOK_OPEN_BRACKET;
\)				return TOK_CLOSE_BRACKET;
[a-zA-Z]+[0-9]*			return IDENTIFIER;
\"([^"]|(\\\"))*\"		return STRING_LITERAL;
('.')|('\\'')			return CHAR_LITERAL;
[ \t]				;
\n				++currentLine;
.				return ERROR;
