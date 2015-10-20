/*
 * Main.cpp
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

int main(int argc, char **argv) {
	Terrain terrain;
	terrain.initTerrain();
	std::cout << "Affichage du Terrain : " << std::endl;
	terrain.toString();
}


