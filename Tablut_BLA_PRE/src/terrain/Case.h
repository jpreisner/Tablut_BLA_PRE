/*
 * Case.h
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#ifndef TERRAIN_CASE_H_
#define TERRAIN_CASE_H_

#include <stddef.h>
#include <boost/optional.hpp>

#include "../Pion.h"

class Case {
private:
	boost::optional<Pion> pion;	// optional<Pion> = permet d'avoir un Pion ou d'avoir null

public:
	Case(boost::optional<Pion> p = boost::none) : pion(p) {};

	bool moscoviteEstPresent() const { return pion == Pion::MOSCOVITE; }
	bool soldatEstPresent() const { return pion == Pion::SOLDAT; }
	bool roiEstPresent() const { return pion == Pion::ROI; }
	bool aucunPionEstPresent() const { return pion == boost::none; }

	boost::optional<Pion> getPion() { return pion; }
	void setPion(boost::optional<Pion> p) { pion = p; }

};

#endif /* TERRAIN_CASE_H_ */
