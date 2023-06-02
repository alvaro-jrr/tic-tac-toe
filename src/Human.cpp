#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Utils.h"
#include "Human.h"
using namespace std;

// constructor
Human::Human(char token) : Player(token) { }

// hacer movida
void Human::makeMove(Board &board) {
    // mostrar mensaje y salir en caso de estar el tablero lleno
    if (board.isFull()) {
        cout << "Tablero ya esta lleno" << endl;
        return;
    }

    int column;
    int row;
    bool isRowValid = false;
    bool isColumnValid = false;
	bool isTokenAdded = false;
    string label;

    while(!isTokenAdded) {
        // formar etiqueta para pedir fila
        label = "Fila (";
        label += getToken();
        label += "): ";

        while(!isRowValid) {
            // pedir y leer fila
            row = Utils::getNumber(label) - 1;
            isRowValid = board.isRowInRange(row);

            if (!isRowValid) {
                cout << "Fila esta fuera de rango\n" << endl;
            }
        }

        // formar etiqueta para pedir columna
        label = "Columna (";
        label += getToken();
        label += "): ";

        while(!isColumnValid) {
            // pedir y leer columna
            column = Utils::getNumber(label) - 1;
            isColumnValid = board.isColumnInRange(column);

            if (!isColumnValid) {
                cout << "Columna esta fuera de rango\n" << endl;
            }
        }
        
        // intentar agregar ficha y obtener estado
        isTokenAdded = board.addToken(row, column, getToken());
        cout << endl;

        // reiniciar valores si ficha no ha sido agregada
        if (!isTokenAdded) {
            isRowValid = false;
            isColumnValid = false;
        }
    }
}