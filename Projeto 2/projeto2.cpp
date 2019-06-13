//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto2 projeto2.cpp

#include <iostream>
#include <string>
#include <time.h>

#include "gerador.h"
#include "buscador.h"
#include "instancias_Reais_Trabalho_2.hpp"

#define BIG 10000000

using namespace std;

// Faz a comparação de resultados
/* Recebe como parametro o texto, o padrão e as ocorrencias
* Dentro da função ele aplica a busca via força bruta e kmp, testa o tempo e da um resultado
* para saber se é igual!!
*/
string benchmark(const char *texto, const char *padrao, int *bruta, int *kmP){
	clock_t start = clock();
	
	busca_sequencia(texto, padrao, bruta);
	cout << "\nForca Bruta: " << (double)(clock() - start) / CLOCKS_PER_SEC << " s.";

	start = clock();
	kmp(texto, padrao, kmP);
	cout << "\nKMP: " << (double)(clock() - start) / CLOCKS_PER_SEC << " s.\n";

	int i = 0;
	while (*(bruta + i) == *(kmP + i)){
		//cout << *(bruta + i) << ", " << *(kmP + i) << endl;
		if(*(bruta + i) == -1 && *(kmP + i) == -1) return "Funcionou! :D";
		++i;
	} 
	/* for (int i = 0; i < 21; i++) cout << bruta[i] << ", ";
	cout << endl;
	for (int i = 0; i < 21; i++) cout << kmP[i] << ", "; */

	return "Não funcionou!! :'(";
}

// Tem que ver isso dai...
int main(){
	srand (time(NULL));
	int opcao = 5, escolha, tamTexto = 2000, tamPadrao = 20, variedade = 26;
	char keep = 'Y';

	const char *texto, *padrao;
	int *bruta, *kmP;

	/* Hunting Bugs
	bruta = new int[tamTexto + 1];
	texto = gerador_aleatorio(tamTexto, variedade);
	padrao = gerador_aleatorio(tamPadrao, variedade);
	kmp(texto, padrao, bruta);
	for (int i = 0; i < 5; i++) cout << bruta[i] << endl; */

	// end

	while (keep == 'Y'){
		system("clear");
		cout << "### Encontrando Padroes em Textos... ###" << endl;
		cout << "Escolha uma opção: " << endl;
		cout << "1 - Aleatorio, 2 - Pior caso 1, 3 - Pior caso 2, 4 - Texto: ";
		cin >> opcao;

		bruta = new int[tamTexto + 1];
		kmP = new int[tamTexto + 1];
		
		if (opcao == 1){

			cout << "\nTestes com instancias aleatorias\n";
			texto = gerador_aleatorio(tamTexto, variedade);
			padrao = gerador_aleatorio(tamPadrao, variedade);

			cout << benchmark(texto, padrao, bruta, kmP) << endl;

			delete[] texto;
			delete[] padrao;
			delete[] bruta;
			delete[] kmP;
		}
		if (opcao == 2){
			cout << "\nTestes com instancias de pior caso 1\n";
			texto = gerador_pior_caso_1(tamTexto);
			padrao = gerador_pior_caso_1(tamPadrao);

			cout << benchmark(texto, padrao, bruta, kmP) << endl;

			delete[] texto;
			delete[] padrao;
			delete[] bruta;
			delete[] kmP;
		}
		if (opcao == 3){
			cout << "\nTestes com instancias de pior caso 2\n";
			texto = gerador_pior_caso_2(tamTexto);
			padrao = gerador_pior_caso_2(tamPadrao);

			cout << benchmark(texto, padrao, bruta, kmP) << endl;

			delete[] texto;
			delete[] padrao;
			delete[] bruta;
			delete[] kmP;
		}
		if (opcao == 4){
			cout << "\nDigite um numero no intervalo de 0 a 35129 para selecionar a palavra: "; 
			cin >> escolha;

			while (escolha < 0 || escolha > 35129) {
				cout << "O numero escolhido deve estar entre 0 e 35129";
				cin >> escolha;
			}

			bruta = new int[BIG];
			kmP = new int[BIG];

			cout << benchmark(Texto_Livros, Padroes_Palavras[escolha], bruta, kmP) << endl;

			delete[] bruta;
			delete[] kmP;
		}

		cout << "Continue? (Y/n): "; cin >> keep;
	}
}