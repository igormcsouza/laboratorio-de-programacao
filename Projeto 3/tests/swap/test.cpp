#include <iostream>
#include "heap.h"

void teste1 () {


    // teste 1
    No n1{1, 1};
    No n2{2, 2};
    swap_no(n1, n2);
    if (!(n1.idx > n2.idx && n1.weight > n2.weight)) {
        std::cout << "teste 1 falhou" << std::endl;
        exit(1);
    }


    std::cout << "Teste swap deu certo!" << std::endl;
}



void teste2 () {

    srand (time(NULL));
    // teste 1
    No* heap = new No[5];
    for(int i = 0; i < 5; i++){ heap[i].idx = rand() % 10; heap[i].weight = rand() % 10; }
    
    fix_branch(heap, 0, 5);
    if (!is_min_heap(heap, 5)) {
        std::cout << "teste 2 falhou" << std::endl;
        exit(1);
    }


    std::cout << "Teste fix branch deu certo!" << std::endl;
}


int main(){
    teste1();
    teste2();

    return 0;
}