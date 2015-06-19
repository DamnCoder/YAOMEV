/*
 * TimerFactory.cpp
 *
 *  Created on: 07/04/2011
 *      Author: jorge
 */

#include "utilitys/timers/TimerFactory.h"

#include "utilitys/timers/SdlTimer.h"
#include "utilitys/timers/SystemTimer.h"
#include "utilitys/timers/UnixTimer.h"

namespace temp{

	Timer* CTimersFactory::getNewTimer(eTimerType type){
		Timer* timer = 0;

		switch(type){
		case SDL_TIMER:
			timer = new CSdlTimer();
			break;
		case C_TIMER:
			timer = new CSystemTimer();
			break;
		case UNIX_TIMER:
			timer = new CUnixTimer();
			break;
		}

		return timer;
	}
}
