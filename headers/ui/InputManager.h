/*
 * InputManager.h
 *
 *  Created on: 11/02/2011
 *      Author: jorge
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <SDL/SDL.h>

#include "event/InputListener.h"
#include "event/KeyListener.h"
#include "event/WindowListener.h"

#include <list>
#include <iostream>

namespace ui {

	typedef std::list<event::MouseInputListener*>	TMILList;
	typedef std::list<event::KeyListener*>			TKLList;
	typedef std::list<event::WindowListener*>		TWLList;

	typedef TKLList::iterator						TKLIterator;
	typedef TMILList::iterator						TMILIterator;
	typedef TWLList::iterator						TWLIterator;

	class CInputManager {
	public:
		CInputManager();
		virtual ~CInputManager();

		/**
		 * Captura de la entrada de usuario a partir de SDL
		 */
		void processUserInput();

		void addListener(event::WindowListener* wListener){
			//std::cout<<"Añado window listener\n";
			_windowListeners.push_back(wListener);
		}

		void removeListener(event::WindowListener* wListener){
			_windowListeners.remove(wListener);
		}

		void addListener(event::KeyListener* keyListener){
			_keyListeners.push_back(keyListener);
		}

		void removeListener(event::KeyListener* keyListener){
			_keyListeners.remove(keyListener);
		}

		void addListener(event::MouseInputListener* mouseInputListener){
			_mouseInputListeners.push_back(mouseInputListener);
		}

		void removeListener(event::MouseInputListener* mouseInputListener){
			_mouseInputListeners.remove(mouseInputListener);
		}

	private:
		void emitMousePressedEvent(event::MouseInputEvent mouseInputEvent);
		void emitMouseReleasedEvent(event::MouseInputEvent mouseInputEvent);
		void emitMouseMovedEvent(event::MouseInputEvent mouseInputEvent);
		void emitKeyEvent(const event::KeyEvent& keyEvent);
		void emitWindowEvent();

		/**
		 * Maneja la entrada por teclado
		 */
		void handleKeyPress(SDL_keysym* keysym);
		void handleKeyUp(SDL_keysym* keysym);

		/**
		 * Maneja las pulsaciones del ratón
		 */
		void handleMousePress(SDL_MouseButtonEvent* mousebutton);

		/**
		 * Maneja el evento de soltar el botón del ratón
		 */
		void handleMouseRelease(SDL_MouseButtonEvent* mousebutton);

		/**
		 * Maneja el movimiento del ratón
		 */
		void handleMouseMotion(SDL_MouseMotionEvent* mousemotion);

		event::KeyEvent::EKey getKey(SDL_keysym* keysym);

		TMILList 	_mouseInputListeners;
		TKLList		_keyListeners;
		TWLList		_windowListeners;

};

}

#endif /* INPUTMANAGER_H_ */
