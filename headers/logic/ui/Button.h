/**
 * @file Button.h
 *
 * @see logic::CGuiComponent
 */

#ifndef MBUTTON_H_
#define MBUTTON_H_

#include "CUiComponent.h"

#include <string>
#include <list>

namespace logic {

	class CButton:
		public CUiComponent{

	public:

		class ButtonStateListener{
		public:
			virtual ~ButtonStateListener(){}

			virtual void pressedButton() = 0;
			virtual void releasedButton() = 0;
			virtual void highlightedButton() = 0;

			virtual void textChanged(const std::string& text, const std::string& font, int size)  = 0;
		};

		enum EButtonStatus{
			NORMAL,
			PRESSED,
			HIGHLIGHTED,
		};

		CButton(float x, float y, float width, float height);
		CButton(const std::string& text, float x, float y);
		CButton(const std::string& text, float x, float y, float width, float height);

		virtual ~CButton();

		// Modificadores
		void setText(const std::string& text, float x, float y);
		void setFontSize(const int size);
		void setFont(const std::string& fontName);
		void setText(const std::string& text);


		// ACCIONES QUE SOPORTA EL BOTON
		void pressed();
		void released();
		void highlighted();

		// ADICION O ELIMINACION DEL OBSERVADOR
		bool addListener(ButtonStateListener* newListener);
		bool removeListener(ButtonStateListener* oldListener);

		const int			status()	const { return _status; }
		const std::string	text() 		const { return _text; }
		const std::string 	fontName()	const { return _fontName; }
		const int			fontSize()	const { return _fontSize; }

		void mousePressed(const event::MouseEvent& e);
		void mouseEntered(const event::MouseEvent& e);
		void mouseExited(const event::MouseEvent& e);
		void mouseReleased(const event::MouseEvent& e);

	private:

		void emitPressedButton();
		void emitReleasedButton();
		void emitHighlightedButton();

		void emitTextChanged();

		int								_status;
		std::string 					_text;
		std::string						_fontName;	// Fuente aplicada en la etiqueta
		int								_fontSize;	// Tamaño de la fuente

		std::list<ButtonStateListener*>	_blisteners;
		std::list<ButtonStateListener*>::iterator it, end;

	};

}

#endif /* MBUTTON_H_ */
