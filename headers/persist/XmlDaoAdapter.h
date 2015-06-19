/*
 * AbstractXmlDao.h
 *
 *  Created on: 07/10/2010
 *      Author: jorge
 */

#ifndef ABSTRACTXMLDAO_H_
#define ABSTRACTXMLDAO_H_

#include "IDao.h"

#include "utilitys/Singleton.h"

#include <tinyxml/tinyxml.h>
#include <string>
#include <iostream>

namespace persist{

	/**
	 * Clase generica que implementa el interfaz de los DAOs
	 * para el caso especifico de acceso a documentos XML.
	 *
	 * Simplemente inicializa algunos parametros habituales
	 * en la lectura de archivos a partir de la ruta
	 * al documento requerido.
	 */
	template<typename T>
	class CXmlDao : public IDao<T> {

	friend class CDaoServer;

	public:
		void init(const std::string& path){
			_path = path;
			initDomParameters();
		}

	protected:
		void initDomParameters();

		CXmlDao(): _hDoc(0), _hRoot(0) {}
		virtual ~CXmlDao() {}

		std::string		_path;
		TiXmlDocument 	_doc;		// Documento XML
		TiXmlHandle		_hDoc;		// Handler del documento
		TiXmlHandle 	_hRoot;		// Handler del nodo raíz
		TiXmlElement* 	_pElem;		// Nodo raiz

	};

	/**
	 * Abre un documentos XML a partir de su ruta e
	 * inicializa los parametros que permiten
	 * su manipulacion.
	 * @param path
	 */
	template<typename T>
	inline void CXmlDao<T>::initDomParameters() {
		if(_path.empty()){
#ifdef _DEBUG
			std::cerr << "[CXmlDao::init] No se ha pasado como argumento ninguna ruta a archivo.\n";
#endif
			return;
		}

		_doc = TiXmlDocument(_path.c_str());

		if(!_doc.LoadFile()){
#ifdef _DEBUG
			std::cerr << "[CXmlDao::init] No se ha podido cargar el documento XML: "<<_path<<"\n";
#endif
			return;
		}

		_hDoc=&_doc;
		// Recuperamos el elemento y el manejador del nodo raiz.
		_pElem = _hDoc.FirstChildElement().Element();
		_hRoot = TiXmlHandle(_pElem);
	}

}


#endif /* ABSTRACTXMLDAO_H_ */
