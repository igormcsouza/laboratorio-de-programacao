//g++ -Wall -Wextra -std=c++17 -pedantic -o project project.cpp

#include <iostream>
#include <time.h>
#include <stdlib.h>     /* srand, rand */
#include "instancias_ruins_Quicksort.hpp"

using namespace std;

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
int *particionamento_triplo(int *inicio, int *fim, int *pivo){
	troca(inicio, pivo);
	pivo = inicio;

	// M é o último menor, i é o último igual e j é o elemento
	// de iteração.

	int *m = inicio; int *i = inicio; int *j = i + 1;

	for( ; j != fim + 1; j++){
		if(*j < *pivo){
			i++; troca(i, j);
			m++; troca(m, i);
		}
		if(*j == *pivo){
			j++; troca(i, j);
		}
	}

	troca(inicio, i);
	return i;
}

// Algoritmo de Seleção de HOARE - Tempo Quadrádico
void selecao(int *inicio, int *idx, int *fim){
	int *pivo = particionamento(inicio, fim, fim);
	if(pivo > idx) selecao(inicio, idx, pivo-1);
	if(pivo < idx) selecao(pivo+1, idx, fim);
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
			if (v[j] < v[p])
			{
				i++;
				troca(&v[i], &v[j]);
			}
		troca(&v[inicio], &v[i]);
		
		// Inicio do Quicksort 
		int pivo = i;
		quickSort_via_indice(v, 0, pivo - 1);
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
void quickSort_medmed(int *inicio, int *fim, int med){
	if (fim > inicio){
		selecao(inicio, inicio, fim);
		quickSort_medmed(inicio, inicio + med, int(med/2));
		quickSort_medmed(inicio + med, fim, int(med/2));		
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

// Funções extras ------------------------------------------

// Recebe um valor e cria um vetor de aleatórios entre 0 e o 
// valor passado como parametro
int *vetor_aleatorio(int tam){
	int *vetor = new int[tam];
  	srand (time(NULL)); /* initialize random seed: */

	for(int i = 0; i < tam; i++){
		vetor[i] = rand() % 101;
	}

	return vetor;
}

// Escolhe pivo com base em um calculo
int escolher_pivo (int primeiro, int ultimo){
	return (primeiro + ultimo) - primeiro;
}

int main(){
	int tam = 10;
	bool keep = true;

	while(keep){
		system("clear");

		int *v = vetor_aleatorio(tam);

		cout << "Before: ";
		for(int i=0; i<tam; i++){ cout << *(v + i) << " "; }
		cout << endl;

		int escolha = 0;

		cout <<"1-Indice; 2-Ponteiro; 3-Memoria; 4-Mediana; 5-Pivo Aleatório" << endl;
		while((escolha < 1) || (escolha > 5)){
			cout << "Escolha o método: ";
			cin >> escolha;
		}

		const clock_t begin_time = clock();
		cout << "Sorting the Vector...";

		// TESTES ----------------------------------------------
		if(escolha == 1) quickSort_via_indice(v, 0, tam - 1);
		if(escolha == 2) quickSort_via_ponteiro(v, v+(tam-1));
		if(escolha == 3) quickSort_memoria(v, v+(tam-1));
		if(escolha == 4) quickSort_medmed(v, v+(tam-1), tam/2);
		if(escolha == 5) quickSort_pivo_aleatorio(v, v+(tam-1));

		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/1000;
		cout << "s" << endl;

		cout << "After: ";
		for(int i=0; i<tam; i++)
			cout << v[i] << " ";
		cout << endl;

		cout << "Continuar? 1/0: ";
		cin >> keep;
	}

	

	return 0;
}