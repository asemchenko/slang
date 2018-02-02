%{
#include <stdlib.h>
#include <string>
using std::string;
#include "astClasses.hpp"
#include "grammar.tab.hpp"
extern YYLTYPE yylloc;
void BeginToken(const char *);
int currentLine = 1;
int currentColumn = 0;
%}
%option noyywrap
%%
[\+-]?[0-9]+			{ BeginToken(yytext); yylval.intV = atoi(yytext); return INT_LITERAL;}
[\+-]?[0-9]+\.[0-9]*		{ BeginToken(yytext); yylval.doubleV = atof(yytext); return FLOAT_LITERAL;}
true|false			{ BeginToken(yytext); yylval.boolV = !strcmp(yytext, "true"); return BOOL_LITERAL;}
func				{ BeginToken(yytext); return TOK_FUNC; }
return 				{ BeginToken(yytext); return TOK_RETURN; }
,				{ BeginToken(yytext); return TOK_COMMA; }
"="				{ BeginToken(yytext); return TOK_ASSIGN; }
"=="				{ BeginToken(yytext); return TOK_EQ; }
"!="				{ BeginToken(yytext); return TOK_NEQ; }	
">"				{ BeginToken(yytext); return TOK_GR; }
">="				{ BeginToken(yytext); return TOK_GRE; }
"<"				{ BeginToken(yytext); return TOK_LE; }
"<="				{ BeginToken(yytext); return TOK_LEE; }
\+				{ BeginToken(yytext); return TOK_PLUS; }
-				{ BeginToken(yytext); return TOK_MINUS; }
\*				{ BeginToken(yytext); return TOK_MULTIPLY; }
\/				{ BeginToken(yytext); return TOK_DIVIDE; }
%				{ BeginToken(yytext); return TOK_MODULO; }
\^				{ BeginToken(yytext); return TOK_POW; }
not				{ BeginToken(yytext); return TOK_NOT; }
\(				{ BeginToken(yytext); return TOK_OPEN_BRACKET; }
\)				{ BeginToken(yytext); return TOK_CLOSE_BRACKET; }
"{"				{ BeginToken(yytext); return TOK_OPEN_BRACE; }
"}"				{ BeginToken(yytext); return TOK_CLOSE_BRACE; }
;				{ BeginToken(yytext); return TOK_SEMICOLON; }
:				{ BeginToken(yytext); return TOK_COLON; }
if 				{ BeginToken(yytext); return TOK_IF; }
else 				{ BeginToken(yytext); return TOK_ELSE; }
while				{ BeginToken(yytext); return TOK_WHILE; }
for 				{ BeginToken(yytext); return TOK_FOR; }
[a-zA-Z_]+[0-9]*		{ BeginToken(yytext); yylval.strV = string(yytext); return IDENTIFIER; }
\"([^"]|(\\\"))*\"		{ BeginToken(yytext); return STRING_LITERAL; }
('.')|('\\'')			{ BeginToken(yytext); return CHAR_LITERAL; }
\n				{ ++currentLine; currentColumn = 0; }
[ \t]				{ ++currentColumn; }
.				{fprintf(stderr, "\x1b[31m[ LEXER ERROR ] unrecognized token in line #%d. Token starts with: %s \n\x1b[0m",currentLine, yytext ); exit(0);}
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
