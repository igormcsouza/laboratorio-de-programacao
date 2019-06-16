//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto4 projeto4.cpp

#include <exception>
#include <iostream>

using std::exception;
using std::cout;

template <typename Tchave, typename Tvalor> // Me da a liberdade de usar o tipo que eu quiser
class ArvoreBinaria {
    private:
    struct Noh { Tchave chave; Tvalor valor; 
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
            Tvalor valor = n->valor;
            while (true){
                if (n->dir != nullptr && n->dir->valor > valor){
                    n = n->dir;
                    while (n->esq != nullptr) n = n->esq; break;
                } e lse {
                    if (n->pai != nullptr){
                        if(n->pai->esq == n){ n = n->pai; break; }
                        else n = n->pai;
                    } else { n = nullptr; break; }
                }
            }
        }

        TV operator*() { return n->valor; }

        bool operator!=(const Iterador &i) { return n != i.n; }
};

    // Cria uma Arvore binária vazia
    ArvoreBinaria() : raiz(nullptr) { }

    void adicionar (Tchave c, Tvalor v) {
        Noh *n = new Noh;
        n->chave = c; n->valor = v;

        if(raiz != nullptr) Noh aux = *raiz;

        while(true){
            if(raiz == nullptr){ raiz = n; break; }
            if(raiz->valor > n->valor) raiz = raiz->esq;
            else raiz = raiz->dir;
        }
    }

    Iterador procurar (Tchave c) {
        Iterador i(nullptr);
        return i; 
    }

    Iterador inicio () { Iterador i(primeiro); return i; }
    Iterador fim () { Iterador i(nullptr); return i; }
};

int main () {

    cout << "Starting...\n";

    try {
        ArvoreBinaria<int, double> C;

        C.adicionar(1, 10.3);
        C.adicionar(2, 12.3);
        C.adicionar(3, 18.7);

        ArvoreBinaria<int, double>::Iterador fim = C.fim(); // ou "auto fim ..."

        //for (auto i = C.inicio(); i != fim; ++i) cout << *i << '\n';
    }

    catch (const exception &e) {
        cout << "EXCEÇÃO: " << e.what() << '\n';

        return 1;
    }
}