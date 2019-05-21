#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../Projeto 2/gerador.h"
#include "../Projeto 2/buscador.h"
#include "heap.h"

struct Folha{
    char character = '\0';
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
int criar_arvore(int *v, Folha *Arvore){
    int j = 0;
    for(int i = 0; i < 26; i++)
        if(v[i] != 0){
            Arvore[j].character = dicionario(i);
            Arvore[j].freq = v[i];
            j++;
        }
    return j;
}

/* Recebe: Array Folha, inteiro pra última posição
* Cria, apartir das folhas de Huffman a arvore de Huffman
* Retorna: Nada, mas modifica via ponteiro a arvore
*/
void arvore_huffman(Folha *huffman, int last){
    No *heap = new No[last];
    for(int i = 0; i < last; i++){
        heap[i].weight = huffman[i].freq;
        heap[i].idx = i;
    }

    heapfy(heap, 0);
    No *min = new No[2];
    int count = last;

    while(count > 1){
        min[0] = remove_min(heap, count); --count;
        min[1] = remove_min(heap, count); --count;

        last++;

        huffman[last].freq = min[0].weight + min[1].weight;
        if (min[0].weight > min[1].weight){ huffman[last].left = min[0].idx; 
                                            huffman[last].right = min[1].idx;}
        else{ huffman[last].left = min[0].idx; 
              huffman[last].right = min[1].idx;}
        
        ++count;
        heap[count].idx = last;
        heap[count].weight = huffman[last].freq;

        heapfy(heap, 0);
    }

}

#endif