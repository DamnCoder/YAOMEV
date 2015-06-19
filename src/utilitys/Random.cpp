/*
 * Random.cpp
 *
 *  Created on: 31/05/2011
 *      Author: jorge
 */

#include "utilitys/Random.h"
#include "utilitys/utils.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

namespace utils {

	void
	CRandom::init() {
		srand(time(NULL));
	}
	
	void
	CRandom::init(unsigned int seed) {
		srand(seed);
	}
	
	int
	CRandom::randomNumber(int high) {
		return randomNumber(0, high);
	}

	int
	CRandom::randomNumber(int low, int high) {
		int temp;

		if (low > high) {
			temp = low;
			low = high;
			high = temp;
		}

		_low = low;
		_high = high;
		_range = (_high - _low);

		//temp = _low + (_range * rand() / (RAND_MAX + 1));
		temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * _range + low;
		/*
		std::cout<<"[CRandom::randomNumber] Low: "<<_low<<"\n";
		std::cout<<"[CRandom::randomNumber] High: "<<_high<<"\n";
		std::cout<<"[CRandom::randomNumber] Range: "<<_range<<"\n";
		std::cout<<"[CRandom::randomNumber] Rand: "<<temp<<"\n";
		*/

		return temp;
	}

	std::vector<int>
	CRandom::randomNumbersList(int maxNumbers){
		std::vector<int> numList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
		numList.reserve(maxNumbers);
		while(numList.size()<(uint)maxNumbers){
			int randNum = randomNumber(maxNumbers);
			numList.push_back(randNum);
			//std::cout<<"[CRandom::getRandomNumbers]Numero aleatorio: "<<randNum<<"\n";
		}

		return numList;
	}

	std::vector<int>
	CRandom::randomNumbersList(int maxNumbers, int high){
		std::vector<int> numList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
		numList.reserve(maxNumbers);

		while(numList.size()<(uint)maxNumbers){
			int randNum = randomNumber(high);
			numList.push_back(randNum);
			//std::cout<<"[CRandom::getRandomNumbers]Numero aleatorio: "<<randNum<<"\n";
		}

		return numList;
	}

	std::vector<int>
	CRandom::nonRepeatedRandomNumbersList(int maxNumbers){
		std::vector<int> numList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
		numList.reserve(maxNumbers);

		while(numList.size()<(uint)maxNumbers){
			int randNum = randomNumber(maxNumbers);
			if(!isInVector(numList, randNum)){
				numList.push_back(randNum);
				//std::cout<<"[CRandom::getRandomNumbers]Numero aleatorio: "<<randNum<<"\n";
			}
		}

		return numList;
	}

	std::vector<int>
	CRandom::nonRepeatedRandomNumbersList(int maxNumbers, int high){
		std::vector<int> numList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
		numList.reserve(maxNumbers);

		while(numList.size()<(uint)maxNumbers){
			int randNum = randomNumber(high);
			if(!isInVector(numList, randNum)){
				numList.push_back(randNum);
				//std::cout<<"[CRandom::getRandomNumbers]Numero aleatorio: "<<randNum<<"\n";
			}
		}

		return numList;
	}
}


