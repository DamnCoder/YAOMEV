/*
 * StaticCamera.h
 *
 *  Created on: 18/10/2010
 *      Author: jorge
 */

#ifndef STATICCAMERA_H_
#define STATICCAMERA_H_

#include "AbstractCamera.h"

namespace gui {

	/**
	 * Tipo de cámara que tiene estático tanto el origen como el punto de mira.
	 * @see nCamera
	 * @see CAbstractCamera
	 */
	class CStaticCamera : public CAbstractCamera {
	public:

		/**
		 * Construcción.
		 *
		 * @param origen Posición de la cámara.
		 * @param destino Posición hacia la que mira la cámara.
		 */
		CStaticCamera(
				const std::string& id,
				CVector3f position,
				CVector3f lookAt);

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
						const CVector3f &displacement);

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
				const CVector3f &displacement);


	protected:

		/**
		 * Posición estática de la cámara.
		 */
		CVector3f		_position;

		/**
		 * Posición hacia la que mira la cámara.
		 */
		CVector3f		_lookAt;

	}; // class CStaticCamera

}

#endif /* STATICCAMERA_H_ */
