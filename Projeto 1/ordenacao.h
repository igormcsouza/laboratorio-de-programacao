#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <time.h>
#include <stdlib.h> // srand, rand
#include "instancias_ruins_Quicksort.hpp"

// Chamada de Funções
void quickSort_via_ponteiro(int *inicio, int *fim);

// Algoritmos auxiliares ------------------------------------------------------------------

// Troca Ponteiros
void troca(int *i, int *j){
	int aux;
	aux = *i; *i = *j; *j = aux;
}

// Algoritmo de Particionamento de Lomuto
int *particionamento(int *inicio, int *fim, int *pivo){
	troca(inicio, pivo); pivo = inicio;

	int *i = inicio; int *j = i + 1;

	for( ; j != fim + 1; j++)
		if(*j < *pivo){
			i++; troca(i, j);
		}
	
	troca(inicio, i); return i;
}

// Algoritmo de Particionamento Triplo
/* 
* Neste algoritmo, vamos particionar os elementos em 3 posições
* os menores, iguais e maiores.
* O princípio do algoritmo é o mesmo, só que se deve resovler
* para os 3 casos.
*/
void particionamento_triplo(int *inicio, int *fim, int *pivo, int **r, int **s){
	troca(inicio, pivo); pivo = inicio;

    int *m = inicio; int *i = inicio;
    int *j = i + 1;

    for (; j != fim + 1; j++){
        if (*j == *pivo){
            i++;
            troca(i, j);
        }
        if (*j < *pivo){
            m++; i++;
            troca(i, j);
            troca(i, m);
        }
    }
    troca(pivo, m);
    *r = m; *s = i;
}

// Algoritmo de Seleção de HOARE - Tempo Quadrádico
void selecao(int *inicio, int *idx, int *fim){
	int *pivo = particionamento(inicio, fim, fim);
	if(pivo > idx) selecao(inicio, idx, pivo-1);
	if(pivo < idx) selecao(pivo+1, idx, fim);
}

// Algoritmo de seleção BRFT
void bfprt(int *inicio, int *i, int *fim){
    if(fim < inicio) return;
	
    int k = 0;
    int *segmento = inicio;
	
    while(fim > segmento + 5){ // caso em que v[a...b] >= 5
		quickSort_via_ponteiro(segmento, segmento + 4);
		troca(inicio + k, segmento + 2); 
		segmento = segmento + 5;
		k++;
	}
	
	if(segmento < fim){ // Caso base, se v[a...b] < 5
		quickSort_via_ponteiro(segmento, fim);
		troca(inicio + k, segmento + (fim - segmento) / 2);
		k++;
	}

	bfprt(inicio, inicio + k / 2, inicio + k - 1);    

	int *Mediana = inicio;
    int *r = NULL;
    int *s = NULL;
    particionamento_triplo(inicio, fim, Mediana, &r, &s);
	
    if (i < r) bfprt(inicio, i, r - 1);
    if (i > s) bfprt(s + 1, i, fim);
}

// Recebe um valor e cria um vetor de aleatórios entre 0 e o 
// valor passado como parametro
int *vetor_aleatorio(int tam, int variedade){
	int *vetor = new int[tam];
  	srand (time(NULL)); /* initialize random seed: */

	for(int i = 0; i < tam; i++){
		vetor[i] = rand() % variedade;
	}

	return vetor;
}

// Escolhe pivo com base em um calculo
int escolher_pivo (int primeiro, int ultimo){
	return (primeiro + ultimo) - primeiro;
}

// QuickSort - ALGORITIMOS ---------------------------------

/* 1 - QuickSort via Indices
* Escolha fixa do pivo, baseada na função “escolher_pivo”, 
* usando ındices para percorrer o vetor, e com 2 chamadas 
* recursivas.
*/
void quickSort_via_indice(int *v, int inicio, int fim){
	if (inicio < fim){
		int p = escolher_pivo(inicio, fim);
		troca(&v[inicio], &v[p]); p = inicio;

		int i = inicio;
		for (int j = i + 1; j < fim + 1; j++)
			if (v[j] < v[p]){
				i++;
				troca(&v[i], &v[j]);
			}
		troca(&v[inicio], &v[i]);
		
		// Inicio do Quicksort 
		int pivo = i;
		quickSort_via_indice(v, inicio, pivo - 1);
		quickSort_via_indice(v, pivo + 1, fim);
	}
}

/* 2 - QuickSort via Ponteiros
* Semelhante  ao  anterior,  mas  usando  ponteiros,  tanto  
* nos parâmetros quando no percurso do vetor durante o algoritmo 
* de particionamento. Observação:  como é baseada em ponteiros, 
* não precisa fazer chamada explícita à função “escolher_pivo”, 
* mas deve fazer a mesma escolha de pivô que a vers ̃ao baseada 
* em  índices. (Opcional:  você pode inclusive escrever uma 
* versão baseada em ponteiros da função escolha do pivô.)
*/
void quickSort_via_ponteiro(int *inicio, int *fim){
	if (fim > inicio){
		int *pivo = particionamento(inicio, fim, fim);
		quickSort_via_ponteiro(inicio, pivo - 1);
		quickSort_via_ponteiro(pivo + 1, fim);
	}
}

/* 3 - QuickSort com economia de memória
* O(logn): Deve ser baseado em uma das 2 versoes anteriores, 
* mastransformando a chamada recursiva de cauda em um laço, 
* e fazendo a chamada recursivarestante sempre sobre a metade 
* de menor tamanho a ser ordenada
*/
void quickSort_memoria(int *inicio, int *fim){
	while (fim > inicio){
		int *pivo = particionamento(inicio, fim, fim);
		quickSort_memoria(inicio, pivo - 1);
		inicio = pivo + 1;		
	}
}

/* 4 - QuickSort usando Mediana das Medianas
* Deve escolher o pivô por meio do Algoritmo de Seleção 
* Linear BFPRT. Pode ser baseado em ındices ou em ponteiros.
*/
void quickSort_medmed(int *inicio, int *fim){
	if (fim > inicio){
		bfprt(inicio, inicio + (fim - inicio) / 2, fim);
		quickSort_medmed(inicio, inicio + (fim - inicio) / 2 - 1);
		quickSort_medmed(inicio + (fim - inicio) / 2 + 1, fim);		
	}
}

/* 5 - Quick Sort com pivo aleatório
Deve ser baseado numa das 2 primeiras versões, mas escolhendo 
o pivô (pseudo)aleatoriamente, via função “rand” ou 
semelhante.
*/
void quickSort_pivo_aleatorio(int *inicio, int *fim){
	srand (time(NULL)); /* initialize random seed: */
	if (fim > inicio){
		int *pivo = particionamento(inicio, fim, 
			rand() % (fim-inicio + 1) + inicio);
		quickSort_pivo_aleatorio(inicio, pivo - 1);
		quickSort_pivo_aleatorio(pivo + 1, fim);
	}
}

#endif