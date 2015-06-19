/*
 * StateHandler.h
 *
 *  Created on: 06/04/2011
 *      Author: jorge
 */

#ifndef STATEHANDLER_H_
#define STATEHANDLER_H_

#include "State.h"

#include <map>
#include <string>
#include <cassert>

namespace utils {

	/**
	 * Manejador de estados.
	 * Se encarga de añadir estados, ejecutar el actual, ejecutar las transiciones,
	 * y de activar/desactivar los estados.
	 */
	class CStateHandler {
	public:

		CStateHandler():
			_actualState(0),
			_nextState(0)
		{}

		~CStateHandler()
		{}

		/**
		 * Añade un nuevo estado
		 */
		void addState(const std::string &name, IState *newState)
		{
			TStateTable::const_iterator it;

			#ifdef _DEBUG
				// Chequea en DEBUG si el nombre
				// del estado esta repetido
				it = _states.find(name);
				assert(it == _states.end());
			#endif

			_states[name] = newState;
			newState->onCreate();
		}

		/**
		 * Establece el siguiente estado del juego
		 */
		bool setState(const std::string& name)
		{
			// Buscamos el nombre del estado
			TStateTable::const_iterator it;
			it = _states.find(name);

			// Si no hay ningún estado con ese nombre, devolvemos false
			if (it == _states.end())
				return false;

			// Establecemos el siguiente estado
			_nextState= it->second;
			return true;
		}

		/**
		 * Devuelve el actual estado del juego
		 */
		IState* getState(){	return _actualState; }

		/**
		 * Comprueba si ha ocurrido un cambio de estado.
		 * Si asi es, activa el nuevo estado y desactiva el anterior.
		 */
		void checkForStateChange(){
			// Si es necesario, se cambia el estado
			if (!_actualState || (_nextState && (_actualState!= _nextState)))
			  changeState();
		}

		/**
		 * Liberamos la memoria de todos los estados que hayamos incluido.
		 */
		void releaseAll(){
			// Desactivamos el estado actual
			if (_actualState)
			  _actualState->onDeactivate();

			// Destruimos los elementos de los estados,
			// los eliminamos y borramos la tabla de estados
			TStateTable::iterator it, end;
			end = _states.end();
			for (it = _states.begin(); it != end; ++it) {
				it->second->onDestroy();
				delete it->second;
			}
			_states.clear();

			_actualState = _nextState = 0;
		}

	protected:

		/**
		 * Situa el siguiente estado como estado actual
		 */
		void changeState(){

			if (_actualState)
				_actualState->onDeactivate();

			// Si no existe el siguiente estado abortamos la aplicacion
			assert(_nextState && "[CStateHandler::changeState] No existe el estado que se quiere activar!");

			_nextState->onActivate();

			// Cambiamos estado siguiente a actual
			_actualState = _nextState;
		}

		typedef std::map<std::string, IState*> TStateTable;

		TStateTable 	_states;		// Tabla de estados
		IState*			_actualState;	// Estado actual
		IState*			_nextState;		// Siguiente estado

	};

}

#endif /* STATEHANDLER_H_ */
