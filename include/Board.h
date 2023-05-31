#ifndef BOARD_H
#define BOARD_H

// clase Tablero
class Board {
	private:
		// constantes
		static const int HEIGHT = 3;
		static const int WIDTH = 3;
		static const char EMPTY_CELL = ' ';

		char board[HEIGHT][WIDTH]; // tablero

	public:
		// constructor
		Board();

		// destructor
		~Board();

		// obtener alto
		int getHeight() const;

		// obtener ancho
		int getWidth() const;

		// obtener si esta llena
		bool isFull() const;

		// obtener si columna esta dentro del rango
		bool isColumnInRange(int) const;

		// obtener si fila esta dentro del rango
		bool isRowInRange(int) const;

		// agregar ficha
		bool addToken(int, int, char);

		// determinar si hay ganador
		bool isWinner(char);

		// obtener si juego se ha acabado
		bool isGameOver(char, char);

		// mostrar
		void display() const;
};

#endif
