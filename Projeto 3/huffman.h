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

void print_Folha(Folha f){
    std::cout << f.character << ", " << f.freq << "|";
}

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
    // Cria um heap, cada nó é um elemento da arvore de huffman
    No *heap = new No[last];
    for(int i = 0; i < last; i++){
        heap[i].weight = huffman[i].freq;
        heap[i].idx = i;
    }

    // Organiza a arvore para ser um heap
    heapfy(heap, 0, last);
    No *min = new No[2]; // Vetor-extração dos minimos
    int count = last; // Contar para acompanhar o tamanho da heap

    // ?? BUGS ?? Huffman não cria os nós artificiais!!
    while(count > 1){
        // Extrai os 2 primeiros (A função extração ajeita a heap tbm)
        min[0] = remove_min(heap, count);
        min[1] = remove_min(heap, count);

        last++; // Incremento a arvore de huffman para receber o no artificial

        // Cria o novo no artificial na arvore de huffman
        huffman[last].freq = min[0].weight + min[1].weight;
        huffman[last].left = min[0].idx; huffman[last].right = min[1].idx;
        print_Folha(huffman[last]);

        ++count; // Coloca esse nó artificial na heap.
        heap[count].idx = last;
        heap[count].weight = huffman[last].freq;
        heapfy(heap, 0, count); // Ajeita a heap
    }
}

#endif