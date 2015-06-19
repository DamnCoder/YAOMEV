/*
 * EntityManager.h
 *
 *  Created on: 14/02/2011
 *      Author: jorge
 */

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cassert>

namespace logic{

	template <typename T>
	class CManager {
	public:

		typedef std::vector<T>	TElementsList;

		CManager():
			_numEntitys(0),
			_selected(0)
		{}

		virtual ~CManager() {
			deleteVector(_entitys);
			_entitys.clear();
			_numEntitys = 0;
		}

		void add(T entity){
			if(exists(entity))
				return;

			_entitys.push_back(entity);
			_numEntitys = _entitys.size();
		}

		void add(std::vector<T> entitys){
			typename std::vector<T>::iterator it, end;
			end = entitys.end();

			for(it = entitys.begin(); it!=end; ++it)
				add(*it);

		}

		TElementsList getAll() const {
			return _entitys;
		}

		T get(int index) {
			if(index < _numEntitys){
				_selected = index;
				return _entitys[index];
			}
			return 0;
		}

		T getRandom(){
			assert(_entitys.size() > 0);
			int randIndex = 0;

			if(_entitys.size() == 1){
				_selected = 0;
				return _entitys[0];
			}
			else if(_entitys.size() >1){
				randIndex = (rand() % (int)_entitys.size());
			}

			_selected = randIndex;

			return _entitys[randIndex];
		}

		int getIndex() const {
			return _selected;
		}

		T getSelected(){
			return _entitys[_selected];
		}

		T getNext() {
			++_selected;

			if(_selected >= _numEntitys)
				_selected = 0;

			//std::cout<<"[EntityManager::getNext] Numero de entidades "<<_numEntitys<<" y estamos con la entidad "<<_selected<<"\n";

			return _entitys[_selected];
		}

		T getPrevious() {

			if(_selected == 0)
				_selected = _numEntitys - 1;
			else
				--_selected;

			//std::cout<<"[EntityManager::getPrevious] Numero de entidades "<<_numEntitys<<" y estamos con la entidad "<<_selected<<"\n";

			return _entitys[_selected];
		}

		bool exists(T entity){
			typename TElementsList::iterator
				it(_entitys.begin()),
				end(_entitys.end());

			for(;it!=end; ++it)
				if((*it) == entity)
					return true;

			return false;
		}

	private:

		TElementsList	_entitys;
		int 			_numEntitys;
		int				_selected;
	};

}

#endif /* ENTITYMANAGER_H_ */
