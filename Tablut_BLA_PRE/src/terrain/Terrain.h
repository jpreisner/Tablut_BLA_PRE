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
	 * teste si la case de position (x,y) est au centre du terrain,
	 * cette case n'est accessible QUE par le pion Pion::ROI
	 */
	bool estCaseDuMilieu(int x, int y) const;

	/**
	 * Init Terrain avec la map suivante :
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
	 * affiche le pion passé en parametre (M || S || R).
	 */
	std::string printPion(boost::optional<Pion> p);

	/**
	 * affiche le terrain comme dans le commentaire de la methode initTerrain
	 */
	std::string toString();

	/**
	 * deplace le pion de la position (x_avant,y_avant) a la position (x_apres,y_apres)
	 */
	bool deplacerPion(int x_avant, int y_avant, int x_apres, int y_apres);

	/**
	 * teste si le Pion::ROI est entouré par des Pion::MOSCOVITE (ou la case centrale)
	 */
	bool testPriseRoi(int x, int y);

	/**
	 * test si les pions à coté de la position(x,y) sotn entourrés par 2 Pion opposés
	 */
	void testPrisePion(int x, int y);
};

#endif /* TERRAIN_TERRAIN_H_ */
