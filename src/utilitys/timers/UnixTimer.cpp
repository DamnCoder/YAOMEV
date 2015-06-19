/*
 * CUnixTimer.cpp
 *
 *  Created on: 07/04/2011
 *      Author: jorge
 */

#include "utilitys/timers/UnixTimer.h"

namespace temp{

	//--------------------------------------------------------------------------
	// IMPLEMENTACION DE CUNIXTIMER
	//--------------------------------------------------------------------------

	CUnixTimer::CUnixTimer()
	{

		_startCount.tv_sec = _startCount.tv_usec = 0;
		_endCount.tv_sec = _endCount.tv_usec = 0;

		_started = 0;
	}

	CUnixTimer::~CUnixTimer()
	{
	}

	void CUnixTimer::start()
	{
		_started = true;
		gettimeofday(&_startCount, 0);
	}

	void CUnixTimer::stop()
	{
		_started = false;
	}

	/**
	 * Devuelve el tiempo con resolucion de microsegundos (dependiente de la maquina)
	 * @return
	 */
	double CUnixTimer::getElapsedTimeInMicroSec()
	{
		return getElapsedTime();// * 0.000001;
	}

	/**
	 * Devuelve el tiempo con resolucion de milisegundos
	 * @return
	 */
	double CUnixTimer::getElapsedTimeInMilliSec()
	{
		return getElapsedTime() * 0.001;
	}

	/**
	 * Devuelve el tiempo transcurrido con resolucion de segundos
	 * @return
	 */
	double CUnixTimer::getElapsedTimeInSec()
	{
		return getElapsedTime() * 0.000001;
	}

	void CUnixTimer::sleep(unsigned int millisecs)
	{
	    unsigned int goal = millisecs + getElapsedTimeInMilliSec();
	    while (goal > getElapsedTimeInMilliSec());
	}



}
