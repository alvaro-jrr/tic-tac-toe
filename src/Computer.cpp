#include <iostream>
#include <limits>
#include "Player.h"
#include "Board.h"
#include "Utils.h"
#include "Computer.h"
using namespace std;

// constructor
Computer::Computer(char token, char enemyToken, int level) : Player(token) {
	setEnemyToken(enemyToken);
	setLevel(level);
}

// establecer ficha enemiga
void Computer::setEnemyToken(char enemyToken) {
	this->enemyToken = enemyToken;
}

// obtener ficha enemiga
char Computer::getEnemyToken() const {
	return enemyToken;
}

// establecer nivel
void Computer::setLevel(int level) {
	if (level > 0) {
		this->level = level;
	}
}

// obtener nivel
int Computer::getLevel() const {
	return level;
}

// algoritmo minimax
Minimax Computer::minimax(
	Board board,
	char maxPlayer,
	char minPlayer,
	int maxDepth,
	int currentDepth,
	bool isMaximizingPlayer
) {
	// almacenar resultados del minimax (puntuacion, movida)
	Minimax state;

	// verificar si ha acabado la recursion
	if (board.isGameOver(maxPlayer, minPlayer) || currentDepth == maxDepth) {
		state.bestScore = board.evaluate(maxPlayer);
		return state;
	}

    // almacenar mejor movida y mejor puntaje
	int bestRowMove;
    int bestColMove;
	int bestScore;

	// jugador actual
	char currentPlayer = isMaximizingPlayer ? maxPlayer : minPlayer;

	// establecer mejor puntuacion inicial
	if (isMaximizingPlayer) {
		bestScore = numeric_limits<int>::min();
	} else {
		bestScore = numeric_limits<int>::max();
	}

	// pasar por cada movida posible
    for (int row = 0; row < board.getHeight(); row++) {
        for (int col = 0; col < board.getWidth(); col++) {
            // saltar paso si la celda esta tomada
            if (board.isCellTaken(row, col)) continue;

            // simular movida
            Board tempBoard = board.copy();
            tempBoard.addToken(row, col, currentPlayer);

            // recursion
            Minimax recursionState = minimax(
                tempBoard,
                maxPlayer,
                minPlayer,
                maxDepth,
                currentDepth + 1,
                !isMaximizingPlayer
            );

            // puntuacion actual
            int currentScore = recursionState.bestScore;

            // actualiza la mejor puntuacion
            if (isMaximizingPlayer) {
                if (currentScore > bestScore) {
                    bestScore = currentScore;
                    bestColMove = col;
                    bestRowMove = row;
                }
            } else {
                if (currentScore < bestScore) {
                    bestScore = currentScore;
                    bestColMove = col;
                    bestRowMove = row;
                }
            }
        }
    }


	// actualizar valores
	state.bestScore = bestScore;
	state.bestRowMove = bestRowMove;
    state.bestColMove = bestColMove;

    // estado del minimax
	return state;
}

// hacer movida
void Computer::makeMove(Board &board) {
	Minimax result = minimax(board, getToken(), getEnemyToken(), getLevel());
	
	// agregar mejor movida
	board.addToken(result.bestRowMove, result.bestColMove, getToken());

	// mostrar columna elegida
	cout << "Fila (" << getToken() << "): " << result.bestRowMove + 1 << "\n" << endl;
	cout << "Columna (" << getToken() << "): " << result.bestColMove + 1 << "\n" << endl;
}