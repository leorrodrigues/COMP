all:
	flex tokens.l
	bison -v grammar.y
	cc -o expr expr.c grammar.tab.c
	@rm -f grammar.tab.c
	@rm -f lex.yy.c
	@rm -f grammar.output
	clear;
	@echo "Digite o nome do arquivo que deseja ler: ";\
	read nome;\
	./expr $$nome;
	@rm -f expr.o
	@rm -f expr
	@mv entradaJasmin.j .jasmin/
	@cd .jasmin;\
	java -jar jasmin.jar entradaJasmin.j;\
	java entradaJasmin;\
	rm -f entradaJasmin.j;\
	rm -f entradaJasmin.class;
