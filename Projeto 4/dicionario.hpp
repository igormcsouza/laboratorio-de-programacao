#ifndef DICIONARIO_HPP
#define DICIONARIO_HPP

#include <exception>
#include <iostream>

using std::exception;
using std::cout;

template <typename Chave, typename Valor> // Me da a liberdade de usar o tipo que eu quiser
class ArvoreBinaria {
    private:
    struct Noh { Chave chave; Valor valor; 
    Noh *pai = nullptr; Noh *esq = nullptr; Noh *dir = nullptr; };
    Noh *primeiro, *raiz;

    public:
    /* Classe Iterador or ++
    * Definições importantes:
    * a) O filho mais a esquerda é o filho a esquerda do nó k que aponta para nulo como 
    * filho esquerdo
    * b) O pai mais a direita é o primeiro pai do nó k, em que k é o filho esquerdo.
    * 
    * Algoritmo do operador++
    * 1. Inicia no nó k
    * 2. Se tem filho a dir, vai pra ele e procura o filho mais a esq.
    * 3. Se não vai pro pai e procura o primeiro pai que seja mais a dir. 
    * */
    class Iterador {
        private:
        Noh *n;

        public:
        Iterador(Noh *noh) : n(noh) {}

        void operator++() {
            Valor valor = n->valor;
            while (true){
                if (n->dir != nullptr && n->dir->valor > valor){
                    n = n->dir;
                    while (n->esq != nullptr) n = n->esq; break;
                } else {
                    if (n->pai != nullptr){
                        if(n->pai->esq == n){ n = n->pai; break; }
                        else n = n->pai;
                    } else { n = nullptr; break; }
                }
            }
        }

        Valor operator*() { return n->valor; }

        bool operator!=(const Iterador &i) { return n != i.n; }
    };

    // Cria uma Arvore binária vazia
    ArvoreBinaria() : raiz(nullptr), primeiro(nullptr) { }

    Iterador adicionar (Chave c, Valor v) {
        Noh *n = new Noh;
        n->chave = c; n->valor = v;
        Noh *aux = nullptr;

        if(raiz == nullptr){ raiz = n; primeiro = n; }
        else aux = raiz;

        while(true){
            if(aux->chave > n->chave){ 
                if(aux->esq == nullptr){ 
                    aux->esq = n; aux->esq->pai = aux; 
                    // Se um nó que foi inserido a esquerda é menor que o primeiro, então ele deve ser o 
                    // primeiro.
                    if(aux->esq->chave < primeiro->chave) primeiro = aux->esq;
                    break; 
                }
            } else if(aux->dir == nullptr){ aux->dir = n; aux->dir->pai = aux; break; }
        }

        Iterador i(n);
        return i;
    }

    Iterador procurar (Chave c) {
        Iterador i(nullptr);
        return i; 
    }

    Iterador inicio () { Iterador i(primeiro); return i; }
    Iterador fim () { Iterador i(nullptr); return i; }
};

#endif
