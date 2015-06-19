/**
 * StateHandler.h
 *
 *  Created on: 27/07/2010
 *      Author: jorge
 */

#ifndef CSTATEHANDLER_H_
#define CSTATEHANDLER_H_

#include <map>
#include <string>
#include <cassert>

namespace app {

	class CApplicationState;

	/**
	 * Manejador de estados del juego.
	 * Se encarga de añadir estados, ejecutar el actual, ejecutar las transiciones,
	 * y de activar/desactivar los estados.
	 */
	class CStateHandler {
	public:
		CStateHandler();
		virtual ~CStateHandler();

		void addState(const std::string &nombre, CApplicationState *newState);
		bool setState(const std::string& name);
		bool setPreviousState();
		void runCurrentState(float dt);
		void checkForStateChange();
		void releaseAll();

	protected:
		// Funciones protegidas
		void changeState();

		// Redefiniciones
		typedef std::map<std::string, CApplicationState*> TStateTable;

		// Atributos
		TStateTable 		_states;		/** Tabla de estados del juego */
		CApplicationState*	_previousState;	/** Ultimo estado ejecutado antes de cambiar */
		CApplicationState*	_currentState;	/** Estado actual del juego */
		CApplicationState*	_nextState;		/** Siguiente estado del juego */

	};

}

#endif /* CSTATEHANDLER_H_ */
