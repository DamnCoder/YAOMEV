/*
 * Random.h
 *
 *  Created on: 31/05/2011
 *      Author: jorge
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include "Singleton.h"

#include <vector>

namespace utils {

	class CRandom : public CSingleton<CRandom > {
	friend class CSingleton<CRandom >;
	public:
		void init();
		void init(unsigned int seed);

		int randomNumber(int high);
		int randomNumber(int low, int high);

		std::vector<int> randomNumbersList(int maxNumbers);
		std::vector<int> randomNumbersList(int maxNumbers, int high);

		std::vector<int> nonRepeatedRandomNumbersList(int maxNumbers);
		std::vector<int> nonRepeatedRandomNumbersList(int maxNumbers, int high);

	protected:
		CRandom(){}
		~CRandom(){}

	private:
		int	_low;
		int	_high;
		int	_range;

	};

}

#endif /* RANDOM_H_ */
