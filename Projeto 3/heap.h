#ifndef HEAP_H
#define HEAP_H

struct No{
    int weight;
    int idx;
};

/* Recebe: Array Heap
* Remove o mínimo dos elementos da Heap, ou seja, a raiz.
* Retorna: No
*/
No remove_min(No *heap);

/* Recebe: Heap
* Constroi a heap, de forma que o mínimo fica na raiz e os filhos
* são sempre maiores que o pai.
* Retorna: Heap
*/
No *heapfy(No *heap);


#endif