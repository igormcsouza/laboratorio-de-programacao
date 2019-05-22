#ifndef HEAP_H
#define HEAP_H

struct No{
    int weight = -1;
    int idx = -1;
};

/* Recebe: Heap desorganizada
* Constroi a heap, de forma que o mínimo fica na raiz e os filhos
* são sempre maiores que o pai.
* A cada interação ele vê de o Pai é maior que os filhos, se for troca,
* se não chama pro filho...
* Retorna: nada, pois trata-se de edição em ponteiros
*/
void heapfy(No *heap, int i, int last){
    No aux;
    while(i < last/2){
        if(heap[i].weight > heap[(2*i) + 1].weight){
            aux.weight = heap[i].weight; aux.idx = heap[i].idx;
            heap[i].weight = heap[(2*i) + 1].weight; heap[i].idx = heap[(2*i) + 1].idx;  
            heap[(2*i) + 1].weight = aux.weight; heap[(2*i) + 1].idx = aux.idx;
        }
        if(heap[i].weight > heap[(2*i) + 2].weight){
            aux.weight = heap[i].weight; aux.idx = heap[i].idx;
            heap[i].weight = heap[(2*i) + 2].weight; heap[i].idx = heap[(2*i) + 2].idx;  
            heap[(2*i) + 2].weight = aux.weight; heap[(2*i) + 2].idx = aux.idx;
        }
        heapfy(heap, (2*i) + 1, last);
        i = (2*i) + 2;
    }
}

/* Recebe: Array Heap
* Remove o mínimo dos elementos da Heap, ou seja, a raiz. Decrementa o tamanho da heap.
* Retorna: No mínimo
*/
No remove_min(No *heap, int &last){
    No min = heap[0];
    heap[0] = heap[last];
    --last;
    heapfy(heap, 0, last);
    return min;
}

#endif