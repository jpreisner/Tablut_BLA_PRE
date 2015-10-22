/*
 * Joueur.h
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include <string>
#include <vector>

#include "Pion.h"

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


};

#endif /* JOUEUR_H_ */
