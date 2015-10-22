/*
 * Utils.h
 *
 *  Created on: 21 oct. 2015
 *      Author: Julien
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <iostream>
#include <string>
#include <limits>
#include <stddef.h>


class Utils {
public:

	/**
	 * get a random value between (min and max)
	 */
	static int getRandomValue(int min, int max){
		srand(time(NULL));
		return rand()%(max-min + 1) + min;
	}

	/**
	 * saisie secure of integer
	 */
	static bool saisieSecureInt(unsigned int &variable){
		std::string temp;
		while (true) {
			std::cin >> temp;

			if (std::cin.bad() || std::cin.eof()) {
				std::cerr << "Une erreur interne est survenue" << std::endl;
				if (std::cin.eof()) {
					return false;
				}

				viderBuffer();
				continue;

			} else if (std::cin.fail() || temp.find_first_not_of("0123456789") != std::string::npos) {
				std::cerr << "Erreur, saisie incorrecte." << std::endl;
				viderBuffer();
				continue;
			}

			viderBuffer();

			std::istringstream stream(temp);
			stream >> variable;

			if (stream.fail() || !stream.eof()) {
				std::cerr << "Erreur, saisie incorrecte." << std::endl;
			} else {
				return true;
			}
		}
		return false;
	}
private:
	/**
	 * flush the cin buffer
	 */
	static void viderBuffer(){
		std::cin.clear();
		std::cin.seekg(0, std::ios::end);

		if (!std::cin.fail())
			std::cin.ignore(std::numeric_limits<std::streamsize>::max()); // Le flux a d�j� un �tat valide donc inutile de faire appel � clear()

		else
			std::cin.clear(); // Le flux est dans un �tat invalide donc on le remet en �tat valide
	}

};

#endif /* UTILS_UTILS_H_ */
