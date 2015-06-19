/*
 * mFTFont.h
 *
 *  Created on: 06/08/2010
 *      Author: jorge
 */

#ifndef MFTFONT_H_
#define MFTFONT_H_

#include <FTGL/ftgl.h>

#include "math/BoundingBox.h"
#include "FontsManager.h"

namespace gui {

	class COglText{

	public:

		COglText();
		virtual ~COglText();

		bool setFont(const std::string& fontName, const uint fontSize, const EFontType fontType);
		void setPosition(float x, float y);
		void setText(const std::string& text);
		void setSize(int size);

		std::string getText() const{ return _text; }
		FTFont* font() const { return _font; }

		virtual math::CBoundingBox getBoundingBox();

	protected:

		FTFont* 			_font;
		std::string 		_text;
		math::CPositionf 	_position;

	};

}

#endif /* MFTFONT_H_ */
