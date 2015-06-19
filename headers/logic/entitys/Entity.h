/*
 * Entidad.h
 *
 *  Created on: 20/12/2009
 *      Author: jorge
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "math/Mathlib.h"

#include <list>
#include <string>
#include <iostream>

namespace logic {

	// Predeclaraciones
	class CBehavior;

	struct tRGBAColor{
		float r;
		float g;
		float b;
		float a;

		tRGBAColor():
			r(0), g(0), b(0), a(1) {}
		tRGBAColor(float r, float g, float b, float a):
			r(r), g(g), b(b), a(a) {}
	};

	/**
	 * Clase que representa todas las entidades del juego con posicion, orientacion y visibilidad.
	 */
	class CEntity {
	public:

		// Escuchador de entidad
		class EntityListener {
		public:
			virtual void changedPosition(
					const CEntity* entity,
					float x, float y, float z) = 0;

			virtual void changedOrientation(
					const CEntity* entity,
					float newOrientation) = 0;

			virtual void changedVisibility(
					const CEntity* entity,
					bool visible) = 0;

			virtual void changedSkin(const std::string& skin) = 0;

			virtual void changedScale(const float scale) = 0;

		}; //class Listener

		//--------------------------------------------------------------------------------------
		// Constructores / Destructores
		//--------------------------------------------------------------------------------------

		CEntity(float x, float y, float z);
		CEntity(
				const std::string& id="",
				float x=0, float y=0, float z=0,
				float orientation=0,
				bool visible=true,
				float scale=1);
		CEntity(
				const std::string& id,
				const std::string& skin,
				float x=0, float y=0, float z=0,
				float orientation=0,
				bool visible=true,
				float scale=1);
		virtual ~CEntity();

		//--------------------------------------------------------------------------------------
		// METODOS A REDEFINIR EN SUS ESPECIALIZACIONES
		//--------------------------------------------------------------------------------------
		virtual void actualize(float dt){}

		//--------------------------------------------------------------------------------------
		// Modificadores
		//--------------------------------------------------------------------------------------

		void setBehavior(CBehavior* behavior) { _behavior = behavior; }
		void setId(const std::string& id){ _id = id; }
		void setPosition(float x, float y, float z);
		void setPosition(const math::CPositionf& position);

		/**
		 * Establece la nueva orientación de la entidad lógica. Se
		 * propagan los eventos a los listeners asociados para
		 * notificarles el cambio.
		 *
		 * @param newOrientation Nueva orientación de la entidad.
		 * Asume que un ángulo de 0 grados mira hacia el norte,
		 * 90 mira hacia el este, 180 hacia el sur y 270
		 * hacia el oeste (es decir, gira en el sentido de las agujas
		 * del reloj).
		 */
		virtual void setOrientation(const float newOrientation);
		void setVisible(bool visible);
		void setSkin(const std::string& skin);
		void setScale(const float scale);
		void setReflection(bool reflection) { _reflection = reflection; }
		void setColor(tRGBAColor color) { _rgbaColor = color; }


		//--------------------------------------------------------------------------------------
		// Accesores
		//--------------------------------------------------------------------------------------
		const std::string	id() 			const { return _id; }
		const std::string 	skin()			const { return _skin; }
		math::CPositionf 	position() 		const { return _position; }
		float 				orientation() 	const { return _orientation; }
		const float			scale()			const { return _scale; }
		const bool 			visible() 		const { return _visible; }
		const bool 			reflection() 	const { return _reflection; }
		const tRGBAColor 	color() 		const { return _rgbaColor; }

		//--------------------------------------------------------------------------------------
		// Añadir / Quitar obervadores de la entidad
		//--------------------------------------------------------------------------------------
		bool addListener(EntityListener* newListener);
		bool removeListener(EntityListener* oldListener);

	protected:

		//--------------------------------------------------------------------------------------
		// Comunicacion de eventos al observador
		//--------------------------------------------------------------------------------------
		void emitChangedPosition();
		void emitChangedOrientation();
		void emitChangedVisibility();
		void emitChangedSkin();
		void emitChangedScale();

		CBehavior*					_behavior;

		std::string					_id;
		std::string 				_skin;
		math::CPositionf 			_position;		/** Posicion de la entidad logica */
		float						_orientation;	/** Orientacion de la entidad */
		float						_scale;			/** Factor de escala de la entidad */
		bool 						_visible;		/** Visibilidad de la entidad */
		bool						_reflection;
		tRGBAColor					_rgbaColor;
		std::list<EntityListener*> 	_listeners;

	};

}

#endif /* ENTITY_H_ */
