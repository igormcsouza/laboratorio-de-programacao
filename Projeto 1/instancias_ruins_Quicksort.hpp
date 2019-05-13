// Author: Pablo M. S. Farias (pablo@dc.ufc.br). Date: 2019-04-03.

/* -----------------------------------------------------------------------------
 * EXPLICAÇÃO DESTE ARQUIVO:
 *
 * Este arquivo possui uma função "escrever_instancia", que constrói uma
 * instância de pior caso para um Quicksort baseado numa escolha "fixa" de pivô.
 *
 * Mais precisamente, as instâncias geradas causarão o pior caso do Quicksort
 * quando:
 *
 *   1. Para ordenar o intervalo de vetor que vai do índice "primeiro" ao índice
 *      "ultimo", o Quicksort sempre escolhe como pivô o elemento cujo índice é
 *      o valor retornado pela função
 *
 *        int escolher_pivo (int primeiro, int ultimo)
 *
 *      a qual deve fazer um cálculo baseado exclusivamente nos dois argumentos
 *      recebidos.
 *
 *   2. O Quicksort realiza o particionamento por meio do algoritmo de Lomuto,
 *      especificamente a versão na qual o pivô é inicialmente trocado com o
 *      elemento do início do intervalo, e depois reposicionado ao final do
 *      particionamento.
 *
 *      Observação: não importa se o particionamento deixa ou não os elementos
 *      iguais ao pivô todos juntos no "meio" do intervalo, pois as instâncias
 *      geradas não possuem elementos repetidos.
 *
 * A função "escrever_instancia" possui a seguinte especificação:
 *
 *   1. O primeiro argumento é o vetor "v" no qual deve ser escrita a instância.
 *
 *   2. O segundo argumento é o número "n" de elementos da instância a ser
 *      escrita.
 *
 *   3. O valor de retorno é do tipo "bool":
 *
 *      * true:  indica erro (falta de memória);
 *      * false: indica sucesso.
 *
 * -------------------------------------------------------------------------- */

#ifndef INSTANCIAS_RUINS_QUICKSORT_HPP
#define INSTANCIAS_RUINS_QUICKSORT_HPP

// -----------------------------------------------------------------------------

#include <new>

using std::nothrow;

#include <utility>

using std::swap;

// -----------------------------------------------------------------------------

int escolher_pivo (int primeiro, int ultimo);


// VALOR DE RETORNO: * true:  indica erro (falta de memória);
//                   * false: indica sucesso.
//
template <typename T>
bool escrever_instancia (T *v, int n)
  {
   int i;  int *pos = new(nothrow) int[n];  if (pos == nullptr) return true;

   for (i = 0; i < n; ++i) pos[i] = i;

   for (i = n-1; i != -1; --i)
     {
      int p = escolher_pivo(0,i);  v[ pos[p] ] = i;

      swap( pos[p], pos[0] );  swap( pos[0], pos[i] );
     }

   delete[] pos;  return false;
  }

// -----------------------------------------------------------------------------

#endif
