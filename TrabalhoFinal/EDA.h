#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAMANHO_VARIAVEL 40
typedef struct lista{
    struct lista *proximo;
    struct lista *anterior;
    char id[50];
}Lista;

typedef struct tabela{
    struct tabela *proximo;
    struct tabela *anterior;
    char id[TAMANHO_VARIAVEL];
    char tipo[20];
    int pos;
}Tabela;

typedef struct dados{
    char tipo[50];
    int constante;
    char id[50];
}Dados;

typedef struct instrucao{
    int label,_instrucao,p1,p2;
}Instrucao;

void mostra_lista();
void insere_lista(char id[TAMANHO_VARIAVEL]);
void tabela_dados(Lista *lista,Dados *dados);
void mostra_tabela();
void mostra_gerar();
void insere_dados(char *lido);
void cria_jasmin();
int procura_tabela(char id[TAMANHO_VARIAVEL]);
Lista *inserefim_lista(Lista *dados,char id[TAMANHO_VARIAVEL]);
Dados *inserefim_dados(char *lido);
Tabela *insere_tabela(Lista *lista,Dados *dados);

int POS=0;//iniciamos as posicoes da tabela.
int PROXINST=0;//iniciamos as posicoes das intrucoes
Lista *list_principal=NULL; //inicia a lista vazia
Tabela *tab=NULL;//inicia a tabela vazia
Dados *dados_principal;//inicia os dados vazios
Instrucao *inst=NULL;//Iniciamos o vetor de instrucoes vazio

void insere_lista(char id[TAMANHO_VARIAVEL]){
    list_principal=inserefim_lista(list_principal,id);
}

Lista *inserefim_lista(Lista *dados,char id[TAMANHO_VARIAVEL]) {
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

void gerar(int comando,int p1, int p2){
    if(inst==NULL)
        inst=(Instrucao *)malloc(sizeof(Instrucao));
    else
        inst=(Instrucao *)realloc(inst,sizeof(Instrucao)*(PROXINST+1)); //Alocamos tamanho para o vetor de instrucoes
    if(comando==20){ //BIPUSH
        if(p1> -128 && p1<127){//verifica se é BIPUSH OU ICONST SE NAO FOR É LDC
            if(p1==0){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=10;
            }
            else if(p1==1){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=11;
            }
            else if(p1==2){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=12;
            }
            else if(p1==3){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=13;
            }
            else if(p1==4){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=14;
            }
            else if(p1==5){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=15;
            }
            else{
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=p1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=20;
            }
        }
        else{//É LDC
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=21;
        }
    }
    else if(comando==16){ //ILOAD
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=p1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=16;
    }
    else if(comando==17){ //ISTORE
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=p1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=17;
    }
    else if(comando==18){//IADD
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=18;
    }
    else if(comando==19){//IMULL
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=19;
    }
    else if(comando==22){//IDIV
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=22;
    }
    else if(comando==23){//ISUB
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=23;
    }
    else if(comando==30){//PRINT_INT
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=p1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=30;
    }
    PROXINST++;
}

int procura_tabela(char id[TAMANHO_VARIAVEL]){
    Tabela *aux;
    aux=tab;
    while(aux!=NULL){
        if(strcmp(aux->id,id)==0)
            return(aux->pos);
        if(aux->proximo!=NULL)
            aux=aux->proximo;
        else
            return(-1);
    }
}

void mostra_gerar(){
    int i;
    for(i=0;i<PROXINST;i++){
        printf("LABEL: %i\tP1: %i\tP2: %i\t _INSTRUCAO: %i\n",inst[i].label,inst[i].p1,inst[i].p2,inst[i]._instrucao);
    }
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

void cria_jasmin(){
    FILE *fp;
    int i,valor_label=0;
    fp=fopen("entradaJasmin.j","w");
	if(!fp){
        puts("Erro na abertura do arquivo Jasmin\n");
        exit(0);
	}
	else{
        fprintf(fp,".class public entradaJasmin\n.super java/lang/Object\n\n.method public <init>()V\n   aload_0\n\n   invokenonvirtual java/lang/Object/<init>()V\n   return\n.end method\n\n");
        fprintf(fp,".method public static main([Ljava/lang/String;)V\n   .limit stack 2\n   .limit locals %i\n",POS);
        for(i=0;i<PROXINST;i++){
            if(inst[i].label!=-1){
                valor_label++;
                fprintf(fp," l%i\n",valor_label);
            }
            if(inst[i]._instrucao>=10 && inst[i]._instrucao<=15){//escreve iconst_n
                fprintf(fp,"   iconst_%i\n",inst[i]._instrucao-10);
            }
            else if(inst[i]._instrucao==16 && inst[i+1]._instrucao!=30){//escreve iload
                fprintf(fp,"   iload %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==17){//escreve istore
                fprintf(fp,"   istore %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==18){//escreve iadd
                fprintf(fp,"   iadd\n");
            }
            else if(inst[i]._instrucao==19){//escreve imul
                fprintf(fp,"   imul\n");
            }
            else if(inst[i]._instrucao==20){//escreve bipush
                fprintf(fp,"   bipush %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==21){//escreve ldc
                fprintf(fp,"   ldc %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==22){//escreve idiv
                fprintf(fp,"   idiv\n");
            }
            else if(inst[i]._instrucao==23){//escreve isub
                fprintf(fp,"   isub\n");
            }
            else if(inst[i]._instrucao==30){//PRINT de INT
                fprintf(fp,"   getstatic java/lang/System/out Ljava/io/PrintStream;\n");
                fprintf(fp,"   iload %i\n",inst[i].p1);
                fprintf(fp,"   invokevirtual java/io/PrintStream/println(I)V\n");
            }
            /*else if(inst[i]._instrucao==31){//PRINT de STRING
                fprintf(fp,"getstatic java/lang/System/out Ljava/io/PrintStream\n");
                fprintf(fp,"ldc \"%s\"\n",inst[i].s);
                fprintf(fp,"invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
            }*/
        }
        fprintf(fp,"   return\n.end method\n");
	}
	fclose(fp);
}
