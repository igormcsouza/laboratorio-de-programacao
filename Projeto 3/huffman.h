#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../Projeto 2/gerador.h"
#include "../Projeto 2/buscador.h"
#include "heap.h"

struct Folha{
    char character;
    int freq;
    // Abaixo se inicia com -1 para indicar nulidade
    int right = -1; // Indice do Filho Direito
    int left = -1; // Indice do Filho Esquerdo
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

// Ocupa a arvore principal com os nós todos folhas a princípio
void criar_arvore(int *v, Folha *Arvore){
    int i = 0;
    for(; i < 26; i++)
        if(*(v+i) != 0){
            Arvore[i].character = dicionario(i);
            Arvore[i].freq = *(v+i);
        }
}

/* Recebe: Array Folha
* Cria, apartir das folhas de Huffman a arvore de Huffman
* Retorna: Array Folha
*/
void arvore_huffman(Folha *huffman);

#endif