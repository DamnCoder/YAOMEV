/*
 * mFTFont.cpp
 *
 *  Created on: 06/08/2010
 *      Author: jorge
 */

#include "gui/text/OglText.h"

#include "utilitys/utils.h"

#include <GL/gl.h>

namespace gui {

	COglText::COglText(): _font(0){
	}

	COglText::~COglText() {
	}

	bool COglText::setFont(const std::string& fontName, const uint fontSize, const EFontType fontType){
		// Aunque la fuente ya exista, de borrar el puntero se encarga CFontsManager
		_font = CFontsCache::instance().getFont(fontName, fontSize, fontType);
		return true;
	}

	void COglText::setPosition(float x, float y){
		_position.x = x;
		_position.y = y;
	}

	void COglText::setText(const std::string& text){
		_text = text;
	}

	void COglText::setSize(int size){
		_font->FaceSize((uint)size);
	}

	math::CBoundingBox COglText::getBoundingBox(){
		FTBBox bbox = _font->BBox(_text.c_str());
		float x1, y1, z1, x2, y2, z2;

		x1 = bbox.Lower().Xf(); y1 = bbox.Lower().Yf(); z1 = bbox.Lower().Zf();
		x2 = bbox.Upper().Xf(); y2 = bbox.Upper().Yf(); z2 = bbox.Upper().Zf();

		return math::CBoundingBox(x1, y1, z1, x2, y2, z2);
	}

}
