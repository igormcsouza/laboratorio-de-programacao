//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto1 projeto1.cpp

#include <iostream>
#include "ordenacao.h"

using namespace std;

int main(){
	int tam = 10;
	bool keep = true;

	while(keep){
		system("clear");

		int *v = vetor_aleatorio(tam);

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
		for(int i=0; i<tam; i++)
			cout << v[i] << " ";
		cout << endl;

		cout << "Continuar? 1/0: ";
		cin >> keep;
	}

	

	return 0;
}