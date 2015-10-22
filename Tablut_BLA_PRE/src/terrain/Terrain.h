/*
 * Terrain.h
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#ifndef TERRAIN_TERRAIN_H_
#define TERRAIN_TERRAIN_H_

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../Pion.h"
#include "Case.h"

#define TAILLE_TERRAIN_X 9

class Terrain {
private:
	Case cases[TAILLE_TERRAIN_X][TAILLE_TERRAIN_X];
public:

	/**
	 * Getter && Setter
	 */
	boost::optional<Pion> get(int x, int y);
	void set(int x, int y, boost::optional<Pion> p);

	/**
	 * Check if the case on position (x,y) is at the center of the terrain,
	 * this case is accessible only to Pion::ROI
	 */
	bool estCaseDuMilieu(int x, int y) const;

	/**
	 * Init Terrain following this map :
	 *      0   1   2   3   4   5   6   7   8
	 *    +---+---+---+---+---+---+---+---+---+
	 *  0 |   |   |   | M | M | M |   |   |   |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  1 |   |   |   |   | M |   |   |   |   |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  2 |   |   |   |   | S |   |   |   |   |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  3 | M |   |   |   | S |   |   |   | M |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  4 | M | M | S | S | R | S | S | M | M |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  5 | M |   |   |   | S |   |   |   | M |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  6 |   |   |   |   | S |   |   |   |   |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  7 |   |   |   |   | M |   |   |   |   |
	 *    +---+---+---+---+---+---+---+---+---+
	 *  8 |   |   |   | M | M | M |   |   |   |
	 *    +---+---+---+---+---+---+---+---+---+
	 */
	void initTerrain();

	/**
	 * print the pion passed in parameter (M || S || R).
	 */
	std::string printPion(boost::optional<Pion> p);

	/**
	 * print the terrain to get the display in comment of the method initTerrain
	 */
	std::string toString();

	/**
	 * move pion form the position (x_avant,y_avant) to the position (x_apres,y_apres)
	 */
	bool deplacerPion(int x_avant, int y_avant, int x_apres, int y_apres);

	/**
	 * test if the Pion::ROI is surrounded by all Pion::MOSCOVITE (or the central case)
	 */
	bool testPriseRoi(int x, int y);

	/**
	 * test if the Pion next to the position(x,y) is surrounded by 2 opposite Pion
	 */
	void testPrisePion(int x, int y);
};

#endif /* TERRAIN_TERRAIN_H_ */
