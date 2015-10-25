/*
 * Terrain.cpp
 */

#include "Terrain.h"

boost::optional<Pion> Terrain::get(int x, int y){
	if(x < 0 || y < 0 || x > TAILLE_TERRAIN_X-1 || x > TAILLE_TERRAIN_X-1)
		throw std::out_of_range("Coordonnées en dehors du terrain");
	return cases[x][y].getPion();
}

void Terrain::set(int x, int y, boost::optional<Pion> p){
	if(x < 0 || y < 0 || x > TAILLE_TERRAIN_X-1 || x > TAILLE_TERRAIN_X-1)
		throw std::out_of_range("Coordonnées en dehors du terrain");

	cases[x][y].setPion(p);
}


bool Terrain::estCaseDuMilieu (int x, int y) const {
	return (x == TAILLE_TERRAIN_X/2) && (x == y);
}

void Terrain::initTerrain(){

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

std::string Terrain::printPion(boost::optional<Pion> p){
	if(!p)
		return " ";
	else if(p == Pion::MOSCOVITE)
		return "M";
	else if(p == Pion::SOLDAT)
		return "S";
	else if(p == Pion::ROI)
		return "R";
	return " ";

}

std::string Terrain::toString(){
	std::string res = "    ";
	std::stringstream sstm;

	for(int i=0; i< TAILLE_TERRAIN_X; i++){
		sstm << "  " << i << " ";
	}
	res += sstm.str() + "  (x)\n    ";
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

	return res + " (y)\n";
}


/**
 * Retourne true si le deplacement s'est correctement effectue
 * 			false si le deplacement n'a pas pu s'effectuer
 */
bool Terrain::deplacerPion(int x_avant, int y_avant, int x_apres, int y_apres){
	if(x_avant == x_apres && y_avant == y_apres){
		std::cout << "Les coordonnees de deplacement sont les memes que les coordonnees initiales." << std::endl;
		return false;
	}

	if(get(x_avant, y_avant) == boost::none){
		std::cout << "Aucun pion n'est present en (" << x_avant << ", " << y_avant << ")"<< std::endl;
		return false;
	}

	if(get(x_apres, y_apres) != boost::none){
		std::cout << "Impossible de deplacer le pion en (" << x_apres << ", " << y_apres << ") car un pion est deja present." << std::endl;
		return false;
	}

	if(x_avant != x_apres && y_avant != y_apres){
		std::cout << "Impossible de faire le deplacement : Deplacement horizontal ou vertical autorise uniquement." << std::endl;
		return false;
	}

	// Horizontal
	if(x_avant == x_apres){
		for(int x = (x_avant<x_apres ? x_avant+1 : x_avant-1); x == x_apres; (x_avant < x_apres) ? x++ : x--){
			if(get(x, y_avant) != boost::none){
				std::cout << "Un pion est present sur le chemin de deplacement en (" << x << ", " << y_avant << ")." << std::endl;
				return false;
			}
		}
	}
	// Vertical
	else{
		for(int y = (y_avant<y_apres ? y_avant+1 : y_avant-1); y == y_apres; (y_avant < y_apres) ? y++ : y--){
			if(get(x_avant, y) != boost::none){
				std::cout << "Un pion est present sur le chemin de deplacement en (" << x_avant << ", " << y << ")." << std::endl;
				return false;
			}
		}
	}

	// ajout du point sur la case
	set(x_apres,y_apres,get(x_avant, y_avant));

	// suppression du pion courant
	set(x_avant, y_avant,boost::none);

	return true;

	/*
	// test de prise du roi à l'adversaire
	if(cases[x_apres][y_apres].moscoviteEstPresent()){
		if(testPriseRoi(x_apres,y_apres)){
			return true;
		}
	}

	// test de prise de pion à l'adversaire
	testPrisePion(x_apres,y_apres);
	return false;

	*/
}


bool Terrain::testPriseRoi(int x, int y){
	int posRoiX, posRoiY;
	bool topKink, bottomKing,leftKing,rightKing;

	/* check king position */
	if(get(x-1,y) == Pion::ROI){
		posRoiY = y;
		posRoiX = x-1;
	}else if(get(x+1,y) == Pion::ROI){
		posRoiY = y;
		posRoiX = x+1;
	}else if(get(x,y-1) == Pion::ROI){
		posRoiY = y-1;
		posRoiX = x;
	}else if(get(x,y+1) == Pion::ROI){
		posRoiY = y+1;
		posRoiX = x;
	}

	/* check around king */
	topKink = get(posRoiX,posRoiY+1) == Pion::MOSCOVITE || estCaseDuMilieu(posRoiX,posRoiY+1);
	bottomKing = get(posRoiX,posRoiY-1) == Pion::MOSCOVITE || estCaseDuMilieu(posRoiX,posRoiY-1);
	leftKing = get(posRoiX-1,posRoiY) == Pion::MOSCOVITE || estCaseDuMilieu(posRoiX-1,posRoiY);
	rightKing = get(posRoiX+1,posRoiY) == Pion::MOSCOVITE || estCaseDuMilieu(posRoiX+1,posRoiY);

	return(topKink && bottomKing && rightKing && leftKing);

}

void Terrain::testPrisePion(int x, int y){
	/* test Top */
	boost::optional<Pion> pion = cases[x][y].getPion();
	if(x >= 2 && pion != cases[x][y-1].getPion() && pion == cases[x][y-2].getPion()){
		set(x,y-1,boost::none);
	}

	/* test Bottom */
	if(x <= TAILLE_TERRAIN_X-3 && pion != cases[x][y+1].getPion() &&pion == cases[x][y+2].getPion()){
		set(x,y+1,boost::none);
	}

	/* test Left */
	if(y >= 2 && pion != cases[x-1][y].getPion() &&pion == cases[x-2][y].getPion()){
		set(x-1,y,boost::none);
	}

	/* test Right */
	if(y <= TAILLE_TERRAIN_X-3 && pion != cases[x+1][y].getPion() &&pion == cases[x+2][y].getPion()){
		set(x+1,y,boost::none);
	}
}

bool Terrain::pionEstEncercle(int x, int y){
	return 	get(x, y) != boost::none
			&& ((x-1 < 0) || ((x-1 >= 0) && (get(x-1, y) != boost::none)))
			&& ((x+1 > TAILLE_TERRAIN_X-1) || ((x+1 <= TAILLE_TERRAIN_X-1) && (get(x+1, y) != boost::none)))
			&& ((y-1 < 0) || ((y-1 >= 0) && (get(x, y-1) != boost::none)))
			&& ((y+1 > TAILLE_TERRAIN_X-1) || ((y+1 <= TAILLE_TERRAIN_X-1) && (get(x, y+1) != boost::none)));
}
