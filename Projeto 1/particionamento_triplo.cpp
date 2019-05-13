//g++ -Wall -Wextra -std=c++17 -pedantic -o particionamento_triplo particionamento_triplo.cpp

#include <iostream>

using namespace std;

void troca(int *i, int *j){
	int aux;
	aux = *i; *i = *j; *j = aux;
}

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

int *vetor_aleatorio(int tam){
	int *vetor = new int[tam];
  	srand (time(NULL)); /* initialize random seed: */

	for(int i = 0; i < tam; i++){
		vetor[i] = rand() % 101;
	}

	return vetor;
}

int main(){

	int tam = 100;
	int *v = vetor_aleatorio(tam);

	cout << "Before: ";
	for(int i=0; i<tam; i++){ cout << *(v + i) << " "; }
	cout << endl;

	int *tmp = particionamento_triplo(v, v+(tam-1), v);

	cout << " Done!" << endl;

	cout << "After: ";
	for(int i=0; i<tam; i++)
		cout << v[i] << " ";
	cout << endl;

	return 0;
}