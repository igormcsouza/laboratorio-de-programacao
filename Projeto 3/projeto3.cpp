//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp

#include <iostream>
#include <vector>
#include "huffman.h"

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

	cout << "Tree..." << endl;
	Arvore *arvore = criar_arvore(freq);
	while(true){
		cout << arvore->character;
		if(arvore->left != NULL) arvore = arvore->left;
		else break;
	}

	return 0;

}