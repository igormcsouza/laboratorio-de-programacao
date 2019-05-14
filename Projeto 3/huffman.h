#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "gerador.h"
#include "buscador.h"

struct Arvore{
    int byte;
    char character;
    Arvore *right;
    Arvore *left;
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

void ocupar_arvore(Arvore *arvore, char character, int byte, int direcao){
   Arvore *S;
   S = (Arvore*)malloc(sizeof(Arvore));
   S->byte = byte;
   S->character = character;
   if (direcao) arvore->left = S;
   else arvore->right = S;
}

Arvore criar_arvore(int *v){
    Arvore *arvore = (Arvore*)malloc(sizeof(Arvore));
    for(int i = 0; i < 26; i++){
        
    }
}

int *get_bits(char texto){
    // ...
}

#endif