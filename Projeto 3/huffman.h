#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <string>
#include "heap.h"

#define pause std::getchar();

struct Huff{
    unsigned char character = '\0';
    unsigned long long int frequency = 0;
    // Abaixo se inicia com -1 para indicar nulidade
    int right = -1; // Indice do Filho Direito
    int left = -1; // Indice do Filho Esquerdo
};

void print_huff(Huff f, int i){
    std::cout << "Folha " << i << ": " 
    << f.character << ", " 
    << f.frequency << ", " 
    << f.right << ", " 
    << f.left << "|" << std::endl;
}

bool find_frequency(
    string file_name, 
    unsigned long long int *frequencia, 
    int &variety,
    int &file_size){
    
    std::ifstream file(file_name);
    if(file.peek() == std::ifstream::traits_type::eof()){
        std::cout << "Arquivo Vazio..." << std::endl;
        file.close();
        return true;
    }

    unsigned int b;
    while(!file.eof()){
        b = file.get();
        if(b <= 256){
            // std::cout << b << std::endl;
            if(frequencia[b] == 0) ++variety;
            ++frequencia[b];
        }
        file_size++;
    }

    file.close();
    return false;  
}

// Ocupa a arvore principal com os nós todos folhas a princípio
void initializing_tree(unsigned long long int *v, int variety, Huff *Tree){
    int j = 0;
    for(int i = 0; i < variety; i++)
        if(v[i] != 0){
            Tree[j].character = i;
            Tree[j].frequency = v[i];
            j++;
        }
}

/* Recebe: Array Folha, inteiro pra última posição
* Cria, apartir das folhas de Huffman a arvore de Huffman
* Retorna: Nada, mas modifica via ponteiro a arvore
*/
void build_huffman_tree(Huff *huffman_tree, int last_position){
    // Cria um heap, cada nó é um elemento da arvore de huffman
    No *heap = new No[last_position];
    for(int i = 0; i < last_position; i++){
        heap[i].weight = huffman_tree[i].frequency;
        heap[i].idx = i;
    }
    
    // Organiza a arvore para ser um heap
    heapfy(heap, 0, last_position);
    No *min = new No[2]; // Vetor-extração dos minimos
    int count = last_position; // Contar para acompanhar o tamanho da heap

    // Still a bug! The final tree isn't as expected
    while(count > 1){
        // Extrai os 2 primeiros (A função extração ajeita a heap tbm)
        min[0] = remove_min(heap, count);
        min[1] = remove_min(heap, count);

        // Cria o novo no artificial na arvore de huffman
        huffman_tree[last_position].frequency = min[0].weight + min[1].weight;
        huffman_tree[last_position].left = min[0].idx; 
        huffman_tree[last_position].right = min[1].idx;
        last_position++; // Incremento a arvore de huffman para receber o no artificial

        // print_Folha(huffman[last-1], last-1);
        // print_No(min[0]); print_No(min[1]);
        // pause; 

        ++count; // Coloca esse nó artificial na heap.
        heap[count].idx = last_position-1;
        heap[count].weight = huffman_tree[last_position-1].frequency;
        // print_No(heap[count]);
        heapfy(heap, 0, count); // Ajeita a heap
        // std::cout << std::endl;
    }
}

// Fas a busca pela folha de Huffman e retorna o código associado
void BFS(string code[256], string &aux, Huff *huffman_tree, int i){
    // cout << "Indice Atual: " << i << endl;
    // cout << "aux = " << aux << endl;
    // if (controle[i] != nullptr){
    if (!(huffman_tree[i].right == -1 && huffman_tree[i].left == -1)){
        aux += '0';
        BFS(code, aux, huffman_tree, (huffman_tree + i)->left);
        aux += '1';
        BFS(code, aux, huffman_tree, (huffman_tree + i)->right);
        // code[huffman[i].elem].append(aux);
    } else 
        code[huffman_tree[i].character].append(aux);
    aux.pop_back();
}

/* Recebe um bytecode e devolve sua cadeia de bits como descrito na arvore
* Entrada: Arvore de Huffman Completa, Bytecode.
* Saída: Cadeia de bits como descrito na arvore.
*/
void codify(string code[256], Huff *huffman_tree, int variety){
    // cout << "Debug codificacao..." << endl;
    // cout << "Numero de elementos: " << numeroElementos << endl;
    // cout << "Tamanho da arvore de huffman: " << 2 * numeroElementos - 1 << endl;
    string aux;
    // cout << "aux: " << aux << endl;
    // getchar();

    BFS(code, aux, huffman_tree, 2 * variety - 2);

    for (int i = 0; i < 256; i++)
        if(!code[i].empty())
            cout << "Byte: " << (unsigned char)i << " Code: " << code[i] << endl;
}

bool writing(Huff *huffman_tree, string file_name, int variety, int file_size){
    int tree_size = (2*variety) - 1;
    std::ofstream out(file_name + ".igr", ios::binary);

    out.write((char*)&tree_size, sizeof(tree_size));
    out.write((char*)huffman_tree, tree_size * sizeof(huffman_tree));
    out.write((char*)&file_size, sizeof(file_size));

    // Writing the file folowing the huffman tree
    std::ifstream in(file_name);
    string code[256];

    codify(code, huffman_tree, variety);
    cout << endl << " ...Codify was done sucessfully!... " << endl;

    unsigned char b;
    while(!in.eof()){
        b = in.get();
        for (unsigned int i = 0; i < code[b].size(); i++)
            out.write((char *)&code[b][i], sizeof(code[b][i]));
    }
    
    in.close();
    out.close();
    return true;
}

// Em fase de teste, ou seja, não está pronta!!
bool reading(string file_name, int n){
    // Reading from it
    return true;
}

#endif