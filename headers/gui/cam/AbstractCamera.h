/*
 * AbstractCamera.h
 *
 *  Created on: 18/10/2010
 *      Author: jorge
 */

#ifndef ABSTRACTCAMERA_H_
#define ABSTRACTCAMERA_H_

#include "math/Mathlib.h"

#include <sys/types.h>
#include <string>

namespace gui {

	using namespace math;

	class CAbstractCamera {
	public:

		CAbstractCamera(const std::string& id):
			_id(id)
		{
		}
		virtual ~CAbstractCamera() {};

		/**
		 * Calcula la nueva posición de la cámara a partir del origen actual,
		 * el destino actual y el desplazamiento deseado (el solicitado por el
		 * usuario con las teclas de control de cámara). <br>
		 * El objeto cámara puede guardar estado, que deberá haber inicializado
		 * en el constructor, para calcular la nueva posición (por ejemplo
		 * la velocidad actual de desplazamiento, o la entidad hacia la que se
		 * apunta siempre).
		 *
		 * @param origenActual Posición de la cámara actualmente.
		 * @param destinoActual Posición hacia la que apunta la cámara actualmente.
		 * @param desplazamiento Desplazamiento de la cámara solicitado por el
		 * usuario con los dispositivos de entrada correspondientes de control de
		 * la cámara.
		 * @return Nueva posición de la cámara de acuerdo a la política de la
		 * "subcámara".
		 */
		virtual CVector3f getNewPosition(
				const CVector3f &actualPosition,
				const CVector3f &actualLookAt,
				const CVector3f &displacement) = 0;

		/**
		 * Calcula la nueva posición hacia la que apunta la cámara a partir del
		 * origen actual, el destino actual y el desplazamiento deseado (el
		 * solicitado por el usuario con las teclas de control de cámara). <br>
		 * El objeto cámara puede guardar estado, que deberá haber inicializado
		 * en el constructor, para calcular la nueva posición (por ejemplo
		 * la velocidad actual de desplazamiento, o la entidad hacia la que se
		 * apunta siempre).
		 *
		 * @param origenActual Posición de la cámara actualmente.
		 * @param destinoActual Posición hacia la que apunta la cámara actualmente.
		 * @param desplazamiento Desplazamiento del destino de la cámara solicitado
		 * por el usuario con los dispositivos de entrada correspondientes de control
		 * de la cámara.
		 *
		 * @return Nueva posición hacia la que mira la cámara de acuerdo a la
		 * política de la "subcámara".
		 */
		virtual CVector3f getNewForward(
				const CVector3f &actualPosition,
				const CVector3f &actualLookAt,
				const CVector3f &displacement) = 0;

		/**
		 * Devuelve una nueva cámara. En algunas cámaras de transición, la propia
		 * cámara puede desear solicitar un cambio de cámara para la siguiente
		 * vuelta. Si eso ocurre, este método devolverá la nueva cámara que hay
		 * que comenzar a utilizar. En caso contrario, devuelve NULL.
		 *
		 * @return Nueva cámara a utilizar, o NULL en caso contrario.
		 * @note La implementación por defecto devuelve NULL, indicando que no hay
		 * que realizar cambio de cámara en ningún caso.
		 */
		virtual CAbstractCamera* getLastCamera() { return NULL; }

		/**
		 * Algunas camaras necesitan tener en cuenta el tiempo que transcurre
		 * entre una vuelta del bucle y otra.
		 * La implementacion por defecto no hace nada.
		 * @param dt
		 */
		virtual void actualize(float dt) {
		}

		const std::string id() const { return _id; }

	private:

		std::string	_id;

	};

}

#endif /* ABSTRACTCAMERA_H_ */
