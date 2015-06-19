/*
 * InputListener.h
 *
 *  Created on: 11/02/2011
 *      Author: jorge
 */

#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_

#include "EventListener.h"
#include "InputEvent.h"

namespace event{

	/**
	 *  Interfaz que debe implementar cualquier Listener que
	 *  desee estar atento a la entrada del raton al interactuar
	 *  con la ventana donde transcurre la accion
	 */
	class MouseInputListener : public EventListener{
	public:
		virtual ~MouseInputListener(){}

		virtual void mousePressed(MouseInputEvent e) = 0;
		virtual void mouseReleased(MouseInputEvent e) = 0;
		virtual void mouseMotion(MouseInputEvent e) = 0;
	};

	/**
	 * Interfaz abstracto para poder elegir implementar solo algunos metodos
	 * del Listener.
	 */
	class MouseInputAdapter : public MouseInputListener{
	public:
		virtual ~MouseInputAdapter(){}

		virtual void mousePressed(MouseInputEvent e) {}
		virtual void mouseReleased(MouseInputEvent e) {}
		virtual void mouseMotion(MouseInputEvent e) {}
	};


}

#endif /* INPUTLISTENER_H_ */
