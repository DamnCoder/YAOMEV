/*
 * MouseEvent.h
 *
 *  Created on: 19/11/2010
 *      Author: jorge
 */

#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include "ComponentEvent.h"

namespace event{

	enum EMouseButton{
		MOUSE_BUTTON_LEFT, 		/// Boton izquierdo
		MOUSE_BUTTON_RIGHT, 	/// Boton derecho
		MOUSE_BUTTON_MIDDLE,	/// Boton central
	};

	/**
	 * Eventos relacionados con el raton a partir de su uso sobre un componente
	 * de la interfaz grafica.
	 */
	class MouseEvent : public ComponentEvent{
	public:

		enum EMouseEvent{
			MOUSE_PRESSED,		/// Boton del raton presionado
			MOUSE_RELEASED,		/// Boton del raton soltado
			MOUSE_EXITED,		/// El puntero del raton ha salido del componente
			MOUSE_ENTERED,		/// El puntero del raton ha entrado en el componente
			MOUSE_MOTION		/// El raton se mueve
		};

		/**
		 * Creates a new MouseEvent with the specified
		 * Component as source.
		 */
		MouseEvent(
				logic::CUiComponent* source,
				int x, int y,
				int mouseButton, int event):
			ComponentEvent(source),
			_x(x),
			_y(y),
			_button(mouseButton),
			_event(event)
		{}

		virtual ~MouseEvent() {}

		const int getX() 		const { return _x; }		/// Devuelve la coordenada x del raton
		const int getY() 		const { return _y; }		/// Devuelve la coordenada y del raton
		const int getButton() 	const { return _button; }	/// Devuelve el boton del raton pulsado
		const int getEvent() 	const { return _event; }	/// Devuelve el tipo de evento ocurrido

	private:
		int _x;
		int	_y;

		int	_button;	/// Se corresponde con un enumerado de EMouseButton
		int	_event;		/// Se corresponde con un enumerado de EMouseEvent
	};

}
#endif /* MOUSEEVENT_H_ */
