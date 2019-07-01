#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) files.push_back(string(dirp->d_name));
    closedir(dp);
    return 0;
}

string get_file(string dir = "inputs/"){
    int t = 0;
    vector<string> files = vector<string>();

    getdir(dir,files);

    std::cout << "Choose the file you want to open: " << std::endl;
    for (unsigned int i = 0;i < files.size();i++) {
        cout << i+1 << ": " << files[i] << endl;
    }
    std::cout << "Choose: "; std::cin >> t;

    return dir + files[t-1];
}

void get_informed_file(int argc, char **argv, string &input_file_name, string &output_file_name){
    // Fazendo a busca do arquivo informado se existir
    if((string)argv[1] == "--compressor"){
        if(argc >= 4 && ((string)argv[2] == "--input" || (string)argv[2] == "-i"))
            input_file_name = "inputs/" + (string)argv[3];
        else input_file_name = get_file();
        cout << "Input File Name: " + input_file_name << endl; 

        if(argc >= 6 && ((string)argv[4] == "--output" || (string)argv[4] == "-o"))
            output_file_name = "middles/" + (string)argv[5];
        else output_file_name = "middles/out.igr";
        cout << "Output File Name: " + output_file_name << endl;
    }

    if((string)argv[1] == "--decompressor"){
        if(argc >= 4 && ((string)argv[2] == "--input" || (string)argv[2] == "-i"))
            input_file_name = "middles/" + (string)argv[3];
        else input_file_name = get_file("middles/");
        cout << "Input File Name: " + input_file_name << endl; 

        if(argc >= 6 && ((string)argv[4] == "--output" || (string)argv[4] == "-o"))
            output_file_name = "outputs/" + (string)argv[5];
        else output_file_name = "outputs/out.txt";
        cout << "Output File Name: " + output_file_name << endl;
    }
}

#endif