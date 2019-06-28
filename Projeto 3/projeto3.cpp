//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "directory.hpp"
#include "huffman.h"

using namespace std;

int main(int argc, char **argv){

	if((argc > 4) || 
	((string)argv[1] != "--compressor" && (string)argv[1] != "--decompressor")){
		cout << "HELP!" << endl;
		cout << "--compressor   : Compress any file at any folder" << endl;
		cout << "--decompressor : Decompress .igr files" << endl;
		cout << "-dir file_path : Specify where the file is, not necessary" << endl;
		return 1;
	}

	system("clear");
	cout << "Hello, Welcome to the compressor..." << endl;
	
    int variety = 0, file_size = 0;
	unsigned long long int *frequency = new unsigned long long int[256];
    for (int i = 0; i < 256; i++) frequency[i] = 0;

	// Lendo o arquivo em bytecode e atualizando as freq
	// string file_name = get_file((string)argv[3]);
	string file_name = get_file();

	if((string)argv[1] == "--compressor"){
		system("clear");
		cout << "Starting the compression!!" << endl << endl;
		cout << "Finding Frequency..." << endl;
		if(find_frequency(file_name, frequency, variety, file_size)) return 0;

		int n = (2*variety) - 1;
		Huff *huffman_tree = new Huff[n];

		initializing_tree(frequency, 256, huffman_tree); 
		cout << "Original Tree...";
		// for(int i = 0; i < n; i++)  print_Folha(List[i], i);
		// cout << endl << endl;
		cout << "done!" << endl;

		cout << "Building the heap and the Tree...";
		build_huffman_tree(huffman_tree, variety);
		cout << "done!" << endl;
		// cout << endl << endl;

		cout << "Huffman Tree Built Succesfully!" << endl;
		for(int i = 0; i < n; i++) print_huff(huffman_tree[i], i);
		cout << endl;

		cout << "Building a output file...";
		if(writing(huffman_tree, file_name)) cout << "Done..." << endl;
	}

	if((string)argv[1] == "--decompressor") cout << "COMMING SOON" << endl;

	return 0;
}