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

// copiar
Board Board::copy() const {
	return *this;
}

// establecer modalidad
void Board::setModality(int modality) {
    if (modality >= 1 && modality <= 2) {
        this->modality = modality;
    }
}

// obtener modalidad
int Board::getModality() const {
    return modality;
}

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

// obtener puntuacion
int Board::getScore(char *window, char token) {
	int score = 0;
	int tokenCount = 0;
	int emptyCount = 0;
	int enemyCount = 0;

	// contar apariciones de ficha, vacio y ficha enemiga
	for (int i = 0; i < 3; i++) {
		if (window[i] == token) tokenCount++;

		if (window[i] == EMPTY_CELL) emptyCount++;

		if (window[i] != token && window[i] != EMPTY_CELL) enemyCount++;
	}

	// mejor puntuacion si gana
	if (tokenCount == 3) score += 100;

    // si hay 2 fichas propias y 1 es vacio
	if (tokenCount == 2 && emptyCount == 1) score += 5;

    // si hay 2 fichas enemigas y 1 vacio
	if (enemyCount == 2 && emptyCount == 1) score -= 5;

    // peor puntuacion si pierde
	if (enemyCount == 3) score -= 100;

	return score;
}

// evaluar ficha en el tablero
int Board::evaluate(char token) {
	int score = 0;
	char window[3];

	// puntuacion central
	for (int row = 0; row < getHeight(); row++) {
		int centerColumn = getWidth() / 2;

        // si es ficha de jugador se suma 3 a puntuacion
		if (board[row][centerColumn] == token) score += 3;
	}

	// puntuacion horizontal
	for (int row = 0; row < getHeight(); row++) {
		for (int col = 0; col < getWidth(); col++) {
			// ir a siguiente columna de la misma fila
			window[col] = board[row][col];
		}

		score += getScore(window, token);
	}

	// puntuacion vertical
	for (int col = 0; col < getWidth(); col++) {
		for (int row = 0; row < getHeight(); row++) {
			// ir a siguiente fila de la misma columna
			window[row] = board[row][col];
		}

		score += getScore(window, token);
	}

	// puntuacion diagonal positiva ( / )
    for (int row = getHeight() - 1, col = 0; row >= 0 && col < getWidth(); row--, col++) {
		// subir una fila e ir a siguiente columna
		window[col] = board[row][col];
    }

	score += getScore(window, token);

	// puntuacion diagonal negativa ( \ )
    for (int row = 0, col = 0; row < getHeight() && col < getWidth(); row++, col++) {
        // bajar una fila e ir a siguiente columna
		window[row] = board[row][col];
    }

    score += getScore(window, token);

	return score;
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
