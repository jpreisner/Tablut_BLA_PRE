/*
 * Case.h
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#ifndef TERRAIN_CASE_H_
#define TERRAIN_CASE_H_

#include <boost/optional.hpp>

#include "../Pion.h"

class Case {
private:
	/**
	 * optional<Pion> utilise boost::none au lieu de NULL
	 */
	boost::optional<Pion> pion;

public:

	Case(boost::optional<Pion> p = boost::none) : pion(p) {};

	/**
	 * fonctions booleennes pour tester quel pion est sur la case courante
	 */
	bool moscoviteEstPresent() const { return pion == Pion::MOSCOVITE; }
	bool soldatEstPresent() const { return pion == Pion::SOLDAT; }
	bool roiEstPresent() const { return pion == Pion::ROI; }
	bool aucunPionEstPresent() const { return pion == boost::none; }

	/**
	 * getter && setter
	 */
	boost::optional<Pion> getPion() { return pion; }
	void setPion(boost::optional<Pion> p) { pion = p; }

};

#endif /* TERRAIN_CASE_H_ */
