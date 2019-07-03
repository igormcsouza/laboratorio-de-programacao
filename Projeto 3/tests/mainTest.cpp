#include "teste.cpp"
#include <iostream>

int main(){
    int res = teste();
    if(res) {
        std::cout << "Teste falhou!" << std::endl;
    }
    return 0;
}