#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Utils.h"
using namespace std;

void handleWinner(Board, Player *, Player *);
void handleMatch(Board, Player *, Player *);
void handleGame();

int main() {
    // opciones
    vector<string> options = {
        "Iniciar Partida",
        "Salir"
    };

    // estado del programa
    bool shouldContinue = true;

    do {
        cout << "----- Tic Tac Toe -----\n" << endl;

        // mostrar opciones
        Utils::displayOptions(options);
        cout << endl;

        // pedir y leer opcion
        int option = Utils::getOption("Opcion: ", 1, options.size());
        cout << endl;

        // ejecutar accion de acuerdo a opcion elegida
        if (option == 1) {
        	handleGame();
		} else if (option == 2) {
			shouldContinue = false;
		} else {
			cout << "Opcion invalida" << endl;
		}

        cout << endl;
    } while(shouldContinue);

    return 0;
}

// controlar ganador
void handleWinner(Board board, Player *P1, Player *P2) {
    // buscar secuencias para cada jugador
    int isFirstPlayerWinner = board.isWinner(P1->getToken());
    int isSecondPlayerWinner = board.isWinner(P2->getToken());

    // determinar resultado
    if (isFirstPlayerWinner || isSecondPlayerWinner) {
        int playerWinner = isFirstPlayerWinner ? 1 : 2;
        char tokenWinner = isFirstPlayerWinner ? P1->getToken() : P2->getToken();
        
        cout << "Ganador es Jugador " << playerWinner << " (" << tokenWinner << ")" << endl;
        return;
    }

    cout << "Empate" << endl;
}

// controlar partida
void handleMatch(Board board, Player *P1, Player *P2) {
    // obtener jugador a iniciar partida
    int playerToStart = Utils::getRandomBetween(1, 2);

    // establecer ficha de turno actual
    char currentTokenTurn = playerToStart == 1
        ? P1->getToken()
        : P2->getToken();

    // mostrar jugador a iniciar partida
    cout << "> Primer Turno es Jugador " << playerToStart
        << " (" << currentTokenTurn << ")\n" << endl;

    // jugar hasta que partida no haya terminado
    while(!board.isGameOver(P1->getToken(), P2->getToken())) {
        // mostrar estado del tablero
		board.display();
		cout << endl;

        // determinar jugador del turno
        if (currentTokenTurn == P1->getToken()) {
            P1->makeMove(board);

            // asignar ficha del proximo turno
            currentTokenTurn = P2->getToken();
        } else {
            P2->makeMove(board);

            // asignar ficha del proximo turno
            currentTokenTurn = P1->getToken();
        }
    }

    // mostrar estado final del tablero
    board.display();
    cout << endl;

    // determinar ganador
    handleWinner(board, P1, P2);
}

// controlar juego
void handleGame() {
    Board board;
    Player *P1 = new Player('X'), *P2 = new Player('O');

    // iniciar partida
    handleMatch(board, P1, P2);

    // destruir objetos
    delete P1;
    delete P2;
}
