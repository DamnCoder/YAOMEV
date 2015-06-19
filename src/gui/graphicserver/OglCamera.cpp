/*
 * OglCamera.cpp
 *
 *  Created on: 23/11/2009
 *      Author: jorge
 */

#include "gui/graphicserver/OglCamera.h"

#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>


namespace gui {

	/**
	 * Por defecto miramos a (0,0,0) y con el vector vertical hacia Y
	 */
	COglCamera::COglCamera(math::CVector3f camPos) :
			_position(camPos),
			_forward(),
			_up(math::CVector3f(0.0f,1.0f,0.0f)),
			_aperture(math::degToRad(60.0f)),
			_near(0.5f), _far(200.0f),
			_projectionType(CAM_PROJECTION),
			_aspectRatio(1.0f)

	{
	}

	COglCamera::COglCamera(float posX, float posY, float posZ) :
			_position(math::CVector3f(posX, posY, posZ)),
			_forward(),
			_up(math::CVector3f(0.0f,1.0f,0.0f)),
			_aperture(math::degToRad(60.0f)),
			_near(0.5f), _far(200.0f),
			_projectionType(CAM_PROJECTION),
			_aspectRatio(1.0f)
	{
	}

	COglCamera::COglCamera(const math::CVector3f position, int camProjection) :
			_position(position),
			_forward(),
			_up(math::CVector3f(0.0f,1.0f,0.0f)),
			_aperture(math::degToRad(60.0f)),
			_near(0.5f), _far(200.0f),
			_projectionType(camProjection),
			_aspectRatio(1.0f)
	{
	}

	COglCamera::COglCamera(float posX, float posY, float posZ, int camProjection) :
			_position(math::CVector3f(posX, posY, posZ)),
			_forward(),
			_up(math::CVector3f(0.0f,1.0f,0.0f)),
			_aperture(math::degToRad(60.0f)),
			_near(0.5f), _far(200.0f),
			_projectionType(camProjection),
			_aspectRatio(1.0f)
	{
	}

	COglCamera::~COglCamera() {
	}

	/**
	 * Actualizamos los atributos de la camara si viene al caso y el tipo de perspectiva,
	 * que puede ser:
	 * - Proyeccion
	 * - Ortografica
	 */
	void COglCamera::actualize(float dt){

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if(_projectionType == CAM_PROJECTION){
			float fovy = math::radToDeg(_aperture );
			gluPerspective(fovy, _aspectRatio, _near, _far);
		}
		else{ // cam_parallel
			glOrtho(_left, _right, _bottom, _top, _near, _far);
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(	_position.x, 	_position.y, 	_position.z,
					_forward.x,		_forward.y, 	_forward.z,
					_up.x,			_up.y,			_up.z
					);

		//printf("Posicion camara [ %f, %f, %f]\n",_position.x, _position.y, _position.z);
	}

	/**
	 * Establecemos el ratio de aspecto.
	 * La variable viewport almacena lo siguiente:
	 *  - 0: x
	 *  - 1: y
	 *  - 2: ancho pantalla
	 *  - 3: alto pantalla
	 */
	void COglCamera::setAspectRatioCamera(){
		GLint viewport[4];

		glGetIntegerv(GL_VIEWPORT, viewport);
		if(viewport[3] > 0)
			_aspectRatio = (float) viewport[2] / (float) viewport[3];
		else
			_aspectRatio = 1.0f;
	}

	void COglCamera::setCamera(
			float viewX, float viewY, float viewZ,
			float atX, float atY, float atZ,
			float upX, float upY, float upZ){

		_position = math::CVector3f(viewX, viewY, viewZ);
		_forward = math::CVector3f(atX, atY, atZ);
		_up = math::CVector3f(upX, upY, upZ);

	}

	//--------------------------------------------------------------------------------------
	// METODOS PARA MOVER LA CAMARA
	//--------------------------------------------------------------------------------------

	void COglCamera::zoom(float inc){
		_aperture+=inc;
	}
}
