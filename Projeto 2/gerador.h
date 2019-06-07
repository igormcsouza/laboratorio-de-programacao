#ifndef GERADOR_H
#define GERADOR_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

const char v[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z'};

const char dicionario(int i){ return v[i]; }

const char *gerador_aleatorio(int tam, int let){
	char *vetor = new char[tam+1];
	srand (time(NULL)); /* initialize random seed: */
	for (int i = 0; i < tam; i++){
		vetor[i] = dicionario(rand() % let);
	}
	vetor[tam] = '\0';
	return vetor;
}

const char *gerador_pior_caso_1(int tam){
	char *vetor = new char[tam + 1];
	for (int i = 0; i < tam - 1; i++){
		vetor[i] = dicionario(0);
	}
	vetor[tam - 1] = dicionario(1);
	vetor[tam] = '\0';
	return vetor;
}

const char *gerador_pior_caso_2(int tam){
	char *vetor = new char[tam + 1];
	for (int i = 0; i < tam; i++){
		vetor[i] = dicionario(0);
	}
	vetor[tam] = '\0';
	return vetor;
}


#endif