/*
 * MouseListener.h
 *
 *  Created on: 19/11/2010
 *      Author: jorge
 */

#ifndef MOUSELISTENER_H_
#define MOUSELISTENER_H_

#include "EventListener.h"

#include "MouseEvent.h"

namespace event{

	/**
	 * Escucha eventos producidos por el raton sobre un componente de la interfaz grafica.
	 */
	class MouseListener : public EventListener{
	public:

		virtual ~MouseListener(){}

		/**
		 * Usado cuando el raton ha sido presionado.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mousePressed(const MouseEvent& e) = 0;

		/**
		 * Usado cuando el puntero del raton entra dentro de un componente.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseEntered(const MouseEvent& e) = 0;

		/**
		 * Usado cuando el cursor del raton sale del componente.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseExited(const MouseEvent& e) = 0;

		/**
		 * Usado cuando un boton del raton es soltado.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseReleased(const MouseEvent& e) = 0;

		/**
		 * Usado cuando el raton se mueve.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseMotion(const MouseEvent& e) = 0;

	};

	/**
	 * Escucha eventos de raton.
	 * El adaptador de raton convierte el Listener en una clase
	 * abstracta para permitir al programador no tener que
	 * implementar todos los metodos del Listener, solo
	 * aquellos que considere necesarios.
	 */
	class MouseAdapter : public MouseListener{
	public:

		virtual ~MouseAdapter() {};

		/**
		 * Usado cuando el raton ha sido presionado.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mousePressed(const MouseEvent& e) {};

		/**
		 * Usado cuando el puntero del raton entra dentro de un componente.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseEntered(const MouseEvent& e) {};

		/**
		 * Usado cuando el cursor del raton sale del componente.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseExited(const MouseEvent& e) {};

		/**
		 * Usado cuando un boton del raton es soltado.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseReleased(const MouseEvent& e) {};

		/**
		 * Usado cuando el raton se mueve.
		 * @param
		 *	e MouseEvent describiendo el evento.
		 */
		virtual void mouseMotion(const MouseEvent& e) {};


	};

}

#endif /* MOUSELISTENER_H_ */
