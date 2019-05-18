#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../Projeto 2/gerador.h"
#include "../Projeto 2/buscador.h"

struct Arvore{
    int byte;
    char character;
    int freq;
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

/* Auxilia na Criação do Heap
* Facilita a criação da Heap. A função recebe como parâmetros...
* 1. Um ponteiro para o nó pai,
* 2. Um caractere que representa aquele nó,
* 3. O byte que aquela arvore vai representar
* 4. A direção, se for false ou 0 esqueda, c.c. direita
* Retorno: Um ponteiro para a folha criada.
*/
void ocupar_arvore(Arvore *arvore, char character, int byte, int direcao){
   Arvore *S = (Arvore*)malloc(sizeof(Arvore));
   S->byte = byte; S->character = character;
   if (direcao) arvore->left = S;
   else arvore->right = S;
}

Arvore *criar_arvore(int *v){
    Arvore *List = new Arvore[26];
    Arvore *arvore = (Arvore*)malloc(sizeof(Arvore));
    int size = 0;
    for(int i = 0; i < 26; i++)
        if(*(v+i) != 0){
            arvore->byte = 0;
            arvore->character = dicionario(i);
            arvore->freq = *(v+i);
            List[i] = *arvore;
            size++;
        }
        
    for(int i = 0; i < size/2; i++){
        List[i].left = &List[2*i + 1];
        List[i].right = &List[2*i + 2];
    }

    return &List[0];
}

//int *get_bits(char texto){
    // TO DO
//}

#endif