/**
 *  Application.h
 *
 *  Created on: 27/10/2009
 *      Author: jorge
 */

#ifndef CAPPLICATION_H_
#define CAPPLICATION_H_

#include <map>
#include <string>
#include <cassert>

using namespace std;

namespace app {

	class CStateHandler;
	class CApplicationState;

	/**
	 * Clase controladora del juego, implementada como un Singleton
	 */
	class CApplication {

	public:
		/**
		 * Constructor
		 */
		CApplication();

		/**
		 * Destructor
		 */
		virtual ~CApplication();

		virtual bool init();

		/**
		 * Se encarga de solicitar la desactivacion del estado actual
		 * y la terminacion de los estados
		 */
		virtual void end();

		/**
		 * Bucle principal del juego
		 */
		virtual void run();

		/**
		 * Devuelve el tiempo que lleva la aplicacion en marcha
		 */
		const double getAppTime() const { return _timeApp; }

		void pauseTimer() { _pauseTimer = !_pauseTimer; }

		/**
		 * Devuelve la instancia al puntero de la aplicacion
		 */
		static CApplication *getApp();

		/**
		 * Solicitud para terminar la aplicacion
		 * Establece la variable _end a true y en la siguiente vuelta
		 * del bucle principal saldremos de el.
		 */
		void askForTermination(){ _end = true; }

		/**
		 * Indica si se ha solicitado la terminacion del juego
		 * Devuelve el valor booleano _end
		 */
		const bool isAskedForTermination() const { return _end; }

		void setState(const std::string& stateID);
		void addState(const std::string& name, CApplicationState *newState);

	protected:

		/**
		 * Inicializa el contador de tiempo de la aplicacion
		 */
		virtual void initTimer() { assert(!"initTimer no implementada en la clase de la aplicación!"); }

		/**
		 * Actualiza el contador de tiempo de la aplicacion
		 */
		virtual void updateTimer() { assert(!"updateTimer no implementada en la clase de la aplicación!"); }

		//--------------------------------------------------------------------------------------
		// ATRIBUTOS
		//--------------------------------------------------------------------------------------

		static CApplication*	_instance; 		// Unica instancia del juego
		CStateHandler*			_stateHandler;	// Manejador de estados asociado a la aplicacion

		bool 					_started;		// Indica si la aplicacion esta activa
		bool 					_end;			// Indica si la aplicacion tiene que acabar

		double					_dt;			// Delta de tiempo
		float					_timeApp;
		float					_lastTimeApp;
		int						_fps;

		bool					_pauseTimer;

	};

	inline CApplication *CApplication::getApp(){
		return _instance;
	}

} // namespace app

#endif /* CAPPLICATION_H_ */
