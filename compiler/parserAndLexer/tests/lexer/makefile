SOURCE_DIR=../../
all: main.cpp lex.yy.c grammar.tab.hpp grammar.tab.cpp
	g++ -O3 -std=c++17 -o main main.cpp lex.yy.c -lgtest -lpthread
lex.yy.c: $(SOURCE_DIR)lexis.y
	flex $(SOURCE_DIR)lexis.y
grammar.tab.hpp:
	bison -d $(SOURCE_DIR)grammar.ypp
clean:
	rm -f main
	rm -f lex.yy.c
	rm -f grammar.tab.hpp
	rm -f grammar.tab.cpp
