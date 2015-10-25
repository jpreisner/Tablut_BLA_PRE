/*
 * Joueur.h
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include <boost/optional/optional.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Pion.h"
#include "terrain/Terrain.h"
#include "utils/Utils.h"

class Joueur {
private:
	std::vector<Pion> mesTypesDePions; // soit moscovite, soit roi & soldat

public:
	Joueur(){
	}
	Joueur(std::vector<Pion> typesPion) : mesTypesDePions(typesPion){}

	std::vector<Pion> const getMesTypesDePions() const{
		return mesTypesDePions;
	}

	std::string typesPionsToString(){
		if(mesTypesDePions.size() == 0)
			return "null";

		std::string str = pionToString(mesTypesDePions[0]);
		for(unsigned int i=1; i<mesTypesDePions.size(); i++){
			str += ", " + pionToString(mesTypesDePions[i]);
		}
		return str;
	}

	std::string pionToString(boost::optional<Pion> p){
		if(p == Pion::MOSCOVITE)
			return "MOSCOVITE";
		if(p == Pion::ROI)
			return "ROI";
		if(p == Pion::SOLDAT)
			return "SOLDAT";
		return "null";
	}

	void jouer(Terrain *terrain) {
		/**
		 * Selection de (x_avant, y_avant)
		 */
		unsigned int x_avant, y_avant;
		std::cout << "Selectionnez les coordonnees (x,y) d'un pion de type {" << typesPionsToString()
				<< "} a deplacer (entrez x, puis entrez y) :" << std::endl;
		Utils::saisieSecureInt(x_avant);
		Utils::saisieSecureInt(y_avant);

		while(terrain->pionEstEncercle(x_avant, y_avant) ||
				std::find(mesTypesDePions.begin(), mesTypesDePions.end(), terrain->get(x_avant, y_avant)) == mesTypesDePions.end()){
			std::cout << "Mauvaise saisie en (" << x_avant << ", " << y_avant << ")" << std::endl;
			std::cout << "Selectionnez les coordonnees (x,y) d'un pion de type {" << typesPionsToString()
							<< "} a deplacer (entrez x, puis entrez y) :" << std::endl;
					Utils::saisieSecureInt(x_avant);
					Utils::saisieSecureInt(y_avant);
		}

		/**
		 * Selection de (x_apres, y_apres)
		 */
		unsigned int x_apres, y_apres;
		std::cout << "Selectionnez les coordonnees (x,y) d'une case où vous souhaitez deplacer le pion [" <<
				pionToString(terrain->get(x_avant, y_avant))<< "] (entrez x, puis entrez y) :" << std::endl;
		Utils::saisieSecureInt(x_apres);
		Utils::saisieSecureInt(y_apres);

		while(!terrain->deplacerPion(x_avant, y_avant, x_apres, y_apres)){
			std::cout << "Selectionnez de nouvelles coordonnees (x,y) d'une case où vous souhaitez deplacer le pion [" <<
					pionToString(terrain->get(x_avant, y_avant))<< "] (entrez x, puis entrez y) :" << std::endl;
			Utils::saisieSecureInt(x_apres);
			Utils::saisieSecureInt(y_apres);
		}

		/**
		 * Verifie si un pion a ete pris. Si c'est le cas il sera supprime du jeu
		 */
		terrain->testPrisePion(x_apres,y_apres);
	}
};

#endif /* JOUEUR_H_ */
