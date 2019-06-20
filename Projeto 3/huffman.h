#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include "heap.h"
#include "directory.hpp"

#define pause std::getchar();

struct Folha{
    unsigned long long int character = '\0';
    int freq = 0;
    // Abaixo se inicia com -1 para indicar nulidade
    int right = -1; // Indice do Filho Direito
    int left = -1; // Indice do Filho Esquerdo
};

void print_Folha(Folha f, int i){
    std::cout << "Folha " << i << ": " 
    << f.character << ", " 
    << f.freq << ", " 
    << f.right << ", " 
    << f.left << "|" << std::endl;
}

int ocorrencias(int *occurs){
    int sum = 0;
    while (*(occurs + sum) != -1) ++sum;
    return sum;
}

bool frequencias(unsigned long long int *frequencia, int &tam_arq){
    unsigned long long int b;
    int t = 0;

    string dir = string("inputs/");
    vector<string> files = vector<string>();

    getdir(dir,files);

    std::cout << "Choose the file you want to open: " << std::endl;
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i+1 << ": " << files[i] << endl;
    }
    std::cin >> t;

    std::ifstream file("inputs/" + files[t-1]);
    if(file.peek() == std::ifstream::traits_type::eof()){
        std::cout << "Arquivo Vazio..." << std::endl;
        return false;
    }

    while(!file.eof()){
        b = file.get();
        if(b <= 256){
            // std::cout << b << std::endl;
            if(frequencia[b] == 0) ++tam_arq;
            ++frequencia[b];
        }
    }
	file.close();
    return true;   
}

// Ocupa a arvore principal com os nós todos folhas a princípio
void criar_arvore(unsigned long long int *v, int variedade, Folha *Arvore){
    int j = 0;
    for(int i = 0; i < variedade; i++)
        if(v[i] != 0){
            Arvore[j].character = i;
            Arvore[j].freq = v[i];
            j++;
        }
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

    // Still a bug! The final tree isn't as expected
    while(count > 1){
        // Extrai os 2 primeiros (A função extração ajeita a heap tbm)
        min[0] = remove_min(heap, count);
        min[1] = remove_min(heap, count);

        // Cria o novo no artificial na arvore de huffman
        huffman[last].freq = min[0].weight + min[1].weight;
        huffman[last].left = min[0].idx; huffman[last].right = min[1].idx;
        last++; // Incremento a arvore de huffman para receber o no artificial

        // print_Folha(huffman[last-1], last-1);
        // print_No(min[0]); print_No(min[1]);
        // pause; 

        ++count; // Coloca esse nó artificial na heap.
        heap[count].idx = last-1;
        heap[count].weight = huffman[last-1].freq;
        // print_No(heap[count]);
        heapfy(heap, 0, count); // Ajeita a heap
        // std::cout << std::endl;
    }
}

#endif