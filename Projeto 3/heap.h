#ifndef HEAP_H
#define HEAP_H

struct No{
    int weight = -1;
    int idx = -1;
};

void print_No(No no){
    std::cout << "No: " <<no.weight << ", " << no.idx << "|";
}

// Be sure a Heap está realmente mínima!
bool is_min_heap(No *heap, int last_position){
    for(int i = 0; i<last_position; i++)
        if(heap[i].weight > heap[2*i+1].weight || heap[i].weight > heap[2*i+2].weight){
            print_No(heap[i]); 
            print_No(heap[2*i+1]); print_No(heap[2*i+2]);
            return false;
        }
    return true;
}

void swap_no(No &a, No &b){
    No aux = a; a = b; b = aux;
}

/* Recebe: Heap desorganizada
* Constroi a heap, de forma que o mínimo fica na raiz e os filhos
* são sempre maiores que o pai.
* A cada interação ele vê de o Pai é maior que os filhos, se for troca,
* se não chama pro filho...
* Retorna: nada, pois trata-se de edição em ponteiros
*/
void fix_branch(No *heap, int i, int size){
    int min = i;
    if(heap[i].weight >= heap[(2*i) + 1].weight && (2*i) + 1 < size){
        min = (2*i) + 1;
    }
    if(heap[min].weight >= heap[(2*i) + 2].weight && (2*i) + 2 < size){
        min = (2*i) + 2;
    }
    if(min != i) {
        swap_no(heap[i], heap[min]);
        fix_branch(heap, min, size);                                             
    }
    // print_No(heap[i]); print_No(heap[2*i+1]); print_No(heap[2*i+2]); std::cout << std::endl;
}

void heapfy(No *heap, int last){
    for(int i = last/2; i >=0; i--){
        // std::cout << "HEAP: " << i << "LAST: " << last;
        fix_branch(heap, i, last);
    }
    // for(int i = 0; i<last; i++) { print_No(heap[i]); std::cout << std::endl; }
}

/* Recebe: Array Heap
* Remove o mínimo dos elementos da Heap, ou seja, a raiz. Decrementa o tamanho da heap.
* Retorna: No mínimo
*/
No remove_min(No *heap, int &last){
    No min = heap[0];
    heap[0] = heap[last];
    --last;
    heapfy(heap, last);
    return min;
}

#endif