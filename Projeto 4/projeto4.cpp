//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto4 projeto4.cpp

#include <exception>
#include <iostream>

using std::exception;
using std::cout;

template <typename Tchave, typename Tvalor> // Me da a liberdade de usar o tipo que eu quiser
class ArvoreBinaria {
    private:
    struct Noh { Tchave chave; Tvalor valor ; Noh *esq; Noh *dir; }; // Estrutura que tem filho esq e dir
    Noh *raiz;

    public:
    /* Essa classe será o meu percorredor, ele vai percorrer a arvore do menor 
    * para o maior elemento. */
    class Iterador {
        private:

        public:

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

    Iterador inicio () { Iterador i(raiz); return i; }
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