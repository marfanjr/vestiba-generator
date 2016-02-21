#include "mfvj11-bib.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define tam 10
/*-----------------------------------------------------------------------------------------------*/
// devolve um int pseudo-aleatório entre min e max, inclusives    
/*-----------------------------------------------------------------------------------------------*/
int sorteia(int min, int max) {
     srand(time(NULL));
    return min + (rand() % (max - min + 1));
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Verifica se um numero 'n' existe dentro de um vetor 'v' de tamanho 'tamanho'
/*-----------------------------------------------------------------------------------------------*/
int ja_existe (int n, int* v, int tamanho) {
    int i;
    for (i = 1; i <= tamanho; i++) {
	if (v[i] == n)
	    return 1;
    }
    return 0;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//Imprime uma questao e suas alternativas com ordem aleatoria
/*-----------------------------------------------------------------------------------------------*/
int Imprime(TipoApontaQuest q) {
    TipoApontaOp o;
    int i, j, pot, soma; int *v;
    j = 1; pot = 1; soma = 0;
    printf ("%s\n", q->enunciado);
    v = (int*) calloc( ((q->opcoes.Ultimo->Chave) + 1) , sizeof(int));
    while (j <= q->opcoes.Ultimo->Chave) {
        i = sorteia (q->opcoes.Primeiro->Prox->Chave, q->opcoes.Ultimo->Chave); // sorteia uma chave
        if (!ja_existe (i, v, q->opcoes.Ultimo->Chave)) {
	    v[j] = i; /* se a chave sorteada ainda nao existe em v entao ela é atribuida
		         à ultima posição de v, para que nao seja sorteada novamente. */
	    for (o = (*q).opcoes.Primeiro->Prox; (o != NULL); o = o->Prox) { //busca a chave
	        if (o->Chave == i) { //se encontrou a chave
	    	    printf ("%d) %s\n", pot, o->opcao); /* imprime a opcao correspondente à chave sorteada */
		    if (o->resp == 'V') /*se a resposta da alternativa for V acumula o numer dela no somatorio resposta correta*/
			soma = soma + pot;
		    pot = pot * 2;
	        }
            }
	    j++;
        }     
    }
    free (v);
    return soma;
}
/*-----------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------*/
//calcula nota de uma questao baseado no somatorio correto das alt e no somatorio dado pelo usuario
/*-----------------------------------------------------------------------------------------------*/
float nota_questao (int correta, int dada) {
    int c, d, cont_c, cont_d;
    cont_c = 0;
    cont_d = 0;
    do {
	c = correta % 2;
	d = dada % 2;
	if ( (c == 0) && (d == 1) ) { //se o usuario marcou uma alternativa errada retorna 0
	    return 0;
	}
	if (c == 1) // conta o numero de alternativa correta
	    cont_c++;
	if (d == 1) // conta o numero de alternativas marcadas como correta pelo usuario (exceto quando ele marca uma errada, neste caso retorna 0)
	    cont_d++;
        if (correta != 0)
	    correta = correta / 2;
        if (dada != 0)
	    dada = dada / 2;
    } while ( (correta != 0) || (dada != 0) );
    if ( cont_d < ( (2*(cont_c)) / 3 ) ) { //se acertou menos do que 2/3 das alternativas zera a nota da questao
	return 0;
    }
    return ( (float) cont_d / (float) cont_c );   
}
/*-----------------------------------------------------------------------------------------------*/

void main () {
    TipoApontaQuest q;
    int j = 1;
    int *v;
    int i, resposta_correta, resposta_dada;
    float nota = 0;
    TipoListaQuestoes prova;
    FLVaziaQ (&prova);
    system ("clear");
    le_arquivo (&prova); 
    v = (int *) calloc(prova.Ultimo->Chave + 1 , sizeof(int));
    while (j <= prova.Ultimo->Chave) {
        i = sorteia (prova.Primeiro->Prox->Chave, prova.Ultimo->Chave); //sorteia uma chave
	if (!ja_existe (i, v, prova.Ultimo->Chave)) {
	    v[j] = i; /* se a chave sorteada ainda nao existe em v entao ela é atribuida
		         à ultima posição de v, para que nao seja sorteada novamente. */
            for (q = prova.Primeiro->Prox; q != NULL; q = q->Prox) { //busca a chave.
	        if (q->Chave == i) { //se encontrou a chave
		    system ("clear");
	            resposta_correta = Imprime (q); /* imprime a questao correspondente à chave sorteada
						       e atribui à variavel o somatorio das respostas corretas */
		    printf ("\nResposta: ");
		    scanf ("%d", &resposta_dada); // le resposta do usuario
		    if (resposta_dada < 0) { //se o usuario entrar com um numero negatio imprime a nota até o momento e sai do programa.
			printf ("\nSua nota é: %.2f\n", (nota/(float)prova.Ultimo->Chave)*10);
			return;
		    }
		    nota = nota + nota_questao (resposta_correta, resposta_dada); //acumula a nota do aluno
	        }
            }
	    j++;
	}
    }
    free (v);
    printf ("\nSua nota é: %.2f\n", (nota/(float)prova.Ultimo->Chave)*10); //imprime a nota final
}
