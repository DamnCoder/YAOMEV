/*
 * IDAO.h
 *
 *  Created on: 01/03/2010
 *      Author: jorge
 */

#ifndef IDAO_H_
#define IDAO_H_

#include <vector>

namespace persist{

	class CDaoServer;

	/**
	 * Interfaz a implementar por cualquier
	 * objeto de acceso a datos (DAO).
	 *
	 * Es necesario que suministren operaciones
	 * de lectura de datos.
	 *
	 * Se ha implementado de forma generica para
	 * independizarlo del objeto de transporte
	 * de datos (DTO) usado.
	 */
	template <class T>
	class IDao {
	public:
		virtual T 				read(int id) = 0;
		virtual std::vector<T>	read() = 0;

	protected:
		virtual ~IDao() {}

	};

}

#endif /* IDAO_H_ */
