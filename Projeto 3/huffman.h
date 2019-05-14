#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "gerador.h"
#include "buscador.h"

struct Arvore{
    int i;
};


int ocorrencias(int *saida, int tam){
    int sum = 0;
    for (int i = 0; i < tam; i++) sum += saida[i];
    return sum;
}

int *frequencias(char *texto, int tamTexto){
    int i = 0;
    int *frequencia = new int[26];
    while (i < 26){
        char *aux = new char[1];
        aux[0] = dicionario(i);
        frequencia[i] = ocorrencias(kmp(texto, aux, tamTexto, 1), tamTexto);
        i++;
    }
    return frequencia;    
}

Arvore criar_arvore(int *v){
    // ...
}

int *get_bits(char texto){
    // ...
}

#endif