#ifndef HEAP_H
#define HEAP_H

struct No{
    int weight = -1;
    int idx = -1;
};

void print_No(No no){
    std::cout << "No: " <<no.weight << ", " << no.idx << "|";
}

// Change positions on a pointer array
void swap(No &a, No &b){
    No aux;
    aux = a;
    a = b;
    b = aux;
}

/* Recebe: Heap desorganizada
* Constroi a heap, de forma que o mínimo fica na raiz e os filhos
* são sempre maiores que o pai.
* A cada interação ele vê de o Pai é maior que os filhos, se for troca,
* se não chama pro filho...
* Retorna: nada, pois trata-se de edição em ponteiros
*/
void minHeapify(No *heap, int i, int tamanho){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int min = i;

    if (l < tamanho && heap[l].weight <= heap[i].weight)
        min = l;
    if (r < tamanho && heap[r].weight <= heap[min].weight)
        min = r;
    if (min != i){
        swap(heap[i], heap[min]);
        minHeapify(heap, min, tamanho);
    }
}

void heapfy(No *heap, int tamanho){
    for(int i = tamanho / 2; i >= 0; i--)
        minHeapify(heap, i, tamanho);
}

/* Recebe: Array Heap
* Remove o mínimo dos elementos da Heap, ou seja, a raiz. Decrementa o tamanho da heap.
* Retorna: No mínimo
*/
No remove_min(No *heap, int &last){
    swap(heap[0], heap[last - 1]);
    --last; heapfy(heap, last);
    return heap[last];
}

#endif