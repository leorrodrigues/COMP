#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct lista{
    struct lista *proximo;
    struct lista *anterior;
    char id[50];
}Lista;

typedef struct tabela{
    struct tabela *proximo;
    struct tabela *anterior;
    char id[40];
    char tipo[20];
    int pos;
}Tabela;

typedef struct dados{
    char tipo[50];
    int constante;
    char id[50];
}Dados;

typedef struct instrucao{
    int label,p1,p2;
    char _instrucao[50];
}Instrucao;

void mostra_lista();
void insere_lista(char id[50]);
void tabela_dados(Lista *lista,Dados *dados);
void mostra_tabela();
void insere_dados(char *lido);
Lista *inserefim_lista(Lista *dados,char id[50]);
Dados *inserefim_dados(char *lido);
Tabela *insere_tabela(Lista *lista,Dados *dados);

int POS=0;//iniciamos as posicoes da tabela.
int PROXINST=0;//iniciamos as posicoes das intrucoes
Lista *list_principal=NULL; //inicia a lista vazia
Tabela *tab=NULL;//inicia a tabela vazia
Dados *dados_principal;//inicia os dados vazios
Instrucao *inst=NULL;//Iniciamos o vetor de instrucoes vazio

void insere_lista(char id[50]){
    list_principal=inserefim_lista(list_principal,id);
}

Lista *inserefim_lista(Lista *dados,char id[50]) {
    //Criando listas auxiliares
    Lista *final,*aux;
    aux=list_principal;//aux aponta para o inicio da lista.
    //Alocando dados para a posição final da lista
    final = (Lista *)malloc(sizeof(Lista));
    strcpy(final->id,id);
    //A pŕoxima posição será Nulo
    final->proximo=NULL;
    final->anterior=NULL;
    //A lista auxiliar será igual a Principal
    if(list_principal==NULL){
        return(final);
    }
    //Enquanto o próximo de auxiliar não for Nulo
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    aux->proximo=final;
    final->anterior=aux;
    return(list_principal);
}

void insere_dados(char *lido){
    dados_principal=inserefim_dados(lido);
}

Dados *inserefim_dados(char *lido){
    Dados *final;
    final = (Dados *)malloc(sizeof(Dados));
    strcpy(final->tipo,lido);
    return(final);
}

void tabela_dados(Lista *lista,Dados *dados){
    Lista *Laux=lista;
    while(Laux!=NULL){
        tab=insere_tabela(Laux,dados);
        Laux=Laux->proximo;
    }
    list_principal=NULL;
}

Tabela *insere_tabela(Lista *lista,Dados *dados){
    POS++;
    Tabela *final,*aux;
    aux=tab;
    final = (Tabela *)malloc(sizeof(Tabela));
    strcpy(final->id,lista->id);
    strcpy(final->tipo,dados->tipo);
    final->pos=POS;
    final->proximo=NULL;
    final->anterior=NULL;
    if(tab==NULL){
        return(final);
    }
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    aux->proximo=final;
    final->anterior=aux;
    return(tab);
}

void gerar(char *comando,char *tipo){
    if(inst==NULL)
        inst=(Instrucao *)malloc(sizeof(Instrucao));
    else
        inst=(Instrucao *)realloc(inst,sizeof(Instrucao)*(PROXINST+1)); //Alocamos tamanho para o vetor de instrucoes
    if(strcmp(tipo,"int")==0){//caso o tipo do comando passado seja inteiro -> Funcoes BIPUSH , ICONST_N , LDC
        int valor;
        valor=atoi(comando);
        if(valor>-128 && valor<127){ //FAZ A VERIFICACAO PARA BIPUSH
            if(valor==1){

            }
            else if(valor==2){

            }
            else if(valor==3){

            }
            else if(valor==4){

            }
            else if(valor==5){

            }
            else{//caso nao seja nenhum ICONS_N chamamos BIPUSH N
                inst[PROXINST].label=-1;
                strcpy(inst[PROXINST]._instrucao,strcat("bipush ",comando));
            }
        }
        else{//GUARDA A FUNCAO LDC

        }
    }
    else{ //caso o tipo do comando passado seja char -> PARA DEMAIS FUNCOES

    }
    PROXINST++;
}

void mostra_tabela(){
    Tabela *aux;
    aux=tab;
    printf("+-----+--------+--------+-----+-------+------+------+-------+------+-----+\n");
    printf("|                             .::Tabela ::.                              |\n");
    printf("+-----+--------+--------+-----+-------+------+------+-------+------+-----+\n");
    printf("|                  ID                    |        TIPO        |  POSICAO |\n");
    printf("+-----+--------+--------+-----+-------+------+------+-------+------+-----+\n");
    while(aux!=NULL){
        printf("|%40s|%20s|%10i|\n",aux->id,aux->tipo,aux->pos);
        aux=aux->proximo;
    }
    printf("+-----+--------+--------+-----+-------+------+------+-------+------+-----+\n");
}
