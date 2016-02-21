#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define tam 10
typedef int TipoChave;
typedef struct Questao *TipoApontaQuest;
typedef struct Opcao *TipoApontaOp;

typedef struct Opcao {
    TipoChave Chave;
    char *opcao;
    char resp;
    TipoApontaOp Prox;
} TipoOpcao;

typedef struct  {
    TipoApontaOp Primeiro, Ultimo;
} TipoListaOpcoes;

typedef struct Questao {
    TipoChave Chave;
    char *enunciado;
    TipoListaOpcoes opcoes;
    TipoApontaQuest Prox;
} TipoQuestao;

typedef struct {
    TipoApontaQuest Primeiro, Ultimo;
} TipoListaQuestoes;

/*-----------------------------------------------------------------------------------------------*/
//Retorna TRUE se a lista de Questoes está vazia
/*-----------------------------------------------------------------------------------------------*/
int VaziaQ(TipoListaQuestoes Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Retorna TRUE se a lista de Opcoes está vazia
/*-----------------------------------------------------------------------------------------------*/
int VaziaO(TipoListaOpcoes Lista) {
    return (Lista.Primeiro == Lista.Ultimo);
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Faz uma Lista de Questoes Ficar Vazia
/*-----------------------------------------------------------------------------------------------*/
void FLVaziaQ(TipoListaQuestoes *Lista) {
    Lista->Primeiro = malloc(sizeof *(Lista->Primeiro));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Chave = 0;
    Lista->Primeiro->Prox = NULL;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Faz uma Lista de Opcoes Ficar Vazia
/*-----------------------------------------------------------------------------------------------*/
void FLVaziaO(TipoListaOpcoes *Lista) {
    Lista->Primeiro = malloc(sizeof *(Lista->Primeiro));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Chave = 0;
    Lista->Primeiro->Prox = NULL;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Insere uma questao x em uma lista de questoes
/*-----------------------------------------------------------------------------------------------*/
void InsereQuestao(TipoQuestao x, TipoListaQuestoes *Lista) {
    Lista->Ultimo->Prox = malloc(sizeof *(Lista->Ultimo->Prox));
    x.Chave = Lista->Ultimo->Chave + 1;
    Lista->Ultimo = Lista->Ultimo->Prox;
    *(Lista->Ultimo) = x;
    Lista->Ultimo->Prox = NULL;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Insere uma opcao x em uma lista de opcoes
/*-----------------------------------------------------------------------------------------------*/
void InsereOp(TipoOpcao x, TipoListaOpcoes *Lista) {
    Lista->Ultimo->Prox = malloc(sizeof *(Lista->Ultimo->Prox));
    x.Chave = Lista->Ultimo->Chave + 1;
    Lista->Ultimo = Lista->Ultimo->Prox;
    *(Lista->Ultimo) = x;
    Lista->Ultimo->Prox = NULL;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//função para ler uma string
/*-----------------------------------------------------------------------------------------------*/
void lestring(char **str) {
    char c;
    int i = 0, j = 0;
    
    *str = (char *) malloc(10 * sizeof(char) + 1);

    do {
	    c = fgetc (stdin);
        if (j == 10) {
            *str = (char *) realloc(*str, strlen(*str) + 10 * sizeof(char) + 1);
            j = 1;
        }
        (*str)[i] = c;
        i++; j++;
    } while (c != '\n');
    (*str)[i-1] = '\0';
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//le o proximo item lexico apontado pelo arquivo dado 
/*-----------------------------------------------------------------------------------------------*/
char* Proximo_item_lexico(FILE *arquivo) {
    char c;
    char *acumulado;
    int separou_simbolo = 0;
    int durante_acumulo = 0; int i = 0; int j = 1;
    acumulado = NULL;
    acumulado = (char *) malloc(10 * sizeof(char) + 1);

    while (!separou_simbolo){
        c = fgetc (arquivo);

        if (j == 10) {
            acumulado = (char *) realloc(acumulado, strlen(acumulado) + 10* sizeof(char) + 1);
            j = 1;
        }
        switch (c) {
            case '{':
		if (strlen (acumulado) == 0) {
                    acumulado[i] = c;
		    i++;
		}
		else 
		    fseek(arquivo, -1, SEEK_CUR);
                separou_simbolo = 1;
                break;
            case '}':
		if (strlen (acumulado) == 0) {
                    acumulado[i] = c;
		    i++;
		}
		else 
		    fseek(arquivo, -1, SEEK_CUR);
                separou_simbolo = 1;
                i++;
                break;
            case ' ': // Ignore brancos
                if (durante_acumulo) {
		    acumulado[i] = c;
		    i++;
		} 
                break;
            case '\n':
                if (durante_acumulo)
                    separou_simbolo = 1;
                break;
	    case EOF:
		return NULL;
		break;
            default:
                acumulado[i] = c;
                durante_acumulo = 1;
                i++;
        }
        j++;
    }
    acumulado[i] = '\0';
    return acumulado;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//le uma prova e salva em uma lista de questoes
/*-----------------------------------------------------------------------------------------------*/
void le_arquivo (TipoListaQuestoes *Lista) {
    FILE *fp;
    char *arquivo;
    char *str;
    int abriu_questao = 0;
    int abriu_alternativa = 0;
    TipoOpcao alternativa;
    TipoQuestao questao;

    do {
        printf ("Digite o nome do arquivo que deseja abrir: ");
        lestring (&arquivo);
    
        fp = fopen(arquivo, "r");
        if (fp == NULL)
	    printf ("Nome de arquivo invalido\n");
    } while (fp == NULL);
    str = Proximo_item_lexico(fp); //le '{' abre prova
    do {
	str = Proximo_item_lexico(fp); //le '{' abre questao
	if ( (str != NULL) && (strcmp (str, "{") == 0) ) {
	    free(str);
	    abriu_questao = 1;
	    FLVaziaO (&questao.opcoes);
	    questao.enunciado = Proximo_item_lexico(fp); //le enunciado
	    do {
		str = Proximo_item_lexico(fp);
		if ( (str != NULL) && (strcmp (str, "{") == 0) ) {//le '{' abre alternativa
		    free(str);
		    abriu_alternativa = 1;
		    alternativa.opcao = Proximo_item_lexico(fp); //le alternativa
		    str = Proximo_item_lexico(fp); //le '{' abre resposta
		    free(str);
		    str = Proximo_item_lexico(fp);//le resposta V ou F
		    alternativa.resp = str[0];
		    free(str);
		    str = Proximo_item_lexico(fp);//le '}' fecha resposta
		    free(str);
		    str = Proximo_item_lexico(fp);//le '}' fecha alternativa
		    free(str);
		    InsereOp (alternativa, &questao.opcoes);
		}
		else if ( (str != NULL) && (strcmp (str, "}") == 0) ) {
		    free(str);
		    abriu_alternativa = 0;
		}
	    } while ( (abriu_alternativa) );
		InsereQuestao (questao, Lista);	    
	}
	else if ( (str != NULL) && (strcmp (str, "}") == 0) ){
	    free(str);
	    abriu_questao = 0;
	}
    } while ( (str != NULL) && (abriu_questao) );
}
/*-----------------------------------------------------------------------------------------------*/

