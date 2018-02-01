#include <string>
#include <string.h>
using std::string;
int yyparse(void);
#include <cstdio>
extern int yydebug;
FILE *parserOut;
extern FILE *yyin;
int main(int argc, char** argv) {
//	yydebug = 1;
	if(argc > 1) {
		fprintf(stderr, "Opening file %s...\n", argv[1]);
		yyin = fopen(argv[1], "r");
		if(!yyin) {
			fprintf(stderr, "\x1b[31m[ ERROR ] Can not open file %s for reading\x1b[0m\n", argv[1]);
			return 0;
		}
		if( argc > 2){
			if(!strcmp(argv[2], "debug")) yydebug = 1;
			else {
				fprintf(stderr, "\x1b[31m[ ERROR ] Unrecognized option %s\x1b[0m\n", argv[2]);		
				return 0;
			}
		}
	}
	parserOut = fopen("parserOutput.txt", "w");
	yyparse();
	fclose(parserOut);
	return 0;
}
