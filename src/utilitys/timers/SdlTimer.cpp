/*
 * SdlTimer.cpp
 *
 *  Created on: 08/02/2011
 *      Author: jorge
 */

#include "utilitys/timers/SdlTimer.h"

#include <SDL/SDL.h>

namespace temp {

	CSdlTimer::CSdlTimer():
		_startTicks(0),
		_pausedTicks(0),
		_started(false),
		_paused(false){
	}

	CSdlTimer::~CSdlTimer() {
	}

	void CSdlTimer::start(){

		_started = true;
		_paused = false;

		// Cogemos el tiempo que llevamos por ahora
		_startTicks = SDL_GetTicks();
	}

	void CSdlTimer::stop(){
		_started = false;
		_paused = false;
	}

	double CSdlTimer::getElapsedTimeInMicroSec() {
		return getElapsedTime()*0.001;
	}

	double CSdlTimer::getElapsedTimeInMilliSec() {
		return getElapsedTime()*0.001;
	}

	double CSdlTimer::getElapsedTimeInSec() {
		return getElapsedTime()*0.000001;
	}

	void CSdlTimer::sleep(unsigned int millisecs)
	{
	    unsigned int goal = millisecs + SDL_GetTicks();
	    while (goal > SDL_GetTicks());
	}

	void CSdlTimer::pause(){
		if(_started && !_paused){
			_paused = true;

			// Tiempo que llevamos cuando el temporizador ha sido pausado
			_pausedTicks = (SDL_GetTicks() - _startTicks)*0.001;
		}
	}

	void CSdlTimer::unpause(){
		if(_paused){
			_paused = false;

			// Reseteamos los ticks que llevamos
			_startTicks = SDL_GetTicks() - _pausedTicks;

			_pausedTicks = 0;
		}
	}

	inline unsigned int CSdlTimer::getElapsedTime(){
		if(_started){
			if(_paused)
				return _pausedTicks;
			else
				// Devuelve el tiempo actual (milisegundos) menos el que llevamos
				return (SDL_GetTicks() - _startTicks)*1000;
		}
		return 0;
	}
}
