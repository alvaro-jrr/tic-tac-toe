#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

// clase Jugador
class Player {
	private:
        int score; // puntuacion
		char token; // ficha

	public:
		// constructor sin parametros
		Player();

		// constructor
		Player(char);

		// destructor
		virtual ~Player() { }

		// obtener ficha
		char getToken() const;

        // obtener puntuacion
		int getScore() const;

		// actualizar puntuacion
		void setScore(int);

		// hacer movida
		virtual void makeMove(Board &) = 0;
};

#endif