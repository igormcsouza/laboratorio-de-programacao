//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto3 projeto3.cpp
//compile projeto3 projeto3.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include "directory.hpp"
#include "huffman.h"

using namespace std;

void help_list(){
	cout << "Do you need some HELP! Let me give you a hand!" << endl << endl;
	cout << "--compressor              : Compress any file at any folder" << endl;
	cout << "--decompressor            : Decompress .igr files" << endl;
	cout << "*--input or -i file_name  : Specify input file, whether compress or not" << endl;
	cout << "*--output or -o file_name : Specify output file, must use .igr if compression" << endl;
	cout << endl;
	cout << "*Those above are not necessary, but if do, must be together" << endl;
}

int main(int argc, char **argv){

	system("clear");
	cout << "*** Hello, Welcome to the compressor... ***" << endl;

	int variety = 0, file_size = 0;
	unsigned long long int *frequency = new unsigned long long int[256];
    for (int i = 0; i < 256; i++) frequency[i] = 0;
	string input_file_name, output_file_name;

	if(argc == 1){
		cout << "Please, enter a valid command, --help or -h can be useful!\n";
	} else if((string)argv[1] == "--help" || (string)argv[1] == "-h"){
		help_list();
		return 0;

	} else if((string)argv[1] == "--compressor"){
		get_informed_file(argc, argv, input_file_name, output_file_name);
		cout << "Continue? Press any key..." << getchar(); 

		cout << "Starting the compression!!" << endl << endl;
		if(find_frequency(input_file_name, frequency, variety, file_size)) return 0;

		Huff *huffman_tree = new Huff[(2*variety) - 1];

		initializing_tree(frequency, 256, huffman_tree); 
		cout << "Original Tree...";
		// for(int i = 0; i < n; i++)  print_Folha(List[i], i);
		// cout << endl << endl;
		cout << "done!" << endl;

		if(build_huffman_tree(huffman_tree, variety)) cout << "done!" << endl;
		else{
			cout << "ERRO, huffman tree is not as expected...\n";
			return 3;
		}
		// cout << endl << endl;

		cout << "Huffman Tree Built Succesfully!" << endl;
		// for(int i = 0; i < (2*variety) - 1; i++) print_huff(huffman_tree[i], i);
		cout << endl;

		if(compressor(
			huffman_tree, 
			input_file_name,
			output_file_name, 
			variety, 
			file_size)) cout << "...Done!" << endl;
	
	} else if((string)argv[1] == "--decompressor"){
		get_informed_file(argc, argv, input_file_name, output_file_name);
		cout << "Continue? Press any key..." << getchar(); 

		cout << "Reading the compressed file and reconstructing a original file..." << endl;
		if(decompressor(input_file_name, output_file_name)) cout << "...Done!" << endl;

	} else {
		cout << "Command not found, please try --help or -h to find out more...\n";
	}

	return 0;
}