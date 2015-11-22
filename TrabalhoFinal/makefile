all:
	flex tokens.l
	bison -v grammar.y
	cc -o expr expr.c grammar.tab.c
	clear;
	@echo "Digite o nome do arquivo a ser lido: ";\
	read entrada;\
	clear;\
	./expr $$entrada;
	@rm -f grammar.tab.c
	@rm -f grammar.output 
	@rm -f lex.yy.c
	@rm -f expr.o
	@rm -f expr
	@mv entradaJasmin.j jasmin
	@cd jasmin;\
	java -jar jasmin.jar entradaJasmin.j;\
	java entradaJasmin;\
	rm -f entradaJasmin.j;\
	rm -f entradaJasmin

