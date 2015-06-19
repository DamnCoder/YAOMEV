/*
 * LabelNode.h
 *
 *  Created on: 12/11/2010
 *      Author: jorge
 */

#ifndef LABELNODE_H_
#define LABELNODE_H_

#include "UINode.h"

#include "logic/ui/Label.h"

#include "gui/text/OglText.h"
#include "gui/graphicserver/OglSprite.h"

namespace gui {

	class CLabelNode :
				public CUINode,
				public logic::CLabel::LabelListener{

	public:

		CLabelNode() :
				CUINode(),
				_logicLabel(0),
				_gfxText(new COglText)
		{}

		virtual ~CLabelNode();

		bool render();

		bool setLogicEntity(logic::CLabel* label);

		//--------------------------------------------------------------------------------------
		// Metodos sobreescritos del LabelListener
		//--------------------------------------------------------------------------------------

		void textChanged(const logic::CLabel* label, const string& text);
		void fontSizeChanged(int size);
		void fontChanged(const std::string& font);

	private:

		logic::CLabel*	_logicLabel;
		std::string		_text;
		std::string		_fontName;
		int				_fontSize;
		COglText*		_gfxText;
		COglSprite*		_gfxSprite;

	};

}

#endif /* LABELNODE_H_ */
