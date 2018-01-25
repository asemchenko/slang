#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include "../../grammar.tab.hpp"
extern "C" FILE *yyin;
extern "C" int yylex();
YYSTYPE yylval;
TEST(lexerTests, yylexTest) {
	yytokentype tokens[] = {INT_LITERAL, INT_LITERAL, FLOAT_LITERAL, FLOAT_LITERAL, BOOL_LITERAL,
	BOOL_LITERAL, TOK_PLUS, TOK_MINUS, TOK_MULTIPLY, TOK_DIVIDE, TOK_MODULO,TOK_POW, TOK_NOT, TOK_OPEN_BRACKET, TOK_CLOSE_BRACKET, IDENTIFIER, IDENTIFIER, IDENTIFIER, STRING_LITERAL,IDENTIFIER, CHAR_LITERAL, TOK_POW};	
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
