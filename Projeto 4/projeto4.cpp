//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto4 projeto4.cpp

#include <exception>
#include <iostream>

using std::exception;
using std::cout;

template <typename T> // Me da a liberdade de usar o tipo que eu quiser
class ArvoreBinaria {
   private:
   struct Noh { T elem; Noh *esq; Noh *dir; }; // Estrutura que tem filho esq e dir
   Noh *primeiro;

   public:
   // Essa classe será o meu percorredor, ele vai percorrer a arvore do menor para o maior elemento.
   class Iterador {
		private:
		Noh *n;

		public:
		Iterador (Noh *noh) : n(noh) { }
		void operator++ () { n = n->prox; }
		T operator* () { return n->elem;}
		bool operator!= (const Iterador &i) { return n != i.n; }
   };

   // Cria uma Arvore binária vazia
   ArvoreBinaria() : primeiro(nullptr) { }

   void adicionar (T e) {
       Noh *aux = primeiro; 
       Noh *n = new Noh;  n->elem = e;
       while (aux != nullptr){
           if (aux->elem > e) aux = aux->esq;
           else aux = aux->dir;
       }
       aux = n;
   }

   Iterador inicio () { Iterador i(primeiro); return i; }
   Iterador fim () { Iterador i(nullptr); return i; }
};

int main () {
   try {
      ArvoreBinaria<double> C;

      C.adicionar(1.1);
      C.adicionar(2.2);
      C.adicionar(3.3);

      ArvoreBinaria<double>::Iterador fim = C.fim(); // ou "auto fim ..."

      for (auto i = C.inicio(); i != fim; ++i)
        cout << *i << '\n';
   }

   catch (const exception &e) {
       cout << "EXCEÇÃO: " << e.what() << '\n';

       return 1;
   }
}