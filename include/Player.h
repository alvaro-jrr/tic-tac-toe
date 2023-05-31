#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

// clase Jugador
class Player {
	private:
		char token; // ficha

	public:
		// constructor sin parametros
		Player();

		// constructor
		Player(char);

		// destructor
		~Player() { }

		// obtener ficha
		char getToken() const;

		// hacer movida
		void makeMove(Board &);
};

#endif