#ifndef HEAP_H
#define HEAP_H

struct No{
    int weight;
    int idx;
};

void swap(No i, No j){
	No aux;
	aux = i; i = j; j = aux;
}

/* Recebe: Heap
* Constroi a heap, de forma que o mínimo fica na raiz e os filhos
* são sempre maiores que o pai.
* Retorna: nada, pois trata-se de edição em ponteiros
*/
void heapfy(No *heap, int i){
    while(true){
        if(heap[i].weight > heap[(2*i) + 1].weight) swap(heap[i], heap[(2*i) + 1]);
        heapfy(heap, (2*i) + 1);
        if(heap[i].weight > heap[(2*i) + 2].weight) swap(heap[i], heap[(2*i) + 2]);
        heapfy(heap, (2*i) + 2);
        break;
    }
}

/* Recebe: Array Heap
* Remove o mínimo dos elementos da Heap, ou seja, a raiz.
* Retorna: No
*/
No remove_min(No *heap, int last){
    No *min = heap;
    heap[0].idx = -1; heap[0].weight = -1;
    swap(heap[0], heap[last]);
    heapfy(heap, 0);
    return *min;
}

#endif