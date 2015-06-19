/*
 * OGLLight.cpp
 *
 *  Created on: 05/02/2010
 *      Author: jorge
 */

#include "gui/graphicserver/OglLight.h"

#include <iostream>

#include <GL/gl.h>

namespace gui {

	COglLight::COglLight():
			_type(AGA_DIRECTIONAL), _id(-1),
			_switched(false), _needsUpdate(true), _white(true), _attenuation(false),
			_ambient	(math::Vec4(0, 0, 0, 1)),
			_diffuse	(math::Vec4(0, 0, 0, 1)),
			_specular	(math::Vec4(0, 0, 0, 1)),
			_position	(math::Vec4(1, 1, 1, 1)),
			_pointAtInfinity(math::Vec4(1, 1, 1, 0)),
			_spotDirection	(math::Vec4(-1, -1, -1, 0)),
			_spotExponent(10),
			_spotCutOff(30), // En grados
			_quadAttenuation(0.1f), _linearAttenuation(0.0f), _constAttenuation(1.0f) {

		_pointAtInfinity.normalize();
		_spotDirection.normalize();

	}

	COglLight::COglLight(ELightType type, ELightID id, math::Vec4 pos):
			_type(type), _id(id),
			_switched(false), _needsUpdate(true), _white(true), _attenuation(false),
			_ambient	( math::Vec4(0, 0, 0, 1)),
			_diffuse	( math::Vec4(0, 0, 0, 1)),
			_specular	( math::Vec4(0, 0, 0, 1)),
			_position	(pos),
			_pointAtInfinity(math::Vec4(1, 1, 1, 0)),
			_spotDirection	(math::Vec4(-1, -1, -1, 0)),
			_spotExponent(10),
			_spotCutOff(30), // En grados
			_quadAttenuation(0.1f), _linearAttenuation(0.0f), _constAttenuation(1.0f) {

		_pointAtInfinity.normalize();
		_spotDirection.normalize();

	}

	COglLight::~COglLight() {
	}

	void COglLight::actualize(){

		if( !_switched ) return;

		if(  _id < GL_LIGHT0 ) return;

		// Los parametros geometricos son siempre establecidos cuando la escena es redibujada
		switch(_type){
		case AGA_DIRECTIONAL:
		{
			float pai[4] = {_pointAtInfinity.x, _pointAtInfinity.y, _pointAtInfinity.z, _pointAtInfinity.w };
			glLightfv(_id, GL_POSITION, pai );
		}
			break;
		case AGA_POSITIONAL:
		{
			float pos[4] = {_position.x, _position.y, _position.z, _position.w};
			glLightfv( _id, GL_POSITION, pos );
		}
			break;
		case AGA_SPOT:
		{
			float pos[4] = {_position.x, _position.y, _position.z, _position.w};
			float sd[4] = {_spotDirection.x, _spotDirection.y, _spotDirection.z, _spotDirection.w};
			glLightfv( _id, GL_POSITION,	pos );
			glLightfv( _id, GL_SPOT_DIRECTION, sd );
		}
			break;
		}

		/*
		 * Estos otros parametros no suelen cambiar,
		 * por lo que solo se actualizaran cuando alguno
		 * de ellos haya sufrido un cambio
		 * El interfaz debe marcar _needsUpdate a true
		 * cuando se cambie cualquier de estos atributos
		 */
		if( _needsUpdate ) {
			_needsUpdate = false;

			float ambient[4] = {_ambient.x, _ambient.y, _ambient.z, _ambient.w};
			float diffuse[4] = {_diffuse.x, _diffuse.y, _diffuse.z, _diffuse.w};
			float specular[4] = {_specular.x, _specular.y, _specular.z, _specular.w};

			glLightfv( _id, GL_AMBIENT, ambient );
			glLightfv( _id, GL_DIFFUSE, diffuse );
			glLightfv( _id, GL_SPECULAR, specular );

			if( _type == AGA_SPOT ) {
				//std::cout << "Llego a fijar luz spotiana?\n";
				glLightf( _id, GL_SPOT_EXPONENT,	_spotExponent );
				glLightf( _id, GL_SPOT_CUTOFF, 		_spotCutOff );
			}
			else {
				glLighti( _id, GL_SPOT_EXPONENT, 0 );
				glLighti( _id, GL_SPOT_CUTOFF, 180 );
			}

			if( ! _attenuation || _type == AGA_DIRECTIONAL ) {
				glLighti( _id, GL_CONSTANT_ATTENUATION, 1 );
				glLighti( _id, GL_LINEAR_ATTENUATION, 0 );
				glLighti( _id, GL_QUADRATIC_ATTENUATION,	0 );
			}
			else {
				glLightf( _id, GL_CONSTANT_ATTENUATION, 	_constAttenuation );
				glLightf( _id, GL_LINEAR_ATTENUATION, 		_linearAttenuation );
				glLightf( _id, GL_QUADRATIC_ATTENUATION,	_quadAttenuation );
			}
		}
	}

	/**
	 * Metodo que activa o desactiva la luz
	 */
	void COglLight::switchLight(bool status){
		if(_id < GL_LIGHT0 ) return;

		_switched = status;

		if( status ) {
			glEnable( _id );
			_needsUpdate = true;
		}
		else
			glDisable( _id );

	}
}
