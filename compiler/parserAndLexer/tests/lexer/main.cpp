#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
using std::string;
#include "astClasses.hpp"
using namespace slang_AST_NODES;
#include "grammar.tab.hpp"
YYLTYPE yylloc;
extern FILE *yyin;
int yylex();
YYSTYPE yylval;
TEST(lexerTests, yylexTest) {
	yytokentype tokens[] = {INT_LITERAL, INT_LITERAL, FLOAT_LITERAL, FLOAT_LITERAL, BOOL_LITERAL,
	BOOL_LITERAL, TOK_PLUS, TOK_MINUS, TOK_MULTIPLY, TOK_DIVIDE, TOK_MODULO,TOK_POW, TOK_NOT, TOK_OPEN_BRACKET, TOK_CLOSE_BRACKET, IDENTIFIER, IDENTIFIER, IDENTIFIER, STRING_LITERAL,IDENTIFIER, CHAR_LITERAL, TOK_POW, TOK_NOT, IDENTIFIER, STRING_LITERAL, TOK_POW, CHAR_LITERAL,IDENTIFIER, TOK_LEE, IDENTIFIER, TOK_GRE, TOK_LE, TOK_GR, TOK_EQ, TOK_ASSIGN, TOK_NEQ, TOK_FUNC, TOK_RETURN};	
	for(int i = 0; i < std::size(tokens); ++i) {
		ASSERT_EQ(yylex(),tokens[i]);
		fprintf(stdout, "Starting test #%d...\n", i+1);
	}
}

int main(int argc, char ** argv) {
	yyin = fopen("testCode.txt","r");
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
