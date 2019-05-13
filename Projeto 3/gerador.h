#ifndef GERADOR_H
#define GERADOR_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

char *v[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z'};

char dicionario(int i){
	char *padrao = v+i;
	return v[i];
}

char *gerador_aleatorio(int tam, int let){
	char *vetor = new char[tam];
	srand (time(NULL)); /* initialize random seed: */
	for (int i = 0; i < tam; i++){
		vetor[i] = dicionario(rand() % let);
	}
	return vetor;
}

#endif