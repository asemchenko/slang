%{
#include <stdlib.h>
#include <string>
using std::string;
#include "astClasses.hpp"
#include "grammar.tab.hpp"
void BeginToken(const char *, YYSTYPE *, YYLTYPE *);
static int currentLine = 1;
static int currentColumn = 1;
%}
%option noyywrap
%option bison-locations
%%
[\+-]?[0-9]+			{ BeginToken(yytext, yylval, yylloc); yylval->intV = atoi(yytext); return INT_LITERAL;}
[\+-]?[0-9]+\.[0-9]*		{ BeginToken(yytext, yylval, yylloc); yylval->doubleV = atof(yytext); return FLOAT_LITERAL;}
true|false			{ BeginToken(yytext, yylval, yylloc); yylval->boolV = !strcmp(yytext, "true"); return BOOL_LITERAL;}
func				{ BeginToken(yytext, yylval, yylloc); return TOK_FUNC; }
return 				{ BeginToken(yytext, yylval, yylloc); return TOK_RETURN; }
,				{ BeginToken(yytext, yylval, yylloc); return TOK_COMMA; }
"="				{ BeginToken(yytext, yylval, yylloc); return TOK_ASSIGN; }
"=="				{ BeginToken(yytext, yylval, yylloc); return TOK_EQ; }
"!="				{ BeginToken(yytext, yylval, yylloc); return TOK_NEQ; }	
">"				{ BeginToken(yytext, yylval, yylloc); return TOK_GR; }
">="				{ BeginToken(yytext, yylval, yylloc); return TOK_GRE; }
"<"				{ BeginToken(yytext, yylval, yylloc); return TOK_LE; }
"<="				{ BeginToken(yytext, yylval, yylloc); return TOK_LEE; }
\+				{ BeginToken(yytext, yylval, yylloc); return TOK_PLUS; }
-				{ BeginToken(yytext, yylval, yylloc); return TOK_MINUS; }
\*				{ BeginToken(yytext, yylval, yylloc); return TOK_MULTIPLY; }
\/				{ BeginToken(yytext, yylval, yylloc); return TOK_DIVIDE; }
%				{ BeginToken(yytext, yylval, yylloc); return TOK_MODULO; }
\^				{ BeginToken(yytext, yylval, yylloc); return TOK_POW; }
not				{ BeginToken(yytext, yylval, yylloc); return TOK_NOT; }
\(				{ BeginToken(yytext, yylval, yylloc); return TOK_OPEN_BRACKET; }
\)				{ BeginToken(yytext, yylval, yylloc); return TOK_CLOSE_BRACKET; }
"{"				{ BeginToken(yytext, yylval, yylloc); return TOK_OPEN_BRACE; }
"}"				{ BeginToken(yytext, yylval, yylloc); return TOK_CLOSE_BRACE; }
;				{ BeginToken(yytext, yylval, yylloc); return TOK_SEMICOLON; }
:				{ BeginToken(yytext, yylval, yylloc); return TOK_COLON; }
if 				{ BeginToken(yytext, yylval, yylloc); return TOK_IF; }
else 				{ BeginToken(yytext, yylval, yylloc); return TOK_ELSE; }
while				{ BeginToken(yytext, yylval, yylloc); return TOK_WHILE; }
for 				{ BeginToken(yytext, yylval, yylloc); return TOK_FOR; }
[a-zA-Z_]+[0-9]*		{ BeginToken(yytext, yylval, yylloc); yylval->strV = string(yytext); return IDENTIFIER; }
\"([^"]|(\\\"))*\"		{ BeginToken(yytext, yylval, yylloc); return STRING_LITERAL; }
('.')|('\\'')			{ BeginToken(yytext, yylval, yylloc); return CHAR_LITERAL; }
\n				{ ++currentLine; currentColumn = 0; }
[ \t]				{ ++currentColumn; }
.				{fprintf(stderr, "\x1b[31m[ LEXER ERROR ] unrecognized token in line #%d. Token starts with: %s \n\x1b[0m",currentLine, yytext ); exit(0);}
%%
void BeginToken(const char * token,YYSTYPE *yylval,YYLTYPE *yylloc) {

	// actions for bison location tracking
	yylloc->first_line = currentLine;
	yylloc->first_column = currentColumn;
	yylloc->last_line = currentLine;
	currentColumn += strlen(token);
	yylloc->last_column = currentColumn;
	// actions for bison semantic value tracking
	yylval->strV = string(token);

}
