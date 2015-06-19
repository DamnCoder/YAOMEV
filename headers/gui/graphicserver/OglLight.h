/*
 * OGLLight.h
 *
 *  Created on: 05/02/2010
 *      Author: jorge
 */

#ifndef OGLLIGHT_H_
#define OGLLIGHT_H_


#include "math/Mathlib.h"

#include <GL/gl.h>

namespace gui {

	class COglLight {
	public:

		enum ELightID{
			LIGHT_0 = GL_LIGHT0,
			LIGHT_1 = GL_LIGHT1,
			LIGHT_2 = GL_LIGHT2,
			LIGHT_3 = GL_LIGHT3,
			LIGHT_4 = GL_LIGHT4,
			LIGHT_5 = GL_LIGHT5,
			LIGHT_6 = GL_LIGHT6,
			LIGHT_7 = GL_LIGHT6,
		};

		enum ELightType{
			AGA_DIRECTIONAL,	// Luz direccional
			AGA_POSITIONAL,		// Luz posicional
			AGA_SPOT			// Luz spot
		};


		COglLight();
		COglLight(ELightType type, ELightID id, math::Vec4 pos);
		virtual ~COglLight();

		/**
		 * Establece la luz en la escena (la "dibuja")
		 */
		void actualize();

		/**
		 * Activa o desactiva la luz
		 */
		void switchLight(bool status);

		//---------------------------------------------------
		// METODOS RELACIONADOS CON LOS PARAMETROS DE LA LUZ
		//---------------------------------------------------

		void setPosition(const math::Vec4& newPos){
			_position = newPos;
			_needsUpdate = true;
		}

		void setPointAtInfinity(const math::Vec4& newPAI){
			_pointAtInfinity = newPAI;
			_pointAtInfinity.normalize();
			_needsUpdate = true;
		}

		void setSpotDirection(const math::Vec4& newDir){
			_spotDirection = newDir;
			_spotDirection.normalize();
			_needsUpdate = true;
		}

		void setAmbientComponent(const math::Vec4& newAmb){
			_ambient = newAmb;
			_needsUpdate = true;
		}

		void setDiffuseComponent(const math::Vec4& newDif){
			_diffuse = newDif;
			_needsUpdate = true;
		}

		void setSpecularComponent(const math::Vec4& newSpec){
			_specular = newSpec;
			_needsUpdate = true;
		}

		void setSpotCutOff(float degrees){
			if(0<=degrees && degrees<=180){
				_spotCutOff = degrees;
				_needsUpdate = true;
			}
		}

		void setSpotExponent(float exponent){
			if(0<=exponent && exponent<=128){
				_spotExponent = exponent;
				_needsUpdate = true;
			}
		}

		math::Vec4 getPosition() const {
			return _position;
		}

	private:

		int			_type;

		int			_id;				/// GL_LIGHTx ; -1 la luz no está activa en OpenGL

		bool		_switched;			/// TRUE => ON
		bool		_needsUpdate;		/// TRUE / FALSE
		bool		_white;				/// TRUE / FALSE
		bool		_attenuation;		/// TRUE / FALSE

		math::Vec4 	_ambient;			/// GL_AMBIENT
		math::Vec4	_diffuse;			/// GL_DIFFUSE
		math::Vec4 	_specular;			/// GL_SPECULAR
		math::Vec4 	_position;			/// GL_POSITION
		/**
		 * Este valor representa un punto situado en el infinito,
		 * por lo que la cuarta coordenada homogenea debe ser 0.0f
		 */
		math::Vec4 	_pointAtInfinity;
		/**
		 * GL_SPOT_DIRECTION
		 * La direccion por defecto es (0,0,-1) y solo tiene efecto
		 * cuando GL_SPOT_CUTOFF no es 180
		 */
		math::Vec4	_spotDirection;
		/**
		 * GL_SPOT_EXPONENT [0,128], por defecto 0
		 * 0 				=> distribucion uniforme de la luz
		 * _spotExponent>0 	=> Fuente de luz mas enfocada en un punto
		 */
		float		_spotExponent;
		/**
		 * GL_SPOT_CUTOFF [0,90] & 180, por defecto 180
		 * 180 => distribucion uniforme de la luz
		 */
		float	 	_spotCutOff;
		float	 	_quadAttenuation;	/// GL_QUADRATIC_ATTENUATION
		float	 	_linearAttenuation;	/// GL_LINEAR_ATTENUATION
		/**
		 * GL_CONSTANT_ATTENUATION
		 *  I = I / ( a*delta*delta + b*delta + c )
		 *  delta : Distancia de la luz a un punto
		 *  Por defecto: a=0 b=0 c=1, no hay atenuacion
		 */
		float	 	_constAttenuation;


	};

}

#endif /* OGLLIGHT_H_ */
