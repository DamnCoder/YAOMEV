/*
 * CameraManager.cpp
 *
 *  Created on: 18/10/2010
 *      Author: jorge
 */

#include "gui/cam/CameraManager.h"

#include "gui/graphicserver/OglCamera.h"

#include "logic/entitys/Entity.h"

#include "gui/cam/StaticCamera.h"

#include <typeinfo>

namespace gui {

	CCameraManager::CCameraManager():
		_currentCamera(0),
		_currentPosition(0.0f, 200.0f, -475.0f),
		_currentForward(0.0f, 100.0f, 0.0f),
		_loop(false),
		_queueMode(false),
		_cameraChange(false),
		_transitionActive(false){

		_camera = CGraphicServer::instance().newCamera(
				_currentPosition,
				gui::CAM_PROJECTION);

		_camera->setFarView(15000);
		_camera->setAspectRatioCamera();

		_currentCamera = new CStaticCamera("default", _currentPosition, _currentForward);
	}

	CCameraManager::~CCameraManager() {
		safeDelete(_camera);
		_cameraMap.clear();
		_listeners.clear();
	}

	void CCameraManager::actualize(float dt){
		if (!_currentCamera)
			return;

		_currentCamera->actualize(dt);

		if(_queueMode)
			actualizeCameraQueue();
		else
			actualizeCamera();


		_camera->setPosition(_currentPosition);
		_camera->setLookAt(_currentForward);
		_camera->actualize(dt);
	}

	void CCameraManager::actualizeCameraQueue(){

		// Si hay una transicion activa actualizamos la camara actual
		if(isATransitionActive()){
			//cout<<"[CCameraManager::actualizeCameraQueue] Transicion activa: "<<isATransitionActive()<<"\n";
			actualizeCamera();
		}
		else if(isCameraChanged()){		// Sino, si se ha terminado la transicion sacamos la camara de la cola

			string cameraName = _cameraNameQueue.back();
			_currentCamera = _cameraMap[cameraName];

			_cameraNameQueue.pop_back();

			_transitionActive = true;
			_cameraChange = false;

			//cout<<"[CCameraManager::actualizeCameraQueue] Cambiamos de camara!\n";
			//cout<<"[CCameraManager::actualizeCameraQueue] La camara activa es: "<<cameraName<<"\n";
			//cout<<"[CCameraManager::actualizeCameraQueue] Transicion activa. No hay cambio de camara esperado.\n";
		}
	}

	void CCameraManager::actualizeCamera(){
		CVector3f desiredMovement;

		_currentPosition = _currentCamera->getNewPosition(
				_currentPosition,
				_currentForward,
				desiredMovement
				);

		_currentForward = _currentCamera->getNewForward(
				_currentPosition,
				_currentForward,
				desiredMovement
				);

		// Las camaras path devuelven una ultima camara con la posicion final
		CAbstractCamera* newCamera = _currentCamera->getLastCamera();
		if (newCamera != NULL) {
			_currentCamera = newCamera;

			//cout<<"[CCameraManager::actualizeCamera] Transicion completa. No hay transicion activa.\n";
			// Si no quedan transiciones desactivamos el modo cola
			if(_cameraNameQueue.empty()){	/// Si no quedan camaras desactivamos todos los flags lanzamos un evento
				//cout<<"[CCameraManager::actualizeCamera] No quedan camaras\n";
				_queueMode = false;
				_transitionActive = false;
				_cameraChange = false;
				emitCameraTransitionsOver();
			}
			else {
				_cameraChange = true;		// Si es ultima camara y quedan camaras en la cola habra cambio
				_transitionActive = false;	// Indicamos que la transicion ha terminado
			}
		}
		else if(_queueMode && (typeid(newCamera) == typeid(CStaticCamera*))){
			_cameraChange = true;
			_transitionActive = false;
		}
	}

	void CCameraManager::clearCameraQueue(){
		_cameraNameQueue.clear();
		_transitionActive = false;
		_queueMode = false;

		CAbstractCamera* newCamera = _currentCamera->getLastCamera();

		if (newCamera != NULL) {
			//cout<<"[CCameraManager::clearCameraQueue] Ultima camara pillada\n";
			_currentCamera = newCamera;
			_cameraChange = true;
		}
	}

	void CCameraManager::addCamera(const string& name, CAbstractCamera* camera){
		//cout<<"[CCameraManager::addCamera] Añadida camara: "<<name<<"\n";
		_cameraMap[name] = camera;
	}

	void CCameraManager::addCameraToQueue(const std::string& cameraName){
		//cout<<"[CCameraManager::addCameraToQueue] Añadida camara a la cola: "<<cameraName<<"\n";
		_cameraNameQueue.push_back(cameraName);
		_queueMode = true;
		_cameraChange = true;
	}

	void CCameraManager::addListener(CameraListener* newListener){
		_listeners.push_back(newListener);
	}

	void CCameraManager::removeListener(CameraListener* oldListener){
		_listeners.remove(oldListener);
	}

	void CCameraManager::emitCameraTransitionsOver(){
		list<CameraListener*>::iterator it(_listeners.begin()), end(_listeners.end());
		for(;it!=end;++it)
			(*it)->emptyCameraQueueEvent();
	}

}
