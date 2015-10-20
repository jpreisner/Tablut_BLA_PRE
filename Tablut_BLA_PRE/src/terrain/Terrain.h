/*
 * Terrain.h
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#ifndef TERRAIN_TERRAIN_H_
#define TERRAIN_TERRAIN_H_

#include <stdexcept>
#include <string>

#include "../Pion.h"
#include "Case.h"

#define TAILLE_TERRAIN_X 9

class Terrain {
private:
	Case cases[TAILLE_TERRAIN_X][TAILLE_TERRAIN_X];
public:
	Terrain();
	virtual ~Terrain();

	bool const estCaseDuMilieu (int x, int y) const {
		return (x == TAILLE_TERRAIN_X/2) && (x == y);
	}

	Pion get(int x, int y){
		if(x < 0 || y < 0 || x > TAILLE_TERRAIN_X-1 || x > TAILLE_TERRAIN_X-1)
			throw std::out_of_range("Case : (" + x + ", " + y + ") est hors du terrain.");
		return cases[x][y].getPion();
	}

	void set(int x, int y, Pion p){
		if(x < 0 || y < 0 || x > TAILLE_TERRAIN_X-1 || x > TAILLE_TERRAIN_X-1)
			throw std::out_of_range("Case : (" + x + ", " + y + ") est hors du terrain.");

		cases[x][y].setPion(p);
	}

	void initTerrain(){
		/**
		 * Roi (vert)
		 */
		set(TAILLE_TERRAIN_X/2, TAILLE_TERRAIN_X/2, Pion::ROI);

		/**
		 * Soldat (vert)
		 */
		for(int i = TAILLE_TERRAIN_X/2-3; i < TAILLE_TERRAIN_X/2-1; i++){
			set(TAILLE_TERRAIN_X/2, i, Pion::SOLDAT);
			set(i, TAILLE_TERRAIN_X/2, Pion::SOLDAT);
		}

		for(int i = TAILLE_TERRAIN_X/2+1; i < TAILLE_TERRAIN_X/2+3; i++){
			set(TAILLE_TERRAIN_X/2, i, Pion::SOLDAT);
			set(i, TAILLE_TERRAIN_X/2, Pion::SOLDAT);
		}

		/*
		 * Moscovite (jaune)
		 */

		for(int i=(TAILLE_TERRAIN_X/2);i<(TAILLE_TERRAIN_X/2)+3;i++){
			set(0, i, Pion::MOSCOVITE);
			set(TAILLE_TERRAIN_X-1, i, Pion::MOSCOVITE);
			set(i, 0, Pion::MOSCOVITE);
			set(i, TAILLE_TERRAIN_X, Pion::MOSCOVITE);
		}

		set(TAILLE_TERRAIN_X/2+1, 1, Pion::MOSCOVITE);
		set(TAILLE_TERRAIN_X/2+1, TAILLE_TERRAIN_X-1, Pion::MOSCOVITE);
		set(1, TAILLE_TERRAIN_X/2+1, Pion::MOSCOVITE);
		set(TAILLE_TERRAIN_X-1, TAILLE_TERRAIN_X/2+1, Pion::MOSCOVITE);
	}

	std::string printPion(Pion p){
		if(p == Pion::MOSCOVITE)
			return "M";
		else if(p == Pion::SOLDAT)
			return "S";
		else if(p == Pion::ROI)
			return "R";
		return " ";
	}

	// TODO
	std::string toString(){
		return "";
	}

	void deplacerPion(int x_avant, int y_avant, int x_apres, int y_apres){
		if(x_avant == x_apres && y_avant == y_apres)
			return;

		if(get(x_avant, y_avant) == NULL)
			throw std::invalid_argument("Aucun pion n'est present en (" + x_avant + "," + y_avant + ")");

		if(x_avant != x_apres && y_avant != y_apres)
			throw std::invalid_argument("Impossible de faire le déplacement : Déplacement horizontal ou vertical autorisé uniquement.");

		// Horizontal
		if(x_avant == x_apres){
			for(int x = (x_avant<x_apres ? x = x_avant+1 : x = x_avant-1); x == x_apres; (x_avant < x_apres) ? x++ : x--){
				if(get(x, y_avant) != NULL)
					throw std::invalid_argument("Un pion est present en (" + x + ", " + y_avant + ")");
			}
		}
		// Vertical
		else{
			for(int y = (y_avant<y_apres ? y = y_avant+1 : y = y_avant-1); y == y_apres; (y_avant < y_apres) ? y++ : y--){
				if(get(x_avant, y) != NULL)
								throw std::invalid_argument("Un pion est present en (" + x_avant + ", " + y + ")");

			}
		}
		if(get(x_apres, y_apres) != NULL)
			throw std::invalid_argument("Un pion est present en (" + x_apres + ", " + y_apres + ")");


		Pion p = get(x_avant, y_avant);

	}
};

#endif /* TERRAIN_TERRAIN_H_ */
