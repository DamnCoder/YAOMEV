/*
 * Player.h
 *
 *  Created on: 12/04/2010
 *      Author: jorge
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Avatar.h"

namespace logic {

	class CPlayer: public CAvatar {
	public:

		/**
		 * Clase que permite ordenar una lista de jugadores
		 * de mas puntuacion a menor.
		 */
		class PointsOrder {
		public:
			bool operator() (const CPlayer* player1, const CPlayer* player2) {
				return player1->points() > player2->points();
			}
		};

		CPlayer(const std::string& id,
				const std::string& name,
				float x, float y, float z,
				float orientation, bool visible,
				float scale = 1,
				const std::string& skin = "default");
		~CPlayer();

		/**
		 * Añade un offset a la orientacion para prevenir que el modelo
		 * haya sido importado con una orientacion diferente a la establecida
		 * por defecto.
		 * @param orientationOffset Offset de orientacion [0, 360]
		 */
		void setOrientationOffset(const float orientationOffset){_orientationOffset = orientationOffset; }

		void addPoints(int points){ _points += points; }
		void setPoints(int points){ _points = points; }

		const int points() const { return _points; }

		// FIXME: Metodos de movimiento para pruebas
		void moveFrontwards();
		void moveBackwards();
		void turnRight();
		void turnLeft();
		void stopTurning();
		void stopped();

		void actualize(float dt);

	private:

		void calculateNewPosition(float dt);

		/**
		 * Offset de orientacion, por si el modelo se
		 * ha creado con la orientacion cambiada.
		 */
		float	_orientationOffset;

		//----------------------------------------------------------------------------------------------------------
		// ATRIBUTOS PARA EL JUEGO DE PREGUNTAS Y RESPUESTAS
		//----------------------------------------------------------------------------------------------------------

		int 	_points;

		//----------------------------------------------------------------------------------------------------------
		// ATRIBUTOS PARA UN MOVIMIENTO SIMPLE DEL JUGADOR
		//----------------------------------------------------------------------------------------------------------

		bool 	_movingFrontwards;
		bool 	_movingBackwards;

		bool 	_turningLeft;
		bool 	_turningRight;

		/**
		 * Guarda la magnitud de la velocidad, medida en unidades
		 * <em>por milisegundo</em>. Esta decisión está tomada debido a que
		 * el método actualizar() recibe el número de milisegundos
		 * transcurridos.
		 */
		float 	_velocityMag;

		/**
		 * Almacena el número de grados que gira el personaje
		 * <br>por milisegundo</br>. Esta decisión está tomada debido a que
		 * el método actualizar() recibe el número de milisegundos
		 * transcurridos.
		 */
		float 	_orientVelocity;

		float				_newOrientation;
		math::CPositionf	_newPosition;

	};

}

#endif /* PLAYER_H_ */
