%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EDA.h"
#define YYSTYPE struct dados // AQUI TEM QUE SER STRUCT 
%}

%token TVOID TINT TSTRING TRETURN TIF TELSE TWHILE TPRINT TREAD TID TADD TSUB TMUL TDIV TAPAR TFPAR TPONTOEVIRGULA TVIRGULA TACHA TFCHA TCOMPARACAOIGUAL TMENORIGUAL TMAIORIGUAL TMENOR TMAIOR TDIFERENTE TAND TOR TNOT TIGUAL TLITERAL TNUM

%%

Principal: 	Programa {mostra_tabela();exit (0);}
		;

Programa:	ListaFuncoes BlocoPrincipal
		| BlocoPrincipal
		;
ListaFuncoes:	ListaFuncoes Funcao
		| Funcao
		;
Funcao:		TipoRetorno TID TAPAR DeclParametros TFPAR BlocoPrincipal
		| TipoRetorno TID TAPAR TFPAR BlocoPrincipal
		;
TipoRetorno: 	Tipo
		| TVOID
		;
DeclParametros:	DeclParametros TVIRGULA Parametro
		| Parametro
		;
Parametro:	Tipo TID {insere_lista(yylval.id);}
		;
BlocoPrincipal:	TACHA Declaracoes ListaCmd TFCHA
		| TACHA ListaCmd TFCHA
		;
Declaracoes:	Declaracoes Declaracao
		| Declaracao
		;
Declaracao:	Tipo ListaId TPONTOEVIRGULA {tabela_dados(list_principal,dados_principal);}
		;
Tipo:		TINT{insere_dados(strcpy(yylval.tipo,"int"));}
		| TSTRING{insere_dados(strcpy(yylval.tipo,"String"));}
		;
ListaId:	ListaId TVIRGULA TID{insere_lista(yylval.id);}
		| TID {insere_lista(yylval.id);}
		;
Bloco:		TACHA ListaCmd TFCHA
		;
ListaCmd:	ListaCmd Comando
		| Comando
		;
Comando:	CmdSe
		| CmdEnquanto
		| CmdAtrib
		| CmdEscrita
		| CmdLeitura
		| ChamadaFuncao
		| Retorno
		;
Retorno:	TRETURN ExpressaoAritimetica TPONTOEVIRGULA
		;
CmdSe:		TIF TAPAR ExpressaoLogica TFPAR Bloco
		| TIF TAPAR ExpressaoLogica TFPAR Bloco TELSE Bloco
		;
CmdEnquanto:	TWHILE TAPAR ExpressaoLogica TFPAR Bloco
		;
CmdAtrib:	TID TIGUAL ExpressaoAritimetica TPONTOEVIRGULA
		| TID TIGUAL TLITERAL TPONTOEVIRGULA
		;
CmdEscrita:	TPRINT TAPAR ExpressaoAritimetica TFPAR TPONTOEVIRGULA
		| TPRINT TAPAR TLITERAL TFPAR TPONTOEVIRGULA
		;
CmdLeitura:	TREAD TAPAR TID TFPAR TPONTOEVIRGULA
		;
ChamadaFuncao:	TID TAPAR ListaParametros TFPAR //TPONTOEVIRGULA
		| TID TAPAR TFPAR //TPONTOEVIRGULA
		;
ListaParametros: ListaParametros TVIRGULA ExpressaoAritimetica
		| ExpressaoAritimetica
		;
ExpressaoAritimetica: 	ExpressaoAritimetica TADD Termo
		 	| ExpressaoAritimetica TSUB Termo
			| Termo
			;
Termo:		Termo TMUL Fator
		| Termo TDIV Fator
		| Fator
		;
Fator:		TAPAR ExpressaoAritimetica TFPAR
		| TSUB Fator
		| TID 
		| TNUM
		| ChamadaFuncao
		;
ExpressaoRelacional:	ExpressaoAritimetica Op ExpRelacionalB
			;

ExpRelacionalB: 	ExpressaoAritimetica
			;
Op:		TDIFERENTE
		| TCOMPARACAOIGUAL
		| TMAIORIGUAL
		| TMENORIGUAL
		| TMAIOR
		| TMENOR
		;
ExpressaoLogica:	ExpressaoLogica TAND TermoLogico
			| ExpressaoLogica TOR TermoLogico
			| TermoLogico
			;
TermoLogico:	TAPAR ExpressaoLogica TFPAR
		| TNOT TermoLogico
		| ExpressaoRelacional
		;

%%
#include "lex.yy.c"

int yyerror (char *str)
{
	printf("%s - antes %s\n", str, yytext);
	
} 		 

int yywrap()
{
	return 1;
}
