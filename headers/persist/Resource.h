/*
 * Resource.h
 *
 *  Created on: 25/11/2010
 *      Author: jorge
 */

#ifndef RES_H_
#define RES_H_

#include <string>
#include <sys/types.h>

namespace persist{

	//-------------------------------------------------------------------------
	// Clase Recurso
	//-------------------------------------------------------------------------
	/**
	 * Un recurso recien creado no tiene ninguna referencia.
	 * El gestor de recursos se encarga de eliminar los recursos cuando que se le solicita
	 * expresamente, y sólo elimina aquellos recursos con el contador de referencias a cero.
	 *
	 */
	class CResource {
	friend class CResourceManager;
	public:
		const std::string	fileName() const { return _filename; }
		const unsigned int	refCount() const { return _refCount; }

		void incRef(){ ++_refCount; }
		void decRef(){ --_refCount; }

	protected:
		CResource(const std::string& filename): _filename(filename), _refCount(0) {}
		virtual ~CResource() {}

	private:
		const std::string	_filename;		/// Fichero donde se almacena el recurso
		unsigned int		_refCount;		/// Contador de referencias al recurso
	};
}

#endif /* RES_H_ */
