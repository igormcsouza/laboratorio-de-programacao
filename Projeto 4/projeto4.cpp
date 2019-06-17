//g++ -Wall -Wextra -std=c++17 -pedantic -o projeto4 projeto4.cpp

#include "dicionario.hpp"

int main () {

    // MAIN!!!
    cout << "Starting...\n";

    try {
        ArvoreBinaria<int, char> C;

        C.adicionar(1, 'a');
        C.adicionar(2, 'b');
        C.adicionar(3, 'c');

        for (auto i = C.inicio(); i != C.fim(); ++i) cout << *i << '\n';
    }

    catch (const exception &e) {
        cout << "EXCEÇÃO: " << e.what() << '\n';

        return 1;
    }
}