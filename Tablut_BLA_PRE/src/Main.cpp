/*
 * Main.cpp
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#include <iostream>
#include <string>

#include "Partie.h"
#include "terrain/Terrain.h"

int main() {

	/*Terrain terrain;
	terrain.initTerrain();
	std::cout << "Affichage du Terrain : " << std::endl;
	std::cout << terrain.toString() << std::endl;
	for(int i=0; i<100 ; i++){
		std::cout << Utils::getRandomValue(0,1)<< std::endl;
	}*/
	Partie partie;
	partie.lancerPartie();
}



