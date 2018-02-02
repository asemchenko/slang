SOURCE_PATH = ../
main: $(SOURCE_PATH)main.cpp lex.yy.c grammar.tab.cpp grammar.tab.hpp
	g++ -I$(SOURCE_PATH) $(SOURCE_PATH)main.cpp lex.yy.c grammar.tab.cpp -std=c++17 -O3 -o main
grammar.tab.cpp: grammar.tab.hpp
grammar.tab.hpp: $(SOURCE_PATH)grammar.ypp
	bison -d $(SOURCE_PATH)grammar.ypp
lex.yy.c: $(SOURCE_PATH)lexis.y grammar.tab.hpp
	flex $(SOURCE_PATH)lexis.y
cleanTmp:
	rm -f grammar.tab.cpp grammar.tab.hpp
	rm -f lex.yy.c
clean: cleanTmp
	rm -f main
