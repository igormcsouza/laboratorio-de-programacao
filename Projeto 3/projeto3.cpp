//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp

#include <iostream>
#include <vector>
#include "huffman.h"

using namespace std;

int main(){

	cout << "Finding Frequency..." << endl;
    int tam_arq = 0, variedade = 256;
	unsigned long long int *freq = new unsigned long long int[variedade];
    for (int i = 0; i < variedade; i++) freq[i] = 0;

	// Lendo o arquivo em bytecode e atualizando as freq
    frequencias(freq, tam_arq);

	cout << "Tree..." << endl;
	int n = (2*tam_arq) - 1;

	Folha *List = new Folha[n];
	criar_arvore(freq, variedade, List);
	for(int i = 0; i < n; i++)  print_Folha(List[i]);
	cout << endl << endl;

	cout << "Huffman Tree..." << endl;
	arvore_huffman(List, tam_arq);
	cout << endl << endl;
	for(int i = 0; i < n; i++) print_Folha(List[i]);
	cout << endl << endl;

	return 0;
}