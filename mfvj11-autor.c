#include "mfvj11-bib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define tam 10
/*-----------------------------------------------------------------------------------------------*/
//Imprime
/*-----------------------------------------------------------------------------------------------*/
void Imprime(TipoListaQuestoes Lista) {
    TipoApontaQuest q;
    TipoApontaOp o;
    for (q = Lista.Primeiro->Prox; q != NULL; q = q->Prox) {
	printf ("%d) %s\n", (*q).Chave, q->enunciado);
	for (o = (*q).opcoes.Primeiro->Prox; o != NULL; o = o->Prox)
	    printf ("    %d) %s  [%c]\n", o->Chave, o->opcao, o->resp);
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//MENUS
/*-----------------------------------------------------------------------------------------------*/
int menu1 (void) {
    int op;
    system ("clear");
    printf ("[1] Criar nova prova;\n");
    printf ("[2] Carregar prova existente;\n");
    printf ("[3] Sair;\n");
    scanf ("%d", &op);
    setbuf(stdin, NULL); //Limpa o buffer do teclado
    return op;
}
/*-----------------------------------------------------------------------------------------------*/
int menu11 (void) {
    int op;
    system ("clear");
    printf ("[1] Incluir questão;\n");
    printf ("[2] Alterar questão;\n");
    printf ("[3] Remover questão;\n");
    printf ("[4] Salvar prova em arquivo;\n");
    printf ("[5] Voltar ao menu anterior;\n");
    scanf ("%d", &op);
    setbuf(stdin, NULL); //Limpa o buffer do teclado
    return op;
}
/*-----------------------------------------------------------------------------------------------*/
int menu111 (void) {
    int op;
    system ("clear");
    printf ("[1] Incluir alternativa;\n");
    printf ("[2] Alterar alternativa;\n");
    printf ("[3] Remover alternativa;\n");
    printf ("[4] Voltar ao menu anterior;\n");
    scanf ("%d", &op);
    setbuf(stdin, NULL); //Limpa o buffer do teclado
    return op;
}
/*-----------------------------------------------------------------------------------------------*/
int menu112 (void) {
    int op;
    printf ("[1] Alterar enunciado;\n");
    printf ("[2] Incluir alternativa;\n");
    printf ("[3] Alterar alternativas;\n");
    printf ("[4] Remover alternativas;\n");
    printf ("[5] Voltar ao menu anterior;\n");
    scanf ("%d", &op);
    setbuf(stdin, NULL); //Limpa o buffer do teclado
    return op;   
}
/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//altera uma alternativa de uma dada questao
/*-----------------------------------------------------------------------------------------------*/
void altera_alternativa (TipoQuestao *Questao) {
    int i;
    TipoApontaOp o;
    system ("clear");
    printf ("%s\n", Questao->enunciado);
    for (o = (*Questao).opcoes.Primeiro->Prox; o != NULL; o = o->Prox)//imprime a questao para que o usuario possa escolher qual alternativa alterar
	printf ("    %d) %s  [%c]\n", o->Chave, o->opcao, o->resp);

    printf ("Digite o número da alternativa que deseja alterar: ");
    scanf ("%d", &i);
    setbuf(stdin, NULL); //Limpa o buffer do teclado
    for (o = (*Questao).opcoes.Primeiro->Prox; o != NULL; o = o->Prox) { //Busca a alternativa a ser alterada
	if (o->Chave == i) {
	    printf ("Digite novamente a alternativa %d: ", i);
	    lestring (&o->opcao);
	    printf ("Resposta (V para verdadeiro ou F para falso): ");
	    scanf("%c", &o->resp);
	}
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//remove uma alternativa de uma dada questao
/*-----------------------------------------------------------------------------------------------*/
void remove_alternativa (TipoQuestao *Questao) {
    char confirma;
    int i;
    int achou = 0;
    TipoApontaOp o, aux;
    do {
	system ("clear");
        printf ("%s\n", Questao->enunciado);
        for (o = (*Questao).opcoes.Primeiro->Prox; o != NULL; o = o->Prox) //imprime a questao para que o usuario possa escolher qual alternativa alterar
	    printf ("    %d) %s  [%c]\n", o->Chave, o->opcao, o->resp);
    
	printf ("Digite o número da questao que deseja remover: ");
	scanf ("%d", &i);
	setbuf(stdin, NULL); //Limpa o buffer do teclado
    } while ( ((*Questao).opcoes.Primeiro->Prox->Chave > i) || ((*Questao).opcoes.Ultimo->Chave < i) ); //enquanto nao entrar um valor valido
    printf ("Tem certeza que deseja remover a questao %d?(s/n) ", i);
    scanf ("%c", &confirma);
    if (confirma == 's'){
        for (o = (*Questao).opcoes.Primeiro; (o != NULL) && (!achou); o = o->Prox) { //busca a chave
	    if (o->Prox->Chave == i) {
    	        aux = o->Prox;
    	        o->Prox = aux->Prox;
	        if (o->Prox == NULL)
	            (*Questao).opcoes.Ultimo = o;
	        free(aux);
	        aux = o->Prox;
	        while (aux != NULL){ 
	    	    aux->Chave = aux->Chave - 1;
		    aux = aux->Prox;
	        }
		achou = 1;
	    }
	}
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//altera uma questao de uma dada lista de questoes
/*-----------------------------------------------------------------------------------------------*/
void altera_questao (TipoListaQuestoes *Lista) {
    int i, op;
    TipoApontaQuest q;
    TipoApontaOp o;
    TipoOpcao alternativa;
    system ("clear");
    Imprime (*Lista);

    printf ("Digite o número da questão que deseja alterar: ");
    scanf ("%d", &i);
    setbuf(stdin, NULL); //Limpa o buffer do teclado
    for (q = Lista->Primeiro->Prox; q != NULL; q = q->Prox) { //Busca a alternativa a ser alterada
	if (q->Chave == i) {
	    system ("clear");
	    printf ("%d) %s\n", (*q).Chave, q->enunciado);
	    for (o = (*q).opcoes.Primeiro->Prox; o != NULL; o = o->Prox)
		printf ("    %d) %s\n", o->Chave, o->opcao);
	    op = menu112();
	    switch (op) {
		case 1://alterar enunciado
		    printf ("Digite novamente o enunciado da questao %d: ", i);
		    lestring (&q->enunciado);
		    break;
		case 2: //incluir alternativa
		    printf ("Alternativa: ");
		    lestring (&alternativa.opcao);
		    printf ("Resposta (V para verdadeiro ou F para falso): ");
		    scanf("%c", &alternativa.resp);
		    InsereOp (alternativa, &q->opcoes);
		    break;
		case 3://alterar alternativa
		    if (!VaziaO(q->opcoes))
			altera_alternativa (q);
		    break;
		case 4://Remover alternativa;
		    if (!VaziaO(q->opcoes))
			remove_alternativa (q);
		    break;
		default://voltar ao menu anterior (OPÇÃO 5)
		    break;
	    }
	}
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//remove uma questao de uma dada lista de questoes
/*-----------------------------------------------------------------------------------------------*/
void remove_questao (TipoListaQuestoes *Lista) {
    int i; char confirma;
    int achou = 0;
    TipoApontaQuest q, aux;
    do {
	system ("clear");
	Imprime (*Lista);
    
	printf ("Digite o número da questao que deseja remover: ");
	scanf ("%d", &i);
	setbuf(stdin, NULL); //Limpa o buffer do teclado
    } while ( ((*Lista).Primeiro->Prox->Chave > i) || ((*Lista).Ultimo->Chave < i) ); //enquanto nao entrar um valor valido
    printf ("Tem certeza que deseja remover a questao %d?(s/n) ", i);
    scanf ("%c", &confirma);
    if (confirma == 's'){
	for (q = (*Lista).Primeiro; (q != NULL) && (!achou); q = q->Prox) { //busca a chave
	    if (q->Prox->Chave == i) {
    		aux = q->Prox;
    		q->Prox = aux->Prox;
		if (q->Prox == NULL)
		    Lista->Ultimo = q;
	        free(aux);
	        aux = q->Prox;
	        while (aux != NULL){ 
	    	    aux->Chave = aux->Chave - 1;
		    aux = aux->Prox;
	        }
	        achou = 1;
	    }
        }
    }
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//inclui uma questao e alternativas em uma lista de questoes
/*-----------------------------------------------------------------------------------------------*/
void incluir_questao (TipoListaQuestoes *Lista) {
    int op;
    TipoOpcao alternativa;
    TipoQuestao questao;
    FLVaziaO (&questao.opcoes);
    printf ("Enunciado: \n");
    lestring (&questao.enunciado);

    do {
	op = menu111 ();
	switch (op) {
	    case 1://inserir alternativa 
		printf ("Alternativa: ");
		lestring (&alternativa.opcao);
		printf ("Resposta (V para verdadeiro ou F para falso): ");
		scanf("%c", &alternativa.resp);
		InsereOp (alternativa, &questao.opcoes);
	        break;
	    case 2: //Alterar alternativa
		if (!VaziaO(questao.opcoes))
		    altera_alternativa (&questao);
	        break;
	    case 3: //remover alternativa
		if (!VaziaO(questao.opcoes))
		    remove_alternativa (&questao);
	        break;
	    default://voltar ao menu anterior (OPÇÃO 4)
	        break;
        }
    } while (op != 4);

    if (!VaziaO (questao.opcoes)) //se a lista de alternativas estiver vazia nao insere a questao na lista de questoes
	InsereQuestao (questao, Lista);
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//salva
/*-----------------------------------------------------------------------------------------------*/
void salva(TipoListaQuestoes Lista) {
    TipoApontaQuest q;
    TipoApontaOp o;
    FILE *fp;
    char *arquivo;
    printf ("Digite o nome do arquivo que deseja salvar: ");
    lestring (&arquivo);
    fp = fopen(arquivo, "w");
    fprintf (fp, "{\n");
    for (q = Lista.Primeiro->Prox; q != NULL; q = q->Prox) {
	fprintf (fp, "  {%s\n", q->enunciado);
	for (o = (*q).opcoes.Primeiro->Prox; o != NULL; o = o->Prox){
	    fprintf (fp, "    {%s {%c}}\n", o->opcao, o->resp);
	    free (o);
	}
	fprintf (fp, "  }\n");
	free (q);
    }
    fprintf (fp, "}");
    fclose(fp);
}
/*-----------------------------------------------------------------------------------------------*/

void main () {
    int op;
    TipoListaQuestoes prova;
    FLVaziaQ (&prova);
    do {
	op = menu1();
	switch (op) {
	    case 1: //criar nova prova
		do {
		    op = menu11();
		    switch (op) {
			case 1: //incluir questao
			    incluir_questao (&prova);
			    break;
			case 2: //alterar questao
			    if (!VaziaQ(prova))
				altera_questao (&prova);
			    break;
			case 3: //remover questao
			    if (!VaziaQ(prova))
				remove_questao (&prova);
			    break;
			case 4: //salvar em arquivo
			    if (!VaziaQ(prova))
				salva (prova);
			    break;
			case 5: //voltar ao menu anterior
			    break;
		    }
		} while (op != 5);
		break;
	    case 2: //carregar prova de arquivo
		le_arquivo (&prova);
		do {
		    op = menu11();
		    switch (op) {
			case 1: //incluir questao
			    incluir_questao (&prova);
			    break;
			case 2: //alterar questao
			    if (!VaziaQ(prova))
				altera_questao (&prova);
			    break;
			case 3: //remover questao
			    if (!VaziaQ(prova))
				remove_questao (&prova);
			    break;
			case 4: //salvar em arquivo
			    if (!VaziaQ(prova))
				salva (prova);
			    break;
			case 5: //voltar ao menu anterior
			    break;
		    }
		} while (op != 5);
		break;
	    default: //sair
		op = 3;
		break;
        }
    } while (op != 3);

}
