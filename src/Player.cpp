#include <iostream>
#include "Player.h"
#include "Utils.h"
using namespace std;

// constructor sin parametros
Player::Player() { }

// constructor
Player::Player(char token) {
	this->token = token;
}

// obtener ficha
char Player::getToken() const {
	return token;
}

// hacer movida
void Player::makeMove(Board &board) {
	int column;
    int row;
    bool isRowValid = false;
    bool isColumnValid = false;
	bool isTokenAdded = false;

    // mostrar mensaje y salir en caso de estar el tablero lleno
    if (board.isFull()) {
        cout << "Tablero ya esta lleno" << endl;
        return;
    }

    // formar etiqueta para pedir fila
    string label = "Fila (";
	label += getToken();
	label += "): ";

    while(!isTokenAdded) {
        while(!isRowValid) {
            // pedir y leer fila
            row = Utils::getNumber(label) - 1;
            isRowValid = board.isRowInRange(row);

            if (!isRowValid) {
                cout << "Fila esta fuera de rango" << endl;
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
                cout << "Columna esta fuera de rango" << endl;
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