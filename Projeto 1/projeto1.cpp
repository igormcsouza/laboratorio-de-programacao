//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto1 projeto1.cpp

#include <iostream>
#include <fstream>
#include <string>
#include "ordenacao.h"

using namespace std;

void helpList(){
	cout << "Do you need some Help? Try the commands below:" << endl;
	cout << "--size or -s  : Size of the random vector*" << endl;
	cout << "--range or -r : Size of the vector range*" << endl;
	cout << "--input or -i : Location of the input vector" << endl;
	cout << endl;
	cout << "* --size and --range has to come together" << endl;
}

int main(int argc, char **argv){
	int tam = 1000;
	int variedade = 1000;
	// bool keep = true;
	int *v;

	if(argc > 5 || argc < 2) {
		helpList();
		return 0;
	}
	if((string)argv[1] == "--size" || (string)argv[1] == "-s"){
		tam = atoi(argv[2]);
		if((string)argv[3] == "--range" || (string)argv[3] == "-r") variedade = atoi(argv[4]);
		cout << "Tamanho do Vetor: " << tam << ", Variedades: " << variedade << endl;
		v = vetor_aleatorio(tam, variedade);
	} else if((string)argv[1] == "--input" || (string)argv[1] == "-i"){
		ifstream file;
		file.open((string)argv[2]);
		if(file.peek() == std::ifstream::traits_type::eof()){
			cout << "Arquivo Vazio ou Inexistente!\n"; file.close(); return 0;
		}
		file >> tam; 
		cout << "Tamanho do Vetor: " << tam << endl;
		v = new int[tam];
		for(int i = 0; i < tam; i++) file >> v[i];
		file.close();
	} else {
		helpList();
		return 0;
	}

	cout << "-----------------------------------------------" << endl;

	int *aux;
	clock_t begin_time;

	// while(keep){
		
		// cout << "Before: ";
		// for(int i=0; i<tam; i++){ cout << *(aux + i) << " "; }
		// cout << endl;

		// int escolha = 0;

		// cout <<"1-Indice; 2-Ponteiro; 3-Memoria; 4-Mediana; 5-Pivo Aleatório" << endl;
		// while((escolha < 1) || (escolha > 5)){
		// 	cout << "Escolha o método: ";
		// 	cin >> escolha;
		// }

		// const clock_t begin_time = clock();
		// cout << "Sorting the Vector...";

		// // TESTES ----------------------------------------------
		// if(escolha == 1) quickSort_via_indice(aux, 0, tam - 1);
		// if(escolha == 2) quickSort_via_ponteiro(aux, aux+(tam-1));
		// if(escolha == 3) quickSort_memoria(aux, aux+(tam-1));
		// if(escolha == 4) quickSort_medmed(aux, aux+(tam-1));
		// if(escolha == 5) quickSort_pivo_aleatorio(aux, aux+(tam-1));

		aux = v;
		begin_time = clock();
		cout << "QuickSort Indice...";
		quickSort_via_indice(aux, 0, tam - 1);
		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
		cout << "s" << endl;
		if(is_ordered(aux, tam)) cout << "Ordenação Funcionou!" << endl;
		else cout << "Ordenação não Funcionou!" << endl;
		cout << "-----------------------------------------------" << endl;

		aux = v;
		begin_time = clock();
		cout << "QuickSort Ponteiro...";
		quickSort_via_ponteiro(aux, aux+(tam-1));
		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
		cout << "s" << endl;
		if(is_ordered(aux, tam)) cout << "Ordenação Funcionou!" << endl;
		else cout << "Ordenação não Funcionou!" << endl;
		cout << "-----------------------------------------------" << endl;

		aux = v;
		begin_time = clock();
		cout << "QuickSort Memória...";
		quickSort_memoria(aux, aux+(tam-1));
		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
		cout << "s" << endl;
		if(is_ordered(aux, tam)) cout << "Ordenação Funcionou!" << endl;
		else cout << "Ordenação não Funcionou!" << endl;
		cout << "-----------------------------------------------" << endl;

		aux = v;
		begin_time = clock();
		cout << "QuickSort Mediana das Medianas...";
		quickSort_medmed(aux, aux+(tam-1));
		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
		cout << "s" << endl;
		if(is_ordered(aux, tam)) cout << "Ordenação Funcionou!" << endl;
		else cout << "Ordenação não Funcionou!" << endl;
		cout << "-----------------------------------------------" << endl;

		aux = v;
		begin_time = clock();
		cout << "QuickSort Aleatório...";
		quickSort_pivo_aleatorio(aux, aux+(tam-1));
		cout << " Done!" << endl;
		cout << "Time Elepsed: "; 
		cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
		cout << "s" << endl;
		if(is_ordered(aux, tam)) cout << "Ordenação Funcionou!" << endl;
		else cout << "Ordenação não Funcionou!" << endl;
		cout << "-----------------------------------------------" << endl;

		// cout << " Done!" << endl;
		// cout << "Time Elepsed: "; 
		// cout << float(clock() - begin_time)/CLOCKS_PER_SEC;
		// cout << "s" << endl;

		// cout << "After: ";
		// for(int i=0; i<tam; i++) cout << v[i] << " ";
		// cout << endl;

	// 	cout << "Continuar? 1/0: ";
	// 	cin >> keep;
	// }

	return 0;
}