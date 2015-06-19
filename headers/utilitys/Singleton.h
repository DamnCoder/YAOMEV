/*
 * Singleton.h
 *
 *  Created on: 06/04/2010
 *      Author: jorge
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_


/**
 * Template para crear singletons genericos
 */

template <typename T>
class CSingleton {
public:
	static T& instance(){
		if(!_instance)
			_instance = new T();

		return *_instance;
	}

	static T* pointer(){
		return &instance();
	}

	static void destroyInstance() {
		if(_instance){
			delete _instance;
			_instance = 0;
		}
	}

protected:
	~CSingleton(){};
	CSingleton(){};

private:
	/// Constructor de copia y operador de asignacion privados para evitar copias del singleton.
	CSingleton(const CSingleton&);
	CSingleton& operator=(const CSingleton&);

	static T* _instance;
};

template <typename T> T* CSingleton<T>::_instance = 0;

template <typename T>
class CPrivateSingleton {
protected:
	static T& instance(){
		if(!_instance)
			_instance = new T();

		return *_instance;
	}

	static T* pointer(){
		return &instance();
	}

	static void destroyInstance() {
		if(_instance){
			delete _instance;
			_instance = 0;
		}
	}

protected:
	~CPrivateSingleton(){};
	CPrivateSingleton(){};

private:
	/// Constructor de copia y operador de asignacion privados para evitar copias del singleton.
	CPrivateSingleton(const CPrivateSingleton&);
	CPrivateSingleton& operator=(const CPrivateSingleton&);

	static T* _instance;
};

template <typename T> T* CPrivateSingleton<T>::_instance = 0;

#endif /* SINGLETON_H_ */
