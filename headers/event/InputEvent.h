/*
 * InputEvent.h
 *
 *  Created on: 11/02/2011
 *      Author: jorge
 */

#ifndef INPUTEVENT_H_
#define INPUTEVENT_H_

#include "Event.h"

namespace event{

	/**
	 * Eventos de raton en su uso sobre la pantalla
	 */
	class MouseInputEvent : public Event{
	public:

		MouseInputEvent(int button, int x, int y):
			_button(button),
			_x(x),
			_y(y)
		{}

		const int getButton() const { return _button; }
		const int getX() const { return _x; }
		const int getY() const { return  _y; }

	private:

		int _button;
		int _x;
		int _y;
	};

}

#endif /* INPUTEVENT_H_ */
