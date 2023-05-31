#include "Utils.h"
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// constructor
Utils::Utils() {
}

// destructor
Utils::~Utils() {
}

// obtener numero
int Utils::getNumber(string label) {
    int number;

    do {
        // si fallo entrada
        if (cin.fail()) {
            cin.clear(); // manejar fallo de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignorar linea
            cout << "Entrada invalida\n" << endl;
        }

        cout << label;
        cin >> number;
    } while(cin.fail());

    return number;
}