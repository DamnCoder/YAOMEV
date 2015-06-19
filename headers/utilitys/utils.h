#ifndef UTILITYS_H_
#define UTILITYS_H_

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <sys/types.h>

#include <iostream>

#include <string>
#include <sstream>

#include <vector>
#include <list>
#include <map>

#include <iterator>
#include <algorithm>

/** Insercion de espacios de nombres muy comunes */

using namespace std;

template <typename K, typename T> void deleteMap(map<K, T*> &m) {
	typename map<K, T* >::iterator it, end;
	end = m.end();
	for(it=m.begin(); it!=end; ++it){
		T* element = it->second;
		m.erase(it);

		safeDelete(element);
	}

	m.clear();
}

/**
 * Plantilla que implementa el borrado seguro de punteros.
 *
 * @param data
 */
template <typename T> void safeDelete(T*& data){
	if(data){
		delete data;
		data = 0;
	}
}


/**
 * Estructura que sobreescribe el operador () para poder usarlo para borrar
 * elementos de listas STL con for_each
 */
struct SafeDeletor{

	template<typename PointerType>
	void operator()(PointerType*& pointer) const {
		safeDelete(pointer);
	}

};


/**
 * Plantilla para borrar los elementos de vectores.
 * Ejecuta la orden clear al borrar de forma segura todos
 * los elementos del vector
 */
template<typename T> void deleteVector(std::vector<T *> &v) {
	typename vector<T *>::iterator it, end;
	end = v.end();

	for (it = v.begin(); it!=end; it++) {
		delete (*it);
		(*it) = 0;
	}

	v.clear();
}

template<typename T> void deleteVector(std::vector<T> &v) {
	v.clear();
}

/**
 * Plantilla para borrar los elementos de listas
 */
template<typename T> void deleteList(std::list<T *> &l) {
	typename list<T *>::iterator it, end;
	end = l.end();

	for (it = l.begin(); it!=end; it++) {
		delete (*it);
		(*it) = 0;
	}

	l.clear();
}

/**
 * Plantilla para convertir datos en cadenas de caracteres
 *
 * @param data
 * @return string, una cadena de caracteres
 */
template <class C> std:: string data2string(const C& data){
	std:: stringstream flow;
	flow << data;
	return(flow.str());
}

/**
 * Divide la cadena en dos a partir del caracter pasado
 * como argumento.
 * La cadena se divide en la primera aparicion del caracter.
 * Devuelve la primera parte de la cadena.
 * @param c
 * @return
 */
std::string splitAndReturnFirstPart(const char c, const std::string& str);

bool isInString(std::string strString, std::string strSubString);

/**
 * Funcion que comprueba si un determinado numero entero se encuentra
 * dentro de una lista de numeros enteros.
 *
 * @param intList
 * @param number
 * @return
 */
bool isInVector(std::vector<int> intList, int number);

/**
 * Funcion que devuelve un numero pseudoaleatorio entre 0 y el
 * entero pasad como parámetro.
 *
 * @param ceiling Numero aleatorio máximo al que se quiere llegar
 * @return
 */
int randomNumber(int ceiling);

double randomNumber( double ceiling);
double randDouble(double low, double high);


vector<int> getRandomNumbers(int maxNumbers);
vector<int> getRandomNumbers(int maxNumbers, int ceiling);
/**
 * Devuelve una lista de maxNumbers numeros aleatorios no repetidos.
 * @param maxNumbers
 * @return
 */
vector<int> getNonRepeatedRandomNumbers(int maxNumbers);

/**
 * Devuelve una lista de maxNumbers numeros aleatorios no repetidos,
 * que van de cero a ceiling.
 * @param maxNumbers
 * @param ceiling
 * @return
 */
vector<int> getNonRepeatedRandomNumbers(int maxNumbers, int ceiling);


/**
 * Plantilla para una tabla hash generica indexada a partir
 * de IDs de texto.
 */
template<class C> class CGenericMap{

public:

	CGenericMap(){

	}

	~CGenericMap(){

	}
	C* operator [](const std::string& id){
		if(!find(id))
			return 0;
		return _map[id];
	}

private:
	typedef std::map<std::string, C*> TMap;

	bool find(const std::string& id){
		typename TMap::const_iterator it;
		it = _map.find(id);

		// Si no hay ningún estado con ese nombre, devolvemos false
		return !(it == _map.end());
	}



	TMap _map;
};


#endif /*UTILITYS_H_*/
