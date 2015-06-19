/*
 * CButtonNode.h
 *
 *  Created on: 10/08/2010
 *      Author: jorge
 */

#ifndef CBUTTONNODE_H_
#define CBUTTONNODE_H_

#include "UINode.h"

#include "logic/ui/Button.h"

#include "gui/graphicserver/OglButton.h"

namespace gui {

	using namespace logic;

	class CButtonNode :
		public CUINode,
		public logic::CButton::ButtonStateListener{

	public:

		CButtonNode();

		virtual ~CButtonNode();

		bool render();

		void load(const std::string& id);

		bool setLogicEntity(logic::CButton* logicButton);

		//--------------------------------------------------------------------------------------
		// Metodos sobreescritos del ButtonListener
		//--------------------------------------------------------------------------------------
		virtual void positionChanged(const math::CVector3f& newPos);

		//--------------------------------------------------------------------------------------
		// Metodos sobreescritos del ButtonListener
		//--------------------------------------------------------------------------------------
		void pressedButton();
		void releasedButton();
		void highlightedButton();

		void textChanged(const std::string& text, const std::string& font, int size);

	protected:
		COglButton* 				_button;
		CButton*					_logicButton;
		std::string					_text;
		std::string					_fontName;
		int							_fontSize;
		math::CVector3f 			_fontPosition;
		COglButton::EButtonStatus 	_status;

	};

}

#endif /* CBUTTONNODE_H_ */
