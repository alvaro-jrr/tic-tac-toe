#include <ctime>
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "Utils.h"
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

// mostrar opciones
void Utils::displayOptions(vector<string> options) {
    int size = options.size();

    // mostrar opcion con su numero correspondiente
    for (int option = 0; option < size; option++) {
        cout << option + 1 << ") " << options[option] << endl;
    }
}

// obtener opcion
int Utils::getOption(string label, int min, int max) {
    int option;

    do {
        option = getNumber(label);
    } while(option < min || option > max);

    return option;
}

// obtener un numero random entre 2 valores
int Utils::getRandomBetween(int min, int max) {
    // semilla de numeros aleatorios
    srand(time(NULL));

    return min + (rand() % max);
}