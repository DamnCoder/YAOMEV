/*
 * TextLayoutNode.h
 *
 *  Created on: 12/11/2010
 *      Author: jorge
 */

#ifndef TEXTLAYOUTNODE_H_
#define TEXTLAYOUTNODE_H_

#include "UINode.h"

#include "logic/ui/TextLayout.h"

#include "gui/text/OglTextLayout.h"

namespace gui {

	class COglSprite;

	class CTextLayoutNode :
			public CUINode,
			public logic::CTextBox::TextBoxListener{

	public:

		CTextLayoutNode():
				CUINode(),
				_background(false),
				_sprite(0),
				_textLayout(new COglTextLayout),
				_logicTL(0){}

		virtual ~CTextLayoutNode();

		bool render();

		bool setLogicEntity(logic::CTextBox* logicTL);

		//--------------------------------------------------------------------------------------
		// Metodos sobreescritos del UiPropertyListener
		//--------------------------------------------------------------------------------------
		virtual void positionChanged(const math::CVector3f& newPos);

		//--------------------------------------------------------------------------------------
		// Metodos sobreescritos del TextBoxListener
		//--------------------------------------------------------------------------------------

		void textChanged(const std::string& text);
		void fontAtribChanged(const std::string& font, const int fontSize, const float lineSize);
		void alignmentChanged(const int alignType);

	private:



		bool 				_background;

		COglSprite*			_sprite;
		COglTextLayout*		_textLayout;

		logic::CTextBox*	_logicTL;


	};

}

#endif /* TEXTLAYOUTNODE_H_ */
