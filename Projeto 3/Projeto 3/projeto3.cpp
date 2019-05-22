//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp

#include <iostream>
#include <vector>
#include "huffman.h"
#include "heap.h"

using namespace std;

int main(){

	cout << "Finding Frequency" << endl;
    int tamTexto = 10, variedade = 26;
	char *texto = gerador_aleatorio(tamTexto, variedade);
	for(int i = 0; i < tamTexto; i++) cout << *(texto + i) << " "; 
	cout << endl;

    int *freq = frequencias(texto, tamTexto);
    for(int i = 0; i < variedade; i++) cout << *(freq + i) << " ";
	cout << endl << endl;

	int size = 0;
	for(int i = 0; i < variedade; i++)  if (*(freq + i) > 0) size++;

	cout << "Tree..." << endl;
	int n = (2*size) - 1;

	Folha *List = new Folha[n];
	int last = criar_arvore(freq, List);
	arvore_huffman(List, last);

	for(int i = 0; i < n; i++)  print_Folha(List[i]);

	return 0;
}