/*
 * KeyListener.h
 *
 *  Created on: 14/02/2011
 *      Author: jorge
 */

#ifndef KEYLISTENER_H_
#define KEYLISTENER_H_

#include "EventListener.h"
#include "KeyEvent.h"

namespace event{

	class KeyListener : public EventListener{
	public:

		virtual ~KeyListener() {};

		virtual void keyPressed(const KeyEvent& ke) = 0;
		virtual void keyReleased(const KeyEvent& ke) = 0;
		virtual void keyTyped(const KeyEvent& ke) = 0;

	};

	class KeyAdapter : public KeyListener {
	public:

		virtual ~KeyAdapter() {};

		virtual void keyPressed(const KeyEvent& ke) {}
		virtual void keyReleased(const KeyEvent& ke) {}
		virtual void keyTyped(const KeyEvent& ke) {}

	};

}
#endif /* KEYLISTENER_H_ */
