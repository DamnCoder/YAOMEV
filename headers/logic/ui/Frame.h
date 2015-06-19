/*
 * Frame.h
 *
 *  Created on: 20/07/2010
 *      Author: jorge
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "CUiComponent.h"

#include <list>

#include "event/InputListener.h"
#include "event/MouseEvent.h"

#include "logic/ui/Button.h"
#include "logic/ui/Label.h"
#include "logic/ui/TextLayout.h"

namespace logic {

	/**
	 * Redefiniciones
	 */
	typedef std::list<CUiComponent*> 				TComponentList;
	typedef std::list<CButton*> 					TButtonList;
	typedef std::list<CLabel*> 						TLabelList;
	typedef std::list<CTextBox*> 					TTextBoxList;

	typedef std::list<event::MouseInputListener*> 	TMIListeners;
	typedef std::list<event::MouseListener*> 		TMListeners;

	typedef TComponentList::iterator	TComponentIterator;
	typedef TButtonList::iterator		TButtonIterator;
	typedef TLabelList::iterator		TLabelIterator;
	typedef TTextBoxList::iterator		TTextBoxIterator;

	typedef TMIListeners::iterator		TMILIterator;
	typedef TMListeners::iterator		TMLterator;

	/**
	 * Clase Frame
	 *
	 * Al ser una clase que contiene multiples componentes del interfaz
	 * escucha la entrada de raton, para comunicarle a sus componentes
	 * si algo ha ocurrido
	 */
	class CFrame:
		public CUiComponent,
		public event::MouseInputListener{

	public:

		CFrame();
		CFrame(float x, float y, float width, float height);
		virtual ~CFrame();

		/// Modificadores sobreescritos
		void setAlpha(const float alpha);
		void setVisible(const bool visible);
		void setDepth(const float z);

		TComponentList 	components()	const { return _components; }
		TButtonList 	buttons() 		const { return _buttons; }
		TTextBoxList	textBoxes()		const { return _textBoxes; }
		TLabelList		labels()		const { return _labels; }

		bool add(CUiComponent* component);
		bool add(CButton* button);
		bool add(CTextBox* textBox);
		bool add(CLabel* label);

		void remove(CUiComponent* component);
		void remove(CButton* button);
		void remove(CTextBox* textBox);
		void remove(CLabel* label);

		//------------------------------------------------
		//	Eventos de entrada de raton
		//------------------------------------------------
		void mousePressed(event::MouseInputEvent e);
		void mouseReleased(event::MouseInputEvent e);
		void mouseMotion(event::MouseInputEvent e);

		bool addListener(event::MouseInputListener* e);
		bool addListener(event::MouseListener* e);
		bool removeListener(event::MouseInputListener* e);
		bool removeListener(event::MouseListener* e);

	protected:

		/**
		 * Emite el evento de raton a todos los listeners del frame
		 * @param mouseEvent
		 */
		void emitMouseEvent(event::MouseEvent mouseEvent);

		//--------------------------------------------------------------------
		// Atributos
		//--------------------------------------------------------------------

		/**
		 * Lista de componentes del frame
		 */
		TComponentList	_components;
		TButtonList		_buttons;
		TLabelList		_labels;
		TTextBoxList	_textBoxes;

		TMIListeners	_mouseInputListeners;
		TMListeners		_mouseListeners;

		TComponentIterator 	_itcomp, _endcomp;
		TButtonIterator		_itbut, _endbut;
		TLabelIterator		_itlab, _endlab;
		TTextBoxIterator	_ittb, _endtb;

	};

}

#endif /* FRAME_H_ */
