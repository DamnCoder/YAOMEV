/*
 * CameraManager.h
 *
 *  Created on: 18/10/2010
 *      Author: jorge
 */

#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "AbstractCamera.h"
#include "utilitys/utils.h"

namespace logic{
	class CEntity;
}

namespace gui {

	class COglCamera;

	/**
	 * Gestor de Camaras del juego Bit Them All.
	 *
	 * Controla todas las camaras del juego.
	 * Almacena todas las camaras que se usaran en el juego y podra establecer transiciones entre ellas, y
	 * cambiar de unas a otras.
	 *
	 */
	class CCameraManager {
	public:

		class CameraListener{
		public:
			virtual ~CameraListener() {}

			virtual void emptyCameraQueueEvent(){}			// Evento ocurrido cuando ya no quedan camaras en la cola
			virtual void cameraTransitionFinishedEvent(){}
		};

		CCameraManager();
		~CCameraManager();

		void actualize(float dt);

		//----------------------------------------------------------------------
		// Accesores
		//----------------------------------------------------------------------

		const bool isCameraChanged()		const { return _cameraChange; }
		const bool isATransitionActive()	const { return _transitionActive; }
		const bool isQueueMode() 			const { return _queueMode; }

		//----------------------------------------------------------------------
		// Modificadores
		//----------------------------------------------------------------------

		void clearCameraQueue();
		void setTransitionActive(bool active){ _transitionActive = active; }

		void addCameraToQueue(const std::string& cameraName);
		void addCamera(const string& name, CAbstractCamera* camera);

		void addListener(CameraListener* newListener);
		void removeListener(CameraListener* oldListener);

	private:
		void actualizeCamera();
		void actualizeCameraQueue();

		void emitCameraTransitionsOver();

		COglCamera*						_camera;			/** Transmite la informacion de la camara a OpenGL */

		CAbstractCamera*				_currentCamera;		/** Camara en funcionamiento en un instante dado */
		CVector3f						_currentPosition;	/** Posicion actual de la camara en funcionamiento */
		CVector3f						_currentForward;	/** Punto al que mira la camara en funcionamiento */

		bool							_loop;				/** Indica si la camara se ejecuta en loop */
		bool							_queueMode;			/** Indica si esta activada la cola de camaras */
		bool							_cameraChange;		/** Indica cuando se ha hecho una transicion de una camara a otra */
		bool							_transitionActive;	/** Indica que hay una camara activa */

		map<string, CAbstractCamera*> 	_cameraMap; 		/** Tabla de las camaras gestionadas */
		vector<string>					_cameraNameQueue;

		list<CameraListener*>			_listeners;
	};
}

#endif /* CAMERAMANAGER_H_ */
