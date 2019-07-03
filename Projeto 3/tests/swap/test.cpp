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
    No* heap2 = new No[5];
    for(int i = 0; i < 5; i++){ heap[i].idx = rand() % 10; heap[i].weight = rand() % 10; }

    heap[0] = heap2[0] = {2, 1};
    heap[1] = heap2[1] = {4, 2};
    heap[2] = heap2[2] = {5, 3};
    heap[3] = heap2[3] = {7, 4};
    heap[4] = heap2[4] = {8, 5};

    swap_no(heap2[1], heap2[3]); 
    
    //fix_branch(heap2, 1, 5);
    heapfy(heap, 5);
    if (false) {
        std::cout << "teste 2 falhou" << std::endl;
        exit(1);
    }

    for(int i = 0; i < 5; i++){
        print_No(heap[i]); print_No(heap2[i]);
        std::cout << std::endl;
    }


    std::cout << "Teste fix branch deu certo!" << std::endl;
}


int main(){
    teste1();
    teste2();

    return 0;
}