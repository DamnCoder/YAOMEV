//////////////////////////////////////////////////////////////////////////////
// Timer.h
// =======
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (c) 2003 Song Ho Ahn
//
// Modificado en 2011 por Jorge Lopez Gonzalez
//////////////////////////////////////////////////////////////////////////////

#ifndef UNIXTIMER_H_
#define UNIXTIMER_H_

// Cabecera de tiempo para sistemas unix (obsoleta)
#include <sys/time.h>

#include "TimerFactory.h"

namespace temp{

	class CUnixTimer : public Timer
	{

	friend class CTimersFactory;

	public:

		void   start();
		void   stop();

		double getElapsedTimeInSec();
		double getElapsedTimeInMilliSec();
		double getElapsedTimeInMicroSec();

		void sleep(unsigned int millisecs);

	private:

		// CONSTRUCTORES
		CUnixTimer();
		~CUnixTimer();

		/**
		 * Devuelve el tiempo con resolucion de microsegundos
		 * en forma de entero sin signo
		 * @return
		 */
		inline unsigned int getElapsedTime();

		// ATRIBUTOS
		bool	_started;

		timeval	_startCount;
		timeval	_endCount;

		timeval _waitCount;

		unsigned int _dt;
	};

	inline unsigned int CUnixTimer::getElapsedTime()
	{
		if(_started){
			gettimeofday(&_endCount, 0);

			return ((_endCount.tv_sec - _startCount.tv_sec)*1000000.0)
					+
					(_endCount.tv_usec-_startCount.tv_usec);
		}

		return 0;
	}
}
#endif /* UNIXTIMER_H_ */
