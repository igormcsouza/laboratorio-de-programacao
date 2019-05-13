//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto2 projeto2.cpp

#include "gerador.h"
#include "buscador.h"

using namespace std;

int main(){

	int tamTexto = 15, tamPadrao = 2, variedade = 3;

	char *texto = gerador_aleatorio(tamTexto, variedade);
	for(int i = 0; i < tamTexto; i++) cout << *(texto + i) << " ";
	cout << endl;
	char *padrao = gerador_aleatorio(tamPadrao, variedade);
	//char padrao[2] = {'a', 'b'};
	for(int i = 0; i < tamPadrao; i++) cout << *(padrao + i) << " ";
	cout << endl;

	// TESTE INTUITIVO -------------------------------------------------------------
	int start = clock();
	int *vetor = busca_sequencia(texto, padrao, tamTexto, tamPadrao);
	for(int i = 0; i < tamTexto; i++) cout << *(vetor + i) << ", ";
	cout << "INTUITIVO - Tempo Transcorrido: " << clock() - start << "ms" << endl;

	// TESTE KMP --------------------------------------------------------------------
	start = clock();
	vetor = kmp(texto, padrao, tamTexto, tamPadrao);
	for(int i = 0; i < tamTexto; i++) cout << *(vetor + i) << ", ";
	cout << "KMP - Tempo Transcorrido: " << clock() - start << "ms" << endl;

	return 0;

}