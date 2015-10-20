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
	bool estCaseDuMilieu (int x, int y) const {
		return (x == TAILLE_TERRAIN_X/2) && (x == y);
	}

	Pion get(int x, int y){
		if(x < 0 || y < 0 || x > TAILLE_TERRAIN_X-1 || x > TAILLE_TERRAIN_X-1)
			throw std::out_of_range("Coordonnées en dehors du terrain");
		return cases[x][y].getPion();
	}

	void set(int x, int y, Pion p){
		if(x < 0 || y < 0 || x > TAILLE_TERRAIN_X-1 || x > TAILLE_TERRAIN_X-1)
			throw std::out_of_range("Coordonnées en dehors du terrain");

		cases[x][y].setPion(p);
	}

	void initTerrain(){
		/* initialisation de toutes les cases a NULL */
		for(int i = 0; i < TAILLE_TERRAIN_X; i++){
			for(int j = 0; j < TAILLE_TERRAIN_X; j++){
				set(i, j, Pion::NONE);
			}
		}

		/**
		 * Roi (vert)
		 */
		set(TAILLE_TERRAIN_X/2, TAILLE_TERRAIN_X/2, Pion::ROI);

		/**
		 * Soldat (vert)
		 */
		for(int i = TAILLE_TERRAIN_X/2-2; i < TAILLE_TERRAIN_X/2; i++){
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

		for(int i=(TAILLE_TERRAIN_X/2-1);i<(TAILLE_TERRAIN_X/2)+2;i++){
			set(0, i, Pion::MOSCOVITE);
			set(i, 0, Pion::MOSCOVITE);
			set(TAILLE_TERRAIN_X-1, i, Pion::MOSCOVITE);
			set(i, TAILLE_TERRAIN_X-1, Pion::MOSCOVITE);
		}

		set(TAILLE_TERRAIN_X/2, 1, Pion::MOSCOVITE);
		set(TAILLE_TERRAIN_X/2, TAILLE_TERRAIN_X-2, Pion::MOSCOVITE);
		set(1, TAILLE_TERRAIN_X/2, Pion::MOSCOVITE);
		set(TAILLE_TERRAIN_X-2, TAILLE_TERRAIN_X/2, Pion::MOSCOVITE);
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

	std::string toString(){
		std::string res = "    ";
		std::stringstream sstm;

		for(int i=0; i< TAILLE_TERRAIN_X; i++){
			sstm << "  " << i << " ";
		}
		res += sstm.str() + "\n    ";
		for(int i=0; i< TAILLE_TERRAIN_X; i++){
			res += "+---";
		}
		res += "+\n";
		for(int i=0; i< TAILLE_TERRAIN_X; i++){
			std::stringstream sstm2;
			sstm2 << "  " << i << " ";
			res += sstm2.str();
			for(int j=0; j < TAILLE_TERRAIN_X; j++){
				res += "| " + printPion(get(i, j)) + " ";
			}
			res += "|\n    ";
			for(int j=0; j< TAILLE_TERRAIN_X; j++){
				res += "+---";
			}
			res += "+\n";
		}

		return res;
	}

	/* méthode qui déplace le piont de la case ayant les positions (x_avant,y_apres)
	 * sur la case de position (x_apres,y_après)*/
	void deplacerPion(int x_avant, int y_avant, int x_apres, int y_apres){
		if(x_avant == x_apres && y_avant == y_apres)
			return;

		if(get(x_avant, y_avant) == Pion::NONE)
			throw std::invalid_argument("Aucun pion n'est present dans la case.");

		if(x_avant != x_apres && y_avant != y_apres)
			throw std::invalid_argument("Impossible de faire le déplacement : Déplacement horizontal ou vertical autorisé uniquement.");

		// Horizontal
		if(x_avant == x_apres){
			for(int x = (x_avant<x_apres ? x_avant+1 : x_avant-1); x == x_apres; (x_avant < x_apres) ? x++ : x--){
				if(get(x, y_avant) != Pion::NONE)
					throw std::invalid_argument("Un pion est present sur le chemin de déplacement");
			}
		}
		// Vertical
		else{
			for(int y = (y_avant<y_apres ? y_avant+1 : y_avant-1); y == y_apres; (y_avant < y_apres) ? y++ : y--){
				if(get(x_avant, y) != Pion::NONE)
					throw std::invalid_argument("Un pion est present sur le chemin de déplacement");
			}
		}
		if(get(x_apres, y_apres) != Pion::NONE)
			throw std::invalid_argument("Un pion est present sur le chemin de déplacement");


		Pion p = get(x_avant, y_avant);

		/* ajout du point sur la case*/
		set(x_apres,y_apres,p);

		/*suppression du piont courant*/
		set(x_avant, y_avant,Pion());


	}
};

#endif /* TERRAIN_TERRAIN_H_ */
