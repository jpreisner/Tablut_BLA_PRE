/*
 * Partie.h
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
	std::vector<Joueur> joueurs;
	Terrain *terrain = new Terrain();
public:
	Partie(){
		terrain->initTerrain();
	}

	void lancerPartie(){
		unsigned int res;
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
		std::cout << "Le premier joueur a commence est : Joueur " << first << ".\n" << std::endl;

		/**
		 * Initialisation des joueurs
		 */
		if (res == 1) {
			// J1 -> Moscovites & J2 -> Roi+Soldat
			joueurs.push_back(Joueur(vectMosco));
			joueurs.push_back(Joueur(vectRoiSoldat));
		} else {
			// J1 -> Roi+Soldat & J2 -> Moscovites
			joueurs.push_back(Joueur(vectRoiSoldat));
			joueurs.push_back(Joueur(vectMosco));
		}

		std::cout << "===============================================" << std::endl;
		std::cout << "               Le jeu commence !               " << std::endl;
		std::cout << "===============================================" << std::endl;

		int i = first-1;

		bool finDePartie = false;

		while(!finDePartie){
			std::cout << "Joueur " << (i+1) << " : a toi de jouer !" << std::endl;

			// Affichage du terrain
			std::cout << terrain->toString() << std::endl;

			// Le joueur (i+1) joue
			finDePartie = joueurs[i].jouer(terrain);

			// Changement de joueur
			if(!finDePartie){
				if(i == 0)
					i = 1;
				else
					i = 0;
			}
		}

		std::cout << "===============================================" << std::endl;
		std::cout << "           Le joueur " << (i+1) << " a gagne !"  << std::endl;
		std::cout << "===============================================" << std::endl;
		// Affichage du terrain
		std::cout << terrain->toString() << std::endl;
	}
};

#endif /* PARTIE_H_ */
