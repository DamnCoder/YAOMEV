/*
 * utilidades.cpp
 *
 *  Created on: 23/05/2010
 *      Author: jorge
 */

#include "utilitys/utils.h"

std::string splitAndReturnFirstPart(const char c, const std::string& str){
	size_t atPos = str.find_first_of(c);
	return str.substr(0, atPos);
}

bool isInString(std::string strString, std::string strSubString){

	if(strString.length() <= 0 || strSubString.length() <= 0) return false;

	// Si no se encuentra en la cadena, devolvera -1
	int index = (int)strString.find(strSubString);

	if(index >= 0 && index < (int)strString.length())
		return true;

	// La subcadena no se encuentra en la cadena
	return false;
}

bool isInVector(std::vector<int> intList, int number){
	std::vector<int>::iterator
		it(intList.begin()),
		end(intList.end());

	for(;it!=end; ++it){
		if(*it == number)
			return true;
	}
	return false;
}

int randomNumber(int ceiling) {
	int randNumber = rand() % ceiling + 1;
	return randNumber;
}

double randomNumber(double ceiling){
	return randDouble(0.0, ceiling );
}

double randDouble(double low, double high) {
	double temp;

	/* swap low & high around if the user makes no sense */
	if (low > high) {
		temp = low;
		low = high;
		high = temp;
	}

	/* calculate the random number & return it */
	temp = (rand() / (static_cast<double>(RAND_MAX) + 1.0)) * (high - low) + low;
	return temp;
}


vector<int> getRandomNumbers(int maxNumbers){
	std::vector<int> intList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
	intList.reserve(maxNumbers);
	while(intList.size()<(uint)maxNumbers){
		int randomNumber = rand() % maxNumbers;
		intList.push_back(randomNumber);
		//cout<<"[getRandomNumbers]Numero aleatorio: "<<randomNumber<<"\n";
	}

	return intList;
}

vector<int> getRandomNumbers(int maxNumbers, int ceiling){

	std::vector<int> intList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
	intList.reserve(maxNumbers);

	while(intList.size()<(uint)maxNumbers){
		int randomNumber = rand() % ceiling;
		intList.push_back(randomNumber);
		//cout<<"[getRandomNumbers]Numero aleatorio: "<<randomNumber<<"\n";
	}

	return intList;
}

vector<int> getNonRepeatedRandomNumbers(int maxNumbers){

	std::vector<int> intList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
	intList.reserve(maxNumbers);
	while(intList.size()<(uint)maxNumbers){
		int randomNumber = rand() % maxNumbers;
		if(!isInVector(intList, randomNumber)){
			intList.push_back(randomNumber);
			//cout<<"[getNonRepeatedRandomNumbers]Numero aleatorio: "<<randomNumber<<"\n";
		}
	}

	return intList;
}

vector<int> getNonRepeatedRandomNumbers(int maxNumbers, int ceiling){

	std::vector<int> intList;	// Lista donde llevamos la cuenta de las preguntas ya escogidas
	intList.reserve(maxNumbers);
	while(intList.size()<(uint)maxNumbers){
		int randomNumber = rand() % ceiling;
		if(!isInVector(intList, randomNumber)){
			intList.push_back(randomNumber);
			//cout<<"[getRandomNumbers]Numero aleatorio: "<<randomNumber<<"\n";
		}
	}

	return intList;
}

