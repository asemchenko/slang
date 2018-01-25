all: main.cpp 
	g++ -std=c++17 -o main main.cpp ../../lex.yy.o -lgtest -lpthread
test: #does'nt work
	pushd ../../
	make lex.yy.c
	gcc -c lex.yy.c
	popd
