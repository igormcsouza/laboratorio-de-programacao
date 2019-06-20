//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "huffman.h"

using namespace std;

int main(){

	system("clear");
	cout << "Hello, Welcome to the compressor..." << endl;
	
    int tam_arq = 0, variedade = 256;
	unsigned long long int *freq = new unsigned long long int[variedade];
    for (int i = 0; i < variedade; i++) freq[i] = 0;

	// Lendo o arquivo em bytecode e atualizando as freq
	bool empty = false;
	string file_name = frequencias(freq, tam_arq, empty);
	if(empty) return 0;

	system("clear");
	cout << "Starting the compression!!" << endl << endl;
	cout << "Finding Frequency..." << endl;
	int n = (2*tam_arq) - 1;
	Folha *List = new Folha[n];

	criar_arvore(freq, variedade, List); 
	cout << "Original Tree...";
	// for(int i = 0; i < n; i++)  print_Folha(List[i], i);
	// cout << endl << endl;
	cout << "done!" << endl;

	cout << "Building the heap and the Tree...";
	arvore_huffman(List, tam_arq);
	cout << "done!" << endl;
	// cout << endl << endl;

	cout << "Huffman Tree Built Succesfully!" << endl;
	for(int i = 0; i < n; i++) print_Folha(List[i], i);
	cout << endl << endl;

	cout << "Building a output file...";
	if(writing(List, file_name)) cout << "Done..." << endl;

	reading(file_name, n);

	return 0;
}