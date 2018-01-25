grammar.tab.cpp: grammar.tab.hpp
grammar.tab.hpp: grammar.ypp
	bison -d grammar.ypp
lex.yy.c: lexis.y grammar.tab.hpp
	flex lexis.y
clean:
	rm -f grammar.tab.cpp grammar.tab.hpp
	rm -f lex.yy.c
