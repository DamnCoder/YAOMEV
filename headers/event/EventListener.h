/*
 * EventListener.h
 *
 *  Created on: 19/11/2010
 *      Author: jorge
 */

#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_


namespace event{

	/**
	 * Clase base vacia para todos los Listeners de eventos
	 * Solo sirve para asegurarse de que todos los Listeners
	 * tienen la misma clase base
	 */
	class EventListener{
	public:
		virtual ~EventListener(){}

	};

}

#endif /* EVENTLISTENER_H_ */
