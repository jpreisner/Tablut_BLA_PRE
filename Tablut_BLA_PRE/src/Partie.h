/*
 * Partie.h
 *
 *  Created on: 21 oct. 2015
 *      Author: Julien
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "Joueur.h"
#include "Pion.h"
#include "terrain/Terrain.h"
#include "utils/Utils.h"

class Partie {
private:
	Joueur j1;
	Joueur j2;
	Terrain terrain;
public:
	Partie(){
		terrain.initTerrain();
	}

	void lancerPartie(){
		unsigned int res;
		unsigned int x_avant, y_avant,x_apres,y_apres;
		int first;
		std::vector<Pion> vectMosco { Pion::MOSCOVITE };
		std::vector<Pion> vectRoiSoldat { Pion::SOLDAT, Pion::ROI };
		do {
			std::cout << "Bienvenue dans le jeu Tablut.\n" << std::endl;
			std::cout << "Joueur 1 : entrez 1 pour choisir les Moscovites ou entrez 2 pour choisir le Roi et les Soldats :" << std::endl;
			Utils::saisieSecureInt(res);
		} while (res != 1 && res != 2);

		/* random pour  savoir qui va commencer */
		first = Utils::getRandomValue(1, 2);
		std::cout << "Le premier joueur à commencer est le joueur " << first << std::endl;

		if (res == 1) {
			// J1 -> Moscovites & J2 -> Roi+Soldat
			j1 = Joueur(vectMosco);
			j2 = Joueur(vectRoiSoldat);
		} else {
			j2 = Joueur(vectMosco);
			j1 = Joueur(vectRoiSoldat);
		}

		std::cout << "Affichage du Terrain : " << std::endl;
		std::cout << terrain.toString() << std::endl;

		bool ok = false;
		do {
			std::cout << "Joueur " << res
					<< " : entrez veuillez saisir la position x du pion a deplacer" << std::endl;
			Utils::saisieSecureInt(x_avant);
			std::cout << " : entrez maintenant la position y du pion a deplacer" << std::endl;
			Utils::saisieSecureInt(y_avant);

			ok = std::find(j1.getMesTypesDePions().begin(), j1.getMesTypesDePions().end(), terrain.get(x_avant,y_avant))!= j1.getMesTypesDePions().end();
		} while (!ok);

		ok = false;
		do{
			try{
				std::cout << "Joueur " << res
						<< " : entrez veuillez saisir la position x de la case ou vous voulez déplacer le pion" << std::endl;
				Utils::saisieSecureInt(x_apres);
				std::cout << " : entrez maintenant la position y de la case ou vous voulez déplacer le pion" << std::endl;
				Utils::saisieSecureInt(y_apres);

				terrain.deplacerPion(x_avant,y_avant,x_apres,y_apres);
				ok = true;
			}catch(const std::invalid_argument &){
				ok = false;
			}
		}while(!ok);

		std::cout << terrain.toString() << std::endl;

	}

	bool jouerTour(int x_avant, int y_avant, int x_apres, int y_apres){
		return terrain.deplacerPion(x_avant, y_avant, x_apres, y_apres);
	}

	bool finPartie(){
		return true;
	}
};

#endif /* PARTIE_H_ */
