#include <iostream>
#include "Board.h"
using namespace std;

// constructor
Board::Board() {
	// asignar vacio a cada celda
	for (int row = 0; row < getHeight(); row++) {
		for (int col = 0; col < getWidth(); col++) {
			board[row][col] = EMPTY_CELL;
		}
	}
}

// destructor
Board::~Board() { };

// obtener alto
int Board::getHeight() const {
	return HEIGHT;
}

// obtener ancho
int Board::getWidth() const {
	return WIDTH;
}

// obtener si esta llena
bool Board::isFull() const {
    for (int row = 0; row < getHeight(); row++) {
        for (int col = 0; col < getWidth(); col++) {
            if (board[row][col] == EMPTY_CELL) return false;
        }
    }

	return true;
}

// obtener si columna esta dentro del rango
bool Board::isColumnInRange(int column) const {
	return column >= 0 && column <= getWidth() - 1;
}

// obtener si fila esta dentro del rango
bool Board::isRowInRange(int row) const {
	return row >= 0 && row <= getHeight() - 1;
}

// agregar ficha
bool Board::addToken(int row, int column, char token) {
    // si esta fuera de rango
    if (!isRowInRange(row)) {
        cerr << "Fila " << row + 1 << " esta fuera de rango debe ser (1-" << getHeight() << ")." << endl;
		return false;
    }

	// si esta fuera de rango
	if (!isColumnInRange(column)) {
		cerr << "Columna " << column + 1 << " esta fuera de rango debe ser (1-" << getWidth() << ")." << endl;
		return false;
	}

    // si fila esta llena retornar FALSO
	if (board[row][column] != EMPTY_CELL) {
		cerr << "Celda ya esta tomada" << endl;
		return false;
	}

	// agregar ficha
	board[row][column] = token;
	return true;
}

// determinar si hay ganador
bool Board::isWinner(char token) {
	int row, col;

	for (row = 0; row < getHeight(); row++) {
		for (col = 0; col < getWidth(); col++) {
			// saltar paso si casilla no pertenece al jugador
			if (board[row][col] != token) continue;

			// verificar posible secuencia horizontal ( - )
			if (
				isColumnInRange(col + 2) &&
				board[row][col + 1] == token &&
				board[row][col + 2] == token
			) {
				return true;
			}

			// verificar posible secuencia vertical ( | )
			if (
				isRowInRange(row + 2) &&
				board[row + 1][col] == token &&
				board[row + 2][col] == token
			) {
				return true;
			}

			// verificar posible secuencia diagonal hacia la derecha ( / )
			if (
				isColumnInRange(col + 2) && 
				isRowInRange(row - 2) &&
				board[row - 1][col + 1] == token &&
				board[row - 2][col + 2] == token
			) {
				return true;
			}

			// verificar posible secuencia diagonal hacia la izquierda ( \ )
			if (
				isColumnInRange(col + 2) &&
				isRowInRange(row + 2) &&
				board[row + 1][col + 1] == token &&
				board[row + 2][col + 2] == token
			) {
				return true;
			}
		}
	}

	return false;
}

// obtener si juego se ha acabado
bool Board::isGameOver(char tokenA, char tokenB) {
	return isWinner(tokenA) || isWinner(tokenB) || isFull();
}

// mostrar
void Board::display() const {
	int row, col;

	// mostrar tablero
	for (row = 0; row < getHeight(); row++) {
		cout << "|";

		for (col = 0; col < getWidth(); col++) {
			cout << " " << board[row][col] << " ";
		}

		cout << "|" << endl;
	}

	cout << endl;
}
