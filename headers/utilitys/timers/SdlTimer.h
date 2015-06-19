/*
 * SdlTimer.h
 *
 *  Created on: 08/02/2011
 *      Author: jorge
 */

#ifndef SDLTIMER_H_
#define SDLTIMER_H_

#include <sys/types.h>

#include "TimerFactory.h"

namespace temp {

	/**
	 * Temporizador basado en SDL.
	 *
	 * Devuelve el tiempo en milisegundos transcurrido desde
	 * que se uso el metodo start
	 */
	class CSdlTimer : public Timer{

	friend class CTimersFactory;

	public:

		/**
		 * Inicia el temporizador
		 */
		void start();

		/**
		 * Detiene el temporizador
		 */
		void stop();

		/**
		 * Devuelve el tiempo transcurrido con resolucion de segundos
		 * @return
		 */
		double getElapsedTimeInSec();

		/**
		 * Devuelve el tiempo con resolucion de milisegundos
		 * @return
		 */
		double getElapsedTimeInMilliSec();

		/**
		 * Devuelve el tiempo con resolucion de microsegundos (dependiente de la maquina)
		 * SDL devuelve el tiempo con precision de milisegundos, luego este metodo
		 * tambien.
		 * @return
		 */
		double getElapsedTimeInMicroSec();

		void sleep(unsigned int millisecs);

		/**
		 * Pausamos el temporizador, se almacena el tiempo
		 * que llevaba activo hasta la pausa
		 */
		void pause();

		/**
		 * Despausamos el temporizador.
		 * Se establece
		 */
		void unpause();

		bool isStarted() const { return _started; }
		bool isPaused() const { return _paused; }

	private:

		CSdlTimer();
		~CSdlTimer();

		inline unsigned int getElapsedTime();

		uint	_startTicks;	// Tiempo en el que se inicio el temporizador
		double	_pausedTicks;	// Tiempo en que se pauso el temporizador

		bool	_started;
		bool	_paused;

	};

}
#endif /* SDLTIMER_H_ */
