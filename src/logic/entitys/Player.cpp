/*
 * Player.cpp
 *
 *  Created on: 12/04/2010
 *      Author: jorge
 */

#include "logic/entitys/Player.h"

namespace logic {

	CPlayer::CPlayer(const std::string& id,
			const std::string& name,
			float x, float y, float z,
			float orientation, bool visible,
			float scale,
			const std::string& skin):
		CAvatar(id, name, x, y, z, orientation, visible, scale, skin),
		_orientationOffset(0),
		_points(0),
		_movingFrontwards(false),
		_movingBackwards(false),
		_turningLeft(false),
		_turningRight(false),
		_velocityMag(0.2f),
		_orientVelocity(0.2f),
		_newOrientation(0)
	{}

	CPlayer::~CPlayer(){}

//----------------------------------------------------------------------------------------------------------
// METODOS PARA UN MOVIMIENTO SIMPLE DEL JUGADOR
//----------------------------------------------------------------------------------------------------------

	void CPlayer::moveFrontwards(){
		_movingFrontwards = true;
		_movingBackwards = false;
	}

	void CPlayer::moveBackwards(){
		_movingBackwards = true;
		_movingFrontwards = false;
	}

	void CPlayer::turnRight(){

		_turningLeft = false;
		_turningRight = true;
	}

	void CPlayer::turnLeft(){

		_turningLeft = true;
		_turningRight = false;

	}

	void CPlayer::stopTurning(){
		_turningLeft = false;
		_turningRight = false;
	}

	void CPlayer::stopped(){
		_movingBackwards = false;
		_movingFrontwards = false;
	}

	void CPlayer::actualize(float dt) {
		calculateNewPosition(dt);

		setPosition(_newPosition);
		setOrientation(_newOrientation);

	}

	void CPlayer::calculateNewPosition(float dt){
		// Calculamos la nueva rotacion
		if (_turningLeft)
			_newOrientation = _orientation + dt * _orientVelocity;
		else if (_turningRight)
			_newOrientation = _orientation - dt * _orientVelocity;
		else
			_newOrientation = _orientation;

		// Calculamos la nueva posición
		_newPosition = this->position();

		if (_movingFrontwards || _movingBackwards) {
			math::CVector3f vel = math::UnitVectorFromOrientation<float>(_newOrientation+_orientationOffset);
			if (_movingFrontwards) {
				vel.x = -vel.x;
				vel.y = -vel.y;
			}

			_newPosition.z += vel.x * (float)dt * _velocityMag;
			_newPosition.x += vel.y * (float)dt * _velocityMag;
		}
	}
}
