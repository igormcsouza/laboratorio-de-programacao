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

// Be sure a Arvore de Huffman está realmente como deveria!
bool is_huffman_tree(Huff *huff, int variety){
    for(int i = variety; i < 2*variety-2; i++)
        if(huff[i].frequency > huff[i+1].frequency){
            cout << "ERRO at huffman tree idx " << i << endl;
            print_huff(huff[i], i);
            print_huff(huff[i+1], i+1);
            return false;
        }
    return true;
}

bool find_frequency(
    string file_name, 
    unsigned long long int *frequencia, 
    int &variety,
    int &file_size){
    
    std::cout << "Finding Frequency..." << endl;
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
void initializing_tree(unsigned long long int *v, Huff *Tree){
    int j = 0;
    for(int i = 0; i < 256; i++)
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
bool build_huffman_tree(Huff *huffman_tree, int variety){
    // Cria um heap, cada nó é um elemento da arvore de huffman
    std::cout << "Building the heap...";
    No *heap = new No[variety];
    for(int i = 0; i < variety; i++){
        heap[i].weight = huffman_tree[i].frequency;
        heap[i].idx = i;
        // print_No(heap[i]); std::cout << std::endl;
    }
    
    // Organiza a arvore para ser um heap
    heapfy(heap, variety); if(!is_min_heap(heap, variety)) std::cout << "ERRO.\n";
    No *min = new No[2]; // Vetor-extração dos minimos
    int count = variety; // Contar para acompanhar o tamanho da heap
    int original_variety = variety;

    std::cout << "Building the Huffman Tree...\n";
    // Still a bug! The final tree isn't as expected
    while(count > 1){
        // Extrai os 2 primeiros (A função extração ajeita a heap tbm)
        min[0] = remove_min(heap, count);
        min[1] = remove_min(heap, count);

        // Cria o novo no artificial na arvore de huffman
        huffman_tree[variety].frequency = min[0].weight + min[1].weight;
        huffman_tree[variety].left = min[0].idx; 
        huffman_tree[variety].right = min[1].idx;
        variety++; // Incremento a arvore de huffman para receber o no artificial

        // print_Folha(huffman[last-1], last-1);
        // print_No(min[0]); print_No(min[1]);
        // pause; 

        ++count; // Coloca esse nó artificial na heap.
        heap[count].idx = variety-1;
        heap[count].weight = huffman_tree[variety-1].frequency;
        // print_No(heap[count]);
        heapfy(heap, count); // Ajeita a heap
        // std::cout << variety << std::endl;
    }

    return is_huffman_tree(huffman_tree, original_variety);
}

/* Aqui se inicia de fato a compressão e também a decompressão. Após ter a árvore pronta, o que
* é necessário ser feito é criar uma matriz de códigos, cada byte terá o seu código, e então
* escreveremos esse código em um arquivo, mas escreveremos o código bit a bit! No branch dog estou
* fazendo alterações para a leitura de bits. Aqui no master estou fazendo outras alterações 
* na aplicação em geral!
*/

/* Faz a busca pelo código associado e preenche o vetor de códigos
* Recebe: Um vetor de códigos, um vetor aux para armazenar os códigos que estamos adquirindo,
*         a arvore de huffman e um inteiro para o indice do byte em questão.
* Retorna: Nada, mas preenche o vetor aux e ao fim, o vetor code.
*/
void BFS(string code[256], string &aux, Huff *huffman_tree, int i){
    // cout << "Indice Atual: " << i << ", aux = " << aux << endl;

    // Verifica se os filhos do nó são ambos nulos, ou seja, se ele é folha
    if(!(huffman_tree[i].right == -1 && huffman_tree[i].left == -1)){
        aux += '0';
        BFS(code, aux, huffman_tree, (huffman_tree + i)->left);
        aux += '1';
        BFS(code, aux, huffman_tree, (huffman_tree + i)->right);
        // code[huffman[i].elem].append(aux);
    } else code[huffman_tree[i].character].append(aux);
    aux.pop_back();
}

/* Preenche o vetor de códigos de acordo com a arvore de Huffman
* Recebe: Vetor de códigos, Arvore de Huffman Completa e o total de variedades da àrvore
* Retorna: Nada, mas preenche o vetor de códigos.
*/
void codify(string code[256], Huff *huffman_tree, int variety){
    string aux;
    BFS(code, aux, huffman_tree, 2 * variety - 2);

    // for (int i = 0; i < 256; i++)
    //     if(!code[i].empty()) cout << "B: " << (unsigned char)i << " C: " << code[i] << endl;
}

/* Escreve o arquivo de saida compactado
* Recebe: Arvore de Huffman, nomes dos arquivos de saída e entrada, a variedade e o tamanho do
*         arquivo original.
* Retorna: Booleano que confirma se a operação deu erro ou não.
*/
bool compressor(
    Huff *huffman_tree, 
    string input_file_name, 
    string output_file_name, 
    int variety, 
    int file_size){

    cout << "Building a output file..." << endl;
    int tree_size = (2*variety) - 1;
    int8_t variety_ = (int8_t)variety - 1;
    std::ofstream out(output_file_name, ios::binary);

    out.write((char*)&variety_, sizeof(variety_));
    out.write((char*)huffman_tree, tree_size * sizeof(Huff));
    out.write((char*)&file_size, sizeof(file_size));

    // Writing the file folowing the huffman tree
    std::ifstream in(input_file_name);
    string code[256];

    codify(code, huffman_tree, variety);
    cout << endl << " ...Codify was done sucessfully!... " << endl;

    unsigned char b, buffer = 0;
    unsigned count = 0;
    while(!in.eof()){
        b = in.get();
        for (unsigned int i = 0; i < code[b].size(); i++){
            buffer <<= 1; // Make room for next bit.
            if (code[b][i] == '1') buffer |= 1; // Set 1 if necessary.
            count++; // Remember we have added a bit.
            if (count == 8) {
                out.write((char*)&buffer, sizeof(buffer)); // writing code
                buffer = 0; count = 0;
            }
        }
    }
    // Caso nem todos os bits sejam gravados, grava o que sobrou
    if (count != 0) { buffer <<= (8 - count); out.write((char*)&buffer, sizeof(buffer));}
    
    in.close();
    out.close();
    return true;
}

// Em fase de teste, ou seja, não está pronta!!
bool decompressor(string input_file_name, string output_file_name) { 
    std::ifstream in(input_file_name);
    int8_t variety; in.read((char*)variety, sizeof(variety)); variety++;

    Huff *huffman_tree = new Huff[2*(variety)-1];
    in.read((char *)&huffman_tree, (2*(variety)-1) * sizeof(huffman_tree));

    string code[256];
    codify(code, huffman_tree, variety);
    cout << endl << " ...Codify was done sucessfully!... " << endl;

    int file_size = in.get();
    std::ofstream out(output_file_name);

    unsigned char b, buffer = 0;
    unsigned count_bits = 0, count = 0;
    while(!in.eof()){
        b = in.get();
        // ? DO What????
    }

    return true; 
}

#endif