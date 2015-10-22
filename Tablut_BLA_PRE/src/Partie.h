/*
 * Partie.h
 *
 *  Created on: 21 oct. 2015
 *      Author: Julien
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include <iostream>

#include "Joueur.h"
#include "terrain/Terrain.h"
#include "utils/Utils.h"

class Partie {
private:
	Joueur j1;
	Joueur j2;
	Terrain terrain;
public:
	Partie(){}

	void lancerPartie(){
		unsigned int res;
		do{
			std::cout << "Bienvenue dans le jeu Tablut.\n" << std::endl;
			std::cout << "\tJoueur 1 : entrez 1 pour choisir les Moscovites ou entrez 2 pour choisir le Roi et les Soldats :" << std::endl;
			Utils::saisieSecureInt(res);
		}while(res != 1 && res != 2);

		/* random */

		if(res == 1){
			// J1 -> Moscovites & J2 -> Roi+Soldat
		}



	}


	bool finPartie(){
		return true;
	}
};

#endif /* PARTIE_H_ */