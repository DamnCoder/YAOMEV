/*
 * PathCamera.h
 *
 *  Created on: 19/02/2011
 *      Author: jorge
 */

#ifndef PATHCAMERA_H_
#define PATHCAMERA_H_

#include "AbstractCamera.h"

#include "math/Spline.h"

#include <vector>

namespace gui {

	struct TCamKeyFrame{
		float 		speed;
		CVector3f 	position;
		CVector3f	lookAt;
		CQuaternionf quaternion;
	};

	class CPathCamera : public CAbstractCamera {
	public:

		CPathCamera(
				const std::string& id,
				std::vector<TCamKeyFrame> keyFrames);

		~CPathCamera();

		CVector3f getNewPosition(
				const CVector3f &actualPosition,
				const CVector3f &actualLookAt,
				const CVector3f &displacement);

		CVector3f getNewForward(
				const CVector3f &actualPosition,
				const CVector3f &actualLookAt,
				const CVector3f &displacement);

		void actualize(float dt) {
			_timeMoving += dt;
		}

		CAbstractCamera* getLastCamera();

	private:

		void calculateSpline();
		void calculateNextMove();

		bool						_cameraReached;			/// Indica si la camara ha alcanzado su destino

		std::vector<TCamKeyFrame> 	_keyFrames;				/// Lista de keyframes de la camara

		Spline						_spline;				/// Curva spline obtenida a partir de los keyframes

		CVector3f					_position;				/// Posicion actual de la camara
		std::vector<CVector3f>		_positionsSpline;		/// Lista de posiciones obtenidas al calcular la spline
		CVector3f					_vDiffPosNor;			/// Vector normal indicando la direccion de movimiento
		uint						_nCurrentPosition;		/// Indice a la posicion actual de la lista de posiciones
		float						_nArrivalTime;			/// Tiempo en llegar a la siguiente posicion
		float 						_timeMoving;			/// Tiempo desplazandose
		uint						_posDistance;

		float						_speedPos;

		CVector3f					_forward;

		CAbstractCamera*			_wantedCamera;

	};

}

#endif /* PATHCAMERA_H_ */
