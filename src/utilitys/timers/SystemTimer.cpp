#include "utilitys/timers/SystemTimer.h"
#include <stdlib.h>

#include <iostream>

namespace temp{

	//--------------------------------------------------------------------------
	// IMPLEMENTACION DE CSYSTEMTIMER
	//--------------------------------------------------------------------------

	CSystemTimer::CSystemTimer()
	{
		_conversionFactor = (long double)(1.0/CLOCKS_PER_SEC);
	}

	CSystemTimer::~CSystemTimer()
	{
	}

	void CSystemTimer::start()
	{
		_started = true;
		_startCount = clock();
		//std::cout<<"Inicio "<<_startCount<<"\n";
	}

	void CSystemTimer::stop()
	{
		_started = false;
		_endCount = clock();
		//std::cout<<"Fin "<<_endCount<<"\n";
	}

	double CSystemTimer::getElapsedTimeInMilliSec()
	{
		if(_started){
			//unsigned int difference = clock() - _startCount;
			return (clock() - _startCount + 0.0)*_conversionFactor;
		}
		return (_endCount - _startCount);
	}

	double CSystemTimer::getElapsedTimeInSec()
	{
		return 0;
	}

	void CSystemTimer::sleep(unsigned int millisecs)
	{
	    clock_t goal = millisecs + clock();
	    while (goal > clock());
	}

}
