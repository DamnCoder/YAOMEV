/*
 * TimerFactory.h
 *
 *  Created on: 06/04/2011
 *      Author: jorge
 */

#ifndef TIMERFACTORY_H_
#define TIMERFACTORY_H_

namespace temp{

	enum eTimerType{
		SDL_TIMER,
		C_TIMER,
		UNIX_TIMER,
	};

	class Timer {
	public:
		virtual ~Timer() {}
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual double getElapsedTimeInSec() = 0;
		virtual double getElapsedTimeInMilliSec() = 0;
		virtual double getElapsedTimeInMicroSec() = 0;

		virtual void sleep(unsigned int millisecs) = 0;
	};

	class CTimersFactory {
	public:
		static Timer* getNewTimer(eTimerType type);
	};
}

#endif /* TIMERFACTORY_H_ */
