//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto1 projeto1.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "ordenacao.h"

using namespace std;

void helpList(){
	cout << "Do you need some Help? Try the commands below:" << endl;
	cout << "--size or -s  : Size of the random vector" << endl;
	cout << "--input or -i : Location of the input vector" << endl;
}

int main(int argc, char **argv){
	int tam = 1000;
	int variedade = 1000;
	bool keep = true;
	int *v;

	while(keep){
		system("clear");

		if(argc > 3 || argc == 1) {
			helpList();
			return 0;
		}else if((string)argv[2] == "--size" || (string)argv[2] == "-s"){
			tam = 100; //atoi(argv[3]);
			v = vetor_aleatorio(tam, variedade);
		} else if((string)argv[2] == "--input" || (string)argv[2] == "-i"){
			fstream file((string)argv[3]);
			tam = file.get();
			file.read((char*)v, tam*sizeof(int));
		}

		cout << "Before: ";
		for(int i=0; i<tam; i++){ cout << *(v + i) << " "; }
		cout << endl;

		int escolha = 0;

		cout <<"1-Indice; 2-Ponteiro; 3-Memoria; 4-Mediana; 5-Pivo Aleatório" << endl;
		while((escolha < 1) || (escolha > 5)){
			cout << "Escolha o método: ";
			cin >> escolha;
		}

		const clock_t begin_time = clock();
		cout << "Sorting the Vector...";

		// TESTES ----------------------------------------------
		if(escolha == 1) quickSort_via_indice(v, 0, tam - 1);
		if(escolha == 2) quickSort_via_ponteiro(v, v+(tam-1));
		if(escolha == 3) quickSort_memoria(v, v+(tam-1));
		if(escolha == 4) quickSort_medmed(v, v+(tam-1));
		if(escolha == 5) quickSort_pivo_aleatorio(v, v+(tam-1));

		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/1000;
		cout << "s" << endl;

		cout << "After: ";
		for(int i=0; i<tam; i++) cout << v[i] << " ";
		cout << endl;

		cout << "Continuar? 1/0: ";
		cin >> keep;
	}

	

	return 0;
}