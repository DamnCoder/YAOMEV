/*
 * InputManager.cpp
 *
 *  Created on: 11/02/2011
 *      Author: jorge
 */

#include "ui/InputManager.h"

#include "event/MouseEvent.h"

namespace ui {

	CInputManager::CInputManager() {
	}

	CInputManager::~CInputManager() {
	}

	void CInputManager::processUserInput(){
		SDL_Event event;
		while ( SDL_PollEvent(&event) ){
			switch(event.type){
			case SDL_KEYUP: 			// Soltamos una tecla
				//std::cout<<"[CInputManager::processUserInput] Recibido evento SDL_KEYUP!\n";
				handleKeyUp(&event.key.keysym);
				break;

			case SDL_KEYDOWN: 			// Soltamos una tecla
				//std::cout<<"[CInputManager::processUserInput] Recibido evento SDL_KEYDOWN!\n";
				handleKeyPress(&event.key.keysym);
				break;

			case SDL_MOUSEMOTION:		// Movimiento del raton
				//std::cout<<"[CInputManager::processUserInput] Recibido evento SDL_MOUSEMOTION!\n";
				handleMouseMotion(&event.motion);
				break;

			case SDL_MOUSEBUTTONUP: 	// Levantamos el boton del raton
				//std::cout<<"[CInputManager::processUserInput] Recibido evento SDL_MOUSEBUTTONUP!\n";
				handleMouseRelease(&event.button);
				break;

			case SDL_MOUSEBUTTONDOWN:	// Presionamos el boton del raton
				//std::cout<<"[CInputManager::processUserInput] Recibido evento SDL_MOUSEBUTTONDOWN!\n";
				handleMousePress(&event.button);
				break;

			case SDL_QUIT:				// Cerramos la aplicacion
				//std::cout<<"[CInputManager::processUserInput] Recibido evento SDL_QUIT!\n";
				emitWindowEvent();
				break;

			default:
				break;
			}
		}
		//std::cout<<"Tipo del evento "<<event.type<<"\n";
	}

	void CInputManager::handleKeyPress(SDL_keysym* keysym){
		event::KeyEvent::EKeyEvent keyEvent = event::KeyEvent::KEY_PRESSED;
		event::KeyEvent::EModifier modifier= event::KeyEvent::MOD_NONE;
		event::KeyEvent::EKey key = getKey(keysym);

		emitKeyEvent(event::KeyEvent( keyEvent, key, modifier));
	}

	void CInputManager::handleKeyUp(SDL_keysym* keysym){
		event::KeyEvent::EKeyEvent keyEvent = event::KeyEvent::KEY_RELEASED;
		event::KeyEvent::EModifier modifier= event::KeyEvent::MOD_NONE;
		event::KeyEvent::EKey key = getKey(keysym);

		emitKeyEvent(event::KeyEvent( keyEvent, key, modifier));

	}

	void CInputManager::handleMousePress(SDL_MouseButtonEvent* mousebutton){
		switch(mousebutton->button){

		case SDL_BUTTON_LEFT:
			emitMousePressedEvent(event::MouseInputEvent( event::MOUSE_BUTTON_LEFT,
														mousebutton->x,
														mousebutton->y));
			break;

		case SDL_BUTTON_RIGHT:
			emitMousePressedEvent(event::MouseInputEvent( event::MOUSE_BUTTON_RIGHT,
																	mousebutton->x,
																	mousebutton->y));
			break;

		case SDL_BUTTON_MIDDLE:
			emitMousePressedEvent(event::MouseInputEvent( event::MOUSE_BUTTON_MIDDLE,
																	mousebutton->x,
																	mousebutton->y));
			break;
		}

	}

	void CInputManager::handleMouseRelease(SDL_MouseButtonEvent* mousebutton){
		switch(mousebutton->button){

		case SDL_BUTTON_LEFT:
			emitMouseReleasedEvent(event::MouseInputEvent( event::MOUSE_BUTTON_LEFT,
														mousebutton->x,
														mousebutton->y));
			break;

		case SDL_BUTTON_RIGHT:
			emitMouseReleasedEvent(event::MouseInputEvent( event::MOUSE_BUTTON_RIGHT,
																	mousebutton->x,
																	mousebutton->y));
			break;

		case SDL_BUTTON_MIDDLE:
			emitMouseReleasedEvent(event::MouseInputEvent(	event::MOUSE_BUTTON_MIDDLE,
															mousebutton->x,
															mousebutton->y));
			break;
		}
	}

	void CInputManager::handleMouseMotion(SDL_MouseMotionEvent* mousemotion){
		switch(mousemotion->state){
		case SDL_BUTTON_LEFT:
			emitMouseMovedEvent(event::MouseInputEvent(	event::MOUSE_BUTTON_LEFT,
														mousemotion->x,
														mousemotion->y));
			break;

		case SDL_BUTTON_RIGHT:
			break;

		case SDL_BUTTON_MIDDLE:
			break;

		default:
			emitMouseMovedEvent(event::MouseInputEvent(	event::MOUSE_BUTTON_LEFT,
														mousemotion->x,
														mousemotion->y));
			break;
		}
	}

	void CInputManager::emitMousePressedEvent(event::MouseInputEvent mouseInputEvent){
		TMILIterator it(_mouseInputListeners.begin()), end(_mouseInputListeners.end());
		for(; it!=end; ++it)
			(*it)->mousePressed(mouseInputEvent);

	}

	void CInputManager::emitMouseReleasedEvent(event::MouseInputEvent mouseInputEvent){
		TMILIterator it(_mouseInputListeners.begin()), end(_mouseInputListeners.end());
		for(; it!=end; ++it)
			(*it)->mouseReleased(mouseInputEvent);
	}

	void CInputManager::emitMouseMovedEvent(event::MouseInputEvent mouseInputEvent){
		TMILIterator it(_mouseInputListeners.begin()), end(_mouseInputListeners.end());
		for(; it!=end; ++it)
			(*it)->mouseMotion(mouseInputEvent);
	}

	void CInputManager::emitKeyEvent(const event::KeyEvent& keyEvent){
		TKLIterator it(_keyListeners.begin()), end(_keyListeners.end());
		for( ;it!=end; ++it){
			switch(keyEvent.getEventType()){
			case event::KeyEvent::KEY_PRESSED:
				(*it)->keyPressed(keyEvent);
				break;
			case event::KeyEvent::KEY_RELEASED:
				(*it)->keyReleased(keyEvent);
				break;
			case event::KeyEvent::KEY_TYPED:
				(*it)->keyTyped(keyEvent);
				break;
			}
		}
	}

	void CInputManager::emitWindowEvent(){
		TWLIterator it(_windowListeners.begin()), end(_windowListeners.end());
		for( ; it!=end; ++it){
			(*it)->closeWindowEvent();
		}
	}

	event::KeyEvent::EKey CInputManager::getKey(SDL_keysym* keysym){
		switch(keysym->sym){

		case SDLK_ESCAPE:
			return event::KeyEvent::MK_ESCAPE;
			break;

		case SDLK_SPACE:
			return event::KeyEvent::MK_SPACE;
			break;
		case SDLK_LEFT:
			return event::KeyEvent::MK_LEFT;
		case SDLK_RIGHT:
			return event::KeyEvent::MK_RIGHT;
		case SDLK_UP:
			return event::KeyEvent::MK_UP;
		case SDLK_DOWN:
			return event::KeyEvent::MK_DOWN;
		case SDLK_a:
			return event::KeyEvent::MK_A;
		case SDLK_b:
			return event::KeyEvent::MK_B;
		case SDLK_c:
			return event::KeyEvent::MK_C;
		case SDLK_d:
			return event::KeyEvent::MK_D;
		case SDLK_e:
			return event::KeyEvent::MK_E;
		case SDLK_f:
			return event::KeyEvent::MK_F;
		case SDLK_g:
			return event::KeyEvent::MK_G;
		case SDLK_h:
			return event::KeyEvent::MK_H;
		case SDLK_i:
			return event::KeyEvent::MK_I;
		case SDLK_j:
			return event::KeyEvent::MK_J;
		case SDLK_k:
			return event::KeyEvent::MK_K;
		case SDLK_l:
			return event::KeyEvent::MK_L;
		case SDLK_m:
			return event::KeyEvent::MK_M;
		case SDLK_n:
			return event::KeyEvent::MK_N;
		case SDLK_o:
			return event::KeyEvent::MK_O;
		case SDLK_p:
			return event::KeyEvent::MK_P;
		case SDLK_q:
			return event::KeyEvent::MK_Q;
		case SDLK_r:
			return event::KeyEvent::MK_R;
		case SDLK_s:
			return event::KeyEvent::MK_S;
		case SDLK_t:
			return event::KeyEvent::MK_T;
		case SDLK_u:
			return event::KeyEvent::MK_U;
		case SDLK_v:
			return event::KeyEvent::MK_V;
		case SDLK_w:
			return event::KeyEvent::MK_W;
		case SDLK_x:
			return event::KeyEvent::MK_X;
		case SDLK_y:
			return event::KeyEvent::MK_Y;
		case SDLK_z:
			return event::KeyEvent::MK_Z;
		case SDLK_KP0:
			return event::KeyEvent::MK_KP0;
		case SDLK_KP1:
			return event::KeyEvent::MK_KP1;
		case SDLK_KP2:
			return event::KeyEvent::MK_KP2;
		case SDLK_KP3:
			return event::KeyEvent::MK_KP3;
		case SDLK_KP4:
			return event::KeyEvent::MK_KP4;
		case SDLK_KP5:
			return event::KeyEvent::MK_KP5;
		case SDLK_KP6:
			return event::KeyEvent::MK_KP6;
		case SDLK_KP7:
			return event::KeyEvent::MK_KP7;
		case SDLK_KP8:
			return event::KeyEvent::MK_KP8;
		case SDLK_KP9:
			return event::KeyEvent::MK_KP9;


		default:
			return event::KeyEvent::MK_COMPOSE;
			break;
		}
	}


}
