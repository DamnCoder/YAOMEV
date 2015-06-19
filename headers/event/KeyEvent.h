/*
 * KeyEvent.h
 *
 *  Created on: 14/02/2011
 *      Author: jorge
 */

#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include "Event.h"

namespace event
{

	class KeyEvent : public Event {
	public:
		enum EKeyEvent {
			KEY_PRESSED,
			KEY_RELEASED,
			KEY_TYPED,
		};

		enum EKey{
			MK_ESCAPE		= 0,
			MK_SPACE		= 96,
			MK_A			= 97,
			MK_B			= 98,
			MK_C			= 99,
			MK_D			= 100,
			MK_E			= 101,
			MK_F			= 102,
			MK_G			= 103,
			MK_H			= 104,
			MK_I			= 105,
			MK_J			= 106,
			MK_K			= 107,
			MK_L			= 108,
			MK_M			= 109,
			MK_N			= 110,
			MK_O			= 111,
			MK_P			= 112,
			MK_Q			= 113,
			MK_R			= 114,
			MK_S			= 115,
			MK_T			= 116,
			MK_U			= 117,
			MK_V			= 118,
			MK_W			= 119,
			MK_X			= 120,
			MK_Y			= 121,
			MK_Z			= 122,
			MK_DELETE		= 127,

			// numeric pad
			MK_KP0			= 256,
			MK_KP1			= 257,
			MK_KP2			= 258,
			MK_KP3			= 259,
			MK_KP4			= 260,
			MK_KP5			= 261,
			MK_KP6			= 262,
			MK_KP7			= 263,
			MK_KP8			= 264,
			MK_KP9			= 265,
			MK_KP_PERIOD	= 266,
			MK_KP_DIVIDE	= 267,
			MK_KP_MULTIPLY	= 268,
			MK_KP_MINUS		= 269,
			MK_KP_PLUS		= 270,
			MK_KP_ENTER		= 271,
			MK_KP_EQUALS	= 272,


			MK_UP			= 273,
			MK_DOWN			= 274,
			MK_RIGHT		= 275,
			MK_LEFT			= 276,
			MK_INSERT		= 277,
			MK_HOME			= 278,
			MK_END			= 279,
			MK_PAGEUP		= 280,
			MK_PAGEDOWN		= 281,

			MK_F1			= 282,
			MK_F2			= 283,
			MK_F3			= 284,
			MK_F4			= 285,
			MK_F5			= 286,
			MK_F6			= 287,
			MK_F7			= 288,
			MK_F8			= 289,
			MK_F9			= 290,
			MK_F10			= 291,
			MK_F11			= 292,
			MK_F12			= 293,
			MK_F13			= 294,
			MK_F14			= 295,
			MK_F15			= 296,

			MK_NUMLOCK		= 300,
			//MK_CAPSLOCK	= 301,
			MK_SCROLLOCK	= 302,
			MK_RSHIFT		= 303,
			MK_LSHIFT		= 304,
			MK_RCTRL		= 305,
			MK_LCTRL		= 306,
			MK_RALT			= 307,
			MK_LALT			= 308,
			MK_RMETA		= 309,
			MK_LMETA		= 310,
			MK_LSUPER		= 311,
			MK_RSUPER		= 312,
			MK_MODE			= 313,
			MK_COMPOSE		= 314,

			MK_HELP			= 315,
			MK_PRINT		= 316,
			MK_SYSREQ		= 317,
			MK_BREAK		= 318,
			MK_MENU			= 319,
			MK_EURO			= 321
		};

		enum EModifier
		{
			MOD_NONE  = 	0x0000,
			MOD_LSHIFT= 	0x0001,
			MOD_RSHIFT= 	0x0002,
			MOD_LCTRL = 	0x0040,
			MOD_RCTRL = 	0x0080,
			MOD_LALT  = 	0x0100,
			MOD_RALT  = 	0x0200,
			MOD_LMETA = 	0x0400,
			MOD_RMETA =		0x0800,
			MOD_NUM   = 	0x1000,
			MOD_CAPS  = 	0x2000,
			MOD_MODE  = 	0x4000,
			MOD_RESERVED = 	0x8000
		};


		/**
		 * Crea un nuevo KeyEvent
		 *
		 * @param
		 *	id Identificador describiendo el tipo de evento
		 * @param
		 *	key Codigo unicode correspondiente a la tecla pulsada o soltada
		 * @param
		 *	modifiers Modificador usado durante la generacion del evento
		 *	con teclas como SHIFT, CTRL o ALT
		 */
		KeyEvent(EKeyEvent id, EKey key, EModifier modifier):
			Event(),
			_key(key),
			_modifiers(modifier),
			_eventType(id)
		{}

		EKeyEvent getEventType() const {
			return _eventType;
		}

		/**
		 * Return the unicode keycode.
		 */
		EKey getKey() const{
			return _key;
		}

		/**
		 * Return the modifier for this KeyEvent.
		 */
		EModifier getModifier() const{
			return _modifiers;
		}

	private:

		EKey 		_key;
		EModifier 	_modifiers;
		EKeyEvent 	_eventType;
	};
}

#endif /* KEYEVENT_H_ */
