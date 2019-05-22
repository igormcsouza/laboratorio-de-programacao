#ifndef HEAP_H
#define HEAP_H

struct No{
    int weight;
    int idx;
};

/* Recebe: 2 nós de uma heap
* Troca de posição os dois nós dados
* Retorna: Nada
*/
void swap(No i, No j){
	No aux;
	aux = i; i = j; j = aux;
}

/* Recebe: Heap desorganizada
* Constroi a heap, de forma que o mínimo fica na raiz e os filhos
* são sempre maiores que o pai.
* A cada interação ele vê de o Pai é maior que os filhos, se for troca,
* se não chama pro filho...
* Retorna: nada, pois trata-se de edição em ponteiros
*/
void heapfy(No *heap, int i, int last){
    while(i < (2*last)+1){
        if(heap[i].weight > heap[(2*i) + 1].weight) swap(heap[i], heap[(2*i) + 1]);
        if(heap[i].weight > heap[(2*i) + 2].weight) swap(heap[i], heap[(2*i) + 2]);
        heapfy(heap, (2*i) + 1, last);
        i = (2*i) + 2;
    }
}

/* Recebe: Array Heap
* Remove o mínimo dos elementos da Heap, ou seja, a raiz.
* Retorna: No
*/
No remove_min(No *heap, int &last){
    No min = heap[0];
    heap[0] = heap[last];
    --last;
    heapfy(heap, 0, last);
    return min;
}

#endif