/*****************************************************************
* Analisador Sintatico LL(1)                                     *
* Exemplo p/ Disciplina de Compiladores                          *
* Cristiano Damiani Vasconcellos                                 *
******************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

/* Nao terminais o bit mais significativo ligado indica que se trata de um nao
terminal */
#define EXPR   0x8001 //E
#define EXPRL  0x8002 //E'
#define TERMO  0x8003 //T
#define TERMOL 0x8004 //T'
#define FATOR  0x8005 //F
#define BOOL   0x8006 //X

/* Terminais */
#define ERRO 	        0x0000
#define SESOMENTESE     0x0A00
#define IMPLICA      	0X0B00
#define E               0x0300
#define OU      		0x0400
#define NOT             0x0500
#define APAR            0x0600
#define FPAR            0x0700
#define CONST           0x0800
#define FIM             0x0900

//Mascaras
#define NTER   0x8000
#define NNTER  0x7FFF

#define TAMPILHA 100


struct Pilha {
	int topo;
	int dado[TAMPILHA];
};

/* Producoes a primeira posicao do vetor indica quantos simbolos
gramaticais a producao possui em seu lado direito */

const int PROD1[] = {2, TERMO, EXPRL};                 // E  -> TE'
const int PROD2[] = {3, SESOMENTESE, TERMO, EXPRL};    // E' -> <->TE'
const int PROD3[] = {3, IMPLICA, TERMO, EXPRL};        // E' -> ->TE'
const int PROD4[] = {0};                               // E' -> vazio
const int PROD5[] = {2, FATOR, TERMOL};                // T  -> FT'
const int PROD6[] = {3, E, FATOR, TERMOL};             // T' -> &FT'
const int PROD7[] = {3, OU, FATOR, TERMOL};            // T' -> |FT'
const int PROD8[] = {0};                               // T' -> vazio
const int PROD9[] = {1, BOOL};                         // F  -> X
const int PROD10[] ={2,NOT,BOOL};                      // F  -> ~X
const int PROD11[]= {1, CONST};                        // X  -> V || X-> F
const int PROD12[]= {3, APAR, EXPR, FPAR};             // X  -> (E)

// vetor utilizado para mapear um numero e uma producao.
const int *PROD[] = {NULL, PROD1, PROD2, PROD3, PROD4, PROD5, PROD6, PROD7, PROD8, PROD9, PROD10, PROD11, PROD12};

// Tabela sintatica LL(1). Os numeros correspondem as producoes acima.
//                               &   |   ~    (  ) CONST   # <-> ->
const int STAB[6][9] =  /*E */{{ 0,  0,  1,   1, 0,    1,  0, 0, 0},
                        /*E'*/{  0,  0,  0,   0, 4,    0,  4, 2, 3},
                        /*T */{  0,  0,  5,   5, 0,    5,  0, 0, 0},
						/*T'*/{  6,  7,  0,   0, 8,    0,  8, 8, 8},
						/*F */{  0,  0, 10,   9, 0,    9,  0, 0, 0},
						/*X */{  0,  0,  0,  12, 0,   11,  0, 0, 0}};

/*****************************************************************
* int lex (char *str, int *pos)                                  *
* procura o proximo token dentro de str a partir de *pos,incre-  *
* menta o valor de *pos a medida que faz alguma tranzicao de     *
* estados.                                                       *
* Retorna o inteiro que identifica o token encontrado.           *
******************************************************************/

int lex (char *str, int *pos)
{
	int estado = 0;
	char c;
	while (1)
	{
		c =  str[*pos];
		switch(estado)
		{
			case 0:
				if (isalpha(c))
				{
                    switch (c)
                    {
                        case 'V':
                            (*pos)++;
                            return CONST;
                        case 'F':
                            (*pos)++;
                            return CONST;
                        default:
                            (*pos)++;
                            return ERRO;
                    }
                }
				else
					switch (c)
					{
						case '<':
                            (*pos)++;
							estado = 1;
							break;
                        case '-':
                            (*pos)++;
                            estado = 2;
                            break;
						case '|':
                            	(*pos)++;
								return OU;
						case '&':
                                (*pos)++;
								return E;
						case '~':
                            	(*pos)++;
								return NOT;
						case '(':
                            	(*pos)++;
								return APAR;
						case ')':
                            	(*pos)++;
								return FPAR;
						case '\0':
                                return FIM;
						default:
                            	(*pos)++;
								return ERRO;
					}
					break;
			case 1:
				if (isalpha(c))
				{
					(*pos)++;
					return ERRO;
				}
				else
				{
					switch(c)
					{
                        case '-':
                            (*pos)++;
                            estado = 3;
                            break;
                        default:
                            (*pos)++;
                            return ERRO;
                    }
				}
				break;
			case 2:
				if (isalpha(c)){
					(*pos)++;
					return ERRO;
                }
				else
				{
					//Adicionar SESOMENTESE ou IMPLICA na tabela
					switch(c)
					{
                        case '>':
                                (*pos)++;
                                return IMPLICA;
                        default:
                                (*pos)++;
                                return ERRO;
                    }
				}
				break;
            case 3:
				if (isalpha(c)){
					(*pos)++;
					return ERRO;
                }
				else
				{
					//Adicionar SESOMENTESE ou IMPLICA na tabela
					switch(c)
					{
                        case '>':
                                (*pos)++;
                                return SESOMENTESE;
                        default:
                                (*pos)++;
                                return ERRO;
                    }
				}
				break;
			default:
					printf("Lex:Estado indefinido");
					exit(1);
		}
	}
}

/*****************************************************************
* void erro (char *erro, char *expr, int pos)                    *
* imprime a mensagem apontado por erro, a expressao apontada por *
* expr, e uma indicacao de que o erro ocorreu na posicao pos de  *
* expr. Encerra a execucao do programa.                          *
******************************************************************/

void erro (char *erro, char *expr, int pos)
{
	int i;
	printf("%s", erro);
	printf("\n%s\n", expr);
	for (i = 0; i < pos-1; i++)
		putchar(' ');
	putchar('^');
	exit(1);
}

/*****************************************************************
* void inicializa(struct Pilha *p)                               *
* inicializa o topo da pilha em -1, valor que indica que a pilha *
* esta vazia.                                                    *
******************************************************************/

void inicializa(struct Pilha *p)
{
	p->topo = -1;
}

/*****************************************************************
* void insere (struct Pilha *p, int elemento                     *
* Insere o valor de elemento no topo da pilha apontada por p.    *
******************************************************************/

void insere (struct Pilha *p, int elemento)
{
	if (p->topo < TAMPILHA)
	{
		p->topo++;
		p->dado[p->topo] = elemento;
    }
	else
	{
		printf("estouro de pilha");
		exit (1);
	}
}

/*****************************************************************
* int remover (struct Pilha *p)                                  *
* Remove e retorna o valor armazenado no topo da pilha apontada  *
* por p                                                          *
******************************************************************/

int remover (struct Pilha *p)
{
	int aux;

	if (p->topo >= 0)
	{
		aux = p->dado[p->topo];
		p->topo--;
		return aux;
	}
	else
	{
		printf("Pilha vazia");
		exit(1);
	}
	return 0;
}

/*****************************************************************
* int consulta (struct Pilha *p)                                 *
* Retorna o valor armazenado no topo da pilha apontada por p     *
******************************************************************/

int consulta (struct Pilha *p)
{
	if (p->topo >= 0)
		return p->dado[p->topo];
	printf("Pilha vazia");
	exit(1);
}

/*****************************************************************
* void parser (char *expr)                                       *
* Verifica se a string apontada por expr esta sintaticamente     *
* correta.                                                       *
* Variaveis Globais Consultadas: STAB e PROD                     *
******************************************************************/


void parser(char *expr)
{
	struct Pilha pilha;
	int x, a, nProd, i, *producao;
	int pos = 0;

	inicializa(&pilha);
	insere(&pilha, FIM);
	insere(&pilha, EXPR);
	if ((a = lex(expr, &pos)) == ERRO)
		erro("Erro lexico", expr, pos);
	do
	{
        x = consulta(&pilha);
		if (!(x&NTER))
		{
			if (x == a)
			{
				remover (&pilha);
				if ((a = lex(expr, &pos)) == ERRO)
					erro("Erro lexico", expr, pos);
			}
			else{
				erro("Erro sintatico2",expr, pos);
            }
		}
		if (x&NTER)
		{
            nProd = STAB[(x&NNTER)-1][(a>>8)-3];
			if (nProd)
			{
				remover (&pilha);
				producao = PROD[nProd];
				for (i = producao[0]; i > 0; i--){
					insere (&pilha, producao[i]);
                }
            }
			else
				erro ("Erro sintatico1", expr, pos);
		}
	} while (x != FIM);
}

void main()
{
	char expr[100];
	printf("\nDigite uma sentenca: ");
	gets(expr);
	parser(expr);
	printf("Expressao sintaticamente correta\n");
}
