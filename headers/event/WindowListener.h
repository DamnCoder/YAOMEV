/*
 * WindowListener.h
 *
 *  Created on: 16/02/2011
 *      Author: jorge
 */

#ifndef WINDOWLISTENER_H_
#define WINDOWLISTENER_H_


#include "EventListener.h"

namespace event{

	class WindowListener : public EventListener {
	public:

		virtual ~WindowListener() {}

		virtual void closeWindowEvent() {}
	};

}


#endif /* WINDOWLISTENER_H_ */
