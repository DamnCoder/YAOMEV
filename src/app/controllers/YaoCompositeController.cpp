/*
 * BTAComposeState.cpp
 *
 *  Created on: 27/09/2010
 *      Author: jorge
 */

#include "app/controllers/YaoCompositeController.h"

#include "app/controllers/StateHandler.h"

namespace app {

	CYaoCompositeController::CYaoCompositeController(CYaoApp* app):
		CYaoController(app),
		_stateHandler(){

	}

	CYaoCompositeController::~CYaoCompositeController() {
		safeDelete(_stateHandler);
	}

	/**
	 * Inicia el manejador de estados
	 */
	void CYaoCompositeController::onCreate(){
		CYaoController::onCreate();
		_stateHandler = new CStateHandler();
	}

	/**
	 * Destruye el manejador de estados
	 */
	void CYaoCompositeController::onDestroy(){
		_stateHandler->releaseAll();
		safeDelete(_stateHandler);

		CYaoController::onDestroy();

	}

	/**
	 * Comprueba si se ha solicitado un cambio de estado y ejecuta
	 * el onRun del estado actual.
	 * @param dt
	 */
	void CYaoCompositeController::onRun(float dt){
		// Comprobamos si hay cambio de estado. Si lo hay, se realizara
		_stateHandler->checkForStateChange();

		// Ejecutamos el estado que se encuentre en marcha en este momento
		_stateHandler->runCurrentState(dt);

		// Llamamos al onRun de la clase padre
		CYaoController::onRun(dt);

	}

	/**
	 * Añade un estado al manejador de estados.
	 * Si no se suministra un nombre o un estado no hace nada.
	 * @param name
	 * @param state
	 */
	void CYaoCompositeController::addState(const std::string& name, CYaoController* state){
		if(name.empty() || state)
			_stateHandler->addState(name, state);
	}

	/**
	 * Indica al manejador de estados que cambie el estado actual
	 * al estado asociado al nombre pasado como parametro.
	 * @param name
	 */
	void CYaoCompositeController::setState(const std::string& name){
		_stateHandler->setState(name);
	}

	void CYaoCompositeController::setPreviousState() {
		_stateHandler->setPreviousState();
	}

}
