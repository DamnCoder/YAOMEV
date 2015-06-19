/*
 * PathCamera.cpp
 *
 *  Created on: 19/02/2011
 *      Author: jorge
 */

#include "gui/cam/PathCamera.h"

#include "gui/cam/StaticCamera.h"

namespace gui {

	CPathCamera::CPathCamera(
			const std::string& id,
			std::vector<TCamKeyFrame> keyFrames):
		CAbstractCamera(id),
		_cameraReached(false),
		_keyFrames(keyFrames),
		_nCurrentPosition(1),
		_nArrivalTime(0),
		_timeMoving(0),
		_posDistance(0),
		_speedPos(0.1f)
	{
		calculateSpline();
		calculateNextMove();

		CVector3f newPosition(_positionsSpline[_positionsSpline.size()-1]);

		_forward = _keyFrames[0].lookAt;
		_wantedCamera = new CStaticCamera("final", newPosition, _forward);
	}

	CPathCamera::~CPathCamera() {
		_keyFrames.clear();
		_positionsSpline.clear();

		safeDelete(_wantedCamera);
	}

	CVector3f CPathCamera::getNewPosition(
			const CVector3f &currentPosition,
			const CVector3f &currentLookAt,
			const CVector3f &displacement){

		// Si ya hemos llegado
		if(_timeMoving >= _nArrivalTime){
			++_nCurrentPosition;

			if(_nCurrentPosition > _positionsSpline.size()-1){
				_cameraReached = true;
				return _position;
			}

			calculateNextMove();
		}

		_position = _positionsSpline[_nCurrentPosition-1]+(_vDiffPosNor * _speedPos * _timeMoving);

		//std::cout<<"[CPathCamera::getNewPosition] Posicion "<<_nCurrentPosition<<"\n";
		//std::cout<<"[CPathCamera::getNewPosition] Tiempo moviendote "<<_timeMoving<<" y tiempo en llegar "<<_nArrivalTime<<"\n";

		return _position;
	}

	CVector3f CPathCamera::getNewForward(
			const CVector3f &currentPosition,
			const CVector3f &currentLookAt,
			const CVector3f &displacement)
	{
		return _forward;
	}

	CAbstractCamera *CPathCamera::getLastCamera(){
		if (_cameraReached){
			_cameraReached = false;
			_nCurrentPosition = 0;
			return _wantedCamera;
		}

		return 0;
	}

	void CPathCamera::calculateSpline(){
		std::vector<CVector3f> positions;
		for(uint i = 0; i<_keyFrames.size(); ++i){
			positions.push_back(_keyFrames[i].position);
		}

		// Calculamos la curva para las posiciones
		_spline = Spline(10, positions);
		_positionsSpline = _spline.naturalCubicSpline();

	}

	/**
	 * Preparacion del siguiente movimiento del punto
	 */
	void CPathCamera::calculateNextMove(){

		if(_positionsSpline.size() == 0) return;

		CVector3f destination = _positionsSpline[_nCurrentPosition];
		CVector3f origin = _positionsSpline[_nCurrentPosition-1];

		CVector3f vDist = destination - origin;
		float nDist = vDist.length();

		vDist.normalize();

		_vDiffPosNor = vDist;
		_nArrivalTime = nDist/_speedPos;		// Cálculo del tiempo que se tarda en llegar al punto de destino
		//cout<<"[CPathCamera::calculateNextMove] Distancia al punto "<<nDist<<"\n";
		//cout<<"[CPathCamera::calculateNextMove] Velocidad de la camara "<<_speedPos<<"\n";
		//cout<<"[CPathCamera::calculateNextMove] Tiempo en llegar al punto "<<_nArrivalTime<<"\n";


		_timeMoving = 0;
	}

}
