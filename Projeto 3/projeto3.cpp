//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp
//compile projeto3 projeto3.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "directory.hpp"
#include "huffman.h"

using namespace std;

int main(int argc, char **argv){

	if((argc > 6) || 
	((string)argv[1] != "--compressor" && (string)argv[1] != "--decompressor") ||
	((string)argv[2] != "--input" && (string)argv[2] != "-i") ||
	((string)argv[4] != "--output" && (string)argv[4] != "-o")){
		cout << "HELP!" << endl;
		cout << "--compressor             : Compress any file at any folder" << endl;
		cout << "--decompressor           : Decompress .igr files" << endl;
		cout << "--input or -i file_name  : Specify input file, inside the input folder" << endl;
		cout << "--output or -o file_name : Specify output file, on the output folder" << endl;
		cout << endl;
		cout << "*Those above are not necessary, but if do, must be together" << endl;
		return 0;
	}

	system("clear");
	cout << "*** Hello, Welcome to the compressor... ***" << endl;
	
    int variety = 0, file_size = 0;
	unsigned long long int *frequency = new unsigned long long int[256];
    for (int i = 0; i < 256; i++) frequency[i] = 0;
	string input_file_name, output_file_name;

	if((string)argv[1] == "--compressor"){
		// Lendo o arquivo em bytecode e atualizando as freq
		if((string)argv[2] == "--input" || (string)argv[2] == "-i")
			input_file_name = "inputs/" + (string)argv[3];
		else input_file_name = get_file();
		cout << "Input File Name: " + input_file_name << endl; 

		if((string)argv[4] == "--output" || (string)argv[4] == "-o")
			output_file_name = "outputs/" + (string)argv[5];
		else output_file_name = "outputs/" + input_file_name + ".igr";
		cout << "Output File Name: " + output_file_name << endl;

		cout << "Continue? Press any key..." << getchar(); 

		cout << "Starting the compression!!" << endl << endl;
		cout << "Finding Frequency..." << endl;
		if(find_frequency(input_file_name, frequency, variety, file_size)) return 0;

		Huff *huffman_tree = new Huff[(2*variety) - 1];

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
		for(int i = 0; i < (2*variety) - 1; i++) print_huff(huffman_tree[i], i);
		cout << endl;

		cout << "Building a output file...";
		if(writing(
			huffman_tree, 
			input_file_name,
			output_file_name, 
			variety, 
			file_size)) cout << "...Done!" << endl;
	}

	if((string)argv[1] == "--decompressor") cout << "COMMING SOON" << endl;

	return 0;
}