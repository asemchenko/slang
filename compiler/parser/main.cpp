#include <string>
using std::string;
int yyparse(void);
#include <cstdio>
extern int yydebug;
FILE *parserOut;
extern FILE *yyin;
int main(int argc, char** argv) {
//	yydebug = 1;
	if(2 == argc) {
		fprintf(stderr, "Opening file %s...\n", argv[1]);
		yyin = fopen(argv[1], "r");
		if(!yyin) {
			fprintf(stderr, "\x1b[31m[ ERROR ] Can not open file %s for reading\x1b[0m\n", argv[1]);
			return 0;
		}
	}
	parserOut = fopen("parserOutput.txt", "w");
	yyparse();
	fclose(parserOut);
	return 0;
}
