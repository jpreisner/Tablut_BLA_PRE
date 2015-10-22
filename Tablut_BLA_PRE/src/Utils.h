/*
 * Utils.h
 *
 *  Created on: 22 oct. 2015
 *      Author: Guillaume
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <stddef.h>

class Utils {
public:

	static int getRandomValue(int min, int max){
		return rand()%(max-min + 1) + min;
	}
};

#endif /* SRC_UTILS_H_ */
