/**
 *
 */
#ifndef SYSTEMTIMER_H_
#define SYSTEMTIMER_H_

// Cabecera de C para manejo de tiempo
#include <time.h>

#include "TimerFactory.h"

namespace temp{

	class CSystemTimer : public Timer {
		friend class CTimersFactory;
	public:

		void start();
		void stop();

		double getElapsedTimeInSec();               // get elapsed time in second (same as getElapsedTime)
		double getElapsedTimeInMilliSec();          // get elapsed time in milli-second
		double getElapsedTimeInMicroSec(){return 0;}
		void sleep(unsigned int millisecs);

	private:

		CSystemTimer();
		~CSystemTimer();

		bool _started;

		long double	_conversionFactor;	// Factor de conversion para convertir clock_t en segundos

		clock_t _startCount;
		clock_t	_endCount;

	};
};

#endif // SYSTEMTIMER_H_
