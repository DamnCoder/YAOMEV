/*
 * OglCamera.h
 *
 *  Created on: 23/11/2009
 *      Author: jorge
 */

#ifndef OGLCAMERA_H_
#define OGLCAMERA_H_

#include "utilitys/utils.h"

#include "GraphicServer.h"

namespace gui {

	enum{
		CAM_ORTHOGRAPHIC,
		CAM_PROJECTION
	};

	class COglCamera {
	friend class CGraphicServer;
	public:

		virtual ~COglCamera();

		//--------------------------------------------------------------------------------------
		// METODOS PARA CONFIGURAR LA CAMARA
		//--------------------------------------------------------------------------------------

		void setAspectRatioCamera();

		// Establece la posicion
		void setCamera(
				float viewX, float viewY, float viewZ,
				float atX, float atY, float atZ,
				float upX, float upY, float upZ);


		void setPosition(float x, float y, float z){
			_position = math::CVector3f(x,y,z);
		}

		void setPosition(const math::CVector3f& newPosition){
			_position = newPosition;
		}

		void setLookAt(const math::CVector3f& newLookAt){
			_forward = newLookAt;
		}

		void setCamProjection(int camProjection){
			_projectionType = camProjection;
		}

		void setFarView(float camFar){
			_far = camFar;
		}

		void setUpVector(float x, float y, float z){
			_up.x = x;
			_up.y = y;
			_up.z = z;
		}

		void setOrthoParameters(
				float left, float right,
				float bottom, float top,
				float near, float far){

			_left = left;
			_right = right;

			_bottom = bottom;
			_top = top;

			_near = near;
			_far = far;
		}

		void setZ(float inc){
			_position.z = _position.z-inc;
		}

		//--------------------------------------------------------------------------------------
		// METODOS PARA MOVER LA CAMARA
		//--------------------------------------------------------------------------------------

		void zoom(float inc);
		void actualize(float dt);

		math::CVector3f getPosition() const { return _position; }

	protected:

		//--------------------------------------------------------------------------------------
		// CONSTRUCTORES
		//--------------------------------------------------------------------------------------

		COglCamera(math::CVector3f camPos);
		COglCamera(float posX, float posY, float posZ);
		COglCamera(const math::CVector3f position, int camProjection);
		COglCamera(float posX, float posY, float posZ, int camProjection);


	private:

		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		/** Atributos propios de la camara*/

		math::CVector3f 	_position; 			// Situacion de la camara, en coordenadas de mundo
		math::CVector3f 	_forward;			// Punto al que la camara mira, en coordenadas de mundo
		math::CVector3f 	_up;				// Up vector de la camara

		float 				_aperture;			// Campo de vista en radianes. NOTA : OpenGL usa grados
		float 				_near;				// Punto inicial a partir del que la camara empieza a dibujar
		float 				_far;				// Punto final a partir del que la camara ya no muestra nada

		int 				_projectionType;	// Paralela / Ortografrica (1) o Conica / Proyeccion(2)

		/** Atributos dependientes del sistema de ventanas */
		float 				_aspectRatio;
		float 				_left, _right,
							_bottom, _top;

	};

}

#endif /* OGLCAMERA_H_ */
