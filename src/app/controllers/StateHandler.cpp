/**
 * StateHandler.cpp
 *
 *  Created on: 27/07/2010
 *      Author: jorge
 */

#include "app/controllers/StateHandler.h"

#include "app/controllers/ApplicationState.h"

namespace app {

	CStateHandler::CStateHandler()  :
			_previousState(0),
			_currentState(0),
			_nextState(0)
	{
	}

	CStateHandler::~CStateHandler() {
	}

	/**
	 * Añade un nuevo estado al juego
	 */
	void CStateHandler::addState(const std::string &name, CApplicationState *newState){
		TStateTable::const_iterator it;

		#ifdef _DEBUG
			it = _states.find(name);
			assert(it == _states.end());
		#endif

		_states[name] = newState;
		newState->onCreate();
	}

	/**
	 * Establece el siguiente estado del juego
	 */
	bool CStateHandler::setState(const std::string &name){
		TStateTable::const_iterator it;
		it = _states.find(name);

		// Si no hay ningún estado con ese nombre, devolvemos false
		if (it == _states.end())
			return false;

		// Establecemos el siguiente estado
		_nextState= it->second;
		return true;
	}

	bool CStateHandler::setPreviousState() {
		if(!_previousState)
			return false;

		_nextState = _previousState;
		return true;
	}

	/**
	 * Ejecuta el estado actual. Si el puntero es nulo no hace nada.
	 * @param dt
	 */
	void CStateHandler::runCurrentState(float dt){
		// Si el estado actual existe, ejecutamos su tick
		if (_currentState)
			_currentState->onRun(dt);
	}

	/**
	 * Comprueba si ha ocurrido un cambio de estado.
	 * Si asi es, activa el nuevo estado y desactiva el anterior.
	 */
	void CStateHandler::checkForStateChange(){
		// Si es necesario, se cambia el estado
		if (!_currentState || (_nextState && (_currentState!= _nextState)))
		  changeState();
	}

	/**
	 * Liberamos la memoria de todos los estados que hayamos incluido.
	 */
	void CStateHandler::releaseAll(){
		// Desactivamos el estado actual
		if (_currentState)
		  _currentState->onDeactivate();

		// Destruimos los elementos de los estados,
		// los eliminamos y borramos la tabla de estados
		TStateTable::iterator it, end;
		end = _states.end();
		for (it = _states.begin(); it != end; ++it) {
			it->second->onDestroy();
			delete it->second;
		}
		_states.clear();

		_currentState = _nextState = 0;
	}

	/**
	 * Situa el siguiente estado como estado actual
	 */
	void CStateHandler::changeState(){
		if(!_currentState && !_nextState) return;

		// Si el estado actual existe
		if (_currentState)
			_currentState->onDeactivate(); // Desactivamos el estado actual

		// Si no existe el siguiente estado abortamos la aplicacion
		assert(_nextState && "[CStateHandler::changeState] No existe el estado que se quiere activar!");

		// Activamos el siguiente estado
		_nextState->onActivate();

		// Guardamos el estado anterior antes de cambiar el actual
		_previousState = _currentState;

		// Cambiamos estado siguiente a actual
		_currentState = _nextState;
	}

}

