/*
 * Case.h
 *
 *  Created on: 20 oct. 2015
 *      Author: Julien
 */

#ifndef TERRAIN_CASE_H_
#define TERRAIN_CASE_H_

#include <stddef.h>

#include "../Pion.h"

class Case {
private:
	Pion pion;	// optional<Pion> = permet d'avoir un Pion ou d'avoir null

public:
	Case(Pion p = Pion::NONE) : pion(p) {};

	bool moscoviteEstPresent() const { return pion == Pion::MOSCOVITE; }
	bool soldatEstPresent() const { return pion == Pion::SOLDAT; }
	bool roiEstPresent() const { return pion == Pion::ROI; }
	bool aucunPionEstPresent() const { return pion == Pion::NONE; }

	Pion getPion() { return pion; }
	void setPion(Pion p) { pion = p; }

};

#endif /* TERRAIN_CASE_H_ */
