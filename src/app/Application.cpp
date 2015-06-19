/*
 * Juego.cpp
 *
 *  Created on: 27/10/2009
 *      Author: jorge
 */

#include "app/Application.h"

#include <memory.h>

#include <cassert>

#include <iostream>

#include "app/controllers/StateHandler.h"
#include "app/controllers/ApplicationState.h"

#include "utilitys/utils.h"

namespace app {

	CApplication *CApplication::_instance = 0;

	CApplication::CApplication() :
		_stateHandler(0),
		_started(false),
		_end(false),
		_dt(0),
		_timeApp(0),
		_lastTimeApp(0),
		_pauseTimer(false)
	{
		assert(!_instance && "[Application::Application] No puede crearse más de una aplicación.\n");
		_instance = this;
	}

	CApplication::~CApplication() {
	}

	bool CApplication::init(){
		assert(!_started);

		// Creamos el gestor de estados de la aplicacion
		_stateHandler = new CStateHandler();

		// Establecemos el flag de comienzo a true
		_started = true;

		return true;
	}

	void CApplication::end(){
		_stateHandler->releaseAll();
		safeDelete(_stateHandler);
	}

	void CApplication::run(){
		while (!isAskedForTermination()) {

			initTimer();

			// Comprobamos si hay cambio de estado. Si lo hay, se realizara
			_stateHandler->checkForStateChange();

			// Ejecutamos el estado que se encuentre en marcha en este momento
			_stateHandler->runCurrentState(_dt);

			// Actualizamos el temporizador
			updateTimer();
		}
	}

	void CApplication::setState(const std::string& stateID){
		_stateHandler->setState(stateID);
	}

	void CApplication::addState(const std::string& name, CApplicationState *newState){
		_stateHandler->addState(name, newState);
	}

} // namespace app
