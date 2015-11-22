all:
	flex tokens.l
	bison -v grammar.y
	cc -o expr expr.c grammar.tab.c
rm:
