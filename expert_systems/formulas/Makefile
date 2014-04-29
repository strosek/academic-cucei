# Makefile: A simple makefile for formula analyzer.

default:
	bison -d formulas.y
	flex formulas.l
	g++ -o formulas.bin formulas.tab.c lex.yy.c
clean:
	rm -f *.tab.c lex.yy.c *.tab.h *.bin
