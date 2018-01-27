main: main.cpp lex.yy.c grammar.tab.cpp grammar.tab.hpp
	g++ main.cpp lex.yy.c grammar.tab.cpp -std=c++17 -o main
grammar.tab.cpp: grammar.tab.hpp
grammar.tab.hpp: grammar.ypp
	bison -d grammar.ypp
lex.yy.c: lexis.y grammar.tab.hpp
	flex lexis.y
cleanTmp:
	rm -f grammar.tab.cpp grammar.tab.hpp
	rm -f lex.yy.c
clean: cleanTmp
	rm -f main
