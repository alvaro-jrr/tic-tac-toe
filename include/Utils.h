#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
	public:
		// constructor
		Utils();

		// destructor
		~Utils();

		// obtener numero
		static int getNumber(std::string);

		// mostrar opciones
		static void displayOptions(std::vector<std::string>);

		// obtener opction
		static int getOption(std::string, int, int);

		// obtener un numero random entre 2 valores
		static int getRandomBetween(int, int);
};

#endif // UTILS_H
