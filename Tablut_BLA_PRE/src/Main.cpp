/*
 * Main.cpp
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#include <iostream>

#include "terrain/Terrain.h"

int main() {
	Terrain terrain;
	terrain.initTerrain();
	std::cout << "Affichage du Terrain : " << std::endl;
	terrain.toString();
}


