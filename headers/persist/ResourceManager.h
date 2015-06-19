/*
 * TableResourceManager.h
 *
 *  Created on: 25/11/2010
 *      Author: jorge
 */

#ifndef RESMANAGER_H_
#define RESMANAGER_H_

#include <map>

#include "Resource.h"

#include <iostream>
namespace persist{

	//-----------------------------------------------------------------------------
	// Resource Manager Class
	//-----------------------------------------------------------------------------
	class CResourceManager {
	public:

		CResourceManager(const std::string& resourcesPath):
			_resourcesPath(resourcesPath)
		{}

		CResourceManager():
			_resourcesPath("")
		{}


		virtual ~CResourceManager() {
			//removeAll();
		}

		/**
		 * Se añade un recurso al gestor de archivos a partir del nombre del fichero
		 * del recurso.
		 *
		 * Si no se le suministra un fichero termina.
		 *
		 * Si ese fichero ya se ha suministrado se incrementa el contador de referencias
		 * a ese recurso.
		 *
		 * Si no existe, se carga el recurso y se añade a la tabla de recursos usando
		 * como clave el nombre del fichero.
		 *
		 * La funcion de carga del recurso ha de ser sobreescrita por las especializaciones
		 * de esta clase.
		 *
		 * @param key
		 */
		void add(const std::string& key){
			// Si no hay clave o ya existe no se añade a la cache.
			if(key.empty() || exists(key)) return;

			//std::cout<<"[ResourceManager::add] Vamos a cargar: "<<key<<"\n";
			// Si no existe se carga
			CResource* resource = loadResource(key);

			// Si no se ha podido cargar no la añade
			if(!resource) return;

			//std::cout<<"[ResourceManager::add] Cargado con exito!\n";

			// Se añade a la cache
			_resourceTable[key] = resource;
		}

		/**
		 * Solicita un recurso y lo devuelve.
		 *
		 * Si ya existe incrementa el contador de referencias.
		 *
		 * Si no existe, lo creara, lo cargara, lo insertara en la tabla de recursos
		 * y lo devolvera.
		 *
		 * @param key
		 * @return
		 */
		virtual CResource* get(const std::string& key){
			//std::cout<<"[ResourceManager::get] Vamos a recuperar a: "<<key<<"\n";
			// Si no hay clave se devuelve una referencia vacia
			if(key.empty()) return 0;

			CResource* res = 0;

			// Si existe incrementamos el numero de referencias al recurso y lo devolvemos
			if(exists(key)){
				res = _resourceTable[key];
				res->incRef();
				return res;
			}

			// Si no existe se carga
			res = loadResource(key);

			// Si no se ha podido cargar no la añade
			if(!res) return 0;

			//std::cout<<"[ResourceManager::get] Cargado con exito!\n";

			// Incrementamos la referencia
			res->incRef();
			// Se añade a la cache
			_resourceTable[key] = res;
			// Lo devolvemos
			return _resourceTable[key];
		}

		/**
		 * Primero comprueba que el elemento exista, si existe decrementa las referencias al recurso.
		 * Solo se elimina el recurso si el contador de referencias llega a cero.
		 * @param key
		 */
		void remove(const std::string& key){
			if(exists(key)){
				CResource* res = _resourceTable[key];
				res->decRef();
				//std::cout<<"[ResourceManager::remove] Eliminado "<<key<<" quedan "<<res->refCount()<<" referencias, hay "<<_resourceTable.size()<<"\n";

				if(res->refCount() == 0){
					_resourceTable.erase(key);
					//std::cout<<"[ResourceManager::remove] Quedan:"<<_resourceTable.size()<<" elementos en la cache\n";
				}
			}
		}

		/**
		 * Elimina todos los recursos.
		 * TODO Implementar la funcion.
		 */
		void removeAll() {
			//std::cout<<"[CResourceManager::removeAll] Inicio quedan "<<_resourceTable.size()<<"\n";

			_end = _resourceTable.end();
			_it = _resourceTable.begin();

			for(; _it!=_end; ++_it){
				//std::cout<<"[CResourceManager::removeAll] Elemento "<< _it->first<<"\n";
				CResource* res = _it->second;
				_resourceTable.erase(_it);

				delete res;
				res = 0;
			}

			//std::cout<<"[CResourceManager::removeAll] Fin quedan "<<_resourceTable.size()<<"\n";

			_resourceTable.clear();
		}

		const std::string resourcesPath() const { return _resourcesPath; }

	private:

		virtual CResource* loadResource(const std::string& filename) = 0;

		bool exists(const std::string& key){
			_it = _resourceTable.find(key);

			return (_it != _resourceTable.end());
		}

		typedef std::map<std::string, CResource*>	TResourceTable;
		typedef TResourceTable::iterator 			TResourceIterator;

		std::string			_resourcesPath;
		TResourceTable		_resourceTable;
		TResourceIterator 	_it, _end;

	};

} // utils


#endif /* RESMANAGER_H_ */
