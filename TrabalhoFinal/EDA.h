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
    int constante,valor;
    char id[50];
    char str[500];
}Dados;

typedef struct instrucao{
    int label,_instrucao,p1,p2;
    char str[500];
}Instrucao;

void mostra_lista();
void insere_lista(char id[TAMANHO_VARIAVEL]);
void tabela_dados(Lista *lista,Dados *dados);
void mostra_tabela();
void mostra_gerar();
void insere_dados(char *lido);
void cria_jasmin();
char *procura_tabela_tipo(int p1);
int procura_tabela(char id[TAMANHO_VARIAVEL]);
Lista *inserefim_lista(Lista *dados,char id[TAMANHO_VARIAVEL]);
Dados *inserefim_dados(char *lido);
Tabela *insere_tabela(Lista *lista,Dados *dados);

int POS=0;//iniciamos as posicoes da tabela.
int PROXINST=0;//iniciamos as posicoes das intrucoes
int LABEL_VALOR=1;
int _LABEL_VALOR=1;
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

void gerar(int comando,int p1, int p2,char p3[500]){
    if(inst==NULL)
        inst=(Instrucao *)malloc(sizeof(Instrucao));
    else
        inst=(Instrucao *)realloc(inst,sizeof(Instrucao)*(PROXINST+1)); //Alocamos tamanho para o vetor de instrucoes
    if(comando==20){ //BIPUSH
        if(strcmp(p3,"\0")==0){
            if(p1==-1 && p2==-2){
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=-1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=10;
                strcpy(inst[PROXINST].str,p3);
            }
            else if(p1> -128 && p1<127){//verifica se é BIPUSH OU ICONST SE NAO FOR É LDC
                if(p1==0){
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=-1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=10;
                    strcpy(inst[PROXINST].str,"\0");
                }
                else if(p1==1){
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=-1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=11;
                    strcpy(inst[PROXINST].str,"\0");
                }
                else if(p1==2){
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=-1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=12;
                    strcpy(inst[PROXINST].str,"\0");
                }
                else if(p1==3){
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=-1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=13;
                    strcpy(inst[PROXINST].str,"\0");
                }
                else if(p1==4){
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=-1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=14;
                    strcpy(inst[PROXINST].str,"\0");
                }
                else if(p1==5){
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=-1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=15;
                    strcpy(inst[PROXINST].str,"\0");
                }
                else{
                    inst[PROXINST].label=-1;
                    inst[PROXINST].p1=p1;
                    inst[PROXINST].p2=-1;
                    inst[PROXINST]._instrucao=20;
                    strcpy(inst[PROXINST].str,"\0");
                }
            }
            else{//É LDC QUE GRAVAREMOS DE NUMERO
                inst[PROXINST].label=-1;
                inst[PROXINST].p1=p1;
                inst[PROXINST].p2=-1;
                inst[PROXINST]._instrucao=21;
                strcpy(inst[PROXINST].str,"\0");
            }
        }
        else{//É LDC DE STRING
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=26;
            strcpy(inst[PROXINST].str,p3);
        }
    }
    else if(comando==16){ //ILOAD
        if(strcmp(inst[PROXINST-1].str,"\0")==0){
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=16;
            strcpy(inst[PROXINST].str,"\0");
        }
        else{
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=25;//escreve aload
            strcpy(inst[PROXINST].str,p3);
        }
    }
    else if(comando==17){ //ISTORE
        if(strcmp("\0",p3)==0){
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=17;
            strcpy(inst[PROXINST].str,"\0");
        }
        else{//ASTORE
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=24;
            strcpy(inst[PROXINST].str,p3);
        }
    }
    else if(comando==18){//IADD
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=18;
        strcpy(inst[PROXINST].str,"\0");
    }
    else if(comando==19){//IMULL
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=19;
        strcpy(inst[PROXINST].str,"\0");
    }
    else if(comando==22){//IDIV
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=22;
        strcpy(inst[PROXINST].str,"\0");
    }
    else if(comando==23){//ISUB
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=23;
        strcpy(inst[PROXINST].str,"\0");
    }
    else if(comando==30){//PRINT_INT
        if(strcmp("int",procura_tabela_tipo(p1))==0){
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=30;
            strcpy(inst[PROXINST].str,"\0");
        }
        else{
            inst[PROXINST].label=-1;
            inst[PROXINST].p1=p1;
            inst[PROXINST].p2=-1;
            inst[PROXINST]._instrucao=32;
            strcpy(inst[PROXINST].str,p3);
        }
    }
    else if(comando==31){//PRINT_STG
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=31;
        strcpy(inst[PROXINST].str,p3);
    }
    else if(comando==40){
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=40;
        strcpy(inst[PROXINST].str,"\0");
    }
    else if(comando==50){//IF
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=50;
        strcpy(inst[PROXINST].str,p3);
    }
    else if(comando==90){//LABEL
        inst[PROXINST].label=p1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=90;
        strcpy(inst[PROXINST].str,"\0");
    }
    else if(comando==98){//GOTO
        inst[PROXINST].label=-1;
        inst[PROXINST].p1=-1;
        inst[PROXINST].p2=-1;
        inst[PROXINST]._instrucao=98;
        strcpy(inst[PROXINST].str,"\0");
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

char *procura_tabela_tipo(int p1){
    Tabela *aux;
    aux=tab;
    while(aux->pos!=p1){
        if(aux->proximo!=NULL)
            aux=aux->proximo;
        else
            return("\0");
    }
    return(aux->tipo);
}

void mostra_gerar(){
    int i;
    for(i=0;i<PROXINST;i++){
        printf("LABEL: %i\tP1: %i\tP2: %i\t _INSTRUCAO: %i STR: %s\n",inst[i].label,inst[i].p1,inst[i].p2,inst[i]._instrucao,inst[i].str);
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
    int i;
    fp=fopen("entradaJasmin.j","w");
	if(!fp){
        puts("Erro na abertura do arquivo Jasmin\n");
        exit(0);
	}
	else{
        fprintf(fp,".class public entradaJasmin\n.super java/lang/Object\n\n.method public <init>()V\n   aload_0\n\n   invokenonvirtual java/lang/Object/<init>()V\n   return\n.end method\n\n");
        fprintf(fp,".method public static main([Ljava/lang/String;)V\n   .limit stack 10\n   .limit locals %i\n",POS+1);
        for(i=0;i<PROXINST;i++){
            if(inst[i]._instrucao>=10 && inst[i]._instrucao<=15){//escreve iconst_n
                fprintf(fp,"   iconst_%i\n",inst[i]._instrucao-10);
            }
            else if(inst[i]._instrucao==16){//escreve iload
                if(strcmp("int",procura_tabela_tipo(inst[i].p1))==0)
                    fprintf(fp,"   iload %i\n",inst[i].p1);
                else
                    fprintf(fp,"   aload %i\n",inst[i].p1);
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
            else if(inst[i]._instrucao==21){//escreve ldc int
                fprintf(fp,"   ldc %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==22){//escreve idiv
                fprintf(fp,"   idiv\n");
            }
            else if(inst[i]._instrucao==23){//escreve isub
                fprintf(fp,"   isub\n");
            }
            else if(inst[i]._instrucao==24){//escreve astore
                fprintf(fp,"   astore %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==25){//escreve aload
                fprintf(fp,"   aload %i\n",inst[i].p1);
            }
            else if(inst[i]._instrucao==26){//escreve ldc string
                fprintf(fp,"   ldc %s\n",inst[i].str);
            }
            else if(inst[i]._instrucao==30){//PRINT de INT
                fprintf(fp,"   invokevirtual java/io/PrintStream/println(I)V\n");
            }
            else if(inst[i]._instrucao==31){//PRINT de Literal
                fprintf(fp,"   ldc %s\n",inst[i].str);
                fprintf(fp,"   invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
            }
            else if(inst[i]._instrucao==32){//PRINT de STRING
                fprintf(fp,"   invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
            }
            else if(inst[i]._instrucao==40){//PRINT
                fprintf(fp,"   getstatic java/lang/System/out Ljava/io/PrintStream;\n");
            }
            else if(inst[i]._instrucao==50){//IF
                fprintf(fp,"   if_icmp%s l%i\n",inst[i].str,LABEL_VALOR);
                LABEL_VALOR++;
            }
            else if(inst[i]._instrucao==90){//LABEL
                fprintf(fp,"l%i:\n",_LABEL_VALOR);
                _LABEL_VALOR++;
            }
            else if(inst[i]._instrucao==98){//GOTO
                fprintf(fp,"   goto l%i\n",LABEL_VALOR);
                LABEL_VALOR++;
            }
        }
        fprintf(fp,"   return\n.end method\n");
	}
	fclose(fp);
}
